/******************************************************************/
/* Eleventh Annual UCF ACM UPE High School Programming Tournament */
/* May 2, 1997                                                    */
/*                                                                */
/* Judges' solution to the problem "Invoke the OrACKle"           */
/*                                                                */
/* Original problem idea by Drue Pautz (modified by Glenn Martin) */
/* Solution by Michael Kujawa                                     */
/******************************************************************/

/*
The Input:

  Each line of the input file will be a command (ADD, VFLIP, HFLIP, REPAINT or 
  CLEAR).  The ADD command will be followed by additional parameters: x, y, and
  the rest of the line will be the text to display.  Note that the starting 
  position, direction and text parameters of the ADD command will separated by a 
  single space.

The Output:

  For each REPAINT command, output the state of the display.


Method of Solution:

  To choose a good solution, you must first see all the possibilities for input.
  The limits on the values of x and y are not specified.  They can, in fact, be 
  any integer.  I also choose a solution which is independant of line length.
  Even though we (eventually) limited the line length, this solution has been
  tested on a line that was 90k long!  (We took that case out of the input.)

  I choose to store a virtual screen as an array of 24 strings.  To clear the
  screen, I set each string to a string of 70 periods.  To flip the screen 
  horizontally, I reverse the contents of each string.  To flip the screen 
  vertically, I reverse the order of the strings in the virtual screen.  
  REPAINTing the screen is simply printing all 24 strings.  

  I handle input by reading from the file only what I need to to proceed.  I 
  start by reading the command word, which is terminated by a space or End-of-
  line.  I then see which command it is and execute it.
  
  A little bit more complex is the processing of the ADD command.  After having
  read the command, the file pointer will be left pointing at the starting 
  position, so I can just read those two numbers in.  Next come several 
  characters indicating where to go after placing each character.  I store these
  as offsets in x and y (eg. UR has an x offset of 1 and a y offset of -1.)  
  Finally, the rest of the line is drawn to the virtual screen.  I read it in
  one character at a time, adding to x and y their respective offsets.  When x 
  and y are both on the screen, I assign the character in the virtual screen.

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* The virtual screen */
char Screen[24][71];





/* cls
   This procedure clears the screen to periods.
*/
void cls()
{
    for (int y = 0; y < 24; y++)
    { 
        strcpy(Screen[y],"......................................................................");
    }
}





/* hflip
    This procedure flips the screen horizontally.  Since each line is stored as
    a string, this simply reverses the strings.
*/
void hflip()
{
    for (int y = 0; y < 24; y++)
        strrev(Screen[y]);
}




/* vflip
    This procedure flips the screen vertically by swapping the lines about
    the center.
*/
void vflip()
{
char Temp[256];

    for (int y=0; y < 12; y++)
    {
        strcpy(Temp, Screen[y]);
        strcpy(Screen[y], Screen[23-y]);
        strcpy(Screen[23-y], Temp);
    }
}




/* paint
   This procedure draws the virtual screen to standard output.  
*/
void paint()
{
    for (int y=0; y < 24; y++)
        printf("%s\n", Screen[y]);
}




/* Draw
   Draws the text on to the virtual screen.  Since there is no way to know how
   much text there will be, and it may not be storable in a single array anyway,
   I pass the file pointer and just read the characters out of that.

   Note that to handle really long lines x and y need to be long integers.
   (This problem doesn't require it anymore, but I left the solution the same)
*/
void Draw(long x, long y, int xofs, int yofs, FILE *InFile)
{
char ch = (char)fgetc(InFile);
    
    while ( !feof(InFile) && (ch != '\n') )
    {
        if (ch == ' ')
            ch = '.';
        if ( (x >= 0) && (x < 70) && (y >= 0) && (y < 24) )
            Screen[y][x] = ch;
        x += xofs;
        y += yofs;
        ch = (char)fgetc(InFile);
    }
}





void main()
{
FILE *InFile;
char Command[256];
long x, y;
int xofs, yofs;
char ch;

    cls(); 
    InFile = fopen("orackle.in", "rt");

    while (!feof(InFile) && fscanf(InFile, "%s", Command))
    {
        /* Process the command */
        if (!strncmp(Command, "HFLIP", 5))
            hflip();
        if (!strncmp(Command, "VFLIP", 5))
            vflip();
        if (!strncmp(Command, "REPAINT", 7))
            paint();
        if (!strncmp(Command, "CLEAR", 5))
            cls();
        if (!strncmp(Command, "ADD", 3))
        {
            /* Read x, y, and the first direction character */
            fscanf(InFile, "%ld %ld %c", &x, &y, &ch);
            
            /* Calculate the offsets */
            xofs = yofs = 0;
            while (ch != ' ')
            {
                if (ch == 'U')
                    yofs = -1;
                if (ch == 'L')
                    xofs = -1;
                if (ch == 'D')
                    yofs = 1;
                if (ch == 'R')
                    xofs = 1;
                ch = (char)fgetc(InFile);
            }
            Draw(x-1, y-1, xofs, yofs, InFile);
        }
    }
    fclose(InFile);
}
