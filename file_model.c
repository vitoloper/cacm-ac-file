/* THE FILE (EXACT) MODEL */

#include <stdio.h>
#include <stdlib.h>
#include "model.h"

#define INIT_FREQUENCY 0

int freq[No_of_symbols+1];  /* Symbol frequencies */


/* INITIALIZE THE FREQUENCY ARRAY */

void init_freq(FILE *fp)
{
    int ch;
    int i;

    /* Read input file until EOF */
    for (;;) {
        ch = getc(fp);
        if (ch == EOF) {
            freq[No_of_symbols]++;
            break;
        }

        freq[ch+1]++;
    }
}

/* INITIALIZE THE MODEL. */

start_model_encode(FILE *fp, FILE *fp_model)
{   
    int i;
    for (i = 0; i<No_of_chars; i++) {       /* Set up tables that       */
        char_to_index[i] = i+1;         /* translate between symbol */
        index_to_char[i+1] = i;         /* indexes and characters.  */
    }

    init_freq(fp);      /* Initialize the frequency array */
    /* Write model to file */
    fwrite(freq, (No_of_symbols+1)*sizeof (int), 1, fp_model);

    cum_freq[No_of_symbols] = 0;
    for (i = No_of_symbols; i > 0 ; i--) {  /* Set up cumulative frequency counts */
        cum_freq[i-1] = cum_freq[i] + freq[i];
    }

    /* for(i = 0; i < No_of_symbols+1; i++) {
        fprintf(stderr, "freq[%d] = %d\n", i, freq[i]);
    } */

    /* Halve all counts if frequency counts are at their maximum. */
    while (cum_freq[0] >= Max_frequency) {
            /* fprintf(stderr, "cum_freq[0]: %d - Halving!\n", cum_freq[0]); */
            int cum;
            cum = 0;
            for (i = No_of_symbols; i>=0; i--) {
                if (freq[i] == 1) {
                    freq[i] = (freq[i]+1)/2;
                } else {
                    freq[i] = (freq[i])/2;
                }
                cum_freq[i] = cum;
                cum += freq[i];
            }
    }

    /* for(i = 0; i < No_of_symbols+1; i++) {
        fprintf(stderr, "cum_freq[%d] = %d\n", i, cum_freq[i]);
    } */

    if (cum_freq[0] > Max_frequency) {
        printf("Cumulative frequency exceeded Max_frequency\n");
        exit(1);
    }

}

start_model_decode(FILE *fp)
{
    int result;
    int i;

    for (i = 0; i<No_of_chars; i++) {       /* Set up tables that       */
        char_to_index[i] = i+1;         /* translate between symbol */
        index_to_char[i+1] = i;         /* indexes and characters.  */
    }

    result = fread(freq, (No_of_symbols+1)*sizeof (int), 1, fp);
    /* fprintf(stderr, "Number of items read: %d\n", result); */

    /* for(i = 0; i < No_of_symbols+1; i++) {
        fprintf(stderr, "freq[%d] = %d\n", i, freq[i]);
    } */

    cum_freq[No_of_symbols] = 0;
    for (i = No_of_symbols; i > 0 ; i--) {  /* Set up cumulative frequency counts */
        cum_freq[i-1] = cum_freq[i] + freq[i];
    }

    // Halve frequency counts
    while (cum_freq[0] >= Max_frequency) {       /* See if frequency counts  */
            /* fprintf(stderr, "cum_freq[0]: %d - Halving!\n", cum_freq[0]); */
            int cum;                /* are at their maximum.    */
            cum = 0;
            for (i = No_of_symbols; i>=0; i--) {    /* If so, halve all the     */
                if (freq[i] == 1) {
                    freq[i] = (freq[i]+1)/2;
                } else {
                    freq[i] = (freq[i])/2;        /* counts (keeping them     */
                }
                cum_freq[i] = cum;          /* non-zero).               */
                cum += freq[i];
            }
    }

    if (cum_freq[0] > Max_frequency) {
        printf("Cumulative frequency exceeded Max_frequency\n");
        exit(1);
    }

    /* for(i = 0; i < No_of_symbols+1; i++) {
        fprintf(stderr, "cum_freq[%d] = %d\n", i, cum_freq[i]);
    } */
}
