#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 256

const char symbols[] = "ADFGVX";

// 6x6 Polybius square
const char square[6][6] = {
    {'A', 'B', 'C', 'D', 'E', 'F'},
    {'G', 'H', 'I', 'J', 'K', 'L'},
    {'M', 'N', 'O', 'P', 'Q', 'R'},
    {'S', 'T', 'U', 'V', 'W', 'X'},
    {'Y', 'Z', '0', '1', '2', '3'},
    {'4', '5', '6', '7', '8', '9'}
};

// Convert character to coordinates in Polybius square
void get_coordinates(char c, int *row, int *col) {
    

}

