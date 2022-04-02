#ifndef ZIC_OSC_H_
#define ZIC_OSC_H_

#include <math.h>
#include <stdint.h>

#define PI 3.141592653589793238

enum
{
    OSC_SINE,
    OSC_SQUARE,
    OSC_TRIANGLE,
    OSC_COUNT
};
class Zic_Osc
{
protected:
    float m_amplitude = 32767.0f;
    double m_time = 0.0;
    double m_deltaTime = 1.0 / 44100.0;
    double double_Pi = PI * 2.0;
    double half_Pi = PI * 0.5;

    // int16_t sine(float freq, float amp)
    //     {}

public:
    float frequency = 103.82617439443122f; // C3
    float amplitude = 0.1f;
    float amplitudeMod = 1.0f;

    float pitch = 1.0f;
    float pitchMod = 1.0f;

    float m_phase = 0.0f;

    uint8_t oscType = OSC_SINE;

    int16_t next()
    {
        float freq = frequency * pitch * pitchMod;
        float amp = amplitudeMod * amplitude * m_amplitude;

        m_time += m_deltaTime;

        switch (oscType)
        {
        case OSC_SINE:
        {
            double angle = double_Pi * freq * m_time + m_phase;
            return amp * sin(angle);
        }
        case OSC_SQUARE:
        {
            // return sineValue > 0 ? amp : -amp;
            double fullPeriodTime = 1.0 / freq;
            double halfPeriodTime = fullPeriodTime * 0.5;
            double localTime = fmod(m_time, fullPeriodTime);
            return localTime < halfPeriodTime ? amp : -amp;
        }
        case OSC_TRIANGLE:
        {
            // return acos(sin(sineValue)) / half_Pi;
            double res = 0.0;
            double fullPeriodTime = 1.0 / frequency;
            double localTime = fmod(m_time, fullPeriodTime);

            double value = localTime / fullPeriodTime;

            if (value < 0.25)
            {
                res = value * 4;
            }
            else if (value < 0.75)
            {
                res = 2.0 - (value * 4.0);
            }
            else
            {
                res = value * 4 - 4.0;
            }
            return amp * res;
        }
        }

        return 0;
    }
};

#endif
