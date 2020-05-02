
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

void draw_letter (uint16_t x_index, uint16_t y_index, uint8_t character) {
		lcd_draw_image(x_index, letters_indexs[character].width, y_index, 0x0017, &letters[letters_indexs[character].offset], LCD_COLOR_WHITE, LCD_COLOR_BLACK);
}

void draw_string(char* string, uint16_t y_index) {
	uint8_t len = strlen(string);
	uint8_t i = 0;
	uint16_t x_start = 0x0020;
	for (i = 0; i < len; ++i) {
		uint8_t char_index = UPPER_CASE_START_A + (string[i] - 'A');
		draw_letter(x_start + (i * 16), y_index, char_index);
	}
}