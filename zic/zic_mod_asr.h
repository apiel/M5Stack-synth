#ifndef ZIC_MOD_ASR_H_
#define ZIC_MOD_ASR_H_

#include "zic/zic_wave_base.h"

/**
 * @brief ASR envelop
 */
class Zic_Mod_Asr
{
protected:
    uint8_t phase = END_PHASE;
    uint16_t attackMs = 10;
    uint16_t releaseMs = 500;

    float attackStep;
    float releaseStep;

    float value = 0.0f;

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

    /**
     * @brief return if the envelop is currently playing.
     *
     * @return true
     * @return false
     */
    bool isOn()
    {
        return phase != END_PHASE;
    }

    /**
     * @brief Set the Attack time in ms
     *
     * @param ms
     */
    void setAttack(uint16_t ms)
    {
        attackMs = ms;
        attackStep = 1.0f / ((float)ms * SAMPLE_PER_MS);
    }

    /**
     * @brief Set the Release time in ms
     *
     * @param ms
     */
    void setRelease(uint16_t ms)
    {
        releaseMs = ms;
        releaseStep = 1.0f / ((float)ms * SAMPLE_PER_MS);
    }

    void debug()
    {
        Serial.printf("attack %d step %.6f\n", attackMs, attackStep);
        Serial.printf("release %d step %.6f\n", releaseMs, releaseStep);
    }

    /**
     * @brief to be called to update the phase
     *
     * @return float
     */
    float next()
    {
        switch (phase)
        {
        case ATTACK_PHASE:
            if (value < 1.0f)
            {
                value = value + attackStep;
            }
            else
            {
                // Serial.println("end ATTACK_PHASE");
                value = 1.0f;
                phase = noSustain ? RELEASE_PHASE : SUSTAIN_PHASE;
            }
            break;
        case SUSTAIN_PHASE:
            break;
        case RELEASE_PHASE:
            if (value > 0.0f)
            {
                value = value - releaseStep;
            }
            else
            {
                // Serial.println("end RELEASE_PHASE");
                value = 0.0f;
                phase = END_PHASE;
            }
            break;
        case END_PHASE:
            break;
        }

        return value;
    }

    /**
     * @brief trigger the envelop to start
     *
     * @param _note
     */
    void on(uint8_t _note = 0)
    {
        note = _note;
        value = 0.0f;
        // Serial.println("start ATTACK_PHASE");
        phase = ATTACK_PHASE;
    }

    /**
     * @brief trigger the envelop to release
     *
     * @param _note
     */
    void off(uint8_t _note = 0)
    {
        if (_note && _note != note)
        {
            return;
        }

        // Serial.println("start RELEASE_PHASE");
        phase = RELEASE_PHASE;
    }
};

#endif
