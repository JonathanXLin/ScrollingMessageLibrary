#ifndef MATRIX_H
#define MATRIX_H

#define DIN   2
#define CS    3
#define CLK   4

void WriteBoldMessage(char* text, int refreshFrequency);
//Writes bold message, takes a string and refreshFrequency, which dictates rate of letter scroll
//Accepts uppercase letters A-Z, digits 0-9, and following punctuation: ! ? . ,

void WriteNormalMessage(char* text, int refreshFrequency);
//Writes non-bold message, takes a string and refreshFrequency, which dictates rate of letter scroll
//Accepts uppercase letters A-Z, digits 0-9, and following punctuation: ! ? . ,

void Togglecs();

void WriteBit(bool data);

void WriteCommand(char select, char data);

void WriteColumn(char column, char data);

char IntegerToFlippedChar(long binNum);

void WritePixel(int x, int y);
//(0, 0) defined as top left pixel

void Clear();

void SetupMatrix();
//Must include in setup

void WriteBoldCharacter(char c, int xoffset);

void WriteNormalCharacter(char c, int xoffset);

#endif
