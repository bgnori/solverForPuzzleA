#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define HSIZE 3
#define VSIZE 3
#define SIZE 9
#define FACT9 362880

#define MATCHMASK (8+4+2+1)
// UGH!

void
perfhash(int i, int* buf)
{
    /* 
     * calculate permunation from hash
     */

}


bool
rotate(int idx, int* buf)
{
    int i;
    if(idx == -1){
        for(i=0;i<SIZE;i++){
            buf[i] = 0;
        }
        return true;
    }

    return false;
}

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


int
idx2h(int idx)
{
    return idx % HSIZE;
}

int
idx2v(int idx)
{
    return idx / HSIZE;
}

int
hv2idx(int h, int v)
{
    return h + v*HSIZE;
}

int
get_pattern(int idx, TTile* tiles, TPlacement* p, int direction)
{
    return (tiles[p->fPermutation[idx]]).fPattern[direction];
}

bool
test_up(int idx, TTile* tiles, TPlacement* p)
{
    int h, v;
    int n;

    if(idx < HSIZE)
        return true;
    h = idx2h(idx);
    v = idx2v(idx);
    n = hv2idx(h - 1, v);

    return !(get_pattern(n, tiles, p, 2) ^ get_pattern(idx, tiles, p, 0) ^ MATCHMASK);
}

bool
test_left(int idx, TTile* tiles, TPlacement* p)
{
    int h, v;
    int n;

    h = idx2h(idx);
    if (h == 0)
        return true;
    v = idx2v(idx);
    n = hv2idx(h - 1, v);

    return !(get_pattern(n, tiles, p, 3) ^ get_pattern(idx, tiles, p, 1) ^ MATCHMASK);
}


int
try_placement(TTile* tiles, TPlacement* p)
{
    int idx;
    bool ok;

    for (idx=0; idx < SIZE; idx++){
        ok = test_up(idx, tiles, p) && test_left(idx, tiles, p);
        //testing left to right, top to bottom.
        if(!ok)
            return idx;//failed at.
    }
    return -1; //success. valid way to place tiles.
}


TPlacement* 
solve(TTile* tiles)
{
    int i;
    int at;
    TPlacement* p;

    p = malloc(sizeof(TPlacement));

    for(i = 0; i < FACT9; i++){
        perfhash(i, p->fPermutation);
        at = -1;
        while(rotate(at, p->fRotation)){
            at = try_placement(tiles, p);
            if (at < 0){
                return p;
            }
        }
    }
    return 0;
}

int
main(int argc, char** argv)
{
    int i;
    TTile tiles[9];
    TPlacement* p;

    for(i=0; i<SIZE; i++){
        tiles[i].fPattern[0] = 1;
        tiles[i].fPattern[1] = 4;
        tiles[i].fPattern[2] = MATCHMASK - 1;
        tiles[i].fPattern[3] = MATCHMASK - 4;
    }

    p = solve(tiles);
    if (p){
        for(i=0; i<SIZE; i++){
            printf("%d th -> (%d, %d)\n", i, p->fPermutation[i], p->fRotation[i]);
        }
    }else{
        printf("No solution.\n");
    }
}
