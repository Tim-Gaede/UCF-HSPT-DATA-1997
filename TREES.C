/******************************************************************/
/* Eleventh Annual UCF ACM UPE High School Programming Tournament */
/* May 2, 1997                                                    */
/*                                                                */
/* Judges' solution to the problem "Mike Likes to Climb Trees"    */
/*                                                                */
/* Original problem idea by Glenn Martin                          */
/* Solution by Michael J. Smith                                   */
/******************************************************************/

#include <stdio.h>
#include <stdlib.h>

void main()
{
  FILE *fin, *fout;
  int num_sets, num_limbs, i, j, max, current_limb;


  // Open the file
  fin = fopen("trees.in", "rt");

  if (fin == NULL) { printf("error opening file.\n"); return; }

  // read the number of data sets
  fscanf(fin, "%d", &num_sets);

  // process each data set
  for (i=0;i<num_sets;i++)
  {
    // read the number of limbs (of the tree, not Mike)
    fscanf(fin, "%d", &num_limbs);
    // Set the max height to zero
    max = 0;
    // process each limb
    for(j=0;j<num_limbs;j++)
    {
      // read a limb height
      fscanf(fin, "%d", &current_limb);
      // if this limb is higher than the previous max, set the
      // new max to this limb
      if (current_limb > max)
        max = current_limb;
    }
    // print the output for this tree
    printf("Look at or below height %d\n", max);
  }
}

