#ifndef ZIC_MOD_ASR_FAST_H_
#define ZIC_MOD_ASR_FAST_H_

#include <math.h>

#include "zic/zic_mod_asrBase.h"

#define ASR_STEP_POWER 15
#define ASR_STEP_TARGET (uint16_t) pow(2, ASR_STEP_POWER)

// TODO see if we couldn't use Q format fixed point instead
// and not have such a limited ms...
/**
 * @brief ASR envelop modulation
 * 
 * Slightly faster than Zic_Mod_Asr as it doesn't use float for the phase transition
 * However with the tradeoff to have a limited amount of millisecond settable on attack
 * and release due to step rounding: 743ms 371ms 247ms ...
 */
class Zic_Mod_AsrFast : public Zic_Mod_AsrBase<uint16_t>
{
protected:
    int16_t getData(int16_t data) override
    {
        return (value * data) >> ASR_STEP_POWER;
    }

public:
    Zic_Mod_AsrFast(bool _noSustain = false) : Zic_Mod_AsrBase(_noSustain)
    {
        stepTarget = ASR_STEP_TARGET;
        setAttack(attackMs);
        setRelease(releaseMs);
    }

    void setAttack(uint16_t ms) override
    {
        attackMs = ms;
        attackStep = (float)ASR_STEP_TARGET / ((float)ms * SAMPLE_PER_MS);
        if (!attackStep)
        {
            attackStep = 1;
        }
    }

    void setRelease(uint16_t ms) override
    {
        releaseMs = ms;
        releaseStep = (float)ASR_STEP_TARGET / ((float)ms * SAMPLE_PER_MS);
        if (!releaseStep)
        {
            releaseStep = 1;
        }
    }
};

#endif
