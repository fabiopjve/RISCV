#include <stdio.h>
#include <stdint.h>
#include "platform.h"
#include "plic/plic_driver.h"

void main(void)
{
	volatile uint64_t lastTimer = get_timer_value();
	while (1){
		if (get_timer_value()>(lastTimer+32768)){
			printf("Hello World from RISC-V!\r\n");
			lastTimer = get_timer_value();
		}
	}
}
