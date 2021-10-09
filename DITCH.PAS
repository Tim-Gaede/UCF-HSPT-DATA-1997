(******************************************************************)
(* Eleventh Annual UCF ACM UPE High School Programming Tournament *)
(* May 2, 1997                                                    *)
(*                                                                *)
(* Judges' solution to the problem "Digging Ditches"              *)
(*                                                                *)
(* Original problem idea by Peter Singhofen                       *)
(* Solution by Michael J. Smith                                   *)
(******************************************************************)

var num,i:integer;
    val1,val2,length,volume:real;

begin
  { open input file }
  assign(input, 'ditch.in');
  reset(input);

  { read number of ditches }
  readln(num);

  { process each ditch }
  for i:=1 to num do
  begin
    { read areas and length between them }
    readln(val1, val2, length);
    { compute the volume (average the two areas and multiply by length) }
    volume := (val1+val2)*0.5*length;
    { output the volume }
    writeln(volume:0:1);
  end;

end.
