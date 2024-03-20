#include <stdint.h>

#define FRAC_BITS 16
#define FIXED_POINT_COEFFICIENT (1 << FRAC_BITS) // 2^FRAC_BITS

/* Fixed point with a 16bit fractional part */
typedef int32_t fx16_t;

// 將 double 轉換為定點數
static inline fx16_t to_fx16_double(double value) {
    return (fx16_t)(value * FIXED_POINT_COEFFICIENT);
}

// 將 int 轉換為定點數
static inline fx16_t to_fx16_int(int value) {
    return value * FIXED_POINT_COEFFICIENT;
}

// 將定點數轉回浮點數
static inline double to_Float(fx16_t fp) {
    return (double)fp / FIXED_POINT_COEFFICIENT;
}

int fx_mul(int, int);

int fx_div(int, int);

int fx_log(unsigned int);

int fx_sqrt(int);
