#ifndef MIDI_H
#define MIDI_H

typedef uint32_t UMP_word;

typedef struct {
    uint8_t num_words;
    UMP_word **words;
} UMP;

UMP *init_UMP(uint32_t **byte_stream, uint8_t num_words);
void free_UMP(UMP *p);

#endif