#ifndef ZIC_MOD_ASR_H_
#define ZIC_MOD_ASR_H_

#include <math.h>

#include "zic/zic_wave_base.h"

#define ASR_STEP_POWER 15
#define ASR_STEP_TARGET (uint16_t) pow(2, ASR_STEP_POWER)

// FIXME still make a cutting noise
class Zic_Mod_Asr
{
protected:
    uint8_t phase = END_PHASE;
    uint8_t nextPhase = END_PHASE;
    uint16_t attackMs = 10;
    uint16_t releaseMs = 500;

    uint16_t attackStep;
    uint16_t releaseStep;

    uint16_t value = 0;

    uint8_t note = 0;

    enum
    {
        ATTACK_PHASE,
        SUSTAIN_PHASE,
        RELEASE_PHASE,
        END_PHASE,
        PHASE_COUNT
    };

public:
    /**
     * @brief set to true to skip substain phase
     */
    bool noSustain = false;

    Zic_Mod_Asr(bool _noSustain = false)
    {
        noSustain = _noSustain;
        setAttack(attackMs);
        setRelease(releaseMs);
    }

    bool isOn()
    {
        return phase != END_PHASE;
    }

    //  743ms 371ms 247ms
    void setAttack(uint16_t ms)
    {
        attackMs = ms;
        attackStep = (float)ASR_STEP_TARGET / ((float)ms * SAMPLE_PER_MS);
        if (!attackStep)
        {
            attackStep = 1;
        }
    }

    void setRelease(uint16_t ms)
    {
        releaseMs = ms;
        releaseStep = (float)ASR_STEP_TARGET / ((float)ms * SAMPLE_PER_MS);
        if (!releaseStep)
        {
            releaseStep = 1;
        }
    }

    void debug()
    {
        Serial.printf("attack %d step %d\n", attackMs, attackStep);
        Serial.printf("release %d step %d\n", releaseMs, releaseStep);
    }

    int16_t next(int16_t data)
    {
        switch (phase)
        {
        case ATTACK_PHASE:
            if (value < ASR_STEP_TARGET)
            {
                value += attackStep;
            }
            else
            {
                Serial.println("end ATTACK_PHASE");
                value = ASR_STEP_TARGET;
                phase = nextPhase;
                nextPhase = END_PHASE;
            }
            break;
        case SUSTAIN_PHASE:
            break;
        case RELEASE_PHASE:
            if (value > 0)
            {
                value -= releaseStep;
            }
            else
            {
                Serial.println("end RELEASE_PHASE");
                value = 0;
                phase = END_PHASE;
            }
            break;
        case END_PHASE:
            break;
        }

        return (value * data) >> ASR_STEP_POWER;
    }

    void on(uint8_t _note = 0)
    {
        Serial.println("start ATTACK_PHASE");
        note = _note;
        value = 0;
        nextPhase = noSustain ? RELEASE_PHASE : SUSTAIN_PHASE;
        phase = ATTACK_PHASE;
    }

    void off(uint8_t _note = 0)
    {
        if (_note && _note != note)
        {
            return;
        }

        phase = RELEASE_PHASE;
    }

    void nextOff(uint8_t _note = 0)
    {
        if (_note && _note != note)
        {
            return;
        }

        if (nextPhase != END_PHASE)
        {
            nextPhase = RELEASE_PHASE;
        }
        else
        {
            off(_note);
        }
    }
};

#endif
