#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

#include "format.h"


#define LOWERCASE_BASE_CHARSET "0123456789abcdefghijklmnopqrstuvwxyz"
#define UPPERCASE_BASE_CHARSET "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"


typedef struct {
    char*       dest;
    size_t      length;
    size_t      written;
} vsnprintf_ctx_t;


static size_t _put(format_put_t put, void* ctx, char c)
{
    put(ctx, c);
    return 1;
}

static void _vsnprintf_put(void* void_ctx, char c)
{
    vsnprintf_ctx_t* ctx = (vsnprintf_ctx_t*)void_ctx;

    if (ctx->written < ctx->length) {
        ctx->dest[ctx->written] = c;
        ctx->written++;
    }
}

static unsigned int _divisor(unsigned int value, unsigned int base)
{
    unsigned int divisor = 1;

    while (value >= base) {
        value /= base;
        divisor *= base;
    }

    return divisor;
}

static size_t _unsigned(format_put_t put, void* ctx, unsigned int value, unsigned int base, const char* charset)
{
    size_t total = 0;

    unsigned int divisor = _divisor(value, base);

    while (divisor > 0) {
        total += _put(put, ctx, charset[value / divisor]);
        value %= divisor;
        divisor /= base;
    }

    return total;
}

static size_t _string(format_put_t put, void* ctx, const char* str)
{
    size_t total = 0;

    while (str[total] != '\0') {
        total += _put(put, ctx, str[total]);
    }

    return total;
}

static size_t _specifier_unsigned(format_put_t put, void* ctx, unsigned int value, unsigned int base, const char* charset)
{
    return _unsigned(put, ctx, value, base, charset);
}

static size_t _specifier_signed(format_put_t put, void* ctx, int value, unsigned int base, const char* charset)
{
    if (value < 0) {
        return _put(put, ctx, '-') + _unsigned(put, ctx, 0 - (unsigned int)value, base, charset);
    } else {
        return _unsigned(put, ctx, (unsigned int)value, base, charset);
    }
}

static size_t _specifier_char(format_put_t put, void* ctx, char c)
{
    return _put(put, ctx, c);
}

static size_t _specifier_string(format_put_t put, void* ctx, const char* str)
{
    if (str == NULL) {
        return _string(put, ctx, "(null)");
    }
    return _string(put, ctx, str);
}


static size_t _specifier_pointer(format_put_t put, void* ctx, void* ptr)
{
    if (ptr == NULL) {
        return _string(put, ctx, "(nil)");
    }
    return _put(put, ctx, '0') + _put(put, ctx, 'x') + _unsigned(put, ctx, (uintptr_t)ptr, 16, LOWERCASE_BASE_CHARSET);
}

static size_t _specifier_percent(format_put_t put, void* ctx)
{
    return _put(put, ctx, '%');
}

static size_t _specifier_unknown(format_put_t put, void* ctx, char specifier)
{
    return _put(put, ctx, '%') + _put(put, ctx, specifier);
}

static size_t _specifier(format_put_t put, void* ctx, char specifier, va_list* args)
{
    switch (specifier) {
        case 'd':
        case 'i':
            return _specifier_signed(put, ctx, va_arg(*args, int), 10, LOWERCASE_BASE_CHARSET);
        case 'u':
            return _specifier_unsigned(put, ctx, va_arg(*args, unsigned int), 10, LOWERCASE_BASE_CHARSET);
        case 'o':
            return _specifier_unsigned(put, ctx, va_arg(*args, unsigned int), 8, LOWERCASE_BASE_CHARSET);
        case 'x':
            return _specifier_unsigned(put, ctx, va_arg(*args, unsigned int), 16, LOWERCASE_BASE_CHARSET);
        case 'X':
            return _specifier_unsigned(put, ctx, va_arg(*args, unsigned int), 16, UPPERCASE_BASE_CHARSET);
        case 'c':
            return _specifier_char(put, ctx, va_arg(*args, int));
        case 's':
            return _specifier_string(put, ctx, va_arg(*args, const char*));
        case 'p':
            return _specifier_pointer(put, ctx, va_arg(*args, void*));
        case '%':
            return _specifier_percent(put, ctx);
        default:
            return _specifier_unknown(put, ctx, specifier);
    }
}



size_t vfnprintf(format_put_t put, void* ctx, const char* format, va_list args)
{
    size_t total = 0;

    while (*format != '\0') {
        if (*format == '%') {
            format++;
            
            if (*format == '\0') {
                break;
            }

            total += _specifier(put, ctx, *format, &args);
        } else {
            total += _put(put, ctx, *format);
        }
        format++;
    }

    return total;
}

size_t vsnprintf(char* dest, size_t size, const char* format, va_list args)
{
    vsnprintf_ctx_t ctx = {
        .dest   = dest,
        .length = size ? size - 1 : 0,
        .written = 0
    };

    size_t total = vfnprintf(_vsnprintf_put, &ctx, format, args);

    if (ctx.written < size) {
        ctx.dest[ctx.written] = '\0';
    }

    return total;
}

size_t snprintf(char* dest, size_t size, const char* format, ...)
{
    va_list args;

    va_start(args, format);
    size_t total = vsnprintf(dest, size, format, args);
    va_end(args);

    return total;
}

size_t fnprintf(format_put_t put, void* ctx, const char* format, ...)
{
    va_list args;

    va_start(args, format);
    size_t total = vfnprintf(put, ctx, format, args);
    va_end(args);

    return total;
}