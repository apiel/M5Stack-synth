#ifndef ZIC_FAST_TRIGO_H_
#define ZIC_FAST_TRIGO_H_

#include <math.h>

#define LUT_TABLE_BITS 8
#define LUT_TABLE_SIZE (1 << LUT_TABLE_BITS)

float *makeLut(void)
{
    static float _lut[LUT_TABLE_SIZE + 1];
    for (uint16_t i = 0; i < LUT_TABLE_SIZE + 1; i++)
    {
        _lut[i] = sin(M_PI_2 * (i / (float)LUT_TABLE_SIZE));
    }
    return _lut;
}

float *lut = makeLut();

// https://www.flipcode.com/archives/Fast_Trigonometry_Functions_Using_Lookup_Tables.shtml
float fastSine(float n)
{
    int i = n * LUT_TABLE_SIZE * 0.5 * M_1_PI; // M_1_PI = 1/M_PI
    if (i < 0)
    {
        return lut[(-((-i) & (LUT_TABLE_SIZE - 1))) + LUT_TABLE_SIZE];
    }
    return lut[i & (LUT_TABLE_SIZE - 1)];
}

#endif