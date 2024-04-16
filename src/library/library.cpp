#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "library.hpp"
// #include "../errors/errors.hpp"

// Write Functions
// ===============

void writeInteger(int integer) {
    printf("%d\n", integer);
}

void writeByte(char byte) {
    printf("%d\n", (int)byte);
}

void writeChar(char character) {
    printf("%c\n", character);
}

void writeString(char* refbyte) {
    printf("%s\n", refbyte);
}

// Read Functions
// ==============

int16_t readInteger() {
    int i;
    if (scanf("%d", &i) <= 0) {
        // RaiseTypeError(integerTypeError_c);
        exit(1);
    }

    if (i > 32767 || i < -32768) {
        // RaiseTypeError(integerOverflowError_c);
        exit(1);
    }

    return i;
}

int16_t readByte() {
    char i;
    if (scanf("%c", &i) <= 0){
        // RaiseTypeError(byteTypeError_c);
        exit(1);
    }

    if ((int)i > 255 || (int)i < 0) {
        // RaiseTypeError(byteTypeError_c);
        exit(1);
    }

    return (int)i;
}

uint8_t readChar(){
    char c;
    if (scanf("%c", &c) <= 0) {
        // RaiseTypeError(charTypeError_c);
        exit(1);
    }
    return c;
}

void readString(int n, char* refbyte){
    for (int i= 0; i < n; i++) {
        char c;

        if (i + 1 < n) {
            c = getchar();
        } else {
            c = '\0';
        }
    if ( c == '\n' || c == EOF) {
            c = '\0';
            *refbyte ++ = c;
            break;
        }

        *refbyte ++ = c;
    }

    return;
}

// Transformation Functions
// ========================

int16_t extend(char byte) {
    return (int) byte;
}

uint8_t shrink(int integer) {
    return (char) integer;
}

// String Functions
// ================

int16_t alan_strlen(char* s) {
    int16_t i = 0;
    while (s[i] != '\0') {
        i++;
    }
    return i;
}

int16_t alan_strcmp(char* s1, char* s2) {
    int i = 0;
    while (s1[i] == s2[i]) {
        if (s1[i] == '\0') {
            return 0;
        }
        i++;
    }
    return 1;
}

void alan_strcpy(char* trg, char* src) {
    int i = 0;
    while (src[i] != '\0') {
        trg[i] = src[i];
        i++;
    }
    trg[i] = '\0';
}

void alan_strcat(char* trg, char* src) {
    int i = 0;
    while (trg[i] != '\0') {
        i++;
    }
    alan_strcpy(trg + i, src);
}

// Test Functions
// ==============

int testIntegers() {
    int i = readInteger();
    writeInteger(i);
    return 0;
}

int testBytes() {
    unsigned char b = readByte();
    writeByte(b);
    return 0;
}

int testChars() {
    char c = readChar();
    writeChar(c);
    return 0;
}

int testString() {
    char refbyte[300];
    readString(100, refbyte);
    writeString(refbyte);
    return 0;
}

