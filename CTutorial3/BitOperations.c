#include <stdio.h>
#include <stdint.h>

// Question 1
void printBits(int num) {
    int mask = 1 << 31;
    for (int i = 0; i < 32; i++) {
        if (i == 16) printf(" ");
        printf("%i", ((num << i) & mask) == mask);
    }
}

// Question 3
void printBits16(uint16_t num) {
    int mask = 1 << 15;
    for (int i = 0; i < 16; i++) {
        printf("%i", (num & mask) == mask);
        mask >>= 1;
    }
}

// Question 7
void printSBits16(int16_t num) {
    int mask = 1 << 15;
    for (int i = 0; i < 16; i++) {
        printf("%i", (num & mask) == mask);
        mask >>= 1;
    }
}

void main(void) {
    // Question 1
    int n = 1288243249;
    printBits(n);
    printf("\n");
    // Question 2
    uint16_t first = (n >> 16) & 0xFFFF;
    uint16_t second = n & 0xFFFF;
    // Question 3
    printBits16(first);
    printf(" ");
    printBits16(second);
    printf("\n");
    // Question 4
    printBits(first);
    printf(" ");
    printBits(second);
    printf("\n");
    // Question 5
    int16_t signedFirst = first;
    printf("%d, %d\n", first, signedFirst);
    // Question 6
    first <<= 1;
    signedFirst = first;
    printf("%d, %d\n", first, signedFirst);
    // Question 7
    printBits16(first);
    printf(", ");
    printSBits16(signedFirst);
    printf("\n");
}