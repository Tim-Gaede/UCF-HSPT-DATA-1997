/******************************************************************/
/* Eleventh Annual UCF ACM UPE High School Programming Tournament */
/* May 2, 1997                                                    */
/*                                                                */
/* Judges' solution to the problem "Digging Ditches"              */
/*                                                                */
/* Original problem idea by Peter Singhofen                       */
/* Solution by Michael J. Smith                                   */
/******************************************************************/

#include <stdio.h>
#include <stdlib.h>

void main()
{
  int num,i;
  float val1, val2, length, volume;
  FILE *fin;

  // open the input file
  fin = fopen("ditch.in", "rt");
  if (fin == NULL) { printf(" error opening input file.\n"); return; }
  
  // Read the number of ditches
  fscanf(fin, "%d", &num);

  // process each ditch
  for(i=0;i<num;i++)
  {
    // read in the two areas and the length between them
    fscanf(fin, "%f %f %f", &val1, &val2, &length);
    // compute the volume (average the two areas and multiply by length)
    volume = (val1 + val2)*0.5*length;
	printf("%.1f\n", volume);
  }
}

