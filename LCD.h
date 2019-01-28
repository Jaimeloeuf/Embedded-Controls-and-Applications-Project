#ifndef LCD_H
#define LCD_H

// Macros
#define LINE1 1
#define LINE2 2
#define CLS 1
#define NO_CLS 0

void LCD(uint8_t cls, uint8_t line, char *msg);
void Init_LCD(void);	// Initialize the LCD
void W_ctr_4bit(char);  // 4-bit Control word for LCD
void W_data_4bit(char); // 4-bit Text Data for LCD

#endif