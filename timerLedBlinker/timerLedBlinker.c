// See LICENSE for license details.

#include <stdio.h>
#include <stdlib.h>
#include "platform.h"
#include <string.h>
#include "plic/plic_driver.h"
#include "fe300prci/fe300prci_driver.h"
#include "encoding.h"
#include <unistd.h>
#include "stdatomic.h"

void reset_demo (void);

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

  clear_csr(mie, MIP_MTIP);

  // Reset the timer for 3s in the future.
  // This also clears the existing timer interrupt.

  volatile uint64_t * mtime       = (uint64_t*) (CLINT_CTRL_ADDR + CLINT_MTIME);
  volatile uint64_t * mtimecmp    = (uint64_t*) (CLINT_CTRL_ADDR + CLINT_MTIMECMP);
  uint64_t now = *mtime;
  uint64_t then = now + 2 * RTC_FREQ;
  *mtimecmp = then;

  // read the current value of the LEDS and invert them.
  uint32_t leds = GPIO_REG(GPIO_OUTPUT_VAL);

  GPIO_REG(GPIO_OUTPUT_VAL) ^= ((0x1 << RED_LED_OFFSET)   |
				(0x1 << GREEN_LED_OFFSET) |
				(0x1 << BLUE_LED_OFFSET));
  
  // Re-enable the timer interrupt.
  set_csr(mie, MIP_MTIP);

}


void reset_demo (){

  // Disable the machine & timer interrupts until setup is done.

  clear_csr(mie, MIP_MEIP);
  clear_csr(mie, MIP_MTIP);

  for (int ii = 0; ii < PLIC_NUM_INTERRUPTS; ii ++){
    g_ext_interrupt_handlers[ii] = no_interrupt_handler;
  }



    // Set the machine timer to go off in 3 seconds.
    // The
    volatile uint64_t * mtime       = (uint64_t*) (CLINT_CTRL_ADDR + CLINT_MTIME);
    volatile uint64_t * mtimecmp    = (uint64_t*) (CLINT_CTRL_ADDR + CLINT_MTIMECMP);
    uint64_t now = *mtime;
    uint64_t then = now + 2*RTC_FREQ;
    *mtimecmp = then;

    // Enable the Machine-External bit in MIE
    set_csr(mie, MIP_MEIP);

    // Enable the Machine-Timer bit in MIE
    set_csr(mie, MIP_MTIP);

    // Enable interrupts in general.
    set_csr(mstatus, MSTATUS_MIE);
}

void main(void)
{
  // Set up the GPIOs such that the LED GPIO
  // can be used as both Inputs and Outputs.


  //GPIO_REG(GPIO_INPUT_EN)    &= ~((0x1<< RED_LED_OFFSET) | (0x1<< GREEN_LED_OFFSET) | (0x1 << BLUE_LED_OFFSET)) ;
  GPIO_REG(GPIO_OUTPUT_EN)   |=  (0x1 << BLUE_LED_OFFSET);
  GPIO_REG(GPIO_OUTPUT_VAL)  |=   (0x1 << BLUE_LED_OFFSET);
  
  
  /**************************************************************************
   * Set up the PLIC
   *
   *************************************************************************/
  PLIC_init(&g_plic,
	    PLIC_CTRL_ADDR,
	    PLIC_NUM_INTERRUPTS,
	    PLIC_NUM_PRIORITIES);
  //currentFrequency = PRCI_set_hfrosctrim_for_f_cpu(256000, PRCI_FREQ_UNDERSHOOT);
  PRCI_use_pll(PLL_REFSEL_HFXOSC, 0, 1, 39, 1, 1, 0, 0);
  volatile uint32_t cpu_freq = PRCI_measure_mcycle_freq(3000, RTC_FREQ);
  cpu_freq = PRCI_measure_mcycle_freq(3000, RTC_FREQ);
  reset_demo();


  
  while (1){
    atomic_fetch_xor_explicit(&GPIO_REG(GPIO_OUTPUT_VAL), (1 << PIN_19_OFFSET), memory_order_relaxed);
  }
}
