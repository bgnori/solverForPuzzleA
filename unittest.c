#include "puzzle.h"

static const char*
test_fact_0()
{
    if (fact[0] != 1)
        return __func__;
    return NULL;
}

static const char*
test_fact_1()
{
    if (fact[1] != 1)
        return __func__;
    return NULL;
}

static const char*
test_fact_6()
{
    if (fact[6] != 720)
        return __func__;
    return NULL;
}


static bool
test_perfhash(void)
{
    int buf[9];
    int i;
    bool ret = true;
    perfhash(fact[9] - 1, buf);

    for(i=0; i < 9; i++){
        printf("%d,", buf[i]);
        ret = ret && (buf[i] == 8 - i);
    }

    perfhash(0, buf);
    for(i=0; i < 9; i++){
        printf("%d,", buf[i]);
        ret = ret && (buf[i] == i);
    }
    return ret;

    // return __func__;
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


typedef const char* const_char_p;
typedef const_char_p (*unittest)(void);

unittest cases[] = {
    test_fact_0,
    test_fact_1,
    test_fact_6,
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



