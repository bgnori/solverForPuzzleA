#include "puzzle.h"

//            0! 1! 2! 3! 4!  5!   6!   7!    8!     9!      10!
int fact[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800};

static int
idx2h(int idx)
{
    return idx % HSIZE;
}

static int
idx2v(int idx)
{
    return idx / HSIZE;
}

static int
hv2idx(int h, int v)
{
    return h + v*HSIZE;
}

void
perfhash(int n, int* buf)
{
    /* 
     * calculate permunation from hash
     * http://www.ic-net.or.jp/home/takaken/nt/slide/hash.html
     */
    int i;
    int nth;
    //                    0, 1, 2, 3, 4, 5, 6, 7, 8, 9
    int availables[10] = {0, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int found;

    for(i = 0; i < SIZE; i++){
        nth = n / fact[8 - i];

        found = -1;
        while(nth > -1){
            found++;
            if(availables[found]){
                nth--;
            }
        }
        availables[found] = 0;
        buf[i] = found - 1; 

        n = n % fact[8-i];
    }
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
    if(buf[idx] >= 3){
        return false;
    }
    buf[idx] ++;
    return true;
}

int
get_pattern(int idx, TTile* tiles, TPlacement* p, int direction)
{
    return (tiles[p->fPermutation[idx]]).fPattern[direction];
}

bool
ok_up(int idx, TTile* tiles, TPlacement* p)
{
    int h, v;
    int n;

    if(idx < HSIZE)
        return true;
    h = idx2h(idx);
    v = idx2v(idx);
    n = hv2idx(h - 1, v);

    return !((get_pattern(n, tiles, p, 2) ^ get_pattern(idx, tiles, p, 0) ^ MATCHMASK) & MATCHMASK);
}

bool
ok_left(int idx, TTile* tiles, TPlacement* p)
{
    int h, v;
    int n;

    h = idx2h(idx);
    if (h == 0)
        return true;
    v = idx2v(idx);
    n = hv2idx(h - 1, v);

    return !((get_pattern(n, tiles, p, 3) ^ get_pattern(idx, tiles, p, 1) ^ MATCHMASK) & MATCHMASK);
}


int
try_placement(TTile* tiles, TPlacement* p)
{
    int idx;
    bool ok;

    for (idx=0; idx < SIZE; idx++){
        ok = ok_up(idx, tiles, p) && ok_left(idx, tiles, p);
        //testing left to right, top to bottom.
        if(!ok)
            return idx;//failed at.
    }
    return -1; //success. valid way to place tiles.
}

bool
solve(TTile* tiles, TPlacement* p, int* start, int end)
{
    int i;
    int at;

    for(i = *start; i < end; i++){
        perfhash(i, p->fPermutation);
        at = -1;
        while(rotate(at, p->fRotation)){
            at = try_placement(tiles, p);
            if (at < 0){
                *start = i;
                return true;
            }
        }
    }
    return false;
}

