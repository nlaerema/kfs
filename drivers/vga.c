#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>

#include "vga.h"
#include "attributes.h"
#include "lib/format.h"


#define VGA_MEMORY ((volatile vga_cell_t *)0xB8000)

#define VGA_COLS 80
#define VGA_ROWS 25

#define EMPTY_CELL ((vga_cell_t) { \
    .character = ' ', \
    .attribute = { \
        .foreground = VGA_WHITE, \
        .background = VGA_BLACK, \
        .blink      = false, \
    } \
})


typedef enum {
    ESCAPE_STATE_NONE,
    ESCAPE_STATE_ESCAPED,
    ESCAPE_STATE_TYPE,
} escape_state_t;

typedef enum {
    ESCAPE_TYPE_UNKNOWN,
    ESCAPE_TYPE_FOREGROUND,
    ESCAPE_TYPE_BACKGROUND,
    ESCAPE_TYPE_BLINK,
    ESCAPE_TYPE_END,
} escape_type_t;

typedef struct {
    escape_state_t state;
    escape_type_t  type;
} escape_ctx_t;

typedef struct PACKED {
    vga_color_t foreground : 4;
    vga_color_t background : 3;
    bool        blink      : 1;
} vga_cell_attribute_t;

typedef struct PACKED {
    char                 character;
    vga_cell_attribute_t attribute;
} vga_cell_t;

static_assert(sizeof(vga_cell_t) == 2, "vga_cell_t must be 2 bytes");


static struct {
    int                  col;
    int                  row;

    vga_cell_attribute_t attribute;

    escape_ctx_t escape;
} s_vga_ctx = {
    .col       = 0,
    .row       = 0,
    .attribute = {
        .foreground = VGA_WHITE,
        .background = VGA_BLACK,
        .blink      = false,
    },
    .escape = {
        .state = ESCAPE_STATE_NONE,
        .type  = ESCAPE_TYPE_UNKNOWN,
    },
};


NO_CALLER_SAVED_REGISTERS
static vga_cell_t _get_cell(int col, int row)
{
    return VGA_MEMORY[row * VGA_COLS + col];
}

NO_CALLER_SAVED_REGISTERS
static void _set_cell(int col, int row, vga_cell_t value)
{
    VGA_MEMORY[row * VGA_COLS + col] = value;
}

NO_CALLER_SAVED_REGISTERS
static void _new_line(void)
{
    s_vga_ctx.col = 0;
    s_vga_ctx.row++;

    if (s_vga_ctx.row >= VGA_ROWS) {
        vga_scroll();
    }
}

NO_CALLER_SAVED_REGISTERS
static vga_cell_t _make_cell(char c)
{
    return (vga_cell_t) {
        .character = c,
        .attribute = s_vga_ctx.attribute,
    };
}

NO_CALLER_SAVED_REGISTERS
static uint8_t _hex_digit_to_value(char c)
{
    if (c >= '0' && c <= '9') {
        return c - '0';
    } else if (c >= 'a' && c <= 'f') {
        return 10 + (c - 'a');
    } else if (c >= 'A' && c <= 'F') {
        return 10 + (c - 'A');
    } else {
        return 0;
    }
}

NO_CALLER_SAVED_REGISTERS
static escape_type_t _escape_type_from_char(char c)
{
    switch (c) {
        case 'f':
        case 'F':
            return ESCAPE_TYPE_FOREGROUND;
        case 'b':
        case 'B':
            return ESCAPE_TYPE_BACKGROUND;
        case 'k':
        case 'K':
            return ESCAPE_TYPE_BLINK;
        case ';':
            return ESCAPE_TYPE_END;
        default:
            return ESCAPE_TYPE_UNKNOWN;
    }
}

NO_CALLER_SAVED_REGISTERS
static void _escape(char c)
{
    switch (s_vga_ctx.escape.state) {
        case ESCAPE_STATE_NONE:
            s_vga_ctx.escape.state = ESCAPE_STATE_ESCAPED;
            break;

        case ESCAPE_STATE_ESCAPED:
            s_vga_ctx.escape.type = _escape_type_from_char(c);
            if (s_vga_ctx.escape.type == ESCAPE_TYPE_END) {
                s_vga_ctx.escape.state = ESCAPE_STATE_NONE;
            } else if (s_vga_ctx.escape.type != ESCAPE_TYPE_UNKNOWN) {
                s_vga_ctx.escape.state = ESCAPE_STATE_TYPE;
            }
            break;

        case ESCAPE_STATE_TYPE:
            switch (s_vga_ctx.escape.type) {
                case ESCAPE_TYPE_FOREGROUND:
                    s_vga_ctx.attribute.foreground = _hex_digit_to_value(c);
                    break;

                case ESCAPE_TYPE_BACKGROUND:
                    s_vga_ctx.attribute.background = _hex_digit_to_value(c);
                    break;

                case ESCAPE_TYPE_BLINK:
                    s_vga_ctx.attribute.blink = (c == '1');
                    break;

                default:
                    break;
            }
            s_vga_ctx.escape.state = ESCAPE_STATE_ESCAPED;
            break;
    }
}

static void _printf_put(UNUSED void *ctx, char c)
{
    vga_put(c);
}

NO_CALLER_SAVED_REGISTERS
void vga_scroll(void)
{
    if (s_vga_ctx.row <= 0) {
        return;
    }

    for (int row = 1; row < VGA_ROWS; row++) {
        for (int col = 0; col < VGA_COLS; col++) {
            _set_cell(col, row - 1, _get_cell(col, row));
        }
    }

    for (int col = 0; col < VGA_COLS; col++) {
        _set_cell(col, VGA_ROWS - 1, EMPTY_CELL); 
    }

    s_vga_ctx.row--;
}

NO_CALLER_SAVED_REGISTERS
size_t vga_put(char c)
{
    if (s_vga_ctx.escape.state != ESCAPE_STATE_NONE || c == '\x1b') {
        _escape(c);
        return 0;
    }

    switch (c) {
        case '\n':
            _new_line();
            return 0;
        case '\r':
            s_vga_ctx.col = 0;
            return 0;
    }

    _set_cell(s_vga_ctx.col, s_vga_ctx.row, _make_cell(c));

    s_vga_ctx.col++;
    if (s_vga_ctx.col >= VGA_COLS) {
        _new_line();
    }

    return 1;
}

NO_CALLER_SAVED_REGISTERS
size_t vga_write(const void* data, size_t size)
{
    const char* bytes = (const char*)data;

    for (size_t i = 0; i < size; i++) {
        vga_put(bytes[i]);
    }

    return size;
}

size_t vga_printf(const char* format, ...)
{
    va_list args;

    va_start(args, format);
    size_t total = vfnprintf(_printf_put, NULL, format, args);
    va_end(args);

    return total;
}