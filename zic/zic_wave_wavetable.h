#ifndef ZIC_WAVE_WAVETABLE_H_
#define ZIC_WAVE_WAVETABLE_H_

#include "zic_wave_base.h"

class Zic_Wave_Wavetable: public Zic_Wave_Base
{
protected:
    double sample(float *freq)
    {
        return fastSine(M_PI_2 * (*freq) * m_time + m_phase);
    }
};

#endif
