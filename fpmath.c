#include "fpmath.h"

// 定點數乘法，輸入和輸出都是定點數
fx16_t fx_mul(fx16_t fixedPointValue1, fx16_t fixedPointValue2) {
    // 使用 long long 避免溢出，計算後右移 FRAC_BITS 以調整精度
    long long temp = (long long)fixedPointValue1 * (long long)fixedPointValue2;
    return (fx16_t)(temp >> FRAC_BITS);
}

// 定點數除法，輸入和輸出都是定點數
fx16_t fx_div(fx16_t fixedPointValue1, fx16_t fixedPointValue2) {
    // 為了保持精fx16_t度，將被除數左移 FRAC_BITS 位後進行除法
    long long temp = ((long long)fixedPointValue1 << FRAC_BITS) / fixedPointValue2;
    return (fx16_t)temp;
}

fx16_t fx_log(fx16_t v) {
    unsigned int x = (uint32_t)v;
    unsigned int t;
    fx16_t y;

    y=0xa65af;
    if(x<0x00008000) x<<=16,              y-=0xb1721;
    if(x<0x00800000) x<<= 8,              y-=0x58b91;
    if(x<0x08000000) x<<= 4,              y-=0x2c5c8;
    if(x<0x20000000) x<<= 2,              y-=0x162e4;
    if(x<0x40000000) x<<= 1,              y-=0x0b172;
    t=x+(x>>1); if((t&0x80000000)==0) x=t,y-=0x067cd;
    t=x+(x>>2); if((t&0x80000000)==0) x=t,y-=0x03920;
    t=x+(x>>3); if((t&0x80000000)==0) x=t,y-=0x01e27;
    t=x+(x>>4); if((t&0x80000000)==0) x=t,y-=0x00f85;
    t=x+(x>>5); if((t&0x80000000)==0) x=t,y-=0x007e1;
    t=x+(x>>6); if((t&0x80000000)==0) x=t,y-=0x003f8;
    t=x+(x>>7); if((t&0x80000000)==0) x=t,y-=0x001fe;
    x=0x80000000-x;
    y-=x>>15;
    return y;
}

// sqrt_fx16_16_to_fx16_16 computes the squrare root of a fixed point with 16 bit
// fractional part and returns a fixed point with 16 bit fractional part. It 
// requires that v is positive. The computation use only 32 bit registers and 
// simple operations.
fx16_t fx_sqrt(fx16_t v) {
    uint32_t t, q, b, r;
    r = (int32_t)v; 
    q = 0;          
    b = 0x40000000UL;
    if( r < 0x40000200 )
    {
        while( b != 0x40 )
        {
            t = q + b;
            if( r >= t )
            {
                r -= t;
                q = t + b; // equivalent to q += 2*b
            }
            r <<= 1;
            b >>= 1;
        }
        q >>= 8;
        return q;
    }
    while( b > 0x40 )
    {
        t = q + b;
        if( r >= t )
        {
            r -= t;
            q = t + b; // equivalent to q += 2*b
        }
        if( (r & 0x80000000) != 0 )
        {
            q >>= 1;
            b >>= 1;
            r >>= 1;
            while( b > 0x20 )
            {
                t = q + b;
                if( r >= t )
                {
                    r -= t;
                    q = t + b;
                }
                r <<= 1;
                b >>= 1;
            }
            q >>= 7;
            return q;
        }
        r <<= 1;
        b >>= 1;
    }
    q >>= 8;
    return q;
}