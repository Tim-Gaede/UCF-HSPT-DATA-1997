(******************************************************************)
(* Eleventh Annual UCF ACM UPE High School Programming Tournament *)
(* May 2, 1997                                                    *)
(*                                                                *)
(* Judges' solution to the problem "Invoke the OrACKle"           *)
(*                                                                *)
(* Original problem idea by Drue Pautz (modified by Glenn Martin) *)
(* Solution by Michael Kujawa                                     *)
(******************************************************************)

program orackle;
{
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

}


{ The virtual screen }
Var
   Screen : Array[1..24] of String;



{ cls
   This procedure clears the screen to periods.
}
procedure cls;
  Var
    y : Integer;

  begin
    for y := 1 to 24 Do
      Screen[y] := '......................................................................';
  end;





{ hflip
    This procedure flips the screen horizontally.  Since each line is stored as
    a string, this simply reverses the strings.
}
procedure hflip;
  Var
    x, y, l : Integer;
    ch      : char;

  begin
    for y := 1 to 24 do
      begin
        l := Length(Screen[y]);
        for x := 1 to l div 2 do
          begin
            ch := Screen[y][x];
            Screen[y][x] := Screen[y][l-x+1];
            Screen[y][l-x+1] := ch;
          end;

      end;
  end;




  
{ vflip
    This procedure flips the screen vertically by swapping the lines about
    the center.
}
procedure vflip;
  Var
    Temp : String;
    y    : Integer;

  begin
    for y := 1 to 12 Do
      begin
        Temp := Screen[y];
        Screen[y] := Screen[25-y];
        Screen[25-y] := Temp;
      end;
  end;





{ paint
   This procedure draws the virtual screen to standard output.  
}
procedure paint;
  Var
    y : Integer;

  begin
    for y := 1 to 24 Do
      Writeln(Screen[y]);
  end;




  
{ Draw
   Draws the text on to the virtual screen.  Since there is no way to know how
   much text there will be, and it may not be storable in a single array anyway,
   I pass the file pointer and just read the characters out of that.

   Note that to handle really long lines x and y need to be long integers.
   (This problem doesn't require it anymore, but I left the solution the same)
}
procedure draw(x, y : LongInt; xofs, yofs : Integer; var F : Text);
  Var
    ch : char;

  begin
    while not eoln(F) and not eof(F) do
      begin
        Read(F, ch);
        if (ch = ' ') then
            ch := '.';
        if (x >= 1) AND (x <= 70) AND
           (y >= 1) AND (y <= 24) then
             Screen[y][x] := ch;
        x := x + xofs;
        y := y + yofs;
      end;
  end;




{ ReadWord
   This function reads up to, but not including, the next space or End-of-line.
}
function ReadWord(var F : Text) : string;
  var
    St : string;
    ch : char;

  begin
    St := '';
    while not eoln(F) and not eof(F) do
      begin
        read(F, ch);
        if ch = ' ' then
          break;
            st := st + ch;
      end;
    ReadWord := st;
  end;





Var
  InFile : Text;
  st     : String;
  x, y   : LongInt;
  xofs,
  yofs   : Integer;
  ch     : char;

BEGIN
  cls;
  Assign(InFile, 'orackle.in');
  Reset(InFile);

  while not EOF(InFile) do
    begin
      st := ReadWord(InFile);
      { Process the command }
      if st = 'HFLIP' then
        hflip;
      if st = 'VFLIP' then
        vflip;
      if st = 'CLEAR' then
        cls;
      if st = 'REPAINT' then
        paint;
      if st = 'ADD' then
        begin
           xofs := 0;
           yofs := 0;
           { Read x, y, and the space afterwards }
           Read(InFile, x, y, ch);

           { Calculate the offsets }
           repeat
             Read(InFile, ch);
             if ch = 'U' then yofs := -1;
             if ch = 'D' then yofs :=  1;
             if ch = 'L' then xofs := -1;
             if ch = 'R' then xofs :=  1;
           until ch = ' ';

           Draw(x, y, xofs, yofs, InFile);
        end;
        { Read the end-of-line to prep the next Read }
        Readln(InFile);
    end;

  Close(InFile);
END.
