#include <stdio.h>
#include <stdbool.h>

#define SEQ_LEN 1023
#define NUM_SEQUENCES 24
#define SHIFT_REGISTER_LENGTH 10

const int registerSums[NUM_SEQUENCES][2] = {
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

void rotateMotherSequence(bool bits[SHIFT_REGISTER_LENGTH], const bool nextValue) {
    for(int i = SHIFT_REGISTER_LENGTH-1; i > 0; i--) {
        bits[i] = bits[i-1];
    }
    bits[0] = nextValue;
}

bool motherSequenceXOR(const bool bits[10], const int* indexes_arr, const size_t len) {
    int result = 0;
    const int *end = indexes_arr + len;
    while (indexes_arr < end) {
        result ^= bits[*indexes_arr];
        indexes_arr++;
    }
    return result;
}

bool nextChipSequenceBit(const bool upper[SHIFT_REGISTER_LENGTH], const bool lower[SHIFT_REGISTER_LENGTH], const int register1, const int register2) {
    const int sequenceIndexes[2] = {register1, register2};
    const bool nextXLower = motherSequenceXOR(lower, sequenceIndexes, 2);
    const bool nextXUpper = upper[9];
    return nextXLower ^ nextXUpper;
}

void generateChipSequences(bool chipSequences[NUM_SEQUENCES][SEQ_LEN], const int registers[NUM_SEQUENCES][2]) {
    bool motherSequence1[SHIFT_REGISTER_LENGTH] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    bool motherSequence2[SHIFT_REGISTER_LENGTH] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    const int upperNextValueIndexes[2] = {2, 9};
    const int lowerNextValueIndexes[6] = {1, 2, 5, 7, 8, 9};

    for (int i = 0; i < SEQ_LEN; i++) {
        for (int j = 0; j < NUM_SEQUENCES; j++) {
            const bool nextX = nextChipSequenceBit(motherSequence1, motherSequence2, registers[j][0], registers[j][1]);
            chipSequences[j][i] = nextX;
        }

        const bool upperNext = motherSequenceXOR(motherSequence1, upperNextValueIndexes, 2);
        rotateMotherSequence(motherSequence1, upperNext);

        const bool lowerNext = motherSequenceXOR(motherSequence2, lowerNextValueIndexes, 6);
        rotateMotherSequence(motherSequence2, lowerNext);
    }
}


int main(void) {
    bool chipSequences[NUM_SEQUENCES][SEQ_LEN];
    generateChipSequences(chipSequences, registerSums);

    for (int i = 0; i < NUM_SEQUENCES; i++) {
        const bool* chipSequence = chipSequences[i];
        const int* registers = registerSums[i];
        printf("Reg %d %d:\t ", registers[0]+1, registers[1]+1);
        for (int j = 0; j < SEQ_LEN; j++) {
            printf("%d", chipSequence[j]);
        }
        printf("\n");
    }
}
