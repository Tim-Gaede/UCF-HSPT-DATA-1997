/******************************************************************/
/* Eleventh Annual UCF ACM UPE High School Programming Tournament */
/* May 2, 1997                                                    */
/*                                                                */
/* Judges' solution to the problem "Counting Dashes"              */
/*                                                                */
/* Original problem idea by Michael Kujawa                        */
/* Solution by Joel Davis                                         */
/******************************************************************/
#include <stdio.h>

/****************************************************************************
 * DASHES.C -- Computes the number of dashes a car passes over.
 *
 * Since the car starts at the end of a dash, we can see that the number
 * of whole dashes it crosses is equal to the total distance travelled
 * divided by the combined length of a dash and a gap.
 *
 * The input was allowed to go up to 500,000, so long ints must be used.
 *
 *****************************************************************************/
void main() {
    FILE *fp;
    unsigned long dash_width, gap_width, distance, num_dashes;

    /* Open the input file for reading */
    fp = fopen( "dashes.in","rt");

    /* Read and process input until end of file */
    while (!feof(fp)) {
        fscanf(fp,"%lu %lu %lu", &dash_width, &gap_width, &distance);

        /* Compute the number of complete dashes passed over */
        num_dashes = distance / (dash_width + gap_width);

        /* Output the result */
        printf("%lu\n", num_dashes );
    }

}
