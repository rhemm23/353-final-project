
#include "kessel_run.h"

uint8_t read_;
bool status_eeprom = true;

//*****************************************************************************
// Writes high score to EEPROM to save
//*****************************************************************************
void write_high_score(uint16_t score) {
  eeprom_byte_write(I2C1_BASE,256, (score & 0xFF));
  eeprom_byte_write(I2C1_BASE,258, ((score >> 8) & 0xFF));
}

//*****************************************************************************
// Read high score from EEPROM and returns it
//*****************************************************************************
uint16_t read_high_score() {
	uint8_t scoreHighByte;
  uint8_t scoreLowByte;
	eeprom_byte_read(I2C1_BASE,256, &scoreLowByte);
	eeprom_byte_read(I2C1_BASE,258, &scoreHighByte);
	return (scoreHighByte << 8) + scoreLowByte;
}

void draw_letter(uint16_t x_index, uint16_t y_index, uint8_t character, uint16_t color) {
		lcd_draw_image(x_index, letters_indexs[character].width, y_index, 0x0017, &letters[letters_indexs[character].offset], color, LCD_COLOR_BLACK);
}

void draw_string(char* string, uint16_t x_start, uint16_t y_index, uint16_t color) {
	uint8_t len = strlen(string);
	uint8_t i = 0;
	for (i = 0; i < len; ++i) {
		uint8_t char_index = UPPER_CASE_START_A + (string[i] - 'A');
		if (string[i] == ' ') continue;
		draw_letter(x_start + (i * 16), y_index, char_index, color);
	}
}

void start_screen() {
	char high_score_string[12] = "High Score:";
	char high_score_value[10];
	char touch_screen_msg[13] = "Touch Screen";
	char to_start_msg[9] = "to Start";
	uint16_t high_score;
	
	high_score = read_high_score();
	sprintf(high_score_value,"%d",high_score);
	
	draw_string(TITLE, 0x0030, 0x0040, LCD_COLOR_CYAN);
	draw_string(high_score_string, 0x0030, 0x0080, LCD_COLOR_RED);
	draw_string(high_score_value, 0x0058, 0x00A0, LCD_COLOR_RED);
	draw_string(touch_screen_msg, 0x0020, 0x0100, LCD_COLOR_RED);
	draw_string(to_start_msg, 0x0038, 0x0118, LCD_COLOR_RED);
}
