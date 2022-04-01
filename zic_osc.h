#ifndef ZIC_OSC_H_
#define ZIC_OSC_H_

#include <math.h>
#include <stdint.h>

#define PI 3.141592653589793238

class Zic_Osc
{
protected:
    float m_phase = 0.0f;
    float m_amplitude = 32767.0f;
    double m_time = 0.0;
    double m_deltaTime = 1.0 / 44100.0;
    double double_Pi = PI * 2.0;

public:
    float frequency = 103.82617439443122f; // C3
    float amplitude = 0.1f;
    float amplitudeMod = 1.0f;

    uint16_t next()
    {
        double angle = double_Pi * frequency * m_time + m_phase;
        uint16_t ret = amplitudeMod * amplitude * m_amplitude * sin(angle);
        m_time += m_deltaTime;

        return ret;
    }
};

#endif
