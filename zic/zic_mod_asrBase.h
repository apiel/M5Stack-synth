#ifndef ZIC_MOD_ASR_BASE_H_
#define ZIC_MOD_ASR_BASE_H_

#include "zic/zic_wave_base.h"

template <typename T>
class Zic_Mod_AsrBase
{
protected:
    uint8_t phase = END_PHASE;
    uint8_t nextPhase = END_PHASE;
    uint16_t attackMs = 10;
    uint16_t releaseMs = 500;

    T stepTarget = 1.0f;
    T attackStep;
    T releaseStep;
    T value = 0;

    uint8_t note = 0;

    enum
    {
        ATTACK_PHASE,
        SUSTAIN_PHASE,
        RELEASE_PHASE,
        END_PHASE,
        PHASE_COUNT
    };

    virtual int16_t getData(int16_t data)
    {
        return value * data;
    }

public:
    /**
     * @brief set to true to skip substain phase
     */
    bool noSustain = false;

    Zic_Mod_AsrBase(bool _noSustain = false)
    {
        noSustain = _noSustain;
        setAttack(attackMs);
        setRelease(releaseMs);
    }

    bool isOn()
    {
        return phase != END_PHASE;
    }

    virtual void setAttack(uint16_t ms)
    {
        attackMs = ms;
        attackStep = stepTarget / ((float)ms * SAMPLE_PER_MS);
    }

    virtual void setRelease(uint16_t ms)
    {
        releaseMs = ms;
        releaseStep = stepTarget / ((float)ms * SAMPLE_PER_MS);
    }

    virtual void debug()
    {
        Serial.print("stepTarget ");
        Serial.println(stepTarget);
        Serial.printf("attack %d step ", attackMs);
        Serial.println(attackStep);
        Serial.printf("release %d step ", releaseMs);
        Serial.println(releaseStep);
    }

    int16_t next(int16_t data)
    {
        switch (phase)
        {
        case ATTACK_PHASE:
            if (value < stepTarget)
            {
                value += attackStep;
            }
            else
            {
                Serial.println("end ATTACK_PHASE");
                value = stepTarget;
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

        return getData(data);
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
