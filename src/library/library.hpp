#ifndef __LIBRARY_HPP__
#define __LIBRARY_HPP__

#include <stdint.h>

void writeInteger(int16_t write_integer);
void writeByte(char write_byte);
void writeChar(uint8_t character);
void writeString(uint8_t* refbyte);

int16_t readInteger();
int16_t readByte();
uint8_t readChar();
void readString(int n, char* refbyte);

int16_t extend(uint8_t extend_byte);
uint8_t shrink(int16_t shrink_integer);

int16_t strlen(uint8_t* s);
int16_t strcmp(uint8_t* s1, uint8_t* s2);
void strcpy(uint8_t* cpy_trg, uint8_t* cpy_src);
void strcat(uint8_t* cat_trg, uint8_t* cat_src);

#endif // __LIBRARY_H__
