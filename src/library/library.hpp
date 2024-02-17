// STD Library for Alan Programming Language
// Author: Elisavet Papadopoulou, Avgerinos Petros

#ifndef __LIBRARY_HPP__
#define __LIBRARY_HPP__

#include <stdint.h>

void writeInteger(int16_t integer);
void writeByte(unsigned char byte);
void writeChar(uint8_t character);
void writeString(uint8_t* refbyte);

int16_t readInteger();
uint8_t readByte();
uint8_t readChar();
void readString(int32_t n, uint8_t* refbyte);

int16_t extend(uint8_t byte);
uint8_t shrink(int16_t integer);

int16_t strlen(uint8_t* s);
int16_t strcmp(uint8_t* s1, uint8_t* s2);
void strcpy(uint8_t* trg, uint8_t* src);
void strcat(uint8_t* trg, uint8_t* src);

#endif // __LIBRARY_H__
