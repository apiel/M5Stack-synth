#ifndef OSC_H_
#define OSC_H_

#include <math.h>


#define PI 3.141592653589793238

class Osc
{
protected:
    double m_time = 0.0;
    double m_amplitude = 10000.0; // -32,768 to 32,767
    double m_deltaTime = 1.0 / 44100.0;
    double m_phase = 0.0;
    double double_Pi = PI * 2.0;

public:
    float frequency = 103.82617439443122;

    uint16_t next()
    {
        double angle = double_Pi * frequency * m_time + m_phase;
        uint16_t ret = m_amplitude * sin(angle);
        m_time += m_deltaTime;

        return ret;
    }
};

#endif
