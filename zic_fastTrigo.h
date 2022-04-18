#ifndef ZIC_FAST_TRIGO_H_
#define ZIC_FAST_TRIGO_H_

#include <math.h>

#define LUT_TABLE_BITS 8
#define LUT_TABLE_SIZE (1 << LUT_TABLE_BITS)

// float *makeLut(void)
// {
//     static float _lut[LUT_TABLE_SIZE + 1];
//     for (uint16_t i = 0; i < LUT_TABLE_SIZE + 1; i++)
//     {
//         _lut[i] = sin(M_PI_2 * (i / (float)LUT_TABLE_SIZE));
//     }
//     return _lut;
// }

// float *lut = makeLut();

float lut[LUT_TABLE_SIZE + 1];

void lut_init(void)
{
    // for (int i = 0; i < LUT_TABLE_SIZE + 1; i++)
    //     lut[i] = sin(M_PI_2 * (i / (float)LUT_TABLE_SIZE));

    for (uint16_t i = 0; i < LUT_TABLE_SIZE; i++)
    {
        lut[i] = (float)sin((double)i * M_PI / LUT_TABLE_SIZE);
    }
}

float fastSine(float n)
{
    float f = n * LUT_TABLE_SIZE / M_PI_2;
    int i = (int)f;
    if (i < 0)
    {
        return lut[(-((-i) & (LUT_TABLE_SIZE - 1))) + LUT_TABLE_SIZE];
    }
    return lut[i & (LUT_TABLE_SIZE - 1)];
}

// float fastSine(uint32_t phase)
// {
//     uint32_t quad_phase;
//     int table_loc;

//     quad_phase = (phase & 0x40000000) ? ~phase : phase;

//     table_loc = (quad_phase & 0x3FFFFFFF) >> (30 - LUT_TABLE_BITS);

//     float x = (quad_phase & ((1 << (30 - LUT_TABLE_BITS)) - 1)) / (float)(1 << (30 - LUT_TABLE_BITS));
//     return lut[table_loc] + ((lut[table_loc + 1] - lut[table_loc]) * x);
// }

// float
// fastSine(uint32_t phase)
// {
// 	uint32_t quad_phase;
// 	int table_loc;
// 	float x, y[2];

// 	/* strict aliasing blah blah blah (otherwise gcc will complain if we
// 	 * do this by type-punning) */
// 	union {
// 		float f;
// 		uint32_t i;
// 	} out;

// 	/* if we're in the second or fourth quadrant, run the phase backwards */
// 	quad_phase = (phase & 0x40000000) ? ~phase : phase;

// 	/* integer part for table index */
// 	table_loc = (quad_phase & 0x3FFFFFFF) >> (30 - LUT_TABLE_BITS);
// 	y[0] = lut[table_loc];
// 	y[1] = lut[table_loc + 1];

// 	/* fractional part for linear interpolation */
// 	x = (quad_phase & ((1 << (30 - LUT_TABLE_BITS)) - 1)) / (float) (1 << (30 - LUT_TABLE_BITS));
// 	out.f = y[0] + ((y[1] - y[0]) * x);

// 	/* invert the second half of the wave by manually
// 	 * setting the float's sign bit */
// 	out.i |= phase & 0x80000000;
// 	return out.f;
// }

#endif