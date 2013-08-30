#include "puzzle.h"

bool
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

int
main(int argc, char** argv)
{
    printf("%d\n", test_perfhash());
    return 0;
}





