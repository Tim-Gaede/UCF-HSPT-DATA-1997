/******************************************************************/
/* Eleventh Annual UCF ACM UPE High School Programming Tournament */
/* May 2, 1997                                                    */
/*                                                                */
/* Judges' solution to the problem "Psychic Gypsy Battle"         */
/*                                                                */
/* Original problem idea by Eric Heimburg                         */
/* Solution by Phillip Dexheimer                                  */
/******************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
  Program ensures that the gypsy takes the last M&M
  Only one special case: if there is only one M&M to start, the princess can't win
*/

void main (void)
{
 FILE *Infile = fopen ("gypsy.in", "rt");  //Input file
 char *InStr, *p;             //String to read data into. Will parse to find nums
 int Pmove[200], Gmove[200];  // Arrays to hold players' moves. Max should be 255/2
 int count, num;              // Game # and # of M&M's
 int i, j;                    // Loop variables

 count = 0;
 while (!feof(Infile))
 {
  count++;
  InStr = malloc (301);  //Since we don't know the number of moves G will make
  fgets (InStr, 300, Infile); //We'll read it in as a string and parse that
  InStr[strlen(InStr)-1] = 0;
  p = InStr;
  num = atoi (p);
  p = strchr (p, ' ');
  *p++ = 0;
  i = 0;

  // Process gypsy's moves
  while (Gmove[i] = atoi (p)) {
	p = strchr (p, ' ');
	*p++ = 0;
	Pmove[i] = 0;
	i++;}

  free(InStr);
  for (j=i;j<200;j++)
   { Pmove[j] = 0;
	Gmove[j] = 0;}

  if (num == 1) num = 0;
  i = 0;
  while (num)
  { //Make moves
   if (num > 6)   //Take 5 until we get near the end, then figure out how many
	{             //to take.  Remember that G probably won't take her full
	 Pmove[i] = 5;//last turn.
	 if (Pmove[i] + Gmove[i] + 1 >= num) Pmove[i]--;
	 if (Pmove[i] < 1) Pmove[i] = 1;
	}
   else Pmove[i] = num - 1;

   num -= Pmove[i];
   if (Gmove[i] > num) Gmove[i] = num;
   num -= Gmove[i];
   i++;
  }

  printf ("Game #%i:", count);//Print the output.
  if (!Pmove[0]) printf (" The princess cannot win!");
  else
   for (i=0;Pmove[i];i++)
	printf (" P:%i G:%i", Pmove[i], Gmove[i]);
  printf ("\n");
 }
 fclose (Infile);
}
