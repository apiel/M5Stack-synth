#ifndef ZIC_WAVE_BASE_H_
#define ZIC_WAVE_BASE_H_

#define SAMPLE_RATE 44100.0

class Zic_Wave_Base
{
protected:
    float amplitudePeak = 32767.0f;
    double time = 0.0;
    double deltaTime = 1.0 / SAMPLE_RATE;

    virtual double sample(float *freq);

public:
    float frequency = 103.82617439443122f; // C3
    float amplitude = 0.1f;
    float amplitudeMod = 1.0f;

    float pitch = 1.0f;
    float pitchMod = 1.0f;

    float phase = 0.0f;

    int16_t next()
    {
        float freq = frequency * pitch * pitchMod;
        float amp = amplitudeMod * amplitude * amplitudePeak;
        time += deltaTime;

        return amp * sample(&freq);
    }
};

#endif
