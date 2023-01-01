#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include "include/midi.h"

/** This C file contains methods to interface with reading MIDI packets. 
* MIDI protocol information can be found in the /SPECS directory.
*/

/** Returns the 1st, 2nd, etc. byte of PACKET. Note this is indexed starting at byte 1,
* NOT zero-indexed, and that the bytes in packet are ordered 1st byte = 8 left-most bits.
*/
uint8_t get_byte(UMP *packet, uint8_t byte_num) {
    uint8_t idx = floor((byte_num - 1) / 4);  // with 32-bit 4-byte words.
    UMP_word word = packet->words[idx];
    uint8_t bit_offset = 24 - (byte_num - 1) % 4 * 8;
    return (word >> bit_offset) & 0xFF;
}

/** Returns the MESSAGE_TYPE determined from the first (and occassionally second) 
* bytes in a packet. */
MESSAGE_TYPE get_message_type(UMP *packet) {
    MESSAGE_TYPE mt;
    switch (get_byte(packet, 1)) {
        case 0x0: mt = UTILITY; break;
        case 0x1: 
            UMP_word byte_2 = get_byte(packet, 2);
            if (byte_2 <= 0xF6) {
                mt = SYSTEM_COMMON;
            } else {
                mt = SYSTEM_REAL_TIME;
            }
            break;
        case 0x2: mt = MIDI_1_CHNL_VOICE; break;
        case 0x3: mt = DATA_64_BIT; break;
        case 0x4: mt = MIDI_2_CHNL_VOICE; break;
        case 0x5: mt = DATA_128_BIT; break;
        default: 
            fprintf(stderr, "Unrecognized message type 0x%X\n", get_byte(packet, 1));
            // exit(EXIT_FAILURE);   exit?
    }
    return mt;
}

/** Returns a pointer to a Universal Midi Packet UMP with a 
* number of NUM_WORDS 32-bit words. 
*/
UMP *init_UMP(uint32_t *byte_stream, uint8_t num_words) {
    if (num_words > 4) {
        fprintf(stderr, "128-bit+ packets have yet to be implemented. ");
        exit(EXIT_FAILURE);
    }
    // TODO: check for NULL malloc
    UMP *p = (UMP *) malloc(sizeof(UMP));
    p->num_words = num_words;
    p->words = malloc(sizeof(UMP_word) * num_words);
    for (int i = 0; i < num_words; i += 1) {
        p->words[i] = byte_stream[i];  // use memcpy instead?
    }
    p->msg_type = get_message_type(p);
    return p;
}

/** Deallocates memory for a UMP. */
void free_UMP(UMP *p) {
    // TODO: update this as time goes on
    free (p->words);
    free(p);
}