/*
 ============================================================================
 Name        : gpioTest.c
 Author      : Fábio Pereira
 Version     : 1
 Copyright   : None
 Description : Toggle pin 19 as fast as possible
 ============================================================================
 */
#include <stdio.h>
#include "platform.h"
#include "plic/plic_driver.h"
#include "fe300prci/fe300prci_driver.h"
#include "encoding.h"
#include <unistd.h>
#include "stdatomic.h"

#define OUTPUT_PIN	(1 << PIN_19_OFFSET)

void toggleAtomic(void){
	while(1){
		atomic_fetch_xor_explicit(&GPIO_REG(GPIO_OUTPUT_VAL), OUTPUT_PIN, memory_order_relaxed);	// toggle pin
		atomic_fetch_xor_explicit(&GPIO_REG(GPIO_OUTPUT_VAL), OUTPUT_PIN, memory_order_relaxed);	// toggle pin
		atomic_fetch_xor_explicit(&GPIO_REG(GPIO_OUTPUT_VAL), OUTPUT_PIN, memory_order_relaxed);	// toggle pin
		atomic_fetch_xor_explicit(&GPIO_REG(GPIO_OUTPUT_VAL), OUTPUT_PIN, memory_order_relaxed);	// toggle pin
	}
}

void toggleDirectStores(void){
	while(1){
		GPIO_REG(GPIO_OUTPUT_VAL) = OUTPUT_PIN;		// set pin
		GPIO_REG(GPIO_OUTPUT_VAL) = ~OUTPUT_PIN;	// clear pin
		GPIO_REG(GPIO_OUTPUT_VAL) = OUTPUT_PIN;		// set pin
		GPIO_REG(GPIO_OUTPUT_VAL) = ~OUTPUT_PIN;	// clear pin
		GPIO_REG(GPIO_OUTPUT_VAL) = OUTPUT_PIN;		// set pin
		GPIO_REG(GPIO_OUTPUT_VAL) = ~OUTPUT_PIN;	// clear pin
	}
}

//***************************************************************/
//	MAIN
//***************************************************************/
void main(void) {
	GPIO_REG(GPIO_OUTPUT_EN) = OUTPUT_PIN;	// set pin (19) as output
	// config CPU clock to 320MHz using PLL
	PRCI_use_pll(PLL_REFSEL_HFXOSC, 0, 1, 39, 1, 1, 0, 0);
	while (1){
	    //toggleAtomic();	// test Atomic instructions
	    toggleDirectStores();	// test direct stores to change pin state
	}
}
