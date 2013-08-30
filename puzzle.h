#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define HSIZE 3
#define VSIZE 3
#define SIZE 9

#define MATCHMASK (8+4+2+1)

#define CRAB_L (8+4+2)
#define CRAB_R (1)

#define FISH_H (8+4+1)
#define FISH_T (2)

#define DRAGON_H (8+2+1)
#define DRAGON_T (4)

#define SHELLS_S (4+2+1)
#define SHELLS_N (8)

typedef struct {
    int fPattern[4];
    /*
     *   0
     * 3   1
     *   2
     */
} TTile;

typedef struct {
    int fPermutation[9];
    int fRotation[9];
} TPlacement;


extern int fact[];
void perfhash(int n, int* buf);
bool rotate(int idx, int* buf);
bool ok_up(int idx, TTile* tiles, TPlacement* p);
bool ok_left(int idx, TTile* tiles, TPlacement* p);

int failed_at(TTile* tiles, TPlacement* p);
bool solve(TTile* tiles, TPlacement* p, int* start, int end);

