// STD Library for Alan Programming Language
// Author: Elisavet Papadopoulou, Avgerinos Petros

#include <stdio.h>
#include <stdint.h>

#include "library.hpp"
#include "../errors/errors.hpp"

// Write Functions
// ===============

void writeInteger(int16_t integer) {
    printf("%d\n", integer);
}

void writeByte(char byte) {
    printf("%d\n", (int)byte);
}

void writeChar(uint8_t character) {
    printf("%c\n", character);
}

void writeString(uint8_t* refbyte) {
    printf("%s\n", refbyte);
}

// Read Functions
// ==============

int16_t readInteger() {
    int32_t i;
    if (scanf("%d", &i) <= 0) {
        RaiseTypeError(integerTypeError_c);
    }

    if (i > 32767 || i < -32768) {
        RaiseTypeError(integerOverflowError_c);
    }

    return i;
}

int16_t readByte() {
    char i;
    if (scanf("%c", &i) <= 0){
        RaiseTypeError(byteTypeError_c);
    }

    if ((int16_t)i > 255 || (int16_t)i < 0) {
        RaiseTypeError(byteTypeError_c);
    }

    return (int16_t)i;
}

uint8_t readChar(){
    uint8_t c;
    if (scanf("%c", &c) <= 0) {
        RaiseTypeError(charTypeError_c);
    }
    return c;
}

void readString(int32_t n, uint8_t* refbyte){
    for (int8_t i= 0; i < n; i++) {
        int8_t c;

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

int16_t extend(uint8_t byte) {
    return (int16_t) byte;
}

uint8_t shrink(int16_t integer) {
    return (uint8_t) integer;
}

// String Functions
// ================

int16_t alan_strlen(uint8_t* s) {
    int16_t i = 0;
    while (s[i] != '\0') {
        i++;
    }
    return i;
}

int16_t alan_strcmp(uint8_t* s1, uint8_t* s2) {
    int16_t i = 0;
    while (s1[i] == s2[i]) {
        if (s1[i] == '\0') {
            return 0;
        }
        i++;
    }
    return 1;
}

void alan_strcpy(uint8_t* trg, uint8_t* src) {
    int16_t i = 0;
    while (src[i] != '\0') {
        trg[i] = src[i];
        i++;
    }
    trg[i] = '\0';
}

void alan_strcat(uint8_t* trg, uint8_t* src) {
    int16_t i = 0;
    while (trg[i] != '\0') {
        i++;
    }
    alan_strcpy(trg + i, src);
}

// Test Functions
// ==============

int testIntegers() {
    int16_t i = readInteger();
    writeInteger(i);
    return 0;
}

int testBytes() {
    unsigned char b = readByte();
    writeByte(b);
    return 0;
}

int testChars() {
    uint8_t c = readChar();
    writeChar(c);
    return 0;
}

int testString() {
    uint8_t refbyte[300];
    readString(100, refbyte);
    writeString(refbyte);
    return 0;
}

int main() {
    int8_t i = readInteger();
    printf("%d\n", i);
    return 0;
}

// int main() {
//     uint8_t refbyte[300];
//     uint8_t refbyte2[300];
//
//     readString(100, refbyte);
//     readString(100, refbyte2);
//
//     alan_strcpy(refbyte2, refbyte);
//
//     printf("%s\n", refbyte);
//     printf("%s\n", refbyte2);
//
//     return 0;
// }

