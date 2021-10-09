(******************************************************************)
(* Eleventh Annual UCF ACM UPE High School Programming Tournament *)
(* May 2, 1997                                                    *)
(*                                                                *)
(* Judges' solution to the problem "Psychic Gypsy Battle"         *)
(*                                                                *)
(* Original problem idea by Eric Heimburg                         *)
(* Solution by Phillip Dexheimer                                  *)
(******************************************************************)

Program Gypsy;

{Program determines how to make sure the princess doesn't take the last M&M  }
{Only special case: If there is only one M&M to start, the princess can't win}


type
  arry1 = array [1..200] of integer; {200 gives a little padding -
                                      shouldn't be more than 255 div 2}

var
  count : integer;       {Game #}
  num : integer;         {# of M&M's}
  infile : text;         {input file}
  Gmove, Pmove : arry1;  {Gypsy's and princess's moves}
  lcv, l2 : integer;     {loop counters}

begin
  count := 0;
  assign (infile, 'gypsy.in');
  reset (infile);

  while (not eof(infile)) do
   begin
    { Increment data set number and read in the number of M&M's }
    inc(count);
    read (infile, num);
    lcv := 0;

    while (not eoln (infile)) do
     begin
      inc(lcv);
      read (infile, Gmove[lcv]); {read G's moves and}
      Pmove[lcv] := 0;           {pad P's array to catch special case}
     end;

    for l2 := lcv+1 to 200 do
     begin
      Gmove[l2] := 0;  {pad arrays to make finding last move easy}
      Pmove[l2] := 0;
     end;

    if (num = 1) then num := 0; {Trap special case}
    lcv := 1;

    while (num <> 0) do
     begin  {Make moves} {Don't forget to change G's last move}
      if (num > 5) then  {Algorithm: take 5 until you will lose if you take 5}
       begin             {Then you take less}
        Pmove[lcv] := 5;
        while (Gmove[lcv] + Pmove[lcv] + 1 >= num) do
         dec(Pmove[lcv]);
        if (Pmove[lcv] <= 0) then Pmove[lcv] := 1;
       end
      else Pmove[lcv] := num - 1;

      num := num - Pmove[lcv];
      if (num < Gmove[lcv]) then Gmove[lcv] := num;
      num := num - Gmove[lcv];
      inc(lcv);
     end;

    write ('Game #', count, ':');  {The output.}
    if (Pmove[1] = 0) then writeln (' The princess cannot win!')
    else
     begin
      lcv := 1;
      while (Pmove[lcv] <> 0) do
       begin
        write (' P:', Pmove[lcv], ' G:', Gmove[lcv]);
        inc (lcv);
       end;
      writeln;
     end;

   end;
  close (infile);
end. {Done.  Yea!}
