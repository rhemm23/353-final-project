
#include "kessel_run.h"

uint8_t scoreHighByte;
uint8_t scoreLowByte;
uint8_t read_;
bool status_eeprom = true;

//*****************************************************************************
// Writes high score to EEPROM to save
//*****************************************************************************
void write_high_score(uint16_t score) {
  eeprom_byte_write(I2C1_BASE,ADDR_LOW_BYTE, (score & 0xFF));
  eeprom_byte_write(I2C1_BASE,ADDR_HIGH_BYTE, ((score >> 8) & 0xFF));
}

//*****************************************************************************
// Read high score from EEPROM and returns it
//*****************************************************************************
uint16_t read_high_score(void) {
	eeprom_byte_read(I2C1_BASE,ADDR_LOW_BYTE, &scoreLowByte);
	eeprom_byte_read(I2C1_BASE,ADDR_HIGH_BYTE, &scoreHighByte);
	
	return scoreHighByte << 8 | scoreLowByte;
}

void print_start_screen(void) {
		lcd_draw_image(0x0020, letters_indexs[0].width, 0x0020, 0x000B, &letters[letters_indexs[0].offset], LCD_COLOR_WHITE, LCD_COLOR_BLACK);
}