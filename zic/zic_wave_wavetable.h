#ifndef ZIC_WAVE_WAVETABLE_H_
#define ZIC_WAVE_WAVETABLE_H_

#include "zic_wave_base.h"
#include "wavetables/wavetable_sine.h"

#define WAVETABLE_SIZE 2048

class Zic_Wave_Wavetable : public Zic_Wave_Base
{
protected:
    double sample(float *freq)
    {
        int i = (M_PI * (*freq) * time + phase) * WAVETABLE_SIZE;
        return table[i & (WAVETABLE_SIZE - 1)];
    }

public:
    float *table = &wavetableSine[0];
};

#endif
