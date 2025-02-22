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

#include "serial_debug.h"

static bool Rx_Interrupts_Enabled = false;
static bool Tx_Interrupts_Enabled = false;

PC_Buffer UART0_Tx_Buffer;
PC_Buffer UART0_Rx_Buffer;

//************************************************************************
// Configures the serial debug interface at 115200.
// UART IRQs can be anbled using the two paramters to the function.
//************************************************************************
bool init_serial_debug(bool enable_rx_irq, bool enable_tx_irq) {
	// Enable GPIO pins
  gpio_enable_port(SERIAL_DBG_GPIO_BASE);
	gpio_config_digital_enable(SERIAL_DBG_GPIO_BASE, SERIAL_DBG_RX_PIN | SERIAL_DBG_TX_PIN);
	gpio_config_alternate_function(SERIAL_DBG_GPIO_BASE, SERIAL_DBG_RX_PIN | SERIAL_DBG_TX_PIN);
	gpio_config_port_control(SERIAL_DBG_GPIO_BASE, SERIAL_DBG_RX_PCTL_M, SERIAL_DBG_RX_PCTL);
	gpio_config_port_control(SERIAL_DBG_GPIO_BASE, SERIAL_DBG_TX_PCTL_M, SERIAL_DBG_TX_PCTL);
  
  Rx_Interrupts_Enabled = enable_rx_irq;
  Tx_Interrupts_Enabled = enable_tx_irq;
  
  // Initialize the circular buffer(s)
  pc_buffer_init(&UART0_Tx_Buffer, UART_BUFFER_SIZE);
  pc_buffer_init(&UART0_Rx_Buffer, UART_BUFFER_SIZE); 
  
  if(!uart_init(UART0_BASE,enable_rx_irq, enable_tx_irq)) {
		return false;
  }
  
  return true;
}

/****************************************************************************
 *
 ****************************************************************************/
int serial_debug_rx(PC_Buffer *rx_buffer, bool block) {
	int c;
	while (pc_buffer_empty(rx_buffer)) {
		if (!block) {
			return -1;
		}
	}
	
	// Atomically remove from buffer
	DisableInterrupts();
	pc_buffer_remove(rx_buffer, (char*)&c);
	EnableInterrupts();

	return c;
}

/****************************************************************************
 *
 ****************************************************************************/
void serial_debug_tx(uint32_t uart_base, PC_Buffer *tx_buffer, int data) {
  UART0_Type *uart = (UART0_Type *)(uart_base);
  bool  tx_buffer_full;
  bool  tx_buffer_empty;
  bool  fifo_full;

  // Determine if the hw fifo is full
  fifo_full = uart->FR & UART_FR_TXFF;
  
  // Determine if the pc_buffer is empty
  tx_buffer_empty = pc_buffer_empty(tx_buffer);
  
  // If there is space in the hardware FIFO, and the circular
  // buffer is empty, send the data to the FIFO.
  if(tx_buffer_empty && !fifo_full) {
		uart->DR = (char)data;
  } else {
    // Wait for buffer space
    do {
			tx_buffer_full = pc_buffer_full(tx_buffer);
    } while(tx_buffer_full);

		// Add data to buffer
		DisableInterrupts();
		pc_buffer_add(tx_buffer, (char)data);
		EnableInterrupts();
  }
  
	// Enable TX interrupts
	uart->IM |= UART_IM_TXIM;

  return;
}


//****************************************************************************
//  This function is called from MicroLIB's stdio library.  By implementing
//  this function, MicroLIB's getchar(), scanf(), etc will now work.
// ****************************************************************************/
int fgetc(FILE* stream)
{
   char c;

   
   if ( Rx_Interrupts_Enabled)
   {
    c = serial_debug_rx(&UART0_Rx_Buffer, true);
   }
   else
   {
     c = uart_rx_poll(UART0_BASE,true);
   }

   if (c == '\r')
      c = '\n';

   fputc(c, stdout);

   return c;
}

//****************************************************************************
// This function is called from MicroLIB's stdio library.  By implementing
// this function, MicroLIB's putchar(), puts(), printf(), etc will now work.
// ****************************************************************************/
int fputc(int c, FILE* stream)
{
   uint32_t uart_base;
   PC_Buffer *tx_buffer;

   if ( Tx_Interrupts_Enabled)
   {
      serial_debug_tx(UART0_BASE, &UART0_Tx_Buffer, c);
   }
   else
   {
      uart_tx_poll(UART0_BASE, c);
   }

   if (c == '\n')
   {
      if ( Tx_Interrupts_Enabled)
      {
        serial_debug_tx(UART0_BASE, &UART0_Tx_Buffer,'\r');
      }
      else
      {
         uart_tx_poll(UART0_BASE, '\r');
      }
   }

   return c;
}

//*****************************************************************************
//*****************************************************************************
// UART ISR Handler
//*****************************************************************************
//*****************************************************************************

//*****************************************************************************
// Rx Portion of the UART ISR Handler
//*****************************************************************************
__INLINE static void UART_Rx_Flow(uint32_t uart_base, PC_Buffer *rx_buffer) {
  UART0_Type *uart = (UART0_Type *)(uart_base);
	
	// Move from FIFO -> circular buffer
  while(!(uart->FR & UART_FR_RXFE)) {
		if(!pc_buffer_full(rx_buffer)) {
			pc_buffer_add(rx_buffer, uart->DR);
		}
	}
  
	// Clear interrupt
	uart->ICR = UART_ICR_RXIC | UART_ICR_RTIC;
}

//*****************************************************************************
// Tx Portion of the UART ISR Handler
//*****************************************************************************
__INLINE static void UART_Tx_Flow(uint32_t uart_base, PC_Buffer *tx_buffer) {
	UART0_Type *uart = (UART0_Type *)(uart_base);

	// Move data from buffer to FIFO
	while(!pc_buffer_empty(tx_buffer) && !(uart->FR & UART_FR_TXFF)) {
		char data;
		pc_buffer_remove(tx_buffer, &data);
		uart->DR = data;
	}
	
	// Clear interrupt
	uart->ICR = UART_ICR_TXIC;
}

//*****************************************************************************
// UART0 Interrupt Service handler
//*****************************************************************************
void UART0_Handler(void) {
	// Read the interrupt status of the UART
	uint32_t status = UART0->MIS;
	
	// Handle RX interrupt
	if(status & (UART_MIS_RTMIS | UART_MIS_RXMIS)) {
		UART_Rx_Flow(UART0_BASE, &UART0_Rx_Buffer);
	}
	
	// Handle TX interrupt
	if(status & UART_MIS_TXMIS) {
		UART_Tx_Flow(UART0_BASE, &UART0_Tx_Buffer);
	}

	return;
}
