#include "Arduino.h"
#include "matrix.h"

void Togglecs()
{
  digitalWrite(CS, HIGH);
  digitalWrite(CS, LOW);
}

void WriteBit(bool data)
{
    digitalWrite(DIN, data);
    digitalWrite(CLK, HIGH);
    digitalWrite(CLK, LOW);
}

void WriteCommand(char select, char data)//Bitwise operations
{
  for (int i=0; i<8; i++)
  {
    WriteBit(select&(128>>i));
  }

  for (int i=0; i<8; i++)
  {
    WriteBit(data&(128>>i));
  }

  Togglecs();
}

void WriteColumn(char column, char data)//Column parameter is value from 1-8, Data parameter is char w/ binary representation for pixel state
{
  char Column = column;

  if (Column>8 || Column<1)
    return;
  
  for (int i=0; i<8; i++)
  {
    WriteBit(Column&(128>>i));
  }

  for (int i=0; i<8; i++)
  {
    WriteBit(data&(128>>i));
  }

  Togglecs();
}

char IntegerToFlippedChar(long binNum)//Integer representation of binary num, flipped b/c convention written up-down
{
  long num = binNum;
  char column = 0;
  
  for (int digit=0; digit<8; digit++)
  {
    column += (binNum%10)<<(7-digit);
    binNum /= 10;                                                                                                                                                                                                                            
  }
  
  return column;
}

static char columnValue[8] = {0};

void WritePixel(int x, int y)//origin top left
{
  int X=x;
  int Y=y;

  if (x<0 || y<0 || x>8 || y>8)
    return;

  else if (!(columnValue[X-1]&(1<<(Y-1))))
    columnValue[X-1] += 1<<(Y-1);
  WriteCommand(X, columnValue[X-1]);
}

void Clear()
{
  for (int index=0; index<8; index++)
    columnValue[index] = 0;
  
  for (int i=1; i<=8; i++)
  {
    WriteCommand(i ,0);
  }
}

void WriteBoldCharacter(char c, int xoffset)
//xoffset is offset from default position in grid
//byte pattern leading 0s are removed, otherwise interprets octal
{
  if (c == ' ')
    return;

  if (c == '.')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(11)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(11)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(0)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(0)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(0)));
    WriteColumn(6-xoffset,(IntegerToFlippedChar(0)));
    WriteColumn(7-xoffset,(IntegerToFlippedChar(0)));
    WriteColumn(8-xoffset,(IntegerToFlippedChar(0)));

    return;
  }

  if (c == ',')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(1)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(111)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(110)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(0)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(0)));
    WriteColumn(6-xoffset,(IntegerToFlippedChar(0)));
    WriteColumn(7-xoffset,(IntegerToFlippedChar(0)));
    WriteColumn(8-xoffset,(IntegerToFlippedChar(0)));

    return;
  }

  if (c == '?')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(0)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(1100000)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(11100000)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(11001011)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(11011011)));
    WriteColumn(6-xoffset,(IntegerToFlippedChar(11111000)));
    WriteColumn(7-xoffset,(IntegerToFlippedChar(1110000)));
    WriteColumn(8-xoffset,(IntegerToFlippedChar(0)));

    return;
  }

  if (c == 39)
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(0)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(0)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(10000)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(1110000)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(1100000)));
    WriteColumn(6-xoffset,(IntegerToFlippedChar(0)));
    WriteColumn(7-xoffset,(IntegerToFlippedChar(0)));
    WriteColumn(8-xoffset,(IntegerToFlippedChar(0)));

    return;
  }
  
  if (c == 'a')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(1111111)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(11001100)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(11001100)));
    WriteColumn(6-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(7-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(8-xoffset,(IntegerToFlippedChar(1111111)));

    return;
  }

  if (c == 'b')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(11011011)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(11011011)));
    WriteColumn(6-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(7-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(8-xoffset,(IntegerToFlippedChar(1100110)));

    return;
  }

  if (c == 'c')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(1111110)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(11000011)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(11000011)));
    WriteColumn(6-xoffset,(IntegerToFlippedChar(11100111)));
    WriteColumn(7-xoffset,(IntegerToFlippedChar(11100111)));
    WriteColumn(8-xoffset,(IntegerToFlippedChar(1100110)));

    return;
  }

  if (c == 'd')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(11000011)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(11000011)));
    WriteColumn(6-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(7-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(8-xoffset,(IntegerToFlippedChar(1111110)));

    return;
  }

  if (c == 'e')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(11011011)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(11011011)));
    WriteColumn(6-xoffset,(IntegerToFlippedChar(11011011)));
    WriteColumn(7-xoffset,(IntegerToFlippedChar(11000011)));
    WriteColumn(8-xoffset,(IntegerToFlippedChar(11000011)));

    return;
  }

  if (c == 'f')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(11011000)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(11011000)));
    WriteColumn(6-xoffset,(IntegerToFlippedChar(11011000)));
    WriteColumn(7-xoffset,(IntegerToFlippedChar(11000000)));
    WriteColumn(8-xoffset,(IntegerToFlippedChar(11000000)));

    return;
  }

  if (c == 'g')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(1111110)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(11000011)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(11001011)));
    WriteColumn(6-xoffset,(IntegerToFlippedChar(11101111)));
    WriteColumn(7-xoffset,(IntegerToFlippedChar(11101111)));
    WriteColumn(8-xoffset,(IntegerToFlippedChar(1101110)));

    return;
  }

  if (c == 'h')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(11000)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(11000)));
    WriteColumn(6-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(7-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(8-xoffset,(IntegerToFlippedChar(11111111)));

    return;
  }

  if (c == 'i')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(0)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(0)));
    WriteColumn(6-xoffset,(IntegerToFlippedChar(0)));
    WriteColumn(7-xoffset,(IntegerToFlippedChar(0)));
    WriteColumn(8-xoffset,(IntegerToFlippedChar(0)));

    return;
  }

  if (c == 'j')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(11)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(11)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(11)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(6-xoffset,(IntegerToFlippedChar(11111110)));
    WriteColumn(7-xoffset,(IntegerToFlippedChar(0)));
    WriteColumn(8-xoffset,(IntegerToFlippedChar(0)));

    return;
  }

  if (c == 'k')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(11000)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(111100)));
    WriteColumn(6-xoffset,(IntegerToFlippedChar(1111110)));
    WriteColumn(7-xoffset,(IntegerToFlippedChar(11100111)));
    WriteColumn(8-xoffset,(IntegerToFlippedChar(11000011)));

    return;
  }

  if (c == 'l')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(11)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(11)));
    WriteColumn(6-xoffset,(IntegerToFlippedChar(11)));
    WriteColumn(7-xoffset,(IntegerToFlippedChar(11)));
    WriteColumn(8-xoffset,(IntegerToFlippedChar(11)));

    return;
  }

  if (c == 'm')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(1110000)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(110000)));
    WriteColumn(6-xoffset,(IntegerToFlippedChar(1110000)));
    WriteColumn(7-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(8-xoffset,(IntegerToFlippedChar(11111111)));

    return;
  }

  if (c == 'n')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(1111000)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(11110)));
    WriteColumn(6-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(7-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(8-xoffset,(IntegerToFlippedChar(11111111)));

    return;
  }

  if (c == 'o')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(1111110)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(11000011)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(11000011)));
    WriteColumn(6-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(7-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(8-xoffset,(IntegerToFlippedChar(1111110)));

    return;
  }

  if (c == 'p')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(11011000)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(11011000)));
    WriteColumn(6-xoffset,(IntegerToFlippedChar(11111000)));
    WriteColumn(7-xoffset,(IntegerToFlippedChar(11111000)));
    WriteColumn(8-xoffset,(IntegerToFlippedChar(1110000)));

    return;
  }

  if (c == 'q')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(1111110)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(11000011)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(11000101)));
    WriteColumn(6-xoffset,(IntegerToFlippedChar(11110110)));
    WriteColumn(7-xoffset,(IntegerToFlippedChar(11111011)));
    WriteColumn(8-xoffset,(IntegerToFlippedChar(1111101)));

    return;
  }

  if (c == 'r')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(11011000)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(11011000)));
    WriteColumn(6-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(7-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(8-xoffset,(IntegerToFlippedChar(1110111)));

    return;
  }

  if (c == 's')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(1110010)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(11111011)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(11111011)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(11011011)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(11011011)));
    WriteColumn(6-xoffset,(IntegerToFlippedChar(11011111)));
    WriteColumn(7-xoffset,(IntegerToFlippedChar(11011111)));
    WriteColumn(8-xoffset,(IntegerToFlippedChar(1001110)));

    return;
  }

  if (c == 't')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(11000000)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(11000000)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(6-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(7-xoffset,(IntegerToFlippedChar(11000000)));
    WriteColumn(8-xoffset,(IntegerToFlippedChar(11000000)));

    return;
  }

  if (c == 'u')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(11111110)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(11)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(11)));
    WriteColumn(6-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(7-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(8-xoffset,(IntegerToFlippedChar(11111110)));

    return;
  }

  if (c == 'v')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(11111100)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(11111110)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(11)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(11)));
    WriteColumn(6-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(7-xoffset,(IntegerToFlippedChar(11111110)));
    WriteColumn(8-xoffset,(IntegerToFlippedChar(11111100)));

    return;
  }

  if (c == 'w')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(11111100)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(11111110)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(111)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(1111110)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(1111110)));
    WriteColumn(6-xoffset,(IntegerToFlippedChar(111)));
    WriteColumn(7-xoffset,(IntegerToFlippedChar(11111110)));
    WriteColumn(8-xoffset,(IntegerToFlippedChar(11111100)));

    return;
  }

  if (c == 'x')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(11000011)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(11100111)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(111100)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(111100)));
    WriteColumn(6-xoffset,(IntegerToFlippedChar(11111111)));
    WriteColumn(7-xoffset,(IntegerToFlippedChar(11100111)));
    WriteColumn(8-xoffset,(IntegerToFlippedChar(11000011)));

    return;
  }

  if (c == 'y')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(11100000)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(11110000)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(11111000)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(11111)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(11111)));
    WriteColumn(6-xoffset,(IntegerToFlippedChar(11111000)));
    WriteColumn(7-xoffset,(IntegerToFlippedChar(11110000)));
    WriteColumn(8-xoffset,(IntegerToFlippedChar(11100000)));

    return;
  }

  if (c == 'z')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(11000111)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(11001111)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(11001111)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(11011111)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(11111011)));
    WriteColumn(6-xoffset,(IntegerToFlippedChar(11110011)));
    WriteColumn(7-xoffset,(IntegerToFlippedChar(11110011)));
    WriteColumn(8-xoffset,(IntegerToFlippedChar(11100011)));

    return;
  }
}

void WriteNormalCharacter(char c, int xoffset)
{
  if (c == ' ')
    return;

  if (c == '.')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(0)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(1)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(0)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(0)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(0)));

    return;
  }

  if (c == ',')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(0)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(1)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(10)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(0)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(0)));

    return;
  }

  if (c == '?')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(100000)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(1000000)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(1000101)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(1001000)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(110000)));

    return;
  }

  if (c == '!')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(0)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(0)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(1111101)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(0)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(0)));

    return;
  }

  if (c == '(')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(0)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(0)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(111110)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(1000001)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(0)));

    return;
  }

  if (c == ')')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(0)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(0)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(1000001)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(111110)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(0)));

    return;
  }

  if (c == ':')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(0)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(0)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(100010)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(0)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(0)));

    return;
  }

  if (c == 'a')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(111111)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(1000100)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(1000100)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(1000100)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(111111)));

    return;
  }

  if (c == 'b')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(1111111)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(1001001)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(1001001)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(1001001)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(110110)));

    return;
  }

  if (c == 'c')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(111110)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(1000001)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(1000001)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(1000001)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(100010)));

    return;
  }

  if (c == 'd')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(1111111)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(1000001)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(1000001)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(1000001)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(111110)));

    return;
  }

  if (c == 'e')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(1111111)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(1001001)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(1001001)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(1001001)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(1000001)));

    return;
  }

  if (c == 'f')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(1111111)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(1001000)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(1001000)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(1001000)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(1000000)));

    return;
  }

  if (c == 'g')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(111110)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(1000001)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(1000001)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(1000101)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(100110)));

    return;
  }

  if (c == 'h')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(1111111)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(1000)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(1000)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(1000)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(1111111)));

    return;
  }

  if (c == 'i')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(0)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(1000001)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(1111111)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(1000001)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(0)));

    return;
  }

  if (c == 'j')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(110)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(1)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(1)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(1)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(1111110)));

    return;
  }

  if (c == 'k')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(1111111)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(1000)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(10100)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(100010)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(1000001)));

    return;
  }

  if (c == 'l')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(1111111)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(1)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(1)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(1)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(1)));

    return;
  }

  if (c == 'm')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(1111111)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(100000)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(10000)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(100000)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(1111111)));

    return;
  }

  if (c == 'n')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(1111111)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(10000)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(1000)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(100)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(1111111)));

    return;
  }

  if (c == 'o')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(111110)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(1000001)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(1000001)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(1000001)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(111110)));

    return;
  }

  if (c == 'p')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(1111111)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(1000100)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(1000100)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(1000100)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(111000)));

    return;
  }

  if (c == 'q')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(111110)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(1000001)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(1000101)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(1000011)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(111111)));

    return;
  }

  if (c == 'r')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(1111111)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(1000100)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(1000100)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(1000100)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(111011)));

    return;
  }

  if (c == 's')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(110010)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(1001001)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(1001001)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(1001001)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(100110)));

    return;
  }

  if (c == 't')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(1000000)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(1000000)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(1111111)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(1000000)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(1000000)));

    return;
  }

  if (c == 'u')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(1111110)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(1)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(1)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(1)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(1111110)));

    return;
  }

  if (c == 'v')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(1111100)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(10)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(1)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(10)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(1111100)));

    return;
  }

  if (c == 'w')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(1111111)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(10)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(100)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(10)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(1111111)));

    return;
  }

  if (c == 'x')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(1100011)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(10100)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(1000)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(10100)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(1100011)));

    return;
  }

  if (c == 'y')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(1110000)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(1000)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(111)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(1000)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(1110000)));

    return;
  }

  if (c == 'z')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(1000011)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(1000101)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(1001001)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(1010001)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(1100001)));

    return;
  }

  if (c == '0')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(1111111)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(1000001)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(1000001)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(1000001)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(1111111)));

    return;
  }

  if (c == '1')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(0)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(100000)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(1111111)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(0)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(0)));

    return;
  }

  if (c == '2')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(1001111)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(1001001)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(1001001)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(1001001)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(1111001)));

    return;
  }

  if (c == '3')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(1000001)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(1001001)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(1001001)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(1001001)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(1111111)));

    return;
  }

  if (c == '4')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(1111000)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(1000)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(1000)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(1000)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(1111111)));

    return;
  }

  if (c == '5')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(1111001)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(1001001)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(1001001)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(1001001)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(1001111)));

    return;
  }

  if (c == '6')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(1111111)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(1001001)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(1001001)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(1001001)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(1001111)));

    return;
  }

  if (c == '7')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(1000000)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(1000000)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(1000111)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(1001000)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(1110000)));

    return;
  }

  if (c == '8')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(1111111)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(1001001)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(1001001)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(1001001)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(1111111)));

    return;
  }

  if (c == '9')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(1111001)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(1001001)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(1001001)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(1001001)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(1111111)));

    return;
  }
    

  if (c == '~')
  {
    WriteColumn(1-xoffset,(IntegerToFlippedChar(1111111)));
    WriteColumn(2-xoffset,(IntegerToFlippedChar(1111111)));
    WriteColumn(3-xoffset,(IntegerToFlippedChar(1111111)));
    WriteColumn(4-xoffset,(IntegerToFlippedChar(1111111)));
    WriteColumn(5-xoffset,(IntegerToFlippedChar(1111111)));

    return;
  }
    
}

void WriteBoldMessage(char* text, int refreshFrequency)//Automatically bolded
{
  char *rawMessage = text;
  int numCharacters = strlen(rawMessage)+2;//Added delay between message loop
  char message[numCharacters];
  strcpy(message, " ");
  strcat(message, rawMessage);

  char buffer1;
  char buffer2;
  char buffer3;

  for (int i=0; i<numCharacters; i++)
  {
    buffer1 = message[i];
    buffer2 = message[i+1];

    for (int offset=0; offset<10; offset++)
    {
      WriteBoldCharacter(buffer1, offset);
      WriteBoldCharacter(buffer2, offset-10);
      delay(1000/refreshFrequency);
      Clear();
    }
  }
}

void WriteNormalMessage(char* text, int refreshFrequency)
{
  char *rawMessage = text;
  int numCharacters = strlen(rawMessage)+2;//Added delay between message loop
  char message[numCharacters];
  strcpy(message, " ");
  strcat(message, rawMessage);

  char buffer1;
  char buffer2;
  char buffer3;

  for (int i=0; i<numCharacters; i++)
  {
    buffer1 = message[i];
    buffer2 = message[i+1];
    buffer3 = message[i+2];

    for (int offset=0; offset<7; offset++)
    //Offset is equal to distance between centers of two adjacent character spaces
    //Buffers refresh after one character box takes over place of adjacent character box
    {
      //Three buffers needed because at one time three characters are fully/partially visible on screen
      WriteNormalCharacter(buffer1, offset);
      WriteNormalCharacter(buffer2, offset-7);
      WriteNormalCharacter(buffer3, offset-14);
      delay(1000/refreshFrequency);
      Clear();
    }
  }
}

void SetupMatrix()
{
  pinMode(DIN, OUTPUT);
  pinMode(CS, OUTPUT);
  pinMode(CLK, OUTPUT);
  
  WriteCommand(0x09, 0x00); //decoding ：BCD
  WriteCommand(0x0a, 1); //brightness: default 3
  WriteCommand(0x0b, 0x07); //scanlimit；8 LEDs
  WriteCommand(0x0c, 0x01); //power-down mode：0，normal mode： 1
  WriteCommand(0x0f, 0x00); //test display：1；EOT，display：0

  Clear();
}
