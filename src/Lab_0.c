#include "Lab_0.h"

const unsigned int EDID_BLOCK_SIZE = 256;

uint8_t parse_edid(uint8_t* block, eEDID_Attribute attribute)
{
    uint8_t ret = 0;
    [[maybe_unused]] uint8_t mask = 0xFF;
    switch(attribute)
    {
        case EDID_VideoInterface:
        {

            ret = get_bits(0xF, 0x0, block[20]);
        }
        case EDID_SAD_AudioFormatCode:
        {
        }
        case EDID_SAD_SuppNumChannels:
        {
        }
        case EDID_SAD_SampleFreq:
        {

        }
        case EDID_SAD_BitDepth:
        {
        }

    }

    return ret;
}

uint8_t get_bits(uint8_t mask, uint8_t bitStartPos, uint8_t value)
{
    printf("Starting bit position: 0x%x\n", value);
    uint8_t ret = (mask & value) >> bitStartPos;
    printf("Ending bit position: 0x%x\n", ret);
    return ret;
    
}
