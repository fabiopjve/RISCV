/*
 * timerLedBlinker.c
 *
 * Author: Fábio Pereira
 * Date  : 2017-06-01
 *
 * EMBEDDEDSYSTEMS.IO
 *
 * This program blinks the blue LED on HiFive board using the machine timer
 * (2 interrupts per second)
 */

#include <stdio.h>
#include <stdlib.h>
#include "platform.h"
#include <string.h>
#include "plic/plic_driver.h"
#include "fe300prci/fe300prci_driver.h"
#include "encoding.h"
#include <unistd.h>
#include "stdatomic.h"

// Structures for registering different interrupt handlers
// for different parts of the application.
typedef void (*function_ptr_t) (void);

void no_interrupt_handler (void) {};

volatile uint64_t * mtimecmp    = (uint64_t*) (CLINT_CTRL_ADDR + CLINT_MTIMECMP);
volatile uint64_t * mtime       = (uint64_t*) (CLINT_CTRL_ADDR + CLINT_MTIME);

/*Entry Point for Machine Timer Interrupt Handler*/
void handle_m_time_interrupt()
{
	// set next timer compare to half a second from its previous value
	*mtimecmp += RTC_FREQ/2;
	// toggle blue LED state
	GPIO_REG(GPIO_OUTPUT_VAL) ^= 1 << BLUE_LED_OFFSET;
}

void boardInit()
{
	// set blue LED pin as output and turn it on
	GPIO_REG(GPIO_OUTPUT_EN) |= (0x1 << BLUE_LED_OFFSET);
	GPIO_REG(GPIO_OUTPUT_VAL)|= (0x1 << BLUE_LED_OFFSET);
	// set CPU clock to 320MHz
	PRCI_use_pll(PLL_REFSEL_HFXOSC, 0, 1, 39, 1, 1, 0, 0);
	clear_csr(mie, MIP_MTIP);		// disable timer interrupt until setup is complete
	// configure next timer compare to half a second from now (mtime)
	*mtimecmp = *mtime + RTC_FREQ/2;
	set_csr(mie, MIP_MTIP);			// enable standard timer interrupt in machine mode
	set_csr(mstatus, MSTATUS_MIE);	// enable interrupts globally
}

void main(void)
{
	boardInit();
	while (1){
	}
}
