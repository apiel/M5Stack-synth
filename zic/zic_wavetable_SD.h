#ifndef ZIC_WAVETABLE_SD_H_
#define ZIC_WAVETABLE_SD_H_

#include "zic_error.h"
#include "zic_wavetable_base.h"

// To generate a wavetable bank use:
// https://synthtech.com/waveedit
// https://github.com/AndrewBelt/WaveEdit
// 64 wavetable of 256 samples

// Reading wav file
// https://github.com/mhroth/tinywav

typedef struct WavHeader
{
    uint32_t ChunkID;
    uint32_t ChunkSize;
    uint32_t Format;
    uint32_t Subchunk1ID;
    uint32_t Subchunk1Size;
    uint16_t AudioFormat;
    uint16_t NumChannels;
    uint32_t SampleRate;
    uint32_t ByteRate;
    uint16_t BlockAlign;
    uint16_t BitsPerSample;
    uint32_t Subchunk2ID;
    uint32_t Subchunk2Size;
} WavHeader;

uint8_t loadWavetableFromSD(Zic_Wavetable_Base *wavetable, const char *filename)
{
    WavHeader header;

    File file = SD.open(filename, "rb");
    if (!file)
    {
        return ERROR_FAIL_OPEN_FILE;
    }

    file.read((uint8_t *)&header, sizeof(WavHeader));

    // skip over any other chunks before the "data" chunk
    bool additionalHeaderDataPresent = false;
    while (header.Subchunk2ID != 1635017060)
    {
        file.seek(4);
        file.read((uint8_t *)&header.Subchunk2ID, 4);
        additionalHeaderDataPresent = true;
    }

    if (additionalHeaderDataPresent)
    {
        // read the value of Subchunk2Size, the one populated when reading 'WavHeader' structure is wrong
        file.read((uint8_t *)&header.Subchunk2Size, 4);
    }

    if (header.BitsPerSample != 16 || header.AudioFormat != 1)
    {
        // Serial.printf("BitsPerSample %d AudioFormat %d\n", header.BitsPerSample, header.AudioFormat);
        return ERROR_UNKNOWN_FORMAT;
    }

    if (header.NumChannels != 1)
    {
        return ERROR_INVALID_CHANNEL_NUM;
    }

    for (int16_t pos = 0; file.available() && pos < wavetable->size; pos++)
    {
        int16_t bit;
        file.read((uint8_t *)&bit, sizeof(int16_t));
        wavetable->table[pos] = (float)bit / INT16_MAX;
    }
    // Serial.printf("Len %d\n", pos);
    // for (int i = 0; i < 255; i++)
    // {
    //     Serial.printf("%.9f, ", wavetable->table[i]);
    // }

    file.close();
    return SUCCESS;
}

#endif
