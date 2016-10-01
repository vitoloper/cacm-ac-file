/* MAIN PROGRAM FOR DECODING. */

#include <stdio.h>
#include <stdlib.h>
#include "model.h"

main(int argc, char *argv[])
{   
    FILE *input_fp; // File containing the model

    if (argc < 2) {
        fprintf(stderr, "Usage: %s input-model-file\n", argv[0]);
        exit(1);
    }

    input_fp = fopen(argv[1], "r");
    if (input_fp == NULL) {
        fprintf(stderr, "Error opening input file\n");
        exit(1);
    }

    start_model_decode(input_fp);               /* Set up other modules.    */
    close(input_fp);
    start_inputing_bits();
    start_decoding();
    for (;;) {                  /* Loop through characters. */
        int ch; int symbol;
        symbol = decode_symbol(cum_freq);   /* Decode next symbol.      */
        if (symbol==EOF_symbol) break;      /* Exit loop if EOF symbol. */
        ch = index_to_char[symbol];     /* Translate to a character.*/
        putc(ch,stdout);            /* Write that character.    */
    }
    exit(0);
}
