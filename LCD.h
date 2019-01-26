#ifndef LCD_H
#define LCD_H

// Macros
#define LINE1 1
#define LINE2 2
#define CLS 1
#define NO_CLS 0

void Init_LCD();
void LCD_sendCW(char x);
void LCD_sendData(char x);

#endif