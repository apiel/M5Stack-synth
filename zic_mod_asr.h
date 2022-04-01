#ifndef ZIC_MOD_ASR_H_
#define ZIC_MOD_ASR_H_

#include <stdint.h>

enum
{
    ATTACK_PHASE,
    SUSTAIN_PHASE,
    RELEASE_PHASE,
    PHASE_COUNT
};

class Zic_Mod_Asr
{
protected:
    uint8_t phase = ATTACK_PHASE;
    uint16_t attackMs = 1000;
    uint16_t releaseMs = 50000;

    float attackStep = 1.0f / attackMs;
    float releaseStep = 1.0f / releaseMs;

    float value = 0.0f;

public:
    bool noSustain = false;

    float next()
    {
        switch (phase)
        {
        case ATTACK_PHASE:
            if (value < 1.0f)
            {
                value += attackStep;
            }
            else
            {
                value = 1.0f;
                phase = noSustain ? RELEASE_PHASE : SUSTAIN_PHASE;
            }
            break;
        case SUSTAIN_PHASE:
            break;
        case RELEASE_PHASE:
            if (value > 0.0f)
            {
                value -= releaseStep;
            }
            else
            {
                value = 0.0f;
            }
            break;
        }

        return value;
    }

    void on()
    {
        value = 0.0f;
        phase = ATTACK_PHASE;
    }

    void off()
    {
        phase = RELEASE_PHASE;
    }
};

#endif
