#include "morse.h"
#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>
#include <util/delay.h>

int main() {
    init();

    uint8_t text_count = 2;
    char* texts[text_count];
    texts[0] = "abc abc";
    texts[1] = "sos ";

    char *morse_texts[text_count];

    for(uint8_t i=0;i<text_count;i++) {
        morse_texts[i] = create_morse_array(texts[i]);
    }

    morse(morse_texts, text_count);
}


