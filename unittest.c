#include "puzzle.h"
typedef const char* const_char_p;
typedef const_char_p (*unittest)(void);

static
const_char_p
test_fact_0(void)
{
    if (fact[0] != 1)
        return __func__;
    return NULL;
}

static
const_char_p
test_fact_1(void)
{
    if (fact[1] != 1)
        return __func__;
    return NULL;
}

static
const_char_p
test_fact_6(void)
{
    if (fact[6] != 720)
        return __func__;
    return NULL;
}


static 
int
dfact(int n)
{
    if(n==0)
        return 1;
    return dfact(n-1) * n;
}

static
const_char_p
test_fact_x(void)
{
    int i;

    for (i=0; i < 11; i++){
        if (fact[i] != dfact(i))
            return __func__;
    }
    return NULL;
}

static
const_char_p
test_perfhash_0(void)
{
    int buf[9];
    int i;
    perfhash(0, buf);

    for(i=0; i < 9; i++){
        if (buf[i] != i){
            return __func__;
        }
    }

    return NULL;
}

static
const_char_p
test_perfhash_max(void)
{
    int buf[9];
    int i;
    perfhash(fact[9] - 1, buf);

    for(i=0; i < 9; i++){
        if (buf[i] != 8 - i){
            //expect: 8, 7, 6, 5, 4, 3, 2, 1, 0
            return __func__;
        }
    }
    return NULL;
}

static
const_char_p
test_rotate_clear(void)
{
    int buf[9];
    int i;
    bool ret;

    ret = rotate(-1, buf);
    if(!ret){
        return __func__;
    }
    for(i=0; i < 9; i++){
        if (buf[i] != 0){
            return __func__;
        }
    }
    return NULL;
}

static
const_char_p
test_rotate_ok(void)
{
    int buf[9] = {0,0,0,0,0,0,0,0,0,};
    int i;
    bool ret;

    ret = rotate(1, buf);
    if(!ret){
        return __func__;
    }
    for(i=0; i < 9; i++){
        if (i == 1) {
            if (buf[i] != 1){
                return __func__;
            }
        }else{
            if (buf[i] != 0){
                return __func__;
            }
        }
    }
    return NULL;
}

static
const_char_p
test_rotate_fail(void)
{
    int buf[9] = {0,3,0,0,0,0,0,0,0,};
    int i;
    bool ret;

    ret = rotate(1, buf);
    if(ret){
        return __func__;
    }
    for(i=0; i < 9; i++){
        if (i == 1) {
            if (buf[i] != 3){
                return __func__;
            }
        }else{
            if (buf[i] != 0){
                return __func__;
            }
        }
    }
    return NULL;
}

static 
void
setUpEasyTiles(TTile* tiles)
{
    int i;
    for(i=0; i<SIZE; i++){
        tiles[i].fPattern[0] = 1;
        tiles[i].fPattern[1] = 4;
        tiles[i].fPattern[2] = MATCHMASK - 1;
        tiles[i].fPattern[3] = MATCHMASK - 4;
    }
}

static 
void
setUpBadTiles(TTile* tiles)
{
    int i;
    for(i=0; i<SIZE; i++){
        tiles[i].fPattern[0] = 1;
        tiles[i].fPattern[1] = 4;
        tiles[i].fPattern[2] = MATCHMASK;
        tiles[i].fPattern[3] = MATCHMASK;
    }
}


static 
void
setUpBugTiles(TTile* tiles)
{
    //bugs
    // data set from http://d.hatena.ne.jp/rikunora/20111227/p1
    tiles[0].fPattern[0] = PURPLE_T;
    tiles[0].fPattern[1] = LADY_H;
    tiles[0].fPattern[2] = BEE_H;
    tiles[0].fPattern[3] = YELLOW_H;

    tiles[1].fPattern[0] = BEE_T;
    tiles[1].fPattern[1] = YELLOW_H;
    tiles[1].fPattern[2] = PURPLE_H;
    tiles[1].fPattern[3] = LADY_T;

    tiles[2].fPattern[0] = LADY_T;
    tiles[2].fPattern[1] = BEE_T;
    tiles[2].fPattern[2] = PURPLE_T;
    tiles[2].fPattern[3] = YELLOW_T;

    tiles[3].fPattern[0] = BEE_T;
    tiles[3].fPattern[1] = LADY_T;
    tiles[3].fPattern[2] = PURPLE_H;
    tiles[3].fPattern[3] = YELLOW_H;

    tiles[4].fPattern[0] = PURPLE_T;
    tiles[4].fPattern[1] = YELLOW_T;
    tiles[4].fPattern[2] = BEE_H;
    tiles[4].fPattern[3] = LADY_H;

    tiles[5].fPattern[0] = PURPLE_H;
    tiles[5].fPattern[1] = LADY_H;
    tiles[5].fPattern[2] = BEE_T;
    tiles[5].fPattern[3] = YELLOW_H;

    tiles[6].fPattern[0] = PURPLE_T;
    tiles[6].fPattern[1] = YELLOW_H;
    tiles[6].fPattern[2] = PURPLE_H;
    tiles[6].fPattern[3] = BEE_T;

    tiles[7].fPattern[0] = BEE_T;
    tiles[7].fPattern[1] = LADY_H;
    tiles[7].fPattern[2] = YELLOW_H;
    tiles[7].fPattern[3] = YELLOW_T;

    tiles[8].fPattern[0] = BEE_H;
    tiles[8].fPattern[1] = PURPLE_H;
    tiles[8].fPattern[2] = LADY_H;
    tiles[8].fPattern[3] = LADY_T;
};

static
void
setUpTrivialPlacemnet(TPlacement* placement)
{
    int i;
        
    perfhash(0, placement->fPermutation);
    for(i=0; i < SIZE;i++){
        placement->fRotation[i] = 0;
    }
}

static
const_char_p
test_ok_up_match_0(void)
{
    TTile tiles[9];
    TPlacement placement[9];

    setUpEasyTiles(tiles);
    setUpTrivialPlacemnet(placement);

    if(!ok_up(0, tiles, placement))
        return __func__;
    return NULL;
}

static
const_char_p
test_ok_up_match_3(void)
{
    TTile tiles[9];
    TPlacement placement[9];

    setUpEasyTiles(tiles);
    setUpTrivialPlacemnet(placement);

    if(!ok_up(0, tiles, placement))
        return __func__;
    return NULL;
}


static
const_char_p
test_ok_up_mismatch_3(void)
{
    TTile tiles[9];
    TPlacement placement[9];

    setUpBadTiles(tiles);
    setUpTrivialPlacemnet(placement);

    if(ok_up(3, tiles, placement))
        return __func__;
    return NULL;
}

static
const_char_p
test_ok_left_match_0(void)
{
    TTile tiles[9];
    TPlacement placement[9];

    setUpEasyTiles(tiles);
    setUpTrivialPlacemnet(placement);

    if(!ok_left(0, tiles, placement))
        return __func__;
    return NULL;
}

static
const_char_p
test_ok_left_match_1(void)
{
    TTile tiles[9];
    TPlacement placement[9];

    setUpEasyTiles(tiles);
    setUpTrivialPlacemnet(placement);

    if(!ok_left(1, tiles, placement))
        return __func__;
    return NULL;
}

static
const_char_p
test_ok_left_mismatch_1(void)
{
    TTile tiles[9];
    TPlacement placement[9];

    setUpBadTiles(tiles);
    setUpTrivialPlacemnet(placement);

    if(ok_left(1, tiles, placement))
        return __func__;
    return NULL;
}

static
const_char_p
test_with_bugs_all(void)
{
    TTile tiles[9];
    TPlacement placement[9];

    setUpBugTiles(tiles);
    setUpTrivialPlacemnet(placement);

    if(failed_at(tiles, placement) != -1)
        return __func__;
    return NULL;
}

static
const_char_p
test_with_bugs_1_left(void)
{
    TTile tiles[9];
    TPlacement placement[9];

    setUpBugTiles(tiles);
    setUpTrivialPlacemnet(placement);

    if(!ok_left(1, tiles, placement))
        return __func__;

    return NULL;
}


static
const_char_p
test_with_bugs_1_left_step0(void)
{
    if(idx2h(1) == 0)
        return __func__;
    return NULL;
}

static
const_char_p
test_with_bugs_1_left_step2(void)
{

    int h, v, n, idx;
    idx = 1;

    h = idx2h(idx);
    v = idx2v(idx);
    n = hv2idx(h - 1, v);
    if ( n != 0)
        return __func__;
    return NULL;
}


static
const_char_p
test_with_bugs_1_left_step3(void)
{
    TTile tiles[9];
    TPlacement placement[9];

    setUpBugTiles(tiles);
    setUpTrivialPlacemnet(placement);

    if ((get_pattern(0, tiles, placement, 3) ^ get_pattern(1, tiles, placement, 1) ^ MATCHMASK) != MATCHMASK)
        return __func__;
    return NULL;
}

unittest cases[] = {
    test_fact_0,
    test_fact_1,
    test_fact_6,
    test_fact_x,
    test_perfhash_0,
    test_perfhash_max,
    test_rotate_clear,
    test_rotate_ok,
    test_rotate_fail,
    test_ok_up_match_0,
    test_ok_up_match_3,
    test_ok_up_mismatch_3,
    test_ok_left_match_0,
    test_ok_left_match_1,
    test_ok_left_mismatch_1,
    test_with_bugs_1_left,
    test_with_bugs_1_left_step0,
    test_with_bugs_1_left_step2,
    test_with_bugs_1_left_step3,
    test_with_bugs_all,
};

int
main(int argc, const char** argv)
{
    int i, len;
    const_char_p msg;
    unittest u;

    len = sizeof(cases)/sizeof(unittest);

    for(i = 0; i < len; i++){
        u = cases[i];
        msg = u();
        if(msg){
            printf("!\n");
            printf("fail, %s\n", msg);
        }else{
            printf(".");
        }
    }

    return 0;
}



