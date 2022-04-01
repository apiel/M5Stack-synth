#ifndef ZIC_MOD_ASR_H_
#define ZIC_MOD_ASR_H_

#include <stdint.h>

enum
{
    ATTACK_PHASE,
    SUSTAIN_PHASE,
    RELEASE_PHASE,
    END_PHASE,
    PHASE_COUNT
};

class Zic_Mod_Asr
{
protected:
    uint8_t phase = ATTACK_PHASE;
    uint16_t attackMs = 100;
    uint16_t releaseMs = 800;

    float attackStep;
    float releaseStep;

    float value = 0.0f;

public:
    bool noSustain = false;

    Zic_Mod_Asr()
    {
        setAttack(attackMs);
        setRelease(releaseMs);
    }

    void setAttack(uint16_t ms)
    {
        // TODO set kind of randomly 50, try to find out
        attackStep = 1.0f / (ms * 50);
    }

    void setRelease(uint16_t ms)
    {
        releaseStep = 1.0f / (ms * 50);
    }

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
                phase = END_PHASE;
            }
            break;
        case END_PHASE:
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
