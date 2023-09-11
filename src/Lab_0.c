#include "Lab_0.h"

uint8_t edid_block[EDID_BLOCK_SIZE] =
{
    0x00,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x0a,0x13,0x45,0x32,0x00,0x00,0x00,0x00,
    0x00,0x18,0x01,0x03,0x80,0x00,0x00,0x78,0x1e,0xee,0x91,0xa3,0x54,0x4c,0x99,0x26,
    0x0f,0x50,0x54,0xff,0xff,0x80,0xd1,0xc0,0xa9,0x40,0xb3,0x00,0x90,0x40,0x81,0x40,
    0x81,0x80,0x81,0x00,0x61,0x40,0x02,0x3a,0x80,0x18,0x71,0x38,0x2d,0x40,0x58,0x58,
    0x45,0x00,0x00,0x00,0x00,0x00,0x00,0x1e,0x02,0x3a,0x80,0xd0,0x72,0x38,0x2d,0x40,
    0x10,0x2c,0x45,0x80,0x00,0x00,0x00,0x00,0x00,0x1e,0x00,0x00,0x00,0xfc,0x00,0x45,
    0x32,0x0a,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xfd,
    0x00,0x17,0x78,0x0f,0xa0,0x3c,0x00,0x0a,0x20,0x20,0x20,0x20,0x20,0x20,0x01,0xaf,
    0x02,0x03,0x35,0xF2,0x23,0x0D,0x16,0x07,0x6D,0x03,0x0C,0x00,0x10,0x00,0xB8,0x42,
	0x20,0x00,0x60,0x03,0x02,0x01,0x67,0xD8,0x5D,0xC4,0x01,0x77,0x80,0x00,0x51,0x90,
	0x05,0x04,0x13,0x14,0x9F,0x20,0x5D,0x5E,0x5F,0x60,0x61,0x62,0x63,0x64,0x65,0x66,
	0xE4,0x0F,0x00,0xFC,0x0F,0x02,0x3A,0x80,0x18,0x71,0x38,0x2D,0x40,0x58,0x2C,0x45,
	0x00,0x00,0x00,0x00,0x00,0x00,0x1E,0x01,0x1D,0x00,0x72,0x51,0xD0,0x1E,0x20,0x6E,
	0x28,0x55,0x00,0x00,0x00,0x00,0x00,0x00,0x1E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x24    
};

const char* interface[NUM_VID_INTERFACES] = {
    "undefined",
    "DVI",
    "HDMIa",
    "HDMIb",
    "MDDI",
    "DisplayPort"
};

const char* audioFormat[NUM_AUD_FORMAT] = {
    "Reserved",
    "Linear Pulse Code Modulation (LPCM)",
    "AC-3",
    "MPEG1 (Layers 1 and 2)",
    "MP3",
    "MPEG2",
    "AAC",
    "DTS",
    "ATRAC",
    "One-bit audio aka SACD",
    "DD+",
    "DTS-HD",
    "MLP/Dolby TrueHD",
    "DST Audio",
    "Microsoft WMA Pro"
};

const char* freq[NUM_FREQUENCIES] = {
    "32kHz",
    "44kHz",
    "48kHz",
    "88kHz",
    "96kHz",
    "176kHz",
    "192kHz"
};

const char* depth[NUM_BIT_DEPTH] = {
    "16 bit",
    "20 bit",
    "24 bit"
};

void print_edid(
    uint8_t version,
    uint8_t revision,
    uint8_t vidInterface,
    uint8_t audioformatcode,
    uint8_t numberchannels,
    uint8_t supportedFrequencies,
    uint8_t bitDepth)
{
    printf("Printing Info on EDID Version: %X.%X\n", version, revision);
    printf("\tVideo Interface: 0x%X -> %s\n",vidInterface, interface[vidInterface]);
    printf("\tAudio Format Code: 0x%X -> %s\n", audioformatcode, audioFormat[audioformatcode]);
    printf("\tSupported Number of channels: %X Channels\n", numberchannels+1);
    printf("\tSupported Sample Frequencies:\n");
    print_edid_values(NUM_FREQUENCIES, freq, supportedFrequencies);
    printf("\tSupported Bit Depths:\n");
    print_edid_values(NUM_BIT_DEPTH, depth, bitDepth); 
}

uint8_t get_edid_attribute(const uint8_t* block, eEDID_Attribute attribute)
{
    uint8_t ret = 0;
    switch(attribute)
    {
        case EDID_VideoInterface:
        {
            ret = get_bits(0xF, 0x0, block[20]);
            break;
        }
        case EDID_SAD_AudioFormatCode:
        {
            ret = get_bits(0xF, 0x3, block[133]);
            break;
        }
        case EDID_SAD_SuppNumChannels:
        {
            ret = get_bits(0x7, 0x0, block[133]);
            break;
        }
        case EDID_SAD_SampleFreq:
        {
            ret = get_bits(0x7f, 0x0, block[134]);
            break;
        }
        case EDID_SAD_BitDepth:
        {
            ret = get_bits(0x7, 0x0, block[135]);
            break;
        }
        case EDID_Version:
        {
            ret = get_bits(0xF, 0x0, block[18]);
            break;
        }
        case EDID_Revision:
        {
            ret = get_bits(0xF, 0x0, block[19]);
            break;
        }

    }

    return ret;
}

uint8_t get_bits(const uint8_t mask, const uint8_t bitStartPos, const uint8_t value)
{
    uint8_t ret = (value >> bitStartPos) & mask;
    return ret;
}

void print_edid_values(const uint8_t size, const char** attributeList, const uint8_t value)
{
    for(size_t i = 0; i < size; i++)
    {
        uint8_t supported = (value >> i) & 1;
        if(supported)
            printf("\t\t%s\n", attributeList[i]);
    }
}

void set_edid_attribute(uint8_t* block, eEDID_Attribute attribute, uint8_t setValue)
{
     switch(attribute)
    {
        case EDID_VideoInterface:
        {
            set_bits(block, 0xF,0x0, setValue, 20);
            break;
        }
        case EDID_SAD_AudioFormatCode:
        {
            break;
        }
        case EDID_SAD_SuppNumChannels:
        {
            set_bits(block, 0x7, 0x0, setValue, 133);
            break;
        }
        case EDID_SAD_SampleFreq:
        {
            set_bits(block, 0x7F, 0x0, setValue, 134);
            break;
        }
        case EDID_SAD_BitDepth:
        {
            set_bits(block, 0x7, 0x0, setValue, 135);
            break;
        }
        case EDID_Version:
        {
            break;
        }
        case EDID_Revision:
        {
            break;
        }

    }
}

void set_bits(uint8_t* block, uint8_t mask, uint8_t bitStartPos, uint8_t setValue, uint8_t setPos)
{
    uint8_t clearedValue = block[setPos] & ~(mask << bitStartPos); 
    uint8_t newBits = setValue << bitStartPos;                      
    block[setPos] = clearedValue | newBits;   
}

void run_lab0()
{
    uint8_t edidVersion  = get_edid_attribute(edid_block, EDID_Version);
    uint8_t edidRevision = get_edid_attribute(edid_block, EDID_Revision);
    uint8_t vidInterface = get_edid_attribute(edid_block, EDID_VideoInterface);
    uint8_t afc          = get_edid_attribute(edid_block, EDID_SAD_AudioFormatCode);
    uint8_t numChan      = get_edid_attribute(edid_block, EDID_SAD_SuppNumChannels);
    uint8_t supFreq      = get_edid_attribute(edid_block, EDID_SAD_SampleFreq);
    uint8_t bitDepth     = get_edid_attribute(edid_block, EDID_SAD_BitDepth);

    print_edid(
        edidVersion,
        edidRevision,
        vidInterface,
        afc,
        numChan,
        supFreq,
        bitDepth);

    printf("\n==================== Set Values======================\n\n");

    set_edid_attribute(edid_block, EDID_VideoInterface, 0x5);
    set_edid_attribute(edid_block, EDID_SAD_SuppNumChannels, 0x1);
    set_edid_attribute(edid_block, EDID_SAD_SampleFreq, 0x4);
    set_edid_attribute(edid_block, EDID_SAD_BitDepth, 0x4);

    vidInterface = get_edid_attribute(edid_block, EDID_VideoInterface);
    numChan      = get_edid_attribute(edid_block, EDID_SAD_SuppNumChannels);
    supFreq      = get_edid_attribute(edid_block, EDID_SAD_SampleFreq);
    bitDepth     = get_edid_attribute(edid_block, EDID_SAD_BitDepth);

    print_edid(
        edidVersion,
        edidRevision,
        vidInterface,
        afc,
        numChan,
        supFreq,
        bitDepth);
}

static void fileSpecificFunction(const uint32_t addValue)
{
    static uint32_t baseNum;
    baseNum += addValue;
    printf("%d\n", baseNum);
}

void runStaticFunction(const uint32_t add )
{
    fileSpecificFunction(add);
}