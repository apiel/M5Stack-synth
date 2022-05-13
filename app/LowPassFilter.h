#ifndef LOWPASS_H_
#define LOWPASS_H_

// // typedef float yoType;
// typedef int16_t yoType;

// enum
// {
//     LPF,   /* low pass filter */
//     HPF,   /* High pass filter */
//     BPF,   /* band pass filter */
//     NOTCH, /* Notch Filter */
//     PEQ,   /* Peaking band EQ filter */
//     LSH,   /* Low shelf filter */
//     HSH    /* High shelf filter */
// };

class LowPassFilter
{
public:
    enum FilterMode
    {
        FILTER_MODE_LOWPASS = 0,
        FILTER_MODE_HIGHPASS,
        FILTER_MODE_BANDPASS,
        kNumFilterModes
    };

    float cutoff;
    float resonance;
    FilterMode mode;
    float feedbackAmount;
    inline void calculateFeedbackAmount()
    {
        feedbackAmount = resonance + resonance / (1.0 - getCalculatedCutoff());
    }
    float buf0;
    float buf1;
    float buf2;
    float buf3;

    inline float getCalculatedCutoff() const
    {
        return cutoff; //0.7; // fmax(fmin(cutoff + cutoffMod, 0.99), 0.01);
    };

    int16_t next(int16_t inputValue)
    {
        if (inputValue == 0)
            return inputValue;
        float calculatedCutoff = getCalculatedCutoff();
        buf0 += calculatedCutoff * (inputValue - buf0 + feedbackAmount * (buf0 - buf1));
        buf1 += calculatedCutoff * (buf0 - buf1);
        buf2 += calculatedCutoff * (buf1 - buf2);
        buf3 += calculatedCutoff * (buf2 - buf3);
        switch (mode)
        {
        case FILTER_MODE_LOWPASS:
            return buf3;
        case FILTER_MODE_HIGHPASS:
            return inputValue - buf3;
        case FILTER_MODE_BANDPASS:
            return buf0 - buf3;
        default:
            return 0.0;
        }
    }


    LowPassFilter() : cutoff(0.2),
                      resonance(0.9),
                      mode(FILTER_MODE_LOWPASS),
                      buf0(0.0),
                      buf1(0.0),
                      buf2(0.0),
                      buf3(0.0)
    {
        calculateFeedbackAmount();
    };
    inline void setCutoff(float newCutoff)
    {
        cutoff = newCutoff;
        calculateFeedbackAmount();
    };
    inline void setResonance(float newResonance)
    {
        resonance = newResonance;
        calculateFeedbackAmount();
    };
    inline void setFilterMode(FilterMode newMode) { mode = newMode; }

    // inline void setCutoffMod(float newCutoffMod)
    // {
    //     cutoffMod = newCutoffMod;
    //     calculateFeedbackAmount();
    // }

    // public:
    //     LowPassFilter()
    //     {
    //         // set(LPF, 10, 100, 44100, 2);
    //         a0 = 0.9;
    //         a1 = 0.5;
    //         a2 = 0.3;
    //         a3 = 0.2;
    //         a4 = 0.1;
    //     }

    //     yoType next(yoType sample)
    //     {
    //         yoType result;

    //         /* compute result */
    //         result = a0 * sample + a1 * x1 + a2 * x2 - a3 * y1 - a4 * y2;

    //         /* shift x1 to x2, sample to x1 */
    //         x2 = x1;
    //         x1 = sample;

    //         /* shift y1 to y2, result to y1 */
    //         y2 = y1;
    //         y1 = result;

    //         return result;
    //     }
    // protected:
    //     float a0, a1, a2, a3, a4;
    //     yoType x1, x2, y1, y2;

    // public:

    //   void setCutoffFreqAndResonance(uyoType cutoff, uyoType resonance)
    //   {
    //     f = cutoff;
    //     q = resonance; // hopefully optimised away when compiled, just here for
    //                    // backwards compatibility
    //     fb = q + ucfxmul(q, SHIFTED_1 - cutoff);
    //   }

    //   yoType next(yoType in)
    //   {
    //     // setPin13High();
    //     buf0 += fxmul(((in - buf0) + fxmul(fb, buf0 - buf1)), f);
    //     buf1 += ifxmul(buf0 - buf1, f); // could overflow if input changes fast
    //     return buf1;
    //   }

    // protected:
    //   uyoType q;
    //   uyoType f;
    //   uint32_t fb;
    //   yoType buf0, buf1;
    //   const uint8_t FX_SHIFT = sizeof(uyoType) << 3;
    //   const uyoType SHIFTED_1 = (1 << FX_SHIFT) - 1;

    //   int32_t ucfxmul(uyoType a, uyoType b)
    //   {
    //     return ((a * b) >> FX_SHIFT);
    //   }

    //   int32_t ifxmul(int32_t a, uyoType b) { return ((a * b) >> FX_SHIFT); }
    //   int32_t fxmul(int32_t a, int32_t b) { return ((a * b) >> FX_SHIFT); }
};

#endif
