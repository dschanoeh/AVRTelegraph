#include "morse.h"
#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>
#include <util/delay.h>

int main() {
    init();

    char* texts[2];
    texts[0] = "attack at midnight";
    texts[1] = "sos we are sinking";

    /* translate texts */
    char *morse_texts[2];
    for(uint8_t i=0;i<text_count;i++) {
        morse_texts[i] = create_morse_array(texts[i]);
    }

    /* send morse code */
    morse(morse_texts, 2);
}

