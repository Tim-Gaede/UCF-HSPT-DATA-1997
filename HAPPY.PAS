(******************************************************************)
(* Eleventh Annual UCF ACM UPE High School Programming Tournament *)
(* May 2, 1997                                                    *)
(*                                                                *)
(* Judges' solution to the problem "Happiness Man"                *)
(*                                                                *)
(* Original problem idea by Eric Heimburg                         *)
(* Solution by Rajkumar Madhuram                                  *)
(******************************************************************)

Program Happy;

Const
 MAXVILL = 5;

Var
 names              : Array[0..MAXVILL-1] of String; (* evil names *)
 evil, weight,
 whichone, solution : Array[0..MAXVILL-1] of integer;
 (* evil and weight contains the evilness and weight of enemies *)
 (* whichone is the binary vector containing a combination *)
 (* solution is the binary vector containing a best feasible combination *)

Procedure solve(numvill:integer);
 Var
  i, j, ecost, wcost : integer;
  maxcases, carry    : integer;
  minpulps, npulps   : integer;

 Begin

  for i:=0 to numvill-1 do (* Initialise *)
   whichone[i] := 0;

  solution := whichone;
  minpulps := MAXVILL;

  maxcases := 1 shl numvill;  (* 2^numvill *)

  for i:=0 to maxcases-1 do
   begin

     ecost := 0; wcost := 0;

     for j:=0 to numvill-1 do
      begin
       if (whichone[j] = 0) then ecost := ecost + evil[j]
        else wcost := wcost + weight[j];
      end;

     if ((ecost <= 50) and (wcost <= 500)) then
      begin  (* valid solution *)
        npulps := 0;
        for j:=0 to numvill-1 do
         if (whichone[j] = 1) then npulps := npulps + 1;
        if (npulps <= minpulps) then  (* Is this the best solution ? *)
         begin
          solution := whichone;  (* Retain the best solution *)
          minpulps := npulps;
         end;
      end;

     (* Add 1 to the binary vector to get the next possible combination *)
     carry := 1;
     for j:= numvill-1 downto 0 do  (* Add 1 to the binary representation *)
      begin
        whichone[j] := whichone[j] + carry;
        if (whichone[j] = 2) then begin whichone[j] := 0; carry := 1; end
         else carry := 0;
      end;
   end;

end;

Var
 i, evilness, villweight, nvill : integer;
 villname : string;
 c        : char;
 fp       : text;

begin

   Assign(fp, 'happy.in');
   Reset(fp);
   while true do
    begin
      Readln(fp, nvill);
      if (nvill = 0) then break;
      for i:=0 to nvill-1 do
       begin
          Readln(fp, villname);
          Readln(fp, evilness, villweight);
	  names[i] := villname;
	  evil[i] := evilness;
	  weight[i] := villweight;
       end;

     solve(nvill);  (* Returns the best combination in 'solution' *)

     for i:= 0 to nvill-1 do
      begin
      	Write('Use the ');
	if (solution[i] = 0) then write('Happiness')
	 else write('Pulping');
	writeln(' Ray on ', names[i]);
      end;
     writeln;
    end;
   close(fp);
 end.



