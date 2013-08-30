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
test_perfhash_x(void)
{
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


/*
        if (false){
            for(i=0; i<SIZE; i++){
                tiles[i].fPattern[0] = 1;
                tiles[i].fPattern[1] = 4;
                tiles[i].fPattern[2] = MATCHMASK - 1;
                tiles[i].fPattern[3] = MATCHMASK - 4;
            }
            for(i=0; i<SIZE; i++){
                tiles[i].fPattern[0] = 1;
                tiles[i].fPattern[1] = 4;
                tiles[i].fPattern[2] = MATCHMASK;
                tiles[i].fPattern[3] = MATCHMASK;
            }
        }
*/



unittest cases[] = {
    test_fact_0,
    test_fact_1,
    test_fact_6,
    test_fact_x,
    test_perfhash_0,
    test_perfhash_max,
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



