/*
 * pwmLedBlinker.c
 *
 * Author: Fábio Pereira
 * Date  : 2017-06-01
 *
 * This program blinks the blue LED on HiFive board using PWM1:
 * channel 0 sets PWM period and is also used to provide periodic interrupts (200us)
 * channel 2 controls PWM duty-cycle
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
#include "FE310G.h"

#define MAX_CYCLE	63999
#define PWM_STEP	150
#define PWM_DELAY	5000

void boardInit (void);

// Structures for registering different interrupt handlers
// for different parts of the application.
typedef void (*function_ptr_t) (void);
void no_interrupt_handler (void) {};
function_ptr_t g_ext_interrupt_handlers[PLIC_NUM_INTERRUPTS];

// Instance data for the PLIC.
plic_instance_t g_plic;

/*Entry Point for PLIC Interrupt Handler*/
void handle_m_ext_interrupt(){
  plic_source int_num  = PLIC_claim_interrupt(&g_plic);
  if ((int_num >=1 ) && (int_num < PLIC_NUM_INTERRUPTS)) {
    g_ext_interrupt_handlers[int_num]();
  }
  else {
    exit(1 + (uintptr_t) int_num);
  }
  PLIC_complete_interrupt(&g_plic, int_num);
}

/*Entry Point for Machine Timer Interrupt Handler*/
void handle_m_time_interrupt(){
}

// PWM1 comparator 0 interrupt handler
void pwm1cmp0Handler(void){
	static uint8_t direction = 0;
	static uint16_t timer = 0;
	uint16_t currentPWM = PWM1_REG(PWM_CMP2);	// read current PWM duty-cycle
	if (!direction) {							// PWM is increasing
		currentPWM += PWM_STEP;
		if (currentPWM > MAX_CYCLE) {
			currentPWM = MAX_CYCLE;
			direction = 1;
		}
	} else if (direction == 1){					// PWM is decreasing
		currentPWM-=PWM_STEP;
		if (currentPWM > MAX_CYCLE) {
			currentPWM = 0;
			timer = 0;
			direction = 2;
		}
	} else {									// wait with PWM signal off
		timer++;
		if (timer >= PWM_DELAY) direction = 0;
	}
	PWM1_REG(PWM_CMP2) = currentPWM;			// update PWM duty-cycle
}


void boardInit (){
	clear_csr(mie, MIP_MEIP);			// disable external machine interrupts
	clear_csr(mstatus, MSTATUS_MIE);	// disable global interrupts
	// start of PLIC set up
	PLIC_init(&g_plic, PLIC_CTRL_ADDR, PLIC_NUM_INTERRUPTS, PLIC_NUM_PRIORITIES);
	for (int ii = 0; ii < PLIC_NUM_INTERRUPTS; ii ++){
		g_ext_interrupt_handlers[ii] = no_interrupt_handler;
	}
	g_ext_interrupt_handlers[INT_PWM1_CMP0] = pwm1cmp0Handler;
	PLIC_enable_interrupt (&g_plic, INT_PWM1_CMP0);	// enable PWM1cmp0 interrupt
	PLIC_set_priority(&g_plic, INT_PWM1_CMP0, 1);	// set PWM1cmp0 interrupt priority to 1
	// end of PLIC set up
	// Configure clock to 320MHz
	PRCI_use_pll(PLL_REFSEL_HFXOSC, 0, 1, 39, 1, 1, 0, 0);
	GPIO_REG(GPIO_IOF_SEL) = (1 << BLUE_LED_OFFSET);	// set GPIO to PWM mode
	GPIO_REG(GPIO_IOF_EN) = (1 << BLUE_LED_OFFSET);		// enable I/O function GPIO
	PWM1_REG(PWM_CFG) = PWM_CFG_ENALWAYS | PWM_CFG_ZEROCMP;
	PWM1_REG(PWM_COUNT) = 0;			// clear PWM counter
	// set PWM frequency: 320MHz / 64000 = 5000Hz
	PWM1_REG(PWM_CMP0) = MAX_CYCLE;		// PWM1 period = MAX_CYCLE
	PWM1_REG(PWM_CMP2) = 0;				// channel 2 (BLUE LED) is off
	set_csr(mie, MIP_MEIP);				// enable external machine interrupts
	set_csr(mstatus, MSTATUS_MIE);		// enable global interrupts
}

void main(void)
{
	boardInit();
	while (1){
	}
}
