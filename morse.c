#include "morse.h"
#include <util/delay.h>
#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>

/*
 * s == dot
 * l == dash
 * w == word pause
 */
char* symbols[27];
void init() {
    MORSE_DDR = 0xFF;
    MORSE_PORT = 0x00;

    symbols[0] = "sl";
    symbols[1] = "lsss";
    symbols[2] = "lsls";
    symbols[3] = "lss";
    symbols[4] = "s"; /* e */
    symbols[5] = "ssls";
    symbols[6] = "lls";
    symbols[7] = "ssss"; /* h */
    symbols[8] = "ss";
    symbols[9] = "slll"; /* j */
    symbols[10] = "lsl";
    symbols[11] = "slss";
    symbols[12] = "ll";
    symbols[13] = "ls";
    symbols[14] = "lll";
    symbols[15] = "slls";
    symbols[16] = "llsl"; /* q */
    symbols[17] = "sls";
    symbols[18] = "sss";
    symbols[19] = "l";
    symbols[20] = "ssl";
    symbols[21] = "sssl"; /* v */
    symbols[22] = "sll";
    symbols[23] = "lssl";
    symbols[24] = "lsll";
    symbols[25] = "llss";

    symbols[26] = "w";


    symbols[27] = "lllll";
    symbols[28] = "sllll";
    symbols[29] = "sslll";
    symbols[30] = "sssll";
    symbols[31] = "ssssl";
    symbols[32] = "sssss";
    symbols[33] = "lssss";
    symbols[34] = "llsss";
    symbols[35] = "lllss";
    symbols[36] = "lllls";
}

char* create_morse_array(char *string) {
    uint16_t length=0;

    /* determine length of string */
    for(uint16_t i=0;string[i] != '\0';i++) {
        uint8_t c = string[i];

        if(c >= 'a' && c <= 'z') {
            c -= 'a';
        } else if(c == ' ') {
            c = 26;
        } else if(c >= '0' && c <= '9') {
            c = c - '0' + 27;
        }

        /* determine length of symbol */
        uint8_t j=0;
        for(;symbols[c][j] != '\0';j++);

        length += j;

    }

    char* morse_string = malloc((sizeof(char) * length)+1);
    morse_string[length] = '\0';
    uint8_t string_pos = 0;

    for(uint16_t i=0;string[i] != '\0';i++) {
        uint8_t c = string[i];
        if(c >= 'a' && c <= 'z') {
            c -= 'a';
        } else if(c == ' ') {
            c = 26;
        } else if(c >= '0' && c <= '9') {
            c = c - '0' + 27;
        }


        /* add symbols of character */
        for(int j=0;symbols[c][j] != '\0';j++) {
            morse_string[string_pos] = symbols[c][j];
            string_pos++;
        }
    }

    return morse_string;
}

void morse(char** strings, uint8_t string_count) {

    uint16_t *positions = malloc(sizeof(uint16_t) * string_count);
    uint8_t *countdown = malloc(sizeof(uint8_t) * string_count);

    for(uint8_t j=0;j<string_count;j++) {
        positions[j] = 0;
        countdown[j];
    }

    while(1) {

        for(uint8_t i=0;i<string_count;i++) {

            if(countdown[i] == 0) {
                char c = strings[i][positions[i]];
                positions[i]++;

                /* if we reached the end of the string start at the beginning */
                if(c == '\0') {
                    positions[i] = 0;
                    continue;
                }

                switch(c) {
                    case 's':
                        set_pin(i, ON);
                        countdown[i] = TIME_DOT+TIME_PAUSE;
                        break;
                    case 'l':
                        set_pin(i, ON);
                        countdown[i] = TIME_DASH+TIME_PAUSE;
                        break;
                    case 'w':
                        set_pin(i, OFF);
                        countdown[i] = TIME_WORD_PAUSE;
                        break;
                }
            } else if(countdown[i] == TIME_PAUSE) {
                set_pin(i, OFF);
            }

            countdown[i]--;

        }
        _delay_ms(TIME_QUANTA);
    }
}

void set_pin(uint8_t pin, uint8_t val) {
    if(val == ON)
        MORSE_PORT |= 1<<pin;
    else
        MORSE_PORT &= ~(1<<pin);
}

