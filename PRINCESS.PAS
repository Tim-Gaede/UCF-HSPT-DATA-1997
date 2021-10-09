(******************************************************************)
(* Eleventh Annual UCF ACM UPE High School Programming Tournament *)
(* May 2, 1997                                                    *)
(*                                                                *)
(* Judges' solution to the problem "Princess's Escape Plan"       *)
(*                                                                *)
(* Original problem idea by Eric Heimburg                         *)
(* Solution by Bryan Kline                                        *)
(******************************************************************)

program PRINCESS;

type
    Point = record
        x : longint;
        y : longint;
    end;

var
    inFile : TEXT;
    goblinCount : longint;
    loop, max : longint;
    slot, result : longint;
    princessLoc, goblinLoc : Point;
        { this array is 1500 long because the longest possible radius }
        { according to the problem spec is somewhere over 1400.       }
        { Think princess(1,1) and goblin(1000,1000)                   }
    hitCount : array[1..1500] of longint;

function Distance(one, two : Point) : real;
    var
        dx, dy : longint;
        result : double;
    begin
        dx := one.x - two.x;
        dy := one.y - two.y;
        Distance := Sqrt(Sqr(dx) + Sqr(dy));

    end;

begin
    Assign(inFile, 'princess.in');
    Reset(inFile);

    ReadLn(inFile, goblinCount);
    while (goblinCount > 0) do
        begin
            { clear the hit array }
            for loop := 1 to 1500 do
                hitCount[loop] := 0;

            { read in the coordinates of the princess }
            ReadLn(inFile, princessLoc.x, princessLoc.y);

            { Compare the coordinates of the princess to those of   }
            { the goblins, one at a time. Mark our hit array as     }
            { the radius of the rope that would hit that particular }
            { goblin.                                               }
            for loop := 1 to goblinCount do
                begin
                    ReadLn(inFile, goblinLoc.x, goblinLoc.y);
                    slot := Round(Distance(princessLoc, goblinLoc));
                    hitCount[slot] := hitCount[slot] + 1;
                end;    { loop through goblins }

            { Find the rope radius that hit the most goblins.       }
            { Goes backwards because if two radii hit the same      }
            { number of goblins, you use the smaller radius.        }
            max := -1;
            for loop := 1500 downto 1 do
                begin
                    if hitCount[loop] >= max then
                        begin
                            max := hitCount[loop];
                            result := loop;
                        end;
                end;    { loop to find the largest }

            WriteLn(result);

            ReadLn(inFile, goblinCount);
        end;    { while goblinCount > 0 }

    Close(inFile);
end.    { Program }
