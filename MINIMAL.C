/******************************************************************/
/* Eleventh Annual UCF ACM UPE High School Programming Tournament */
/* May 2, 1997                                                    */
/*                                                                */
/* Judges' solution to the problem "A Minimal Problem"            */
/*                                                                */
/* Original problem idea by everybody                             */
/* Solution by Travis Terry                                       */
/******************************************************************/

/*
        This is the C/C++ solution to 'A Minimal Problem'.  Note long
        integers are used to handle the input case 32767 -32768, because
        the result, 65535, it too large for a signed 16-bit integer.
*/

/*  These are the standard include files needed for file I/O  */
#include <stdio.h>
#include <stdlib.h>

/*
    function: Max

    input:      two long integers, a and b
    output:     the larger of 'a' and 'b'
*/

long Max ( long a, long b )
{
    long result;                        /*  the result of the function      */

    if ( a > b )                        /*  a is larger than b              */
        result = a;
    else                                /*  b is at least as large as a     */
        result = b;

    return result;                      /*  return the maximum of a and b   */
}

/*
    function: main

    input:      none
    output:     error result to the OS
*/
int main ( void )
{
    FILE *inf;                          /*  input stream                    */
    int N,                              /*  number of data sets             */
	i;                              /*  a loop variable                 */
    long a, b,                          /*  the two numbers for a data set  */
	 maximum;                       /*  the maximum of the two numbers  */

    inf = fopen ( "minimal.in", "rt" ); /*  open input file                 */

    if ( inf == NULL )                  /* check to make sure files exist   */
    {
	fprintf ( stderr, "Could not open input or output file\n" );
	return 1;                       /* exit the program                 */
    }

    /* if the input file exists, assume the judge input is valid from here  */
    fscanf ( inf, "%d\n", &N );         /*  read number of data sets        */

    for ( i=0; i<N; i++ )               /*  for each data set do:           */
    {
	fscanf ( inf, "%ld %ld\n", &a, &b );    /*  read data set           */

	maximum = Max ( Max(a,b), a-b );        /*  compute the maximum
						    of a, b, and (a-b)      */
	printf ( "%ld\n", maximum );            /*  print the result        */
    }

    fclose ( inf );                     /* close input file                 */

    return 0;
}
