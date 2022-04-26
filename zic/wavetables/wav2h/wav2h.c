#include "tinywav.h"

#include <assert.h>
#include <string.h>

#define NUM_CHANNELS 1
#define SAMPLE_RATE 44100
#define BLOCK_SIZE 256

#define BUF_SIZE 1024

int getSize(char* string, char c) {
    char *e = strrchr(string, c);
    if (e == NULL) {
        return -1;
    }
    return (int)(e - string) + 1;
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Please provide input wav file and target name: ./wav2h bank.wav BankDemo");
        return -1;
    }
    const char *inputPath = argv[1];
    const char *name = argv[2];

    TinyWav twReader;
    tinywav_open_read(&twReader, inputPath, TW_INLINE);
    if (twReader.numChannels != NUM_CHANNELS || twReader.h.SampleRate != SAMPLE_RATE)
    {
        printf("Supplied test wav has wrong format - should be [%d]channels, fs=[%d]\n", NUM_CHANNELS, SAMPLE_RATE);
        return -1;
    }

    int totalNumSamples = twReader.numFramesInHeader;
    printf("Size %d, sampleCount %d, count of wavetable %d\n", totalNumSamples, BLOCK_SIZE, totalNumSamples / BLOCK_SIZE);

    char buffer[BUF_SIZE];
    snprintf(buffer, BUF_SIZE, "../wavetable_%s.h", name);
    FILE *file = fopen(buffer, "w");

    snprintf(buffer, BUF_SIZE, "#ifndef WAVETABLE_%s_H_\n\
#define WAVETABLE_%s_H_\n\n\
#include \"../zic_wavetable_base.h\"\n\n\
class Wavetable_%s : public Zic_Wavetable_Base\n\
{\n\
protected:\n\
    float _table[%d] = {",
             name, name, name, totalNumSamples);
    fwrite(buffer , sizeof(char), getSize(buffer, '{'), file);

    // int samplesProcessed = 0;
    // while (samplesProcessed < totalNumSamples)
    // {
    //     float buffer[NUM_CHANNELS * BLOCK_SIZE];

    //     int samplesRead = tinywav_read_f(&twReader, buffer, BLOCK_SIZE);
    //     assert(samplesRead > 0 && " Could not read from file!");

    //     // printf("\nsamplesRead %d:\n", samplesRead);
    //     // for (int p = 0; p < samplesRead; p++)
    //     // {
    //     //   printf("%.6f,", buffer[p]);
    //     // }

    //     int samplesWritten = tinywav_write_f(&twWriter, buffer, samplesRead);
    //     assert(samplesWritten > 0 && "Could not write to file!");

    //     samplesProcessed += samplesRead * NUM_CHANNELS;
    // }

    fclose(file);
    tinywav_close_read(&twReader);

    return 0;
}
