#pragma once

typedef enum {
    STATUS_OK,
    STATUS_INVALID_BASE,
    STATUS_NULL_POINTER
} StatusCode;
StatusCode to_base_string(unsigned long long number, int base, char *result_buffer);

StatusCode toBinBase(unsigned long long number, int base, char *res);