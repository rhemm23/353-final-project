#include "ws2812b.h"

void ws2812b_rotate( 
  WS2812B_t *base,
  uint8_t num_leds) {
	int i;
	WS2812B_t temp = base[num_leds - 1];
	for(i = num_leds - 1; i > 0; i--) {
		base[i] = base[i - 1];
	}
	base[0] = temp;
}

void ws2812b_pulse( 
  WS2812B_t *base,
  uint8_t num_leds) {
	int i;
	static int direction = 1;
	for(i = 0; i < num_leds; i++) {
		if(direction > 0) {
			if(base[i].red < 0xFF) {
				base[i].red += num_leds;
			} else {
				direction = -1;
				base[i].red -= num_leds;
			}
		} else {
			if(base[i].red > 0x00) {
				base[i].red -= num_leds;
			} else {
				direction = 1;
				base[i].red += num_leds;
			}
		}
	}
}
