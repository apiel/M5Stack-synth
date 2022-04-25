#ifndef ZIC_WAVE_WAVETABLE_H_
#define ZIC_WAVE_WAVETABLE_H_

#include "zic_wave_base.h"
#include "zic_wavetable_base.h"
#include "wavetables/wavetable_sine.h"

class Zic_Wave_Wavetable : public Zic_Wave_Base
{
protected:
    double sample(float *freq)
    {
        int i = (M_PI * (*freq) * time + phase) * sampleCount;
        // return table[i & (sampleCount - 1)];
        return table[((i & (sampleCount - 1)) + pos) & (size - 1)];
    }

public:
    float *table = &wavetableSine[0];
    uint16_t sampleCount = 2048;
    uint16_t size = 2048;
    uint16_t pos = 0;

    void set(Zic_Wavetable_Base * wavetable)
    {
        table = wavetable->table;
        size = wavetable->size;
        sampleCount = wavetable->sampleCount;
    }
};

#endif
