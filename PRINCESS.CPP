/******************************************************************/
/* Eleventh Annual UCF ACM UPE High School Programming Tournament */
/* May 2, 1997                                                    */
/*                                                                */
/* Judges' solution to the problem "Princess's Escape Plan"       */
/*                                                                */
/* Original problem idea by Eric Heimburg                         */
/* Solution by Bryan Kline                                        */
/******************************************************************/

// PRINCESS.CPP

#include <stdio.h>
#include <math.h>

// This array size is 1500 because largest possible distance between
// princess and goblin is just over 1400; the size is too large just
// to be safe.
#define ARRAY_SIZE	1500

struct TPoint
	{
	long x;
	long y;
	};

TPoint princess, goblin;
int hitCount[ARRAY_SIZE];

// Find the distance between the two given points
double dist(TPoint one, TPoint two)
	{
	long dx, dy;

	dx = one.x - two.x;
	dy = one.y - two.y;

	return sqrt((dx*dx) + (dy*dy));
	}

void main()
	{
	FILE *inFile;
	int loop, slot;
	double distance;
	int max, result;
	int goblinCount;

	inFile = fopen("princess.in", "r");

	// Read goblin locations until goblinCount == 0
	fscanf(inFile, "%d\n", &goblinCount);
	while (goblinCount > 0)
		{
		fscanf(inFile, "%ld %ld\n", &(princess.x), &(princess.y));
		for (loop = 0; loop < ARRAY_SIZE; loop++)
			hitCount[loop] = 0;

		for (loop = 0; loop < goblinCount; loop++)
			{
			fscanf(inFile, "%ld %ld\n", &(goblin.x), &(goblin.y));

			// Since the goblins are 1 unit in diameter, and the crown basically
			// has no diameter, any rope radius that comes within 0.5 units of the
			// distance between the center of the princess and the center of the
			// goblin will hit it. This amounts to being the nearest integer rope
			// length to the real distance between the two. A simple roundoff works.
			distance = dist(princess, goblin);
			slot = floor(distance + 0.5);	// Round to nearest integer
			(hitCount[slot])++;	// Mark that we hit a goblin at that radius
			} // End of counting goblins loop

		// Search through the array to find the radius with the largest number of
		// hits. This is done from back to front because if the number of hits is
		// the same, the one with the smallest radius is to be chosen.
		max = 0;
		for (loop = (ARRAY_SIZE - 1); loop >= 0; loop--)
			if (hitCount[loop] >= max)
				{
				max = hitCount[loop];
				result = loop;
				}

		printf("%d\n", result);

		fscanf(inFile, "%d\n", &goblinCount);
		} // while goblinCount > 0
	}
