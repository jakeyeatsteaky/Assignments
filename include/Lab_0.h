#include <stdint.h>

#if 0 

Demo: Write a functions that gets the following information from the EDID block:
1. Video Interface
2. SAD: Audio Format Code
3. SAD: Supported Number of channels
4. SAD: Supported Sample Frequencies
5. SAD: Supported Bit Depth

#endif

void parse_edid(uint8_t* block);

#if 0

Demo: Write a functions that will set the following information to the EDID block:
1. Video Interface = DisplayPort
2. SAD: Supported Number of channels = 2
3. SAD: Supported Sample Frequencies = only 48KHz
4. SAD: Supported Bit Depth = only 24 bit

#endif

void set_edid(uint8_t* block, uint8_t offset, uint8_t set);


