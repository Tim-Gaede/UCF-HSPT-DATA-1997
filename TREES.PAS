(******************************************************************)
(* Eleventh Annual UCF ACM UPE High School Programming Tournament *)
(* May 2, 1997                                                    *)
(*                                                                *)
(* Judges' solution to the problem "Mike Likes to Climb Trees"    *)
(*                                                                *)
(* Original problem idea by Glenn Martin                          *)
(* Solution by Michael J. Smith                                   *)
(******************************************************************)

var num_sets, num_limbs, i, j, max, current_limb:integer;

begin

  (* open the input file *)
  assign(input, 'trees.in');
  reset(input);

  (* read the number of trees *)
  readln(num_sets);
  (* process each tree *)
  for i:=1 to num_sets do
  begin
    (* Set the maximum to 0 *)
    max := 0;
    (* Read the number of limbs (of the tree, not Mike's) *)
    readln(num_limbs);
    (* Process each limb *)
    for j:=1 to num_limbs do
    begin
      (* Read the next limb *)
      read(current_limb);
      (* If this limb is higher than the max height then set the 
         max to this limb *)
      if (current_limb > max) then
        max := current_limb;
    end;
    readln;
    writeln('Look at or below height ',max);
  end;


end.
