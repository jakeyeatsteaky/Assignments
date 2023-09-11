#ifndef LAB_0_H
#define LAB_0_H

#include <stdint.h>
#include <stdio.h>

#define EDID_BLOCK_SIZE 256
#define NUM_VID_INTERFACES 6
#define NUM_AUD_FORMAT 15
#define NUM_FREQUENCIES 7
#define NUM_BIT_DEPTH 3

extern uint8_t edid_block[EDID_BLOCK_SIZE];
extern const char* interface[NUM_VID_INTERFACES];
extern const char* audioFormat[NUM_AUD_FORMAT];
extern const char* freq[NUM_FREQUENCIES];
extern const char* depth[NUM_BIT_DEPTH];

typedef enum
{
    EDID_VideoInterface = 0,
    EDID_SAD_AudioFormatCode = 1,
    EDID_SAD_SuppNumChannels = 2,
    EDID_SAD_SampleFreq = 3,
    EDID_SAD_BitDepth = 4,
    EDID_Version = 5,
    EDID_Revision = 6
}eEDID_Attribute;

void print_edid(
    uint8_t version,
    uint8_t revision,
    uint8_t interface,
    uint8_t audioformatcode,
    uint8_t numberchannels,
    uint8_t supportedFrequencies,
    uint8_t bitDepth);

uint8_t get_edid_attribute(const uint8_t* block, eEDID_Attribute attribute);

uint8_t get_bits(const uint8_t mask, const uint8_t bitStartPos, const uint8_t value);

void print_edid_values(const uint8_t size, const char** attributeList, const uint8_t value);

void set_edid_attribute(uint8_t* block, eEDID_Attribute attribute, uint8_t setValue);

void set_bits(uint8_t* block, uint8_t mask, uint8_t bitStartPos, uint8_t setValue, uint8_t setPos);

void run_lab0();

void runStaticFunction(const uint32_t add);

#if 0
NOTES:

Video Interface: Byte 19, bits 0-3
Mask is 3 bits in size (0xf = 0b1111)
Start position is the first 3 bits
    0000 = undefined
    0001 = DVI
    0010 = HDMIa
    0011 = HDMIb
    0100 = MDDI
    0101 = DisplayPort 

AFC is in SAD Byte 1
Bit 7: reserved
Bits [6:3] is Audio format Code
Bits [2:0] is Num channels - 1 (i.e. 000 = 1 channel)
value is in Block 1 (extended) and the first byte after:
      1) Data Block Collection header (4 bytes)
      2) Specific Data Block Header (1 byte)
Mask for AFC is 4 bits (0xF)
start position is bit 3
    1 = Linear Pulse Code Modulation (LPCM)
    2 = AC-3
    3 = MPEG1 (Layers 1 and 2)
    4 = MP3
    5 = MPEG2
    6 = AAC
    7 = DTS
    8 = ATRAC
    0, 15: Reserved 
    9 = One-bit audio aka SACD
    10 = DD+
    11 = DTS-HD
    12 = MLP/Dolby TrueHD
    13 = DST Audio
    14 = Microsoft WMA Pro

Supported Number of channels is in SAD Byte1
Bits [2:0] = num Channels - 1 i.e ooo = 1 channel
Mask is 3 bits = 0x7
value is block 133
start position at 0

Supported Sample Freq is SAD Byte 2:
bit 7 reserved (0)
bits [6:0] enumerate frequencies:
    bit 6: 192kHz
    bit 5: 176kHz
    bit 4: 96kHz
    bit 3: 88kHz
    bit 2: 48kHz
    bit 1: 44kHz
    bit 0: 32kHz
Mask is 7 bits = 0x7F
Starts at bit 0
value is 134 idx

Supported Bit depth for LPCM:
bits [7:3] are reserved
    bit 2: 24 bit
    bit 1: 20 bit
    bit 0: 16 bit
mask is 3 bits = 0x7
bit pos starts at 0
value is SAD Byte 3

Version is at idx 18.  
Mask can be 4 bits
Starts at first bit

Revision is at idx 19
Mask is 4 bits
Starts at first bit

EDID info taken from :
http://www.drhdmi.eu/dictionary/edid.html

#endif
#endif
