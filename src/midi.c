#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include "include/midi.h"

/** This C file contains methods to interface with reading MIDI packets. 
* MIDI protocol information can be found in the /SPECS directory.
*/

/** Returns a pointer to a Universal Midi Packet UMP with a 
* number of NUM_WORDS 32-bit words. 
*/
UMP *init_UMP(uint32_t *byte_stream, uint8_t num_words) {
    if (num_words > 4) {
        fprintf(stderr, "128-bit+ packets have yet to be implemented. ");
        exit(EXIT_FAILURE);
    }
    UMP *p = (UMP *) malloc(sizeof(UMP));
    p->num_words = num_words;
    p->words = malloc(sizeof(UMP_word) * num_words);
    for (int i = 0; i < num_words; i += 1) {
        p->words[i] = byte_stream[i];
    }
    return p;
}

/** Deallocates memory for a UMP. */
void free_UMP(UMP *p) {
    // TODO: update this as time goes on
    free (p->words);
    free(p);
}