#ifndef ZIC_WAVE_OSC_H_
#define ZIC_WAVE_OSC_H_

#include <math.h>
#include <stdint.h>

#include "zic_fastTrigo.h"
#include "zic_wave_base.h"

enum
{
    OSC_SINE,
    OSC_SQUARE,
    OSC_TRIANGLE,
    OSC_SAW,
    OSC_NOIZE,
    OSC_COUNT
};

const char *getOscName(uint8_t _oscType)
{
    switch (_oscType)
    {
    case OSC_SINE:
        return "Sine";
    case OSC_SQUARE:
        return "Square";
    case OSC_TRIANGLE:
        return "Triangle";
    case OSC_SAW:
        return "Saw";
    case OSC_NOIZE:
        return "Noize";
    }
    return "Unknown";
}

// https://github.com/audiowaves/simpleWavesGenerator
// https://olehc.medium.com/basic-sound-waves-with-c-and-juce-50ec9f0bfe5c
class Zic_Wave_Osc: public Zic_Wave_Base
{
protected:
    double sine(float *freq)
    {
        // This use too much ressources
        // return sin(M_PI_2 * (*freq) * time + phase);

        // TODO use other fastSine
        return fastSine2(M_PI_2 * (*freq) * time + phase);
    }

    double square(float *freq)
    {
        double fullPeriodTime = 1.0 / (*freq);
        double halfPeriodTime = fullPeriodTime * 0.5;
        double localTime = fmod(time, fullPeriodTime);
        return localTime < halfPeriodTime ? 1 : -1;
    }

    double triangle(float *freq)
    {
        double fullPeriodTime = 1.0 / (*freq);
        double localTime = fmod(time, fullPeriodTime);

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
        double localTime = fmod(time, fullPeriodTime);

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
    // uint8_t oscType = OSC_TRIANGLE;
    uint8_t oscType = OSC_SINE;
};

#endif
