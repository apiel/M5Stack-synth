#ifndef ZIC_WAVE_WAVETABLE_H_
#define ZIC_WAVE_WAVETABLE_H_

#include "zic_wave_base.h"
#include "wavetables/wavetable_sine.h"

class Zic_Wave_Wavetable : public Zic_Wave_Base
{
protected:
    double sample(float *freq)
    {
        int i = (M_PI * (*freq) * time + phase) * size;
        return table[i & (size - 1)];
    }

public:
    float *table = &wavetableSine[0];
    uint16_t size = 2048;
    uint16_t pos = 0;
};

#endif
