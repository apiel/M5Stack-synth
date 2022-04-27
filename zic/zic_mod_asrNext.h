#ifndef ZIC_MOD_ASR_NEXT_H_
#define ZIC_MOD_ASR_NEXT_H_

#include <stdint.h>

enum
{
    ATTACK_PHASE,
    SUSTAIN_PHASE,
    RELEASE_PHASE,
    END_PHASE,
    PHASE_COUNT
};

/**
 * Because using ASR with a touchscreen does work so well no play the full note,
 * Let's the Attack phase force to finish before to switch to another phase
 * even if off() is called.
 */
class Zic_Mod_AsrNext
{
protected:
    uint8_t phase = END_PHASE;
    uint8_t nextPhase = END_PHASE;
    uint16_t attackMs = 10;
    uint16_t releaseMs = 500;

    float attackStep;
    float releaseStep;

    float value = 0.0f;

public:
    bool noSustain = false;

    Zic_Mod_AsrNext()
    {
        setAttack(attackMs);
        setRelease(releaseMs);
    }

    bool isOn()
    {
        return phase != END_PHASE;
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
                phase = nextPhase;
                nextPhase = END_PHASE;
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
        nextPhase = noSustain ? RELEASE_PHASE : SUSTAIN_PHASE;
        phase = ATTACK_PHASE;
    }

    void off()
    {
        if (nextPhase != END_PHASE) {
            nextPhase = RELEASE_PHASE;
        } else {
            phase = RELEASE_PHASE;
        }
    }
};

#endif
