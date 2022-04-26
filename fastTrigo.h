#ifndef FAST_TRIGO_H_
#define FAST_TRIGO_H_

#include <math.h>

#define FAST_TRIGO_TABLE_SIZE 1024

int16_t getPos(float radian)
{
    int16_t i = radian * FAST_TRIGO_TABLE_SIZE * 0.5 * M_1_PI; // M_1_PI = 1/M_PI
    return i % FAST_TRIGO_TABLE_SIZE;
}

float *makeLutSine(void)
{
    static float _lut[FAST_TRIGO_TABLE_SIZE];
    for (uint16_t i = 0; i < FAST_TRIGO_TABLE_SIZE; i++)
    {
        _lut[i] = sin(i * 2 * M_PI / (float)FAST_TRIGO_TABLE_SIZE);
    }
    return _lut;
}

float *makeLutCos(void)
{
    static float _lut[FAST_TRIGO_TABLE_SIZE];
    for (uint16_t i = 0; i < FAST_TRIGO_TABLE_SIZE; i++)
    {
        _lut[i] = cos(i * 2 * M_PI / (float)FAST_TRIGO_TABLE_SIZE);
    }
    return _lut;
}

float *lutSine = makeLutSine();
float *lutCos = makeLutCos();

float fastSine(float radian) // 0 to 2PI (6.28)
{
    return lutSine[getPos(radian)];
}

float fastCos(float radian)
{
    return lutCos[getPos(radian)];
}

#endif