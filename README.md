AVRTelegraph
============

AVRTelegraph is a telegraph simulator for the ATMEL 8bit microcontroller family. 
It is able to send up to 8 strings in morse code on single pins of the controller.
The transmission takes part in parallel and each string is repeated infinitely.

### Build
A configurable Makefile for different controllers is included. You will need the default avr packets like
avr-libc, avrdude and gcc-avr.

### Configuration
The symbols, the symbol timings of the morse code and the transfer speed are configurable in morse.h

    /* speed of the CPU */
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

    /* PORT and DDR on which morse code is sent */
    #define MORSE_PORT PORTD
    #define MORSE_DDR DDRD

### Sending

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
