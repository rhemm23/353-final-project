#include "ft6x06.h"

//*****************************************************************************
// Sets the address to read/write from in the FT6x06  
//
// Paramters
//    i2c_base:   a valid base address of an I2C peripheral
//
//    reg_address:    8-bit address of which register is going to be accessed.
//                    This is NOT the same as the I2C device address.
//
// Returns
// I2C_OK if the byte was written to the FT6X06.
//*****************************************************************************
static i2c_status_t ft6x06_set_addr(uint32_t  i2c_base, uint8_t  reg_address) {
  i2c_status_t status;
  
  // Before doing anything, make sure the I2C device is idle
  while(I2CMasterBusy(i2c_base)) { }

	// Send slave to writing
  if((status = i2cSetSlaveAddr(i2c_base, FT6X06_DEV_ID, I2C_WRITE)) != I2C_OK) {
    return status;
  }

	// Send register address
	status = i2cSendByte(i2c_base, reg_address, I2C_MCS_START | I2C_MCS_RUN | I2C_MCS_STOP);

  return status;
}

//*****************************************************************************
// Reads one byte of data from the current address of the FT6x06  
//
// Paramters
//    i2c_base:   a valid base address of an I2C peripheral
//
//    data:       data to read.
//
// Returns
// I2C_OK if the byte was written to the FT6X06.
//*****************************************************************************
static i2c_status_t ft6x06_read_data(uint32_t  i2c_base, uint8_t *data) {
  i2c_status_t status;
  
  // Before doing anything, make sure the I2C device is idle
  while(I2CMasterBusy(i2c_base)) { }

	// Set slave to writing
  if((status = i2cSetSlaveAddr(i2c_base, FT6X06_DEV_ID, I2C_READ)) != I2C_OK) {
    return status;
  }

	// Read byte
	status = i2cGetByte(i2c_base, data, I2C_MCS_START | I2C_MCS_RUN | I2C_MCS_STOP);

  return status;
}


//*****************************************************************************
// Read the number of active touch points.
//*****************************************************************************
uint8_t ft6x06_read_td_status(void) {
	uint8_t data;
	ft6x06_set_addr(FT6X06_I2C_BASE, FT6X06_TD_STATUS_R);
	ft6x06_read_data(FT6X06_I2C_BASE, &data);
	return data;
} 


//*****************************************************************************
// Read the X value of last touch event
//*****************************************************************************
uint16_t ft6x06_read_x(void) {
	uint8_t xh, xl;
	uint16_t x;
	
	// Read XL
	ft6x06_set_addr(FT6X06_I2C_BASE, FT6X06_P1_XL_R);
	ft6x06_read_data(FT6X06_I2C_BASE, &xl);
	
	// Read XH
	ft6x06_set_addr(FT6X06_I2C_BASE, FT6X06_P1_XH_R);
	ft6x06_read_data(FT6X06_I2C_BASE, &xh);
	
	// Calculate x
	x = (xh & 0x7) << 8;
	x |= (uint16_t)xl;
	return 239 - x;
} 

//*****************************************************************************
// Read the Y value of last touch event
//*****************************************************************************
uint16_t ft6x06_read_y(void) {
	uint8_t yh, yl;
	uint16_t y;
	
	// Read YL
	ft6x06_set_addr(FT6X06_I2C_BASE, FT6X06_P1_YL_R);
	ft6x06_read_data(FT6X06_I2C_BASE, &yl);
	
	// Read YH
	ft6x06_set_addr(FT6X06_I2C_BASE, FT6X06_P1_YH_R);
	ft6x06_read_data(FT6X06_I2C_BASE, &yh);
	
	// Calculate y
	y = (yh & 0x7) << 8;
	y |= (uint16_t)yl;
	return 319 - y;
} 

//*****************************************************************************
// Test the ft6x06
//*****************************************************************************
bool ft6x06_init(void)
{ 
  //==============================
  // Configure I2C GPIO Pins
  //==============================  
  if(gpio_enable_port(FT6X06_GPIO_BASE) == false)
  {
    return false;
  }
  
  // Configure SCL 
  if(gpio_config_digital_enable(FT6X06_GPIO_BASE, FT6X06_I2C_SCL_PIN)== false)
  {
    return false;
  }
    
  if(gpio_config_alternate_function(FT6X06_GPIO_BASE, FT6X06_I2C_SCL_PIN)== false)
  {
    return false;
  }
    
  if(gpio_config_port_control(FT6X06_GPIO_BASE, FT6X06_I2C_SCL_PCTL_M, FT6X06_I2C_SCL_PIN_PCTL)== false)
  {
    return false;
  }
    

  
  // Configure SDA 
  if(gpio_config_digital_enable(FT6X06_GPIO_BASE, FT6X06_I2C_SDA_PIN)== false)
  {
    return false;
  }
    
  if(gpio_config_open_drain(FT6X06_GPIO_BASE, FT6X06_I2C_SDA_PIN)== false)
  {
    return false;
  }
    
  if(gpio_config_alternate_function(FT6X06_GPIO_BASE, FT6X06_I2C_SDA_PIN)== false)
  {
    return false;
  }
    
  if(gpio_config_port_control(FT6X06_GPIO_BASE, FT6X06_I2C_SDA_PCTL_M, FT6X06_I2C_SDA_PIN_PCTL)== false)
  {
    return false;
  }
  
  
  //  Initialize the I2C peripheral
  if( initializeI2CMaster(FT6X06_I2C_BASE)!= I2C_OK)
  {
    return false;
  }
  
  return true;
  
} 

