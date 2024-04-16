#ifndef __LIBRARY_HPP__
#define __LIBRARY_HPP__

#include <stdint.h>

void writeInteger(int integer);
void writeByte(char byte);
void writeChar(char character);
void writeString(char* refbyte);

int16_t readInteger();
int16_t readByte();
uint8_t readChar();
void readString(int n, char* refbyte);

int16_t extend(char byte);
uint8_t shrink(int integer);

int16_t strlen(char* s);
int16_t strcmp(char* s1, char* s2);
void strcpy(char* trg, char* src);
void strcat(char* trg, char* src);

#endif // __LIBRARY_H__
