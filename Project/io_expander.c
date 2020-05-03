
#include <io_expander.h>

static i2c_status_t io_expander_wait_for_write()
{
  
  i2c_status_t status;
  
  if(!i2cVerifyBaseAddr(IO_EXPANDER_GPIO_BASE))
  {
    return  I2C_INVALID_BASE;
  }

  // Set the I2C address to be the EEPROM and in Write Mode
  status = i2cSetSlaveAddr(IO_EXPANDER_GPIO_BASE, MCP23017_DEV_ID, I2C_WRITE);

  // Poll while the device is busy.  The  MCP24LC32AT will not ACK
  // writing an address while the write has not finished.
  do 
  {
    // The data we send does not matter.  This has been set to 0x00, but could
    // be set to anything
    status = i2cSendByte(IO_EXPANDER_GPIO_BASE, 0x00, I2C_MCS_START | I2C_MCS_RUN | I2C_MCS_STOP);
    
    // Wait for the address to finish transmitting
    while (I2CMasterBusy(IO_EXPANDER_GPIO_BASE)) { };
    
    // If the address was not ACKed, try again.
  } while (I2CMasterAdrAck(IO_EXPANDER_GPIO_BASE) == false);

  return  status;
}

bool io_expander_init(void) {

  if(gpio_enable_port(IO_EXPANDER_GPIO_BASE) == false)
  {
    return false;
  }
  
  // Configure SCL 
  if(gpio_config_digital_enable(IO_EXPANDER_GPIO_BASE, IO_EXPANDER_I2C_SCL_PIN)== false)
  {
    return false;
  }
    
  if(gpio_config_alternate_function(IO_EXPANDER_GPIO_BASE, IO_EXPANDER_I2C_SCL_PIN)== false)
  {
    return false;
  }
    
  if(gpio_config_port_control(IO_EXPANDER_GPIO_BASE, IO_EXPANDER_I2C_SCL_PCTL_M, IO_EXPANDER_I2C_SCL_PIN_PCTL)== false)
  {
    return false;
  }
    

  
  // Configure SDA 
  if(gpio_config_digital_enable(IO_EXPANDER_GPIO_BASE, IO_EXPANDER_I2C_SDA_PIN)== false)
  {
    return false;
  }
    
  if(gpio_config_open_drain(IO_EXPANDER_GPIO_BASE, IO_EXPANDER_I2C_SDA_PIN)== false)
  {
    return false;
  }
    
  if(gpio_config_alternate_function(IO_EXPANDER_GPIO_BASE, IO_EXPANDER_I2C_SDA_PIN)== false)
  {
    return false;
  }
    
  if(gpio_config_port_control(IO_EXPANDER_GPIO_BASE, IO_EXPANDER_I2C_SDA_PCTL_M, IO_EXPANDER_I2C_SDA_PIN_PCTL)== false)
  {
    return false;
  }
    
  //  Initialize the I2C peripheral
  if( initializeI2CMaster(IO_EXPANDER_I2C_BASE)!= I2C_OK)
  {
    return false;
  }
  
  return true;
  
}


void io_expander_write_reg(uint8_t reg, uint8_t data) {
	
	// Before doing anything, make sure the I2C device is idle
  while(I2CMasterBusy(IO_EXPANDER_I2C_BASE)) { };
	
	i2cSetSlaveAddr(IO_EXPANDER_I2C_BASE, MCP23017_DEV_ID, I2C_WRITE);
	
	io_expander_wait_for_write();
	
	i2cSendByte(IO_EXPANDER_I2C_BASE, reg, I2C_MCS_START | I2C_MCS_RUN);
	
	i2cSendByte(IO_EXPANDER_I2C_BASE, data, I2C_MCS_RUN | I2C_MCS_STOP);
}

uint8_t io_expander_read_reg(uint8_t address) {
  
	uint8_t   data;
	
  // Before doing anything, make sure the I2C device is idle
  while (I2CMasterBusy(IO_EXPANDER_I2C_BASE)) { };
	
	// If the EEPROM is still writing the last byte written, wait
  io_expander_wait_for_write();

  i2cSetSlaveAddr(IO_EXPANDER_I2C_BASE, MCP23017_DEV_ID, I2C_WRITE);

	i2cSendByte(IO_EXPANDER_I2C_BASE, address, I2C_MCS_START | I2C_MCS_RUN);

	i2cSetSlaveAddr(IO_EXPANDER_I2C_BASE, MCP23017_DEV_ID, I2C_READ);

	i2cGetByte(IO_EXPANDER_I2C_BASE, &data, I2C_MCS_START | I2C_MCS_RUN | I2C_MCS_STOP);

  return data;
}