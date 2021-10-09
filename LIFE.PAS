(******************************************************************)
(* Eleventh Annual UCF ACM UPE High School Programming Tournament *)
(* May 2, 1997                                                    *)
(*                                                                *)
(* Judges' solution to the problem "The Cycle of Life"            *)
(*                                                                *)
(* Original problem idea by Rajkumar Madhuram                     *)
(* Solution by Peter Singhofen                                    *)
(******************************************************************)

(* This array stores when we have been to each state.  States are
   assumed to be binary integers for storage purposes. *)
var

been : array [0..16383] of integer;
step :integer;


(* This checks a state (represented as a string).  If it is all 0's
   then the state has "died out". *)
function IsDead( s : string ):integer;
var
  c : integer;
begin
  IsDead := 1;
  for c:=1 to Length(s) do
    if (s[c] <> '0') then IsDead := 0;
end;

(* This converts the state (represented as a string) to an integer
   by assuming the state is a binary integer. *)
function AsInt( s: string ) : integer;
var
  val, c, p : integer;
begin
  val := 0; p := 1; c := Length(s);
  while (c >= 1 ) do
  begin
    if (s[c]='1') then inc(val,p);
    p := p * 2;
    dec(c);
  end;

  AsInt := val;
end;


(* This "evolves" the state by the rules given in the problem spec. *)
procedure Evolve( var s : string );
var
  old:string;
  c : integer;
begin
  old := s;
  for c:=2 to Length(s)-1 do
  begin
    if (old[c-1]=old[c+1]) then
      s[c] := '0'
    else
      s[c] := '1';
   end;
end;


var
  f : TEXT;
  s:string;
  done, c : integer;
begin
  assign( f, 'life.in');
  reset( f );


  while (not eof(f) ) do
  begin
    readln(f, s );
    step:=1; done:=0;

    (* Initialize the been array.  0 means we have never seen this state. *)
    for c := 0 to 16383 do
      been[c] := 0;

    write(s,' ');

    (* evolve the state until it dies out or we detect a cycle. *)
    while (done=0) do
    begin

      if (IsDead(s)=1) then begin
        writeln('dies out.');
        done:=1;
      end else begin
        (* convert state to integer. *)
        c := AsInt(s);
        if (been[c]<>0) then begin
          (* We've seen this state before...*)

          (* compute the cycle length.  Its the current step minus
             the step last time we saw this state. *)

          writeln('has a period of ',step-been[c],' units.');
          done:=1;
        end else begin
          (* This is the first time we've seen this state.
             Set the been array for this state to the current step. *)
          been[AsInt(s)]:=step; inc(step);

          (* Evolve the state. *)
          Evolve(s);
        end;
      end;
    end;
  end;
end.
