(******************************************************************)
(* Eleventh Annual UCF ACM UPE High School Programming Tournament *)
(* May 2, 1997                                                    *)
(*                                                                *)
(* Judges' solution to the problem "Warcraft"                     *)
(*                                                                *)
(* Original problem idea by Joel Davis                            *)
(* Solution by Eric Heimburg                                      *)
(******************************************************************)

program Warcraft;

(*The current map is stored in the global 2-d array called Map. The symbols
  are stored in x-by-y order; that is, the first dimension is the horizontal
  position, and the second dimension is the vertical position. Thus,
  Map[7][1] indicates the 7th column from the left, on the topmost row.*)
var
  Map : array[1..64, 1..64] of char;

(*MapWidth and MapHeight store the width and height of the current map.*)
  MapWidth, MapHeight : integer;

(*IsValidMapLocation() is a utility function that determines if a given x-y
  coordinate is in the legal range of the Map.*)

function IsValidMapLocation(x : integer; y : integer) : boolean;
begin
  if (x > 0) and (x <= MapWidth) and (y > 0) and (y <= MapHeight) then
    IsValidMapLocation := true
  else
    IsValidMapLocation := false;
end;


(*PathExists() does the actual searching of the map. It takes map symbols as
  input. You pass it the symbol that it should start at (which, for this
  problem, is always '1'), the symbol that it should end at (which, for this
  problem, is always '2'), and a string of symbols that it is allowed to cross.
  If there is a path from the start to the finish that crosses over only the
  given symbols, the function returns true. Otherwise, it returns false.
  Note that if PassableSymbols doesn't contain the StopSymbol ('2'), then
  PathExists() would never be able to find a path that leads to the stop
  point!*)
function PathExists(StartSymbol : char; StopSymbol : char;
                                        PassableSymbols : string) : boolean;
  (*This function works by continuously "filling in" places on the map, sort of
    like the "flood fill" function in a paint program. If it ever "fills in"
    the stop-symbol, then there's a path from start to finish. If it never
    fills in the stop-symbol, then there's no path.*)

  (*AreaAroundMe is an array of constant values. These values indicate how to
    get to the map locations surrounding a position. This array is used in
    the repeat-until loop, below.*)
  const
    AreaAroundMe : array[1..4,1..2] of integer =
    ( (0, 1), (0, -1), (1, 0), (-1, 0) );

  (*the Used array keeps track of the places that have been examined.
    Used[x,y] is true if Map[x,y] has been "filled."*)
  var
    Used : array[1..64, 1..64] of boolean;
    StartX : integer;
    StartY : integer;
    FilledSomeArea : boolean;
    FoundStopSymbol : boolean;
    xloop, yloop, loop : integer;  (* looping variables *)
    X, Y : integer;                (* temporary variables *)
begin
  StartX := -1;
  StartY := -1;
  (*the first task is to find where the heck the start symbol is.*)
  for xloop:=1 to MapWidth do
    for yloop:=1 to MapHeight do
      if Map[xloop,yloop] = StartSymbol then (*found it!*)
      begin
        StartX := xloop;
        StartY := yloop;
      end;

  (*at this point, StartX and StartY should have the position of the starting
    symbol, instead of -1 (which is what they were initialized with).*)
  if (StartX = -1) or (StartY = -1) then
    writeln('Error: No starting location detected!');

  (*clear Used to false, initialize FoundStopSymbol to false.*)
  fillchar(Used, sizeof(Used), false);
  FoundStopSymbol := false;

  (*set Used[StartX,StartY] to true, indicating that we have "filled" that
    spot. By filling this space, we "prime" the algorithm below. It will keep
    expanding the filled-in area around the starting position.*)
  Used[StartX,StartY] := true;

  (*Now, continuously scan the entire map. Whenever we encounter a
    "filled in" space, see if we can fill in area around that space.
    If we fill in any spot on the board, FilledSomeArea = true. This means
    that more area may now be available to fill. If FilledSomeArea is never
    set to true, that means that the filled-in area can get no larger. Note
    also that if the "stop symbol" is ever filled in, we set
    FoundStopSymbol to true, indicating that there is a path from start to
    stop. Otherwise, it will remain false.*)

  repeat
    (*initialize FilledSomeArea to false*)
    FilledSomeArea := false;

    for xloop := 1 to MapWidth do
      for yloop := 1 to MapHeight do
      begin
        if Used[xloop,yloop] then (*spot is "filled in"; fill around it *)
        begin
          (*see if any of the spaces that surround this filled-in spot
            can be filled in. The AreaAroundMe array contains offsets for the
            current x and y location. An alternate way of coding this would
            have been to use four separate if-blocks, one to see if I could
            go to Map[xloop,yloop+1], another to see if I could go to
            Map[xloop+1,yloop], etc., but this method is more compact.*)
          for loop := 1 to 4 do
          begin
            X := xloop + AreaAroundMe[loop,1];
            Y := yloop + AreaAroundMe[loop,2];

            (*This spot will be filled if it meets the following requirements:
                A: is a spot that is on the map
                B: is hasn't already been filled in
                C: it is a type of terrain that can be moved onto *)
            if IsValidMapLocation(X, Y) and
               not Used[X, Y] and
               (Pos(Map[X,Y], PassableSymbols) > 0) then
            begin
              (*fill this space in.*)
              Used[X,Y] := true;
              FilledSomeArea := true;
              if Map[X,Y] = StopSymbol then
                FoundStopSymbol := true;
            end
          end
        end
      end;

    (*stop if we've found the symbol, or if no more filling can occur*)
  until (not FilledSomeArea or FoundStopSymbol);

  PathExists := FoundStopSymbol;
end;



(*ProcessMap processes the map once it has been read from the input file.
  It is called by main().*)
procedure ProcessMap;
begin
  (*See if city 1 can reach city 2 with various items. Try the cheapest
    items first, then go on to the more expensive ones.

    First, see if there is a path from town 1 to town 2 that crosses only
    grass and dirt. If so, then our advice is to build ogres. Otherwise,
    see if a shipyard would work (that is, if there is a path that crosses
    only grass, dirt, and water). If not, see if there's a path crossing
    only grass, dirt, trees, and mountains; recommend building sappers
    if there is such path. If nothing has worked up to now, recommend
    building dragons (which can cross over any territory).*)

  if PathExists('1', '2', '.:12') then
    writeln('Build Ogres.')
  else if PathExists('1', '2', '.:~12') then
    writeln('Build a Shipyard.')
  else if PathExists('1', '2', '.:T#12') then
    writeln('Build Sappers.')
  else
    writeln('Build Dragons.');
end;


var
  st : string;
  MapNum : integer;
  InFile : text;
  xloop, yloop : integer; (* looping variables *)

begin
  MapNum := 1;

  assign(InFile, 'warcraft.in');
  reset(InFile);

  while not eof(InFile) do
  begin
    (* find the map's width and height *)
    readln(InFile, MapWidth, MapHeight);

    (* read in the map, store it into global variable Map *)
    for yloop := 1 to MapHeight do
    begin
      readln(InFile, st);
      for xloop := 1 to MapWidth do
        Map[xloop, yloop] := st[xloop];
    end;

    (*Map is read in; now process the map to see what we should build. We'll
      call ProcessMap() to determine this. First, though, print the current map
      number. main() is responsible for keeping track of the map number;
      ProcessMap() will print the rest of the output line, and print the
      carriage-return. *)

    write('Map #', MapNum, ': ');
    inc(MapNum);
    ProcessMap;

  end;

  close(InFile);
end.
