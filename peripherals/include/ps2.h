// Copyright (c) 2014-16, Joe Krachey
// All rights reserved.
//
// Redistribution and use in binary form, with or without modification, 
// are permitted provided that the following conditions are met:
//
// 1. Redistributions in binary form must reproduce the above copyright 
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
#ifndef __PS2_H__
#define __PS2_H__

#include <stdint.h>
#include <stdbool.h>

#include "adc.h"
#include "gpio_port.h"
#include "driver_defines.h"

//*****************************************************************************
// Fill out the #defines below to configure which pins are connected to
// the directional buttons
//*****************************************************************************
#define   PS2_GPIO_ANALOG_BASE 			GPIOE_BASE
#define   PS2_X_DIR_PIN      				PE3
#define   PS2_X_DIR_CH							1
#define   PS2_Y_DIR_PIN      				PE2
#define   PS2_Y_DIR_CH							0

#define   PS2_ADC_BASE              ADC0_BASE

#define PS2_ADC_LOW_THRESHOLD		    0x0400
#define PS2_ADC_HIGH_THRESHOLD	    0x0C0

#define PS2_SAMPLE_TICKS						50000

// Set the analog channel for each direction
#define   PS2_X_ADC_CHANNEL  1
#define   PS2_Y_ADC_CHANNEL  0

#define ADC_LOW_THRESHOLD		0x0600
#define ADC_MID_THRESHOLD	  0x0800
#define ADC_HIGH_THRESHOLD	0x0A00

//*****************************************************************************
// Used to initialize the PS2 joystick for both the analog inputs and the 
// push button.  
//
// Configuration Info
//		Fill out relevant information in boardUtil.h.  boardUtil.h defines 
//		how various peripherals are physically connected to the board.
//*****************************************************************************
void ps2_initialize(void);

/*******************************************************************************
* Function Name: ps2_disable
********************************************************************************
* Disables the timer and ADC used for the PS2 Joystick.
*******************************************************************************/
void ps2_disable(void);

//*****************************************************************************
// Returns the most current reading of the X direction  Only the lower 12-bits
// contain data.
//*****************************************************************************
uint16_t ps2_get_x(void);

//*****************************************************************************
// Returns the most current reading of the Y direction.  Only the lower 12-bits
// contain data.
//*****************************************************************************
uint16_t ps2_get_y(void);

//*****************************************************************************
// STAFF: Returns if the pushbutton is currently pressed.
//*****************************************************************************
bool ps2_get_pressed(void);

#endif