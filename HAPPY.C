/******************************************************************/
/* Eleventh Annual UCF ACM UPE High School Programming Tournament */
/* May 2, 1997                                                    */
/*                                                                */
/* Judges' solution to the problem "Happiness Man"                */
/*                                                                */
/* Original problem idea by Eric Heimburg                         */
/* Solution by Rajkumar Madhuram                                  */
/******************************************************************/

#include <stdio.h>
#include <string.h>
#define MAXVILL 5

char names[MAXVILL][80];    /* evil names */
int  evil[MAXVILL];
int  weight[MAXVILL];
int  whichone[MAXVILL], solution[MAXVILL];
/* evil and weight contains the evilness and weight of the enemies */
/* whichone is the binary vector containing a combination */
/* solution is the binary vector containing the best feasible combination */

void solve(int numvill);

void main()
 {
   int i, evilness, villweight, nvill;
   char villname[80];
   FILE *fp;

   fp = fopen("happy.in", "r");
   while (1)
    {
      fscanf(fp, "%d\n", &nvill);
      if (nvill == 0) break;
	  for (i=0; i<nvill; i++)
	   {
		 fgets(villname, 80, fp);
		 villname[strlen(villname)-1] = 0;
		 fscanf(fp, "%d %d\n", &evilness, &villweight);
		 strcpy(names[i], villname);
		 evil[i] = evilness;
		 weight[i] = villweight;
	  }

	 solve(nvill);  /* Returns the best combination in 'solution' */

	 for (i=0; i<nvill; i++)
	  {
		printf("Use the ");
		if (solution[i] == 0) printf("Happiness");
		 else printf("Pulping");
		printf(" Ray on %s\n", names[i]);
	  }
	 printf("\n");
	}
   fclose(fp);
 }


void solve(int numvill)
 {
  int i, j, ecost, wcost;
  int maxcases, carry;
  int minpulps, npulps;

  for (i=0; i<numvill; i++)   /* initialise */
	whichone[i] = solution[i] = 0;

  minpulps = MAXVILL;

  maxcases = 1 << numvill;   /* 2^numvill */

  for (i=0; i<maxcases; i++)
   {
	 ecost = 0; wcost = 0;

	 for (j=0; j<numvill; j++)
	  {
	   if (whichone[j] == 0) ecost += evil[j];
		else wcost += weight[j];
	  }

	 if ((ecost <= 50) && (wcost <= 500))  /* valid solution */
	  {
	   npulps = 0;
	   for (j=0; j<numvill; j++)
		if (whichone[j] == 1) npulps++;
	   if (npulps <= minpulps)  /* Is this the best solution ?  */
		{
		 for (j=0; j<numvill; j++) solution[j] = whichone[j];
		 minpulps = npulps;  /* Retain the best solution */
		}
	  }

	/* Add 1 to the binary representation to get the next possible combination */
	 carry = 1;
	 for (j=numvill-1; j>=0; j--)
	  {
		whichone[j] += carry;
		if (whichone[j] == 2) { whichone[j] = 0; carry = 1; }
		else carry = 0;
      }
   }

 }

