#include <stdint.h>

#define F_CPU 16000000
/* time quanta of symbols in ms */
#define TIME_QUANTA 100

/* length of symbols (in time quanta) */
#define TIME_DOT 1
#define TIME_DASH 3
#define TIME_PAUSE 1
#define TIME_WORD_PAUSE 7

#define ON 1
#define OFF 0

#define MORSE_PORT PORTD
#define MORSE_DDR DDRD

char* create_morse_array(char *string);
void morse(char** strings, uint8_t string_count);
void init();
