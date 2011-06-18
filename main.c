#include "morse.h"
#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>
#include <util/delay.h>

int main() {
    init();

    char* texts[2];
    texts[0] = "explosion zwischen see und gebirge";
    texts[1] = "explosion zwischen baum und gebirge";

    /* translate texts */
    char *morse_texts[2];
    for(uint8_t i=0;i<2;i++) {
        morse_texts[i] = create_morse_array(texts[i]);
    }

    /* send morse code */
    morse(morse_texts, 2);
}

