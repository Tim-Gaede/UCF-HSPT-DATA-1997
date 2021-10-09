/******************************************************************/
/* Eleventh Annual UCF ACM UPE High School Programming Tournament */
/* May 2, 1997                                                    */
/*                                                                */
/* Judges' solution to the problem "Warcraft"                     */
/*                                                                */
/* Original problem idea by Joel Davis                            */
/* Solution by Eric Heimburg                                      */
/******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//Your C++ compiler may not yet support the "bool" keyword, since it is
//relatively new. To make sure this code compiles under older compilers, the
//following macros are used.
#define		bool	int
#define		true	1
#define		false	0 

//The current map is stored in the global 2-d array called Map. The symbols
//are stored in x-by-y order; that is, the first dimension is the horizontal
//position, and the second dimension is the vertical position. Also,
//all C / C++ arrays are 0-based, meaning that the first element in the
//array is numbered 0. Thus, Map[6][0] indicates the 7th column from the left,
//on the topmost row.
char Map[64][64];

//MapWidth and MapHeight store the width and height of the current map. Since
//C arrays are 0-based, the valid range of Map is
//Map[0][0] through Map[MapWidth-1][MapHeight-1].
int MapWidth, MapHeight;


//IsValidMapLocation() is a utility function that determines if a given x-y
//coordinate is in the legal range of the Map.
bool IsValidMapLocation(int x, int y)
{
  return ( (x >= 0) && (x < MapWidth) && (y >= 0) && (y < MapHeight) );
}


//PathExists() does the actual searching of the map. It takes map symbols as
//input. You pass it the symbol that it should start at (which, for this
//problem, is always '1'), the symbol that it should end at (which, for this
//problem, is always '2'), and a string of symbols that it is allowed to cross.
//If there is a path from the start to the finish that crosses over only the
//given symbols, the function returns true. Otherwise, it returns false.
//Note that if PassableSymbols doesn't contain the StopSymbol ('2'), then
//PathExists() would never be able to find a path that leads to the stop point!
bool PathExists(char StartSymbol, char StopSymbol, const char *PassableSymbols)
{
  //This function works by continuously "filling in" places on the map, sort of
  //like the "flood fill" function in a paint program. If it ever "fills in"
  //the stop-symbol, then there's a path from start to finish. If it never
  //fills in the stop-symbol, then there's no path.

  //AreaAroundMe is an array of constant values. These values indicate how to
  //get to the map locations surrounding a position. This array is used in
  //the do-while loop, below.
  static const int AreaAroundMe[4][2] =
  {
    {0, 1}, {0, -1}, {1, 0}, {-1, 0}
  };


  //the Used array keeps track of the places that have been examined. Used[x][y]
  //is true if Map[x][y] has been "filled."
  bool Used[64][64];
  int StartX = -1, StartY = -1;
  bool FilledSomeArea;
  bool FoundStopSymbol;

  //the first task is to find where the heck the start symbol is.
  for (int loop = 0; loop < MapHeight; loop++)
  {
    for (int loop2 = 0; loop2 < MapWidth; loop2++)
    {
      if (Map[loop2][loop] == StartSymbol) //found it!
      {
        StartX = loop2;
        StartY = loop;
      }
    }
  }

  //at this point, StartX and StartY should have the position of the starting
  //symbol, instead of -1 (which is what they were initialized with).
  //The following assertion makes this expectation explicit. If the assertion
  //fails, something has gone very wrong (or, perhaps there is no starting
  //symbol on the map).
  assert( (StartX != -1) && (StartY != -1) );

  //clear Used to false, initialize FoundStopSymbol to false
  memset(Used, false, sizeof(Used));
  FoundStopSymbol = false;

  //set Used[StartX][StartY] to true, indicating that we have "filled" that
  //spot. By filling this space, we "prime" the algorithm below. It will keep
  //expanding the filled-in area around the starting position.
  Used[StartX][StartY] = true;

  //Now, continuously scan the entire board. Whenever we encounter a "filled in"
  //space, see if we can fill in area around that space. If we fill in any spot
  //on the board, FilledSomeArea == true. This means that more area may now be
  //available to fill. If FilledSomeArea is never set to true, that means that
  //the filled-in area can get no larger. Note also that if the "stop symbol" is
  //ever filled in, we set FoundStopSymbol to true, indicating that there is a
  //path from start to stop. Otherwise, it will remain false.

  do
  {
    //initialize FilledSomeArea to false
    FilledSomeArea = false;

    for (int YPos = 0; YPos < MapHeight; YPos++)
    {
      for (int XPos = 0; XPos < MapWidth; XPos++)
      {
        if (Used[XPos][YPos]) //spot is "filled in"; try to fill area around it
        {
          //see if any of the spaces that surround this filled-in spot
          //can be filled in. The AreaAroundMe array contains offsets for the
          //current x and y location. An alternate way of coding this would have
          //been to use four separate if-blocks, one to see if I could go to
          //Map[XPos][YPos+1], another to see if I could go to
          //Map[XPos+1][YPos], etc., but this method is more compact.
          for (int loop = 0; loop < 4; loop++)
          {
            int X = XPos + AreaAroundMe[loop][0];
            int Y = YPos + AreaAroundMe[loop][1];

            //This spot will be filled if it meets the following requirements:
            //  A: is a spot that is on the map
            //  B: is hasn't already been filled in
            //  C: it is a type of terrain that can be moved onto
            if (IsValidMapLocation(X, Y) &&
                !Used[X][Y] &&
                (strchr(PassableSymbols, Map[X][Y]) != 0) )
            {
              //fill this space in.
              Used[X][Y] = true;
              FilledSomeArea = true;
              if (Map[X][Y] == StopSymbol)
                FoundStopSymbol = true;
            }
          }
        }
      }
    }
    //stop if we've found the symbol, or if no more filling can occur
  } while (FilledSomeArea && !FoundStopSymbol);

  return FoundStopSymbol;
}


//ProcessMap() processes the map once it has been read from the input file. It
//is called by main().
void ProcessMap()
{
  //See if city 1 can reach city 2 with various items. Try the cheapest items
  //first, then go on to the more expensive ones.

  //First, see if there is a path from town 1 to town 2 that crosses only grass
  //and dirt. If so, then our advice is to build ogres. Otherwise, see if
  //a shipyard would work (that is, if there is a path that crosses only grass,
  //dirt, and water). If not, see if there's a path crossing only grass, dirt,
  //trees, and mountains; recommend building sappers if there is such path. If
  //nothing has worked up to now, recommend building dragons (which can cross
  //over any territory).
  if (PathExists('1', '2', ".:12"))
    printf("Build Ogres.\n");
  else if (PathExists('1', '2', ".:~12"))
    printf("Build a Shipyard.\n");
  else if (PathExists('1', '2', ".:T#12"))
    printf("Build Sappers.\n");
  else
    printf("Build Dragons.\n");
}


void main()
{
  char st[256];
  int MapNum = 1;
  FILE *in = fopen("warcraft.in", "r");

  while (fgets(st, sizeof(st), in) != NULL)
  {
    //find the map's width and height
    sscanf(st, "%d %d", &MapWidth, &MapHeight);

    //read in the map, store it into global variable Map
    for (int loop = 0; loop < MapHeight; loop++)
    {
      fgets(st, sizeof(st), in);
      for (int loop2 = 0; loop2 < MapWidth; loop2++)
      {
        Map[loop2][loop] = st[loop2];
      }
    }

    //map is read in; now process the map to see what we should build. We'll
    //call ProcessMap() to determine this. First, though, print the current map
    //number. main() is responsible for keeping track of the map number;
    //ProcessMap() will print the rest of the output line, and print the
    //carriage-return.
    printf("Map #%d: ", MapNum);
    MapNum++;

    ProcessMap();

  }

  fclose(in);
}

