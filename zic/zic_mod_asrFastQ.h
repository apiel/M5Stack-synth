#ifndef ZIC_MOD_ASR_FAST_Q_H_
#define ZIC_MOD_ASR_FAST_Q_H_

#include <math.h>

#include "zic/zic_mod_asrBase.h"

// Still not perfect... Even wonder if it is not sometime crashing!

// It is still using float in getData, so it is just improving on step accumulation
// Zic_Mod_AsrFast might use less ressources, as it don't use float at all.
// Maybe it is possible not using float in getData?

typedef uint32_t uq32_t;
typedef uint64_t uq64_t;

#define f32_to_uq32(f) ((uq32_t)((float)(f) * (float)0xFFFFFFFF))
#define uq32_to_f32(q) ((float)(q)*4.65661287307739e-010f)

#define q32mul(a, b) ((uq32_t)(((uq64_t)(uq32_t)(a) * (uq32_t)(b)) >> 32))

// https://en.wikipedia.org/wiki/Q_(number_format)
// https://www.pathpartnertech.com/representing-decimal-data-in-q-format/

class Zic_Mod_AsrFastQ : public Zic_Mod_AsrBase<uq32_t>
{
protected:
    int16_t getData(int16_t data) override
    {
        // Maybe it is possible to not convert to float but instead to convert data?
        return uq32_to_f32(value) * data;
    }

public:
    Zic_Mod_AsrFastQ(bool _noSustain = false) : Zic_Mod_AsrBase(_noSustain)
    {
        stepTarget = f32_to_uq32(0.9f);
        setAttack(attackMs);
        setRelease(releaseMs);
    }

    void setAttack(uint16_t ms) override
    {
        attackMs = ms;
        attackStep = q32mul(stepTarget, f32_to_uq32(1 / ((float)ms * SAMPLE_PER_MS)));
    }

    void setRelease(uint16_t ms) override
    {
        releaseMs = ms;
        releaseStep = q32mul(stepTarget, f32_to_uq32(1 / ((float)ms * SAMPLE_PER_MS)));
    }
};

#endif
