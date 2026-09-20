#pragma once


#include "attributes.h"

#include <stdint.h>


#define MULTIBOOT_SEARCH       32768
#define MULTIBOOT_HEADER_ALIGN 8
#define MULTIBOOT_MOD_ALIGN    0x00001000
#define MULTIBOOT_INFO_ALIGN   0x00000008
#define MULTIBOOT_TAG_ALIGN    8


#define MULTIBOOT_HEADER(_architecture, _header_length) \
    ((multiboot_header_t) { \
        .magic         = MULTIBOOT2_HEADER_MAGIC, \
        .architecture  = (multiboot_architecture_t)(_architecture), \
        .header_length = (uint32_t)(_header_length), \
        .checksum      = (uint32_t)(-(MULTIBOOT2_HEADER_MAGIC + (_architecture) + (_header_length))), \
    })

#define MULTIBOOT_HEADER_TAG_END() \
    ((multiboot_header_tag_t) { \
        .type  = MULTIBOOT_HEADER_TAG_END, \
        .flags = 0, \
        .size  = sizeof(multiboot_header_tag_t), \
    })

#define MULTIBOOT_HEADER_TAG_INFORMATION_REQUEST(_tag_t, _flags, ...) \
    ((_tag_t) { \
        .type     = MULTIBOOT_HEADER_TAG_INFORMATION_REQUEST, \
        .flags    = (multiboot_header_tag_flag_t)(_flags), \
        .size     = (uint32_t)(sizeof(multiboot_header_tag_t) + sizeof((multiboot_tag_type_t[]){__VA_ARGS__})), \
        .requests = {__VA_ARGS__}, \
    })

#define MULTIBOOT_HEADER_TAG_ADDRESS(_flags, _header_addr, _load_addr, _load_end_addr, _bss_end_addr) \
    ((multiboot_header_tag_address_t) { \
        .type          = MULTIBOOT_HEADER_TAG_ADDRESS, \
        .flags         = (multiboot_header_tag_flag_t)(_flags), \
        .size          = sizeof(multiboot_header_tag_address_t), \
        .header_addr   = (uint32_t)(_header_addr), \
        .load_addr     = (uint32_t)(_load_addr), \
        .load_end_addr = (uint32_t)(_load_end_addr), \
        .bss_end_addr  = (uint32_t)(_bss_end_addr), \
    })

#define MULTIBOOT_HEADER_TAG_ENTRY_ADDRESS(_flags, _entry_addr) \
    ((multiboot_header_tag_entry_address_t) { \
        .type       = MULTIBOOT_HEADER_TAG_ENTRY_ADDRESS, \
        .flags      = (multiboot_header_tag_flag_t)(_flags), \
        .size       = sizeof(multiboot_header_tag_entry_address_t), \
        .entry_addr = (uint32_t)(_entry_addr), \
    })

#define MULTIBOOT_HEADER_TAG_ENTRY_ADDRESS_EFI32(_flags, _entry_addr) \
    ((multiboot_header_tag_entry_address_t) { \
        .type       = MULTIBOOT_HEADER_TAG_ENTRY_ADDRESS_EFI32, \
        .flags      = (multiboot_header_tag_flag_t)(_flags), \
        .size       = sizeof(multiboot_header_tag_entry_address_t), \
        .entry_addr = (uint32_t)(_entry_addr), \
    })

#define MULTIBOOT_HEADER_TAG_ENTRY_ADDRESS_EFI64(_flags, _entry_addr) \
    ((multiboot_header_tag_entry_address_t) { \
        .type       = MULTIBOOT_HEADER_TAG_ENTRY_ADDRESS_EFI64, \
        .flags      = (multiboot_header_tag_flag_t)(_flags), \
        .size       = sizeof(multiboot_header_tag_entry_address_t), \
        .entry_addr = (uint32_t)(_entry_addr), \
    })

#define MULTIBOOT_HEADER_TAG_CONSOLE_FLAGS(_flags, _console_flags) \
    ((multiboot_header_tag_console_flags_t) { \
        .type          = MULTIBOOT_HEADER_TAG_CONSOLE_FLAGS, \
        .flags         = (multiboot_header_tag_flag_t)(_flags), \
        .size          = sizeof(multiboot_header_tag_console_flags_t), \
        .console_flags = (multiboot_console_flag_t)(_console_flags), \
    })

#define MULTIBOOT_HEADER_TAG_FRAMEBUFFER(_flags, _width, _height, _depth) \
    ((multiboot_header_tag_framebuffer_t) { \
        .type   = MULTIBOOT_HEADER_TAG_FRAMEBUFFER, \
        .flags  = (multiboot_header_tag_flag_t)(_flags), \
        .size   = sizeof(multiboot_header_tag_framebuffer_t), \
        .width  = (uint32_t)(_width), \
        .height = (uint32_t)(_height), \
        .depth  = (uint32_t)(_depth), \
    })

#define MULTIBOOT_HEADER_TAG_MODULE_ALIGN(_flags) \
    ((multiboot_header_tag_module_align_t) { \
        .type  = MULTIBOOT_HEADER_TAG_MODULE_ALIGN, \
        .flags = (multiboot_header_tag_flag_t)(_flags), \
        .size  = sizeof(multiboot_header_tag_module_align_t), \
    })

#define MULTIBOOT_HEADER_TAG_EFI_BS(_flags) \
    ((multiboot_header_tag_efi_bs_t) { \
        .type  = MULTIBOOT_HEADER_TAG_EFI_BS, \
        .flags = (multiboot_header_tag_flag_t)(_flags), \
        .size  = sizeof(multiboot_header_tag_efi_bs_t), \
    })

#define MULTIBOOT_HEADER_TAG_RELOCATABLE(_flags, _min_addr, _max_addr, _align, _preference) \
    ((multiboot_header_tag_relocatable_t) { \
        .type       = MULTIBOOT_HEADER_TAG_RELOCATABLE, \
        .flags      = (multiboot_header_tag_flag_t)(_flags), \
        .size       = sizeof(multiboot_header_tag_relocatable_t), \
        .min_addr   = (uint32_t)(_min_addr), \
        .max_addr   = (uint32_t)(_max_addr), \
        .align      = (uint32_t)(_align), \
        .preference = (multiboot_load_preference_t)(_preference), \
    })


typedef enum : uint32_t {
    MULTIBOOT2_HEADER_MAGIC = 0xe85250d6,
} multiboot_header_magic_t;

typedef enum : uint32_t {
    MULTIBOOT2_BOOTLOADER_MAGIC = 0x36d76289,
} multiboot_bootloader_magic_t;

typedef enum : uint32_t {
    MULTIBOOT_TAG_TYPE_END              = 0,
    MULTIBOOT_TAG_TYPE_CMDLINE          = 1,
    MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME = 2,
    MULTIBOOT_TAG_TYPE_MODULE           = 3,
    MULTIBOOT_TAG_TYPE_BASIC_MEMINFO    = 4,
    MULTIBOOT_TAG_TYPE_BOOTDEV          = 5,
    MULTIBOOT_TAG_TYPE_MMAP             = 6,
    MULTIBOOT_TAG_TYPE_VBE              = 7,
    MULTIBOOT_TAG_TYPE_FRAMEBUFFER      = 8,
    MULTIBOOT_TAG_TYPE_ELF_SECTIONS     = 9,
    MULTIBOOT_TAG_TYPE_APM              = 10,
    MULTIBOOT_TAG_TYPE_EFI32            = 11,
    MULTIBOOT_TAG_TYPE_EFI64            = 12,
    MULTIBOOT_TAG_TYPE_SMBIOS           = 13,
    MULTIBOOT_TAG_TYPE_ACPI_OLD         = 14,
    MULTIBOOT_TAG_TYPE_ACPI_NEW         = 15,
    MULTIBOOT_TAG_TYPE_NETWORK          = 16,
    MULTIBOOT_TAG_TYPE_EFI_MMAP         = 17,
    MULTIBOOT_TAG_TYPE_EFI_BS           = 18,
    MULTIBOOT_TAG_TYPE_EFI32_IH         = 19,
    MULTIBOOT_TAG_TYPE_EFI64_IH         = 20,
    MULTIBOOT_TAG_TYPE_LOAD_BASE_ADDR   = 21,
} multiboot_tag_type_t;

typedef enum : uint16_t {
    MULTIBOOT_HEADER_TAG_END                 = 0,
    MULTIBOOT_HEADER_TAG_INFORMATION_REQUEST = 1,
    MULTIBOOT_HEADER_TAG_ADDRESS             = 2,
    MULTIBOOT_HEADER_TAG_ENTRY_ADDRESS       = 3,
    MULTIBOOT_HEADER_TAG_CONSOLE_FLAGS       = 4,
    MULTIBOOT_HEADER_TAG_FRAMEBUFFER         = 5,
    MULTIBOOT_HEADER_TAG_MODULE_ALIGN        = 6,
    MULTIBOOT_HEADER_TAG_EFI_BS              = 7,
    MULTIBOOT_HEADER_TAG_ENTRY_ADDRESS_EFI32 = 8,
    MULTIBOOT_HEADER_TAG_ENTRY_ADDRESS_EFI64 = 9,
    MULTIBOOT_HEADER_TAG_RELOCATABLE         = 10,
} multiboot_header_tag_type_t;

typedef enum : uint16_t {
    MULTIBOOT_HEADER_TAG_REQUIRED = 0,
    MULTIBOOT_HEADER_TAG_OPTIONAL = 1,
} multiboot_header_tag_flag_t;

typedef enum : uint32_t {
    MULTIBOOT_ARCHITECTURE_I386   = 0,
    MULTIBOOT_ARCHITECTURE_MIPS32 = 4,
} multiboot_architecture_t;

typedef enum : uint32_t {
    MULTIBOOT_LOAD_PREFERENCE_NONE = 0,
    MULTIBOOT_LOAD_PREFERENCE_LOW  = 1,
    MULTIBOOT_LOAD_PREFERENCE_HIGH = 2,
} multiboot_load_preference_t;

typedef enum : uint32_t {
    MULTIBOOT_CONSOLE_FLAGS_CONSOLE_REQUIRED   = 1,
    MULTIBOOT_CONSOLE_FLAGS_EGA_TEXT_SUPPORTED = 2,
} multiboot_console_flag_t;

typedef enum : uint32_t {
    MULTIBOOT_MEMORY_AVAILABLE        = 1,
    MULTIBOOT_MEMORY_RESERVED         = 2,
    MULTIBOOT_MEMORY_ACPI_RECLAIMABLE = 3,
    MULTIBOOT_MEMORY_NVS              = 4,
    MULTIBOOT_MEMORY_BADRAM           = 5,
} multiboot_memory_type_t;

typedef enum : uint8_t {
    MULTIBOOT_FRAMEBUFFER_TYPE_INDEXED  = 0,
    MULTIBOOT_FRAMEBUFFER_TYPE_RGB      = 1,
    MULTIBOOT_FRAMEBUFFER_TYPE_EGA_TEXT = 2,
} multiboot_framebuffer_type_t;


// Header

typedef struct PACKED {
    multiboot_header_magic_t magic;
    multiboot_architecture_t architecture;
    uint32_t                 header_length;
    uint32_t                 checksum;
} multiboot_header_t;

typedef struct PACKED {
    multiboot_header_tag_type_t type;
    multiboot_header_tag_flag_t flags;
    uint32_t                    size;
} multiboot_header_tag_t;

typedef struct PACKED {
    multiboot_header_tag_type_t type;
    multiboot_header_tag_flag_t flags;
    uint32_t                    size;
    multiboot_tag_type_t        requests[];
} multiboot_header_tag_information_request_t;

typedef struct PACKED {
    multiboot_header_tag_type_t type;
    multiboot_header_tag_flag_t flags;
    uint32_t                    size;
    uint32_t                    header_addr;
    uint32_t                    load_addr;
    uint32_t                    load_end_addr;
    uint32_t                    bss_end_addr;
} multiboot_header_tag_address_t;

typedef struct PACKED {
    multiboot_header_tag_type_t type;
    multiboot_header_tag_flag_t flags;
    uint32_t                    size;
    uint32_t                    entry_addr;
} multiboot_header_tag_entry_address_t;

typedef struct PACKED {
    multiboot_header_tag_type_t type;
    multiboot_header_tag_flag_t flags;
    uint32_t                    size;
    multiboot_console_flag_t      console_flags;
} multiboot_header_tag_console_flags_t;

typedef struct PACKED {
    multiboot_header_tag_type_t type;
    multiboot_header_tag_flag_t flags;
    uint32_t                    size;
    uint32_t                    width;
    uint32_t                    height;
    uint32_t                    depth;
} multiboot_header_tag_framebuffer_t;

typedef struct PACKED {
    multiboot_header_tag_type_t type;
    multiboot_header_tag_flag_t flags;
    uint32_t                    size;
} multiboot_header_tag_module_align_t;

typedef struct PACKED {
    multiboot_header_tag_type_t type;
    multiboot_header_tag_flag_t flags;
    uint32_t                    size;
} multiboot_header_tag_efi_bs_t;

typedef struct PACKED {
    multiboot_header_tag_type_t type;
    multiboot_header_tag_flag_t flags;
    uint32_t                    size;
    uint32_t                    min_addr;
    uint32_t                    max_addr;
    uint32_t                    align;
    multiboot_load_preference_t preference;
} multiboot_header_tag_relocatable_t;


// Boot info

typedef struct PACKED {
    uint32_t total_size;
    uint32_t reserved;
    uint8_t  tags[];
} multiboot_info_t;

typedef struct PACKED {
    multiboot_tag_type_t type;
    uint32_t             size;
    uint8_t              data[];
} multiboot_tag_t;

typedef struct PACKED {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} multiboot_color_t;

typedef struct PACKED {
    uint64_t                addr;
    uint64_t                len;
    multiboot_memory_type_t type;
    uint32_t                zero;
} multiboot_mmap_entry_t;

typedef struct PACKED {
    uint64_t                addr;
    uint64_t                len;
    multiboot_memory_type_t type;
    uint32_t                zero;
} multiboot_memory_map_t;

typedef struct PACKED {
    multiboot_tag_type_t type;
    uint32_t             size;
    char                 string[];
} multiboot_tag_string_t;

typedef struct PACKED {
    multiboot_tag_type_t type;
    uint32_t             size;
    uint32_t             mod_start;
    uint32_t             mod_end;
    char                 cmdline[];
} multiboot_tag_module_t;

typedef struct PACKED {
    multiboot_tag_type_t type;
    uint32_t             size;
    uint32_t             mem_lower;
    uint32_t             mem_upper;
} multiboot_tag_basic_meminfo_t;

typedef struct PACKED {
    multiboot_tag_type_t type;
    uint32_t             size;
    uint32_t             biosdev;
    uint32_t             slice;
    uint32_t             part;
} multiboot_tag_bootdev_t;

typedef struct PACKED {
    multiboot_tag_type_t   type;
    uint32_t               size;
    uint32_t               entry_size;
    uint32_t               entry_version;
    multiboot_mmap_entry_t entries[];
} multiboot_tag_mmap_t;

typedef struct PACKED {
    uint8_t external_specification[512];
} multiboot_vbe_info_block_t;

typedef struct PACKED {
    uint8_t external_specification[256];
} multiboot_vbe_mode_info_block_t;

typedef struct PACKED {
    multiboot_tag_type_t            type;
    uint32_t                        size;

    uint16_t                        vbe_mode;
    uint16_t                        vbe_interface_seg;
    uint16_t                        vbe_interface_off;
    uint16_t                        vbe_interface_len;

    multiboot_vbe_info_block_t      vbe_control_info;
    multiboot_vbe_mode_info_block_t vbe_mode_info;
} multiboot_tag_vbe_t;

typedef struct PACKED {
    multiboot_tag_type_t         type;
    uint32_t                     size;

    uint64_t                     framebuffer_addr;
    uint32_t                     framebuffer_pitch;
    uint32_t                     framebuffer_width;
    uint32_t                     framebuffer_height;
    uint8_t                      framebuffer_bpp;
    multiboot_framebuffer_type_t framebuffer_type;
    uint16_t                     reserved;
} multiboot_tag_framebuffer_common_t;

typedef struct PACKED {
    uint16_t          num_colors;
    multiboot_color_t palette[];
} multiboot_framebuffer_palette_t;

typedef struct PACKED {
    uint8_t red_field_position;
    uint8_t red_mask_size;
    uint8_t green_field_position;
    uint8_t green_mask_size;
    uint8_t blue_field_position;
    uint8_t blue_mask_size;
} multiboot_framebuffer_rgb_t;

typedef union PACKED {
    multiboot_framebuffer_palette_t palette;
    multiboot_framebuffer_rgb_t     rgb;
} multiboot_framebuffer_data_t;

typedef struct PACKED {
    multiboot_tag_framebuffer_common_t common;
    multiboot_framebuffer_data_t       data;
} multiboot_tag_framebuffer_t;

typedef struct PACKED {
    multiboot_tag_type_t type;
    uint32_t             size;
    uint32_t             num;
    uint32_t             entsize;
    uint32_t             shndx;
    char                 sections[];
} multiboot_tag_elf_sections_t;

typedef struct PACKED {
    multiboot_tag_type_t type;
    uint32_t             size;
    uint16_t             version;
    uint16_t             cseg;
    uint32_t             offset;
    uint16_t             cseg_16;
    uint16_t             dseg;
    uint16_t             flags;
    uint16_t             cseg_len;
    uint16_t             cseg_16_len;
    uint16_t             dseg_len;
} multiboot_tag_apm_t;

typedef struct PACKED {
    multiboot_tag_type_t type;
    uint32_t             size;
    uint32_t             pointer;
} multiboot_tag_efi32_t;

typedef struct PACKED {
    multiboot_tag_type_t type;
    uint32_t             size;
    uint64_t             pointer;
} multiboot_tag_efi64_t;

typedef struct PACKED {
    multiboot_tag_type_t type;
    uint32_t             size;
    uint8_t              major;
    uint8_t              minor;
    uint8_t              reserved[6];
    uint8_t              tables[];
} multiboot_tag_smbios_t;

typedef struct PACKED {
    multiboot_tag_type_t type;
    uint32_t             size;
    uint8_t              rsdp[];
} multiboot_tag_old_acpi_t;

typedef struct PACKED {
    multiboot_tag_type_t type;
    uint32_t             size;
    uint8_t              rsdp[];
} multiboot_tag_new_acpi_t;

typedef struct PACKED {
    multiboot_tag_type_t type;
    uint32_t             size;
    uint8_t              dhcpack[];
} multiboot_tag_network_t;

typedef struct PACKED {
    multiboot_tag_type_t type;
    uint32_t             size;
    uint32_t             descr_size;
    uint32_t             descr_vers;
    uint8_t              efi_mmap[];
} multiboot_tag_efi_mmap_t;

typedef struct PACKED {
    multiboot_tag_type_t type;
    uint32_t             size;
    uint32_t             pointer;
} multiboot_tag_efi32_ih_t;

typedef struct PACKED {
    multiboot_tag_type_t type;
    uint32_t             size;
    uint64_t             pointer;
} multiboot_tag_efi64_ih_t;

typedef struct PACKED {
    multiboot_tag_type_t type;
    uint32_t             size;
    uint32_t             load_base_addr;
} multiboot_tag_load_base_addr_t;

