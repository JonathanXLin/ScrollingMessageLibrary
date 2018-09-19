# ScrollingMessages

ScrollingMessages is an Arduino library for the MAX7291 8x8 LED Matrix that can write scrolling text.

## Installation

Download the .cpp and .h files and paste them into your project folder. Include the header file in your .ino, by pasting the following code at the top:

```C
#include "matrix.h"
```

## Wiring

<p align="center"> 
  <img src="https://i.imgur.com/8d8RIHm.png" width="500">
</p>

## Features

Messages can be written in normal and bold font as shown in the example below.


```C
  char message[] = "Test Message 123 !";

  WriteNormalMessage(message, 25);
  //Writes message in normal font with 25ms delay between pixel shifts
  
  WriteBoldMessage(message, 50);
  //Writes message in bold font with 50ms delay between pixel shifts
```

Messages can contain all letters A-Z, all digits 0-9, and basic punctuation (. , ! ?).
