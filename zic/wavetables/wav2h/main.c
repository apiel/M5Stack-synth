#include "tinywav.h"

#include <assert.h>

#define NUM_CHANNELS 1
#define SAMPLE_RATE 44100
#define BLOCK_SIZE 256

int main(int argc, char *argv[])
{
    char *outputPath = "new_table.h";

    if (argc < 2)
    {
        printf("Please provide in put file");
        return -1;
    }
    const char *inputPath = argv[1];

    TinyWav twReader;
    tinywav_open_read(&twReader, inputPath, TW_INLINE);
    if (twReader.numChannels != NUM_CHANNELS || twReader.h.SampleRate != SAMPLE_RATE)
    {
        printf("Supplied test wav has wrong format - should be [%d]channels, fs=[%d]\n", NUM_CHANNELS, SAMPLE_RATE);
        return -1;
    }

    int totalNumSamples = twReader.numFramesInHeader;
    printf("Size %d, sampleCount %d, count of wavetable %d\n", totalNumSamples, BLOCK_SIZE, totalNumSamples / BLOCK_SIZE);

    FILE *file = fopen(argc > 2 ? argv[2] : outputPath, "w");

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
