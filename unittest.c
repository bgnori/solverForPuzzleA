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
test_ok_up_match(void)
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
test_ok_up_mismatch(void)
{
    return NULL;
}

static
const_char_p
test_ok_left_match(void)
{
    return NULL;
}

static
const_char_p
test_ok_left_mismatch(void)
{
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
    test_ok_up_match,
    test_ok_up_mismatch,
    test_ok_left_match,
    test_ok_left_mismatch,
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



