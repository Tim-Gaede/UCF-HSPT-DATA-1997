(******************************************************************)
(* Eleventh Annual UCF ACM UPE High School Programming Tournament *)
(* May 2, 1997                                                    *)
(*                                                                *)
(* Judges' solution to the problem "Counting Dashes"              *)
(*                                                                *)
(* Original problem idea by Michael Kujawa                        *)
(* Solution by Joel Davis                                         *)
(******************************************************************)

program dashes;
(****************************************************************************
 * DASHES -- Computes the number of dashes a car passes over.
 *
 * Since the car starts at the end of a dash, we can see that the number
 * of whole dashes it crosses is equal to the total distance travelled
 * divided by the combined length of a dash and a gap.
 *
 * The input was allowed to go up to 500,000, so long ints must be used.
 *
 *****************************************************************************)
var
    infile : TEXT;
    dash_width, gap_width, distance, num_dashes : Longint;
begin

    (* Open the input file for reading *)
    assign( infile, 'dashes.in');
    reset( infile );

    (* Read and process input until end of file *)
    while (not eof(infile) ) do
    begin
        readln( infile, dash_width, gap_width, distance );

        (* Compute the number of complete dashes passed over *)
        num_dashes := distance div (dash_width + gap_width);

        (* Output the result *)
        writeln( num_dashes );
    end;

end.
