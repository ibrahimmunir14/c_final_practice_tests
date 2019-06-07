#include <stdbool.h>
#include <stdio.h>

const int codeSize = 4;

bool anotherGame(void);
void readGuess(int guess[codeSize]);
int blackScore(int guess[codeSize], int code[codeSize]);
int whiteScore(int guess[codeSize], int code[codeSize]);
void printScore(int guess[codeSize], int code[codeSize]);

void main(void) {
    int codes[5][4] = {{1, 8, 9, 2},{2, 4, 6, 8},{1, 9, 8, 3},{7, 4, 2, 1},{4, 6, 8, 9}};
    int numCodes = sizeof(codes)/sizeof(codes[0]);

    for (int i = 0; i < numCodes; i++) {
        int guess[codeSize];
        readGuess(guess);
        while (blackScore(guess, codes[i]) != codeSize) {
            printScore(guess, codes[i]);
            readGuess(guess);
        }
        printf("You have guessed correctly!\n");
        if (i < numCodes - 1) {
            if (!anotherGame()) {
                break;
            }
        }
    }
}

bool anotherGame(void) {
    char answer;
    do {
        printf("Do you want to play another game? [y/n]: ");
        fflush(stdout);
        fflush(stdin);
        answer = getchar();
    } while (!(answer == 'y' || answer == 'n'));
    return answer == 'y';
}

void readGuess(int guess[codeSize]) {
    printf("Enter your guess: ");
    fflush(stdout);
    fflush(stdin);
    for (int i = 0; i < codeSize; i++) {
        do {
            scanf("%i", &guess[i]);
        } while (guess[i] < 1 || guess[i] > 9);
    }
}

int blackScore(int guess[codeSize], int code[codeSize]) {
    int score = 0;
    for (int i = 0; i < codeSize; i++) {
        if (code[i] == guess[i]) {
            score++;
        }
    }
    return score;
}

int whiteScore(int guess[codeSize], int code[codeSize]) {
    int score = 0;
    for (int i = 0; i < codeSize; i++) {
        for (int j = 0; j < codeSize; j++) {
            if (i != j && code[i] == guess[j]) {
                score++;
            }
        }
    }
    return score;
}

void printScore(int guess[codeSize], int code[codeSize]) {
    printf("(%i, %i)\n", blackScore(guess, code), whiteScore(guess, code));
    fflush(stdout);
}