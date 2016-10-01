/* MAIN PROGRAM FOR ENCODING. */

#include <stdio.h>
#include <stdlib.h>
#include "model.h"

main(int argc, char *argv[])
{   
    FILE *input_fp;     /* The file from which the model is calculated */
    FILE *output_fp;    /* The file that will contain the calculated model */

    if (argc < 3) {
        fprintf(stderr, "Usage: %s inputfile outputmodelfile\n", argv[0]);
        exit(1);
    }

    input_fp = fopen(argv[1], "r");
    if (input_fp == NULL) {
        fprintf(stderr, "Error opening input file\n");
        exit(1);
    }

    output_fp = fopen(argv[2], "w");
    if (output_fp == NULL) {
        fprintf(stderr, "Error opening file for model writing");
        exit(1);
    }

    start_model_encode(input_fp, output_fp);            /* Set up other modules.    */
    fclose(output_fp);
    rewind(input_fp);   /* Set the file position indicator to the beginning of the file. */
    start_outputing_bits();
    start_encoding();
    for (;;) {                  /* Loop through characters. */
        int ch; int symbol;
        ch = getc(input_fp);           /* Read the next character from file. */
        if (ch==EOF) break;         /* Exit loop on end-of-file.*/
        symbol = char_to_index[ch];     /* Translate to an index.   */
        encode_symbol(symbol,cum_freq);     /* Encode that symbol.      */
    }
    encode_symbol(EOF_symbol,cum_freq);     /* Encode the EOF symbol.   */
    done_encoding();                /* Send the last few bits.  */
    done_outputing_bits();
    fclose(input_fp);   /* Close input file */
    exit(0);
}
