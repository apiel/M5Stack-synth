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

public:
    float frequency = 103.82617439443122f; // C3
    float amplitude = 0.1f;
    float amplitudeMod = 1.0f;

    float pitch = 1.0f;
    float pitchMod = 1.0f;

    float m_phase = 0.0f;

    uint8_t oscType = OSC_SINE;

    uint16_t next()
    {
        float freq = frequency * pitch * pitchMod;
        float amp = amplitudeMod * amplitude * m_amplitude;

        double angle = double_Pi * freq * m_time + m_phase;
        m_time += m_deltaTime;

        uint16_t sineValue = amp * sin(angle);

        switch (oscType)
        {
        // case OSC_SQUARE:
        //     return sineValue > 0 ? 2000 : 0;
        // case OSC_TRIANGLE:
        //     return amp * acos(sin(freq * m_time)) / half_Pi;
        }
        return sineValue;
    }
};

#endif
