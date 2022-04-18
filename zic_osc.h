#ifndef ZIC_OSC_H_
#define ZIC_OSC_H_

#include <math.h>
#include <stdint.h>

#include "zic_fastTrigo.h"

enum
{
    OSC_SINE,
    OSC_SQUARE,
    OSC_TRIANGLE,
    OSC_SAW,
    OSC_NOIZE,
    OSC_COUNT
};

// https://github.com/audiowaves/simpleWavesGenerator
// https://olehc.medium.com/basic-sound-waves-with-c-and-juce-50ec9f0bfe5c
class Zic_Osc
{
protected:
    float m_amplitude = 32767.0f;
    double m_time = 0.0;
    double m_deltaTime = 1.0 / 44100.0;

    double sine(float *freq)
    {
        // This use too much ressources
        // return sin(M_PI_2 * (*freq) * m_time + m_phase);

        return fastSine(M_PI_2 * (*freq) * m_time + m_phase);
    }

    double square(float *freq)
    {
        double fullPeriodTime = 1.0 / (*freq);
        double halfPeriodTime = fullPeriodTime * 0.5;
        double localTime = fmod(m_time, fullPeriodTime);
        return localTime < halfPeriodTime ? 1 : -1;
    }

    double triangle(float *freq)
    {
        double fullPeriodTime = 1.0 / (*freq);
        double localTime = fmod(m_time, fullPeriodTime);

        double value = localTime / fullPeriodTime;

        if (value < 0.25)
        {
            return value * 4;
        }
        if (value < 0.75)
        {
            return 2.0 - (value * 4.0);
        }
        return value * 4 - 4.0;
    }

    double saw(float *freq)
    {
        double fullPeriodTime = 1.0 / (*freq);
        double localTime = fmod(m_time, fullPeriodTime);

        return ((localTime / fullPeriodTime) * 2 - 1.0);
    }

    double noize(float *freq)
    {
        return (rand() % 10000) * 0.00001;
    }

    double sample(float *freq)
    {
        switch (oscType)
        {
        case OSC_SINE:
            return sine(freq);
        case OSC_SQUARE:
            return square(freq);
        case OSC_TRIANGLE:
            return triangle(freq);
        case OSC_SAW:
            return saw(freq);
        case OSC_NOIZE:
            return noize(freq);
        }
        return 0;
    }

public:
    float frequency = 103.82617439443122f; // C3
    float amplitude = 0.1f;
    float amplitudeMod = 1.0f;

    float pitch = 1.0f;
    float pitchMod = 1.0f;

    float m_phase = 0.0f;

    // uint8_t oscType = OSC_TRIANGLE;
    uint8_t oscType = OSC_SINE;

    int16_t next()
    {
        float freq = frequency * pitch * pitchMod;
        float amp = amplitudeMod * amplitude * m_amplitude;

        m_time += m_deltaTime;

        return amp * sample(&freq);
    }
};

#endif
