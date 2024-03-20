#include <stdint.h>

#define FRAC_BITS 16
#define FIXED_POINT_COEFFICIENT (1 << FRAC_BITS) // 2^FRAC_BITS

/* Fixed point with a 16bit fractional part */
typedef int32_t fx16_16_t;

// 將 double 轉換為定點數
static inline int to_fp_double(double value) {
    return (int)(value * FIXED_POINT_COEFFICIENT);
}

// 將 int 轉換為定點數
static inline int to_fp_int(int value) {
    return value * FIXED_POINT_COEFFICIENT;
}

// 將定點數轉回浮點數
static inline double to_Float(int fp) {
    return (double)fp / FIXED_POINT_COEFFICIENT;
}

int fp_mul(int, int);

int fp_div(int, int);

int fx_log(unsigned int);

int sqrt_fx16_16_to_fx16_16(int);
