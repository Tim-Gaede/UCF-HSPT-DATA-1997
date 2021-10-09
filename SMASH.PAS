(******************************************************************)
(* Eleventh Annual UCF ACM UPE High School Programming Tournament *)
(* May 2, 1997                                                    *)
(*                                                                *)
(* Judges' solution to the problem "Smash the Copy Machine!"      *)
(*                                                                *)
(* Original problem idea by Dr. Ali Orooji                        *)
(* Solution by Joel Davis                                         *)
(******************************************************************)

program smash;
(*****************************************************************************
 * SMASH -- Given the number of pages in a document, a number of copies to
 * make and the number of stacks a malfunctioning copier tries to collate them
 * into, print out the contents of each stack.
 *
 * This is just a straightforward simulation of the copier's behavior. There
 * is an array that holds the contents of the stack, and another which holds
 * the size of each stack. These are filled by stepping through the pages
 * and the number of copies of each on the stacks. Then, the stacks are
 * printed.
 *
 *)
var
    infile: TEXT;       (* The input file *)

    num_pages,          (* The inputs *)
    num_copies,
    num_stacks,

    curr_page,    (* The page that we are on            *)
    curr_stack,   (* The stack that we are on           *)
    page_copies,  (* Number of copies made of this page *)
    dataset,      (* The data set number                *)
    i, j:integer; (* Loop counters                      *)

    (* Hold which pages are in which stack. There are 10 stacks, *)
    (* each can hold up to 100 copies. *)
    stack : array[1..10,1..100] of integer;

   (* Holds how many pages are in each stack *)
   stack_sz : array[1..10] of integer;

begin
    (* Open the input file *)
    assign( infile, 'smash.in' );
    reset( infile );

    (* Initialize the set counter *)
    dataset := 1;
    while (not eof(infile) ) do
    begin

        (* Read in the inputs from the input file *)
        readln( infile, num_pages, num_copies, num_stacks );

        (* Initialize the simulation variables *)
        curr_page := 1;
        curr_stack := 1;
        page_copies := 0;

        (* Set the stacks to be empty *)
        for i := 1 to 10 do stack_sz[i] := 0;

        (* Print a header for this data set *)
        writeln('Data set ', dataset);
        inc( dataset);

        (* Step through the pages until all pages have been copied *)
        while (curr_page <= num_pages) do
        begin

            (* Place the current page on the current stack, and *)
            (* increment the size of the current stack.         *)
            inc (stack_sz[curr_stack]);
            stack[curr_stack,stack_sz[curr_stack] ] := curr_page;

            (* Move to the next stack. If we move past the last stack *)
            (* go back to the first stack.                            *)
            inc(curr_stack);
            if (curr_stack > num_stacks) then curr_stack := 1;

            (* Count this copy *)
            inc(page_copies);

            (* Check to see if enough copies of this page have been made *)
            if (page_copies = num_copies) then begin
               (* If so, move on to the next page and reset the count *)
               inc( curr_page );
               page_copies := 0;
            end;
        end;

        (* Now all the data is collected. All that is left to do is print *)
        (* the contents of each stack.                                    *)
        for i := 1 to num_stacks do
        begin
            (* Print a title for this stack *)
            write('   Stack', i:2,':');

            (* Print the contents of this stack *)
            for j := 1 to stack_sz[i] do
                write(' ',stack[i][j]);

            writeln;
        end;

        (* Print a blank line after each data set *)
        writeln;
    end;
end.
