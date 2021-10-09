/******************************************************************/
/* Eleventh Annual UCF ACM UPE High School Programming Tournament */
/* May 2, 1997                                                    */
/*                                                                */
/* Judges' solution to the problem "Smash the Copy Machine!"      */
/*                                                                */
/* Original problem idea by Ali Orooji                            */
/* Solution by Joel Davis                                         */
/******************************************************************/

#include <stdio.h>

/*****************************************************************************
 * SMASH -- Given the number of pages in a document, a number of copies to
 * make and the number of stacks a malfunctioning copier tries to collate them
 * into, print out the contents of each stack.
 *
 * This is just a straightforward simulation of the copier's behavior. There
 * is an array that holds the contents of the stack, and another which holds
 * the size of each stack. These are filled by stepping through the pages
 * and the number of copies of each on the stacks. Then, the stacks are
 * printed.
 *
 */
void main() {
    FILE *fp;          /* The input file */
    int num_pages,     /* The inputs */
        num_copies,
        num_stacks,

        curr_page,    /* The page that we are on            */
        curr_stack,   /* The stack that we are on           */
        page_copies,  /* Number of copies made of this page */
        set,          /* The data set number                */
        i, j;         /* Loop counters                      */

    int stack[10][100]; /* Hold which pages are in which stack */
                        /* There are 10 stacks, each can hold  */
                        /* up to 100 copies.                   */
    int stack_sz[10];  /* Holds how many pages are in each stack */

    /* Open the input file */
    fp = fopen( "smash.in", "rt" );

    /* Initialize the set counter */
    set = 1;
    while (!feof(fp)) {

        /* Read in the inputs from the input file */
        fscanf( fp, "%d %d %d", &num_pages, &num_copies, &num_stacks);

        /* Initialize the simulation variables */
        curr_page = 1;
        curr_stack = 0;
        page_copies = 0;

        /* Set the stacks to be empty */
        for (i = 0; i < 10; i++) stack_sz[i] = 0;

        /* Print a header for this data set */
        printf("Data set %d\n", set++);

        /* Step through the pages until all pages have been copied */
        while (curr_page <= num_pages) {

            /* Place the current page on the current stack, and */
            /* increment the size of the current stack.         */
            stack[curr_stack][stack_sz[curr_stack]++] = curr_page;

            /* Move to the next stack. If we move past the last stack */
            /* go back to the first stack.                            */
            curr_stack++;
            if (curr_stack == num_stacks) curr_stack = 0;

            /* Count this copy */
            page_copies++;

            /* Check to see if enough copies of this page have been made */
            if (page_copies == num_copies) {
               /* If so, move on to the next page and reset the count */
               curr_page++;
               page_copies = 0;
            }
        }

        /* Now all the data is collected. All that is left to do is print */
        /* the contents of each stack.                                    */
        for (i = 0; i < num_stacks; i++) {

            /* Print a title for this stack */
            printf("   Stack%2d: ", i+1);

            /* Print the contents of this stack */
            for (j = 0; j < stack_sz[i]; j++) {
                printf("%d ", stack[i][j]);
            }
            printf("\n");
        }
        /* Print a blank line after each data set */
        printf("\n");
    }
}
