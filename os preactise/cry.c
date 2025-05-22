#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Function to reverse columnar transposition
void reverseTransposition(char *cipher, char *key, char *output) {
    int keyLength = strlen(key);
    int textLength = strlen(cipher);
    int rows = textLength / keyLength;
    int col = 0, row = 0;

    // Array to hold columns
    char columns[keyLength][rows + 1];

    // Sort the key alphabetically to get the correct column order
    char sortedKey[keyLength];
    strcpy(sortedKey, key);
    for (int i = 0; i < keyLength; i++) {
        for (int j = i + 1; j < keyLength; j++) {
            if (sortedKey[i] > sortedKey[j]) {
                char temp = sortedKey[i];
                sortedKey[i] = sortedKey[j];
                sortedKey[j] = temp;
            }
        }
    }

    // Distribute cipher characters into columns based on sorted key
    int index = 0;
    for (int i = 0; i < keyLength; i++) {
        for (int j = 0; j < rows; j++) {
            int keyIndex = strchr(sortedKey, key[i]) - sortedKey;
            columns[keyIndex][j] = cipher[index++];
        }
    }

    // Reconstruct the text from columns based on the original key order
    index = 0;
    for (int i = 0; i < keyLength; i++) {
        for (int j = 0; j < rows; j++) {
            output[index++] = columns[i][j];
        }
    }
    output[index] = '\0';
}

// Function to check if the known plaintext exists in the result
int containsKnownPlaintext(char *decryptedText, char *knownPlaintext) {
    return strstr(decryptedText, knownPlaintext) != NULL;
}

int main() {
    // Example ciphertext and known plaintext
    char cipher[] = "XVGXADFDADGX";  // Example ciphertext (ADFGVX format)
    char knownPlaintext[] = "ATTACK";  // Known part of the plaintext
    char key[] = "CIPHER";  // The guessed key

    char decryptedText[strlen(cipher) + 1];  // To store the decrypted result

    // Try to reverse the columnar transposition
    reverseTransposition(cipher, key, decryptedText);

    // Check if the known plaintext is part of the result
    if (containsKnownPlaintext(decryptedText, knownPlaintext)) {
        printf("Possible key found: %s\n", key);
        printf("Decrypted intermediate text: %s\n", decryptedText);
    } else {
        printf("Key does not match.\n");
    }

    return 0;
}
