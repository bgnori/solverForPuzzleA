#include "puzzle.h"

#define TEST false

// UGH!

#define CHUNK 100000
#define SHOW true


int
main(int argc, char** argv)
{
    int i;
    int start;
    int end;
    int count;
    int ln;
    bool found;
    TTile tiles[9];
    TPlacement p;

    //real data

    tiles[0].fPattern[0] = SHELLS_S;
    tiles[0].fPattern[1] = SHELLS_N;
    tiles[0].fPattern[2] = DRAGON_H;
    tiles[0].fPattern[3] = FISH_H;

    tiles[1].fPattern[0] = FISH_T;
    tiles[1].fPattern[1] = CRAB_L;
    tiles[1].fPattern[2] = DRAGON_H;
    tiles[1].fPattern[3] = SHELLS_N;

    tiles[2].fPattern[0] = FISH_H;
    tiles[2].fPattern[1] = DRAGON_T;
    tiles[2].fPattern[2] = FISH_T;
    tiles[2].fPattern[3] = CRAB_R;

    tiles[3].fPattern[0] = DRAGON_T;
    tiles[3].fPattern[1] = CRAB_R;
    tiles[3].fPattern[2] = FISH_H;
    tiles[3].fPattern[3] = SHELLS_S;

    tiles[4].fPattern[0] = DRAGON_T;
    tiles[4].fPattern[1] = CRAB_R;
    tiles[4].fPattern[2] = FISH_H;
    tiles[4].fPattern[3] = SHELLS_N;

    tiles[5].fPattern[0] = FISH_H;
    tiles[5].fPattern[1] = CRAB_R;
    tiles[5].fPattern[2] = DRAGON_T;
    tiles[5].fPattern[3] = SHELLS_N;

    tiles[6].fPattern[0] = FISH_T;
    tiles[6].fPattern[1] = CRAB_L;
    tiles[6].fPattern[2] = SHELLS_N;
    tiles[6].fPattern[3] = DRAGON_T;

    tiles[7].fPattern[0] = DRAGON_H;
    tiles[7].fPattern[1] = CRAB_R;
    tiles[7].fPattern[2] = FISH_T;
    tiles[7].fPattern[3] = SHELLS_S;

    tiles[8].fPattern[0] = CRAB_R;
    tiles[8].fPattern[1] = CRAB_L;
    tiles[8].fPattern[2] = DRAGON_T;
    tiles[8].fPattern[3] = SHELLS_S;


    count = 0;
    printf("argc= %d\n", argc);
    if (argc == 1){
        start = 0;
    }else{
        sscanf(argv[1], "%i", &start);
        printf("start = %d\n", start);
    }
    ln = 0;
    while(start < fact[9]){
        if(start + CHUNK < fact[9]){
            end =  start + CHUNK;
        }else{
            end = fact[9];
        }
        printf("end= %d\n", end);

        found = solve(tiles, &p, &start, end);
        if (found){
            count++;
            start++;
            if(SHOW){
                for(i=0; i<SIZE; i++){
                    printf("%d th -> (%d, %d)\n", i, p.fPermutation[i], p.fRotation[i]);
                }
            }else{
                printf("!");
            }
        }else{
            //fwrite(".", 1, 1, stdout);
            if (false){
                printf(".");
                ln ++;
                if (ln >= 20){
                    printf("\n");
                    ln = 0;
                }
                fflush(stdout);
            }
        }
    }
    printf("\n");
    printf("=====\n");
    printf("%d solutions found.\n", count);
    fflush(stdout);
    return 0;
}

