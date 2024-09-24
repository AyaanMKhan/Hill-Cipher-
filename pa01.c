/*============================================================================
| Assignment: pa01 - Encrypting a plaintext file using the Hill cipher
|
| Author: Ayaan Khan
| Language: C
| To Compile: javac pa01.java
| gcc -o pa01 pa01.c
| To Execute: c -> ./pa01 kX.txt pX.txt
| where kX.txt is the keytext file
| and pX.txt is plaintext file
| Note:
| All input files are simple 8 bit ASCII input
| All execute commands above have been tested on Eustis
|
| Class: CIS3360 - Security in Computing - Fall 2024
| Instructor: McAlpin
| Due Date: September 29th 2024
+===========================================================================*/
#include <stdio.h>
#include <ctype.h>

void hillCipher(char *plain, int matrix[][9], int index, int size){

    int block[size];
    char cipherText[10000];
    int cipherIndex = 0;

    for(int i = 0; i < index; i += size){

        for(int j = 0; j < size; j++){
            block[j] = plain[i + j] - 'a';
        }

        for(int k = 0; k < size; k++){
            int sum = 0;
            for(int l = 0; l < size; l++){
                sum += matrix[k][l] * block[l];
            }
            cipherText[cipherIndex++] = (sum % 26) + 'a';
        }

    }
    cipherText[cipherIndex] = '\0';


    printf("Ciphertext: \n");
    for(int i = 0; i < cipherIndex; i++){
        printf("%c", cipherText[i]);
        // Every 80 letters in a row, it is required to make a new line
        if((i + 1) % 80 == 0){
            printf("\n");
        }
    }
    printf("\n");
}


int main(int argc, char *argv[]){

    int size = 9;
    FILE *key;
    int matrix[size][size];  // Supports matrix sizes from 2x2 up to 9x9

    // Open the key file
    key = fopen("k1.txt", "r");
    
    fscanf(key, "%d", &size);

    printf("Key matrix:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            fscanf(key, "%d", &matrix[i][j]);
            // Using 4d as for the integer format required
            printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }
    
    fclose(key);
    printf("\n");


    FILE* plain;
    plain = fopen("p1.txt", "r");

    char string[10000];
    int index = 0;
    char character;

    while((character = fgetc(plain)) != EOF){
        if(isalpha(character)){
            string[index++] = tolower(character);
        }
    }

    fclose(plain);


    // Padding the last part of the buffer with x
    while(index % size != 0){
        string[index++] = 'x';
    }
    // Null terminator indicates the end of the string
    string[index] = '\0';

    printf("Plaintext: ");
    for(int i = 0; i < index; i++){
        printf("%c", string[i]);
        if((i + 1) % 80 == 0){
            printf("\n");
        }
    }
    printf("\n\n");
    
    hillCipher(string, matrix, index, size);

}


/*=============================================================================
| I Ayaan Khan 5547292 affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/