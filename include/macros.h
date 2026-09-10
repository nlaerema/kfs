#pragma once


#define ARRAY_LENGTH(array) (sizeof(array) / sizeof((array)[0]))

#define FIELD_SIZEOF(type, field) (sizeof(((type*)0)->field))