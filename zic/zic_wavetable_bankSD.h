#ifndef ZIC_WAVETABLE_BANK_SD_H_
#define ZIC_WAVETABLE_BANK_SD_H_

#include "zic_wavetable_base.h"
#include "zic_error.h"

// To generate a watble bank use:
// https://synthtech.com/waveedit
// https://github.com/AndrewBelt/WaveEdit

// Reading wav file
// https://github.com/mhroth/tinywav

#define SD_WAVETABLES_SAMPLE_COUNT 256
#define SD_WAVETABLES_COUNT 64
#define SD_WAVETABLES_SIZE SD_WAVETABLES_SAMPLE_COUNT *SD_WAVETABLES_COUNT

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

class Zic_Wavetable_BankSD : public Zic_Wavetable_Base
{
protected:
    float _table[SD_WAVETABLES_SIZE];

public:
    WavHeader header;

    Zic_Wavetable_BankSD() : Zic_Wavetable_Base(&_table[0], SD_WAVETABLES_SAMPLE_COUNT, SD_WAVETABLES_SIZE)
    {
    }

    uint8_t load(const char *filename)
    {
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

        int16_t bit;
        int16_t pos = 0;
        while (file.available())
        {
            file.read((uint8_t *)&bit, sizeof(int16_t));
            _table[pos] = (float)bit / INT16_MAX;
            pos++;
        }
        // Serial.printf("Len %d\n", pos);
        // for (int i = 0; i < 255; i++)
        // {
        //     Serial.printf("%.9f, ", table[i]);
        // }

        file.close();
        return SUCCESS;
    }
};

#endif
