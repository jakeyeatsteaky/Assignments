#ifndef LAB_0_H
#define LAB_0_H

#include <stdint.h>
#include <stdio.h>
typedef enum
{
  EDID_VideoInterface = 0,
  EDID_SAD_AudioFormatCode = 1,
  EDID_SAD_SuppNumChannels = 2,
  EDID_SAD_SampleFreq = 3,
  EDID_SAD_BitDepth = 4
}eEDID_Attribute;

extern const unsigned int EDID_BLOCK_SIZE;

uint8_t parse_edid(uint8_t* block, eEDID_Attribute attribute);

uint8_t get_bits(uint8_t mask, uint8_t bitStartPos, uint8_t value);

void set_edid(uint8_t* block, uint8_t offset, uint8_t set);

#endif
