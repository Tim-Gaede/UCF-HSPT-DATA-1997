/******************************************************************/
/* Eleventh Annual UCF ACM UPE High School Programming Tournament */
/* May 2, 1997                                                    */
/*                                                                */
/* Judges' solution to the problem "Proper Penguin Speech"        */
/*                                                                */
/* Original problem idea by Peter Singhofen                       */
/* Solution by Rajkumar Madhuram                                  */
/******************************************************************/

#include <stdio.h>
#include <math.h>
#define  MAXSITES 20
#define  MAXPLANES 500

typedef struct
 {
  int x, y;
 } POINT;

POINT	sites[MAXSITES][2];   /* stores the sites' coordinates */

FILE	*fp;
int 	nsites, nplanes;
void	intersect(POINT p1, POINT p2, int planeno);
int		seg_inter(POINT p1, POINT p2, POINT q1, POINT q2);
int		left_on(POINT p1, POINT p2, POINT q);

void main()
 {
   int	 i,x1,y1,x2,y2;
   POINT p1, p2;

   fp = fopen("feep.in", "r");

   fscanf(fp, "%d", &nsites);  /* Read sites */
   for (i=0; i<nsites; i++)
	{
	 fscanf(fp, "%d %d %d %d", &x1, &y1, &x2, &y2);
	 sites[i][0].x = x1; sites[i][0].y = y1;
	 sites[i][1].x = x2; sites[i][1].y = y2;
	}

   fscanf(fp, "%d", &nplanes); /* Read planes */
   for (i=0; i<nplanes; i++)
	{
	 fscanf(fp, "%d %d %d %d", &x1, &y1, &x2, &y2);
	 p1.x = x1; p1.y = y1;
	 p2.x = x2; p2.y = y2;
	 /* check and list all the sites over which the plane flies */
	 intersect(p1, p2, i);
	}
   fclose(fp);
 }

void intersect(POINT p1, POINT p2, int planeno)
 {
  int 	    i, flag;
  int 	    sx1, sy1, sx2, sy2;
  double    t;
  POINT	    q1, q2;

  for (i=0; i<nsites; i++)
   {

	sx1 = sites[i][0].x;   /* Retrieve the corners of the rectangle */
	sy1 = sites[i][0].y;
	sx2 = sites[i][1].x;
	sy2 = sites[i][1].y;

	q1.x = sx1; q1.y = sy1;
	q2.x = sx1; q2.y = sy2;

	flag = 0;

	/* check if path of the plane intersects any of the four edges of
	   the rectangle */

	if (seg_inter(q1, q2, p1, p2)==1) flag = 1;
	if (flag == 0)
	 {
	  q2.x = sx2; q2.y = sy1;
	  if (seg_inter(q1, q2, p1, p2)==1) flag = 1;
	 }
	if (flag == 0)
	 {
	  q1.x = sx2; q1.y = sy1;
	  q2.x = sx2; q2.y = sy2;
	  if (seg_inter(q1, q2, p1, p2)==1) flag = 1;
	 }
	if (flag == 0)
     {
      q1.x = sx1; q1.y = sy2;
      if (seg_inter(q1, q2, p1, p2)==1) flag = 1;
     }

    if (flag == 1)
      printf("Plane #%d would fly over nesting site #%d.\n",planeno+1, i+1);
   }
 }

int seg_inter(POINT p1, POINT p2, POINT q1, POINT q2)
/* Does segment p intersect segment q? */
 {
   int d1, d2, d3, d4;
   int pt1, pt2, qt1, qt2;
   int pp1, pp2, qp1, qp2;

   d1 = left_on(p1, p2, q1);
   d2 = left_on(p1, p2, q2);
   d3 = left_on(q1, q2, p1);
   d4 = left_on(q1, q2, p2);

   if ((d1==0) && (d2==0) && (d3==0) && (d4==0)) /* collinear segments */
	{
	 if (p1.y == p2.y) /* aligned with x axis */
	   {
		pt1 = p1.x; pt2 = p2.x;
		qt1 = q1.x; qt2 = q2.x;
	   }
	 else /* aligned with y axis */
	   {
		pt1 = p1.y; pt2 = p2.y;
		qt1 = q1.y; qt2 = q2.y;
	   }

	pp1 = (pt1>pt2)?pt2:pt1;
	pp2 = (pt1>pt2)?pt1:pt2;
	qp1 = (qt1>qt2)?qt2:qt1;
	qp2 = (qt1>qt2)?qt1:qt2;

	if ( ((qp1 <= pp1) && (qp2 >= pp1)) ||
		 ((qp1 >= pp1) && (qp1 <= pp2)) ) return 1;
	else return 0;
	}
   else
	{
	  if ((((d1 <= 0) && (d2 >= 0)) ||
			((d2 <= 0) && (d1 >= 0))) &&
			(((d3 <= 0) && (d4 >= 0)) ||
			((d4 <= 0) && (d3 >= 0))) ) return 1;
	 else return 0;
	}
 }

int left_on(POINT p1, POINT p2, POINT q)
/* Is q to the left or on segment p ? -1 if left, 0 if on, 1 if right*/
 {
  long det;

  det = (long) p1.x * (long) (q.y - p2.y) -
		(long) p1.y * (long)(q.x - p2.x) +
		((long) q.x * p2.y) - ((long) q.y * p2.x);

  if (det < 0) return -1;
   else if (det == 0) return 0;
	else return 1;
 }
