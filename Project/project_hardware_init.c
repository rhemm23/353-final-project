// Copyright (c) 2015-19, Joe Krachey
// All rights reserved.
//
// Redistribution and use in source or binary form, with or without modification, 
// are permitted provided that the following conditions are met:
//
// 1. Redistributions in source form must reproduce the above copyright 
//    notice, this list of conditions and the following disclaimer in 
//    the documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "main.h"

//*****************************************************************************
// Initializes all aspects of the hardware used for the game
//*****************************************************************************
void initialize_hardware() {
  // Setup alive LED
  gpio_enable_port(GPIOF_BASE);
  gpio_config_digital_enable(GPIOF_BASE, RED_M);
  gpio_config_enable_output(GPIOF_BASE, RED_M);
  
  // Setup IO expander interrupt pin
  gpio_config_digital_enable(IO_EXPANDER_IRQ_GPIO_BASE, IO_EXPANDER_IRQ_PIN_NUM);
  gpio_config_enable_input(IO_EXPANDER_IRQ_GPIO_BASE, IO_EXPANDER_IRQ_PIN_NUM);
  gpio_config_enable_pullup(IO_EXPANDER_IRQ_GPIO_BASE, IO_EXPANDER_IRQ_PIN_NUM);
  gpio_config_open_drain(IO_EXPANDER_IRQ_GPIO_BASE, IO_EXPANDER_IRQ_PIN_NUM);
  gpio_config_falling_edge_irq(IO_EXPANDER_IRQ_GPIO_BASE, IO_EXPANDER_IRQ_PIN_NUM);
  
  // Enable Interrupt
  NVIC_EnableIRQ(GPIOF_IRQn);
  NVIC_SetPriority(GPIOF_IRQn, 0);
  
  // Sets up the LCD touch screen
  ft6x06_init();
  
  // Sets up the GPIO pins for the LCD screen
  lcd_config_gpio();
  
  // Sets up the LCD screen to be used
  lcd_config_screen();
  
  // Starts serial debugging
  init_serial_debug(true, true);
  
  // Sets up GPIO pins for EEPROM
	eeprom_init();
 
  // Setup io expander
	io_expander_init();
  io_expander_write_reg(MCP23017_IODIRB_R, 0xFF);
  io_expander_write_reg(MCP23017_IODIRA_R, 0x00);
  io_expander_write_reg(MCP23017_GPPUB_R, 0x0F);
  io_expander_write_reg(MCP23017_GPINTENB_R, 0x0F);
  
  // Reset screen to a black color
  lcd_clear_screen(LCD_COLOR_BLACK);
  
  // Sets up the PS2 joystick
  ps2_initialize();
}