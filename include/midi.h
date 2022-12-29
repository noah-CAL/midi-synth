#ifndef MIDI_H
#define MIDI_H

#include <stdint.h>

#define UMP_word uint32_t

typedef struct {
    uint8_t num_words;
    UMP_word **words;
} UMP;

UMP *init_UMP(UMP_word **byte_stream, uint8_t num_words);
void free_UMP(UMP *p);

#endif