/******************************************************************/
/* Eleventh Annual UCF ACM UPE High School Programming Tournament */
/* May 2, 1997                                                    */
/*                                                                */
/* Judges' solution to the problem "The Cycle of Life"            */
/*                                                                */
/* Original problem idea by Rajkumar Madhuram                     */
/* Solution by Peter Singhofen                                    */
/******************************************************************/

#include <stdio.h>
#include <string.h>

// This array stores when we have been to each state.  States are
// assumed to be binary integers for storage purposes.
int been[16384];


int step;


// This checks a state (represented as a string).  If it is all 0's
// then the state has "died out".
int IsDead(char *s) {
  int c;
  for (c=0;c<strlen(s);c++)
    if (s[c]!='0') return(0);
  return(1);
}

// This converts the state (represented as a string) to an integer
// by assuming the state is a binary integer.
int AsInt(char *s) {
  int val=0,c=0,p=1;
  for (c=strlen(s)-1;c>=0;c--,p*=2)
    if (s[c]=='1') val+=p;
  return(val);
}


// This "evolves" the state by the rules given in the problem spec.
void Evolve(char *s) {
  char old[15];
  int c;
  strcpy(old,s);
  for (c=1;c<strlen(s)-1;c++)
    if (old[c-1]==old[c+1])
      s[c] = '0';
    else
      s[c] = '1';
}


void main() {
  FILE *f;
  char s[15];
  int done, c;

  f=fopen("LIFE.IN","rt");

  while (!feof(f)) {
    fscanf(f,"%s",s);
    step=1; done=0;

    // Initialize the been array.  0 means we have never seen this state.
    for (c=0;c<16384;c++)
      been[c] = 0;

    printf("%s ",s);

    // evolve the state until it dies out or we detect a cycle.
    while (!done) {

      if (IsDead(s)) {
	printf("dies out.\n");
        done=1;
      } else {
        // convert state to integer.
        c=AsInt(s);
        if (been[c]) {
          // We've seen this state before...
	  // compute the cycle length.  Its the current step minus
          // the step last time we saw this state.
          printf("has a period of %d units.\n",step-been[c]);
          done=1;
        } else {
          // This is the first time we've seen this state.
	  // Set the been array for this state to the current step.
          been[AsInt(s)]=step++;
          // Evolve the state.
          Evolve(s);
        }
      }
    }
  }
}
