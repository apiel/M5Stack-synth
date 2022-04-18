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

float fastSine(float n)
{
    float f = n * LUT_TABLE_SIZE / M_PI_2;
    int i = round(f);
    if (i < 0)
    {
        return lut[(-((-i) & (LUT_TABLE_SIZE - 1))) + LUT_TABLE_SIZE];
    }
    return lut[i & (LUT_TABLE_SIZE - 1)];
}

#endif