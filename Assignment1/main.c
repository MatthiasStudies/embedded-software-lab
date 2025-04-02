#include <stdio.h>
#include <stdbool.h>

#define SEQ_LEN 1023
#define NUM_SEQUENCES 24

void rotate10bit(bool bits[10], bool nextValue) {
    for(int i = 9; i > 0; i--) {
        bits[i] = bits[i-1];
    }
    bits[0] = nextValue;
}

bool xor10Bit(bool bits[10], int* arr, size_t len ) {
    int result = 0;
    int *end = arr + len;
    while (arr < end) {
        result ^= bits[*arr];
        arr++;
    }
    return result;
}

bool nextXValue(bool upper[10], bool lower[10], int reg1, int reg2) {
    int sequenceIndexes[2] = {reg1, reg2};
    bool nextXLower = xor10Bit(lower, sequenceIndexes, 2);
    bool nextXUpper = upper[9];
    return nextXLower ^ nextXUpper;
}



int main(void) {
    bool upperPart[10] = {1,1,1,1,1,1,1,1,1,1};
    bool lowerPart[10] = {1,1,1,1,1,1,1,1,1,1};
    int upperNextValueIndexes[2] = {2, 9};
    int lowerNextValueIndex[6] = {1,2,5,7,8,9};

    int registerSums[24][2] = {
            {1,5},
            {2,6},
            {3,7},
            {4,8},
            {0,8},
            {1,9},
            {0,7},
            {1,8},
            {2,9},
            {1,2},
            {2,3},
            {4,5},
            {5,6},
            {6,7},
            {7,8},
            {8,9},
            {0,3},
            {1,4},
            {2,5},
            {3,6},
            {4,7},
            {5,8},
            {0,2},
            {3,5},
    };

    bool chipsequences[NUM_SEQUENCES][SEQ_LEN];


    for (int i = 0; i < SEQ_LEN; i++) {
        for (int j = 0; j < 24; j++) {
            bool nextX = nextXValue(upperPart, lowerPart, registerSums[j][0], registerSums[j][1]);
            chipsequences[j][i] = nextX;
        }

        bool upperNext = xor10Bit(upperPart, upperNextValueIndexes, 2);
        rotate10bit(upperPart, upperNext);

        bool lowerNext = xor10Bit(lowerPart, lowerNextValueIndex, 6);
        rotate10bit(lowerPart, lowerNext);
    }

    for (int i = 0; i < NUM_SEQUENCES; i++) {
        printf("Reg %d %d: ", registerSums[i][0]+1, registerSums[i][1]+1);
        for (int j = 0; j < SEQ_LEN; j++) {
            printf("%d ", chipsequences[i][j]);
        }
        printf("\n");
    }
}
