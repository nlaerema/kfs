#pragma once

#include <stdarg.h>
#include <stddef.h>

typedef void (*format_put_t)(void* ctx, char c);

size_t vfnprintf(format_put_t put, void* ctx, const char* format, va_list args);
size_t fnprintf(format_put_t put, void* ctx, const char* format, ...);

size_t vsnprintf(char* dest, size_t size, const char* format, va_list arg);
size_t snprintf(char* dest, size_t size, const char* format, ...);