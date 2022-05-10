#ifndef ZIC_WAVETABLE_SYNTH_H_
#define ZIC_WAVETABLE_SYNTH_H_

#include <zic/zic_mod_asr.h>
#include <zic/zic_wave_wavetable.h>

/**
 * @brief Basic wavetable synth combining wave, modulation, effect...
 *
 */
class Zic_Wavetable_Synth
{
public:
    Zic_Wave_Wavetable wave;
    Zic_Mod_Asr asr;

    Zic_Wavetable_Synth(Zic_Wavetable_Base *wavetable) : wave(wavetable)
    {
    }

    int16_t next()
    {
        wave.amplitudeMod = asr.next();
        return wave.next();
    }
};

#endif
