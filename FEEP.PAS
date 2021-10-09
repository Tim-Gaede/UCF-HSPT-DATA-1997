(******************************************************************)
(* Eleventh Annual UCF ACM UPE High School Programming Tournament *)
(* May 2, 1997                                                    *)
(*                                                                *)
(* Judges' solution to the problem "Proper Penguin Speech"        *)
(*                                                                *)
(* Original problem idea by Peter Singhofen                       *)
(* Solution by Rajkumar Madhuram                                  *)
(******************************************************************)

Program Feep;

Const
 MAXSITES = 20;
 MAXPLANES = 500;

type
  POINT = Record
            x,y : integer;
          End;

Var

sites   : array[0..MAXSITES,0..1] of POINT; (* stores the sites' coordinates *)
fp      : text;
nsites,
nplanes : integer;

function left_on(p1, p2, q : POINT):integer;
(* Is q to the left or on segment p ? -1 if left, 0 if on, 1 if right*)
 Var
  det, term1, term2, term3, term4 : longint;

 begin

  term1 := p1.x * longint(q.y - p2.y);
  term2 := p1.y * longint(q.x - p2.x);
  term3 := q.x*longint(p2.y);
  term4 := q.y*longint(p2.x);

  det := term1 - term2 + term3 - term4;

  if (det < 0) then left_on := -1
   else if (det = 0) then left_on := 0
    else left_on := 1;

 end;

Function seg_inter(p1, p2, q1, q2: POINT):integer;
(* Does segment p intersect segment q? *)
 Var
   d1, d2, d3, d4       : integer;
   pt1, pt2, qt1, qt2   : integer;
   pp1, pp2, qp1, qp2   : integer;

 Begin
   d1 := left_on(p1, p2, q1);
   d2 := left_on(p1, p2, q2);
   d3 := left_on(q1, q2, p1);
   d4 := left_on(q1, q2, p2);

   if ((d1=0) and (d2=0) and (d3=0) and (d4=0)) then (* collinear segments *)
    begin
     if (p1.y = p2.y) then (* aligned with x axis *)
       begin
	pt1 := p1.x; pt2 := p2.x;
	qt1 := q1.x; qt2 := q2.x;
       end
     else (* aligned with y axis *)
       begin
	pt1 := p1.y; pt2 := p2.y;
	qt1 := q1.y; qt2 := q2.y;
       end;

     if (pt1 > pt2) then
      begin pp1 := pt2; pp2 := pt1; end
     else
      begin pp1 := pt1; pp2 := pt2; end;

     if (qt1 > qt2) then
      begin qp1 := qt2; qp2 := qt1; end
     else
      begin qp1 := qt1; qp2 := qt2; end;

     if ( ((qp1 <= pp1) and (qp2 >= pp1)) or
        ((qp1 >= pp1) and (qp1 <= pp2)) ) then seg_inter := 1
     else seg_inter := 0;
    end
   else
    begin
     if ((((d1 <= 0) and (d2 >= 0)) or
	  ((d2 <= 0) and (d1 >= 0))) and
         (((d3 <= 0) and (d4 >= 0)) or
  	  ((d4 <= 0) and (d3 >= 0)))) then seg_inter := 1
     else seg_inter := 0;
   end;
 end;

Procedure intersect(p1, p2 : POINT; planeno:integer);
 Var
  flag, i  : integer;
  sx1, sy1,
  sx2, sy2 : integer;
  q1, q2   : POINT;

 Begin

  for i:=0 to nsites-1 do
   begin

    sx1 := sites[i,0].x;   (* Retrieve the corners of the rectangle *)
    sy1 := sites[i,0].y;
    sx2 := sites[i,1].x;
    sy2 := sites[i,1].y;

    q1.x := sx1; q1.y := sy1;
    q2.x := sx1; q2.y := sy2;

    flag := 0;

    (* check if path of the plane intersects any of the four edges of
       the rectangle *)
    if (seg_inter(q1, q2, p1, p2)=1) then flag := 1;
    if (flag = 0) then
     begin
      q2.x := sx2; q2.y := sy1;
      if (seg_inter(q1, q2, p1, p2)=1) then flag := 1;
     end;
    if (flag = 0) then
     begin
      q1.x := sx2; q1.y := sy1;
      q2.x := sx2; q2.y := sy2;
      if (seg_inter(q1, q2, p1, p2)=1) then flag := 1;
     end;
    if (flag = 0) then
     begin
      q1.x := sx1; q1.y := sy2;
      if (seg_inter(q1, q2, p1, p2)=1) then flag := 1;
     end;

    if (flag = 1) then
      writeln('Plane #', planeno+1,' would fly over nesting site #', i+1,'.');
   end;
 end;

Var

 i,x1,y1,x2,y2  : integer;
 p1, p2         : POINT;

Begin

   Assign(fp, 'feep.in');
   Reset(fp);

   Readln(fp, nsites); (* Read sites *)
   for i:=0 to nsites-1 do
    begin
     Readln(fp, x1, y1, x2, y2);
     sites[i,0].x := x1; sites[i,0].y := y1;
     sites[i,1].x := x2; sites[i,1].y := y2;
    end;

   Readln(fp, nplanes); (* Read planes *)
   for i:=0 to nplanes-1 do
    begin
     Readln(fp, x1, y1, x2, y2);
     p1.x := x1; p1.y := y1;
     p2.x := x2; p2.y := y2;
     intersect(p1, p2, i);
    end;

   close(fp);
 end.
