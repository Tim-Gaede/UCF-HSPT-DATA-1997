(******************************************************************)
(* Eleventh Annual UCF ACM UPE High School Programming Tournament *)
(* May 2, 1997                                                    *)
(*                                                                *)
(* Judges' solution to the problem "A Minimal Problem"            *)
(*                                                                *)
(* Original problem idea by everybody                             *)
(* Solution by Travis Terry                                       *)
(******************************************************************)

(*
        This is the Pascal solution to 'A Minimal Problem'.  Note long
        integers are used to handle the input case 32767 -32768, because
        the result, 65535, it too large for a signed 16-bit integer.
*)

(*
    function: Max

    input:      two long integers, a and b
    output:     the larger of 'a' and 'b'
*)

FUNCTION Max ( a, b : longint ) : longint;
BEGIN
    IF ( a > b ) THEN                   (*  a is larger than b              *)
        Max := a
    ELSE                                (*  b is at least as large as a     *)
        Max := b;
END; {Max}

VAR
    inf, outf : text;                   (*  input and output file streams   *)
    N,                                  (*  number of data sets             *)
    i : integer;                        (*  a loop variable                 *)
    a, b,                               (*  the two numbers for a data set  *)
    maximum : longint;                  (*  the maximum of the two numbers  *)

BEGIN
    Assign ( inf, 'minimal.in' );

    Reset ( inf );                      (*  open input file                 *)

    Readln ( inf, N );                  (*  read number of data sets        *)

    FOR i := 1 TO N DO BEGIN            (*  for each data set do:           *)
        Readln ( inf, a, b );                   (*  read data set           *)
        maximum := Max ( Max(a,b), a-b );       (*  compute the maximum
                                                    of a, b, and (a-b)      *)
        Writeln ( maximum );            (*  print the result                *)
    END;

    Close ( inf );                      (* close input file                *)
END.
