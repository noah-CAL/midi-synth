#ifndef MIDI_H
#define MIDI_H

#include <stdint.h>

#define WORD_SIZE_BITS  32
#define WORD_SIZE_BYTES 4
#define UMP_word uint32_t

typedef enum { 
    UTILITY,
    SYSTEM_COMMON,
    SYSTEM_REAL_TIME,
    MIDI_1_CHNL_VOICE,
    DATA_64_BIT,
    MIDI_2_CHNL_VOICE,
    DATA_128_BIT
} MESSAGE_TYPE;

typedef struct {
    uint8_t num_words;
    UMP_word *words;
    MESSAGE_TYPE msg_type;
} UMP;

UMP *init_UMP(UMP_word *byte_stream, uint8_t num_words);
uint8_t get_byte(UMP *packet, uint8_t byte);
void free_UMP(UMP *p);


#endif