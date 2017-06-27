#include <stdio.h>
#include <stdint.h>
#include "platform.h"
#include "plic/plic_driver.h"

int main()
{
	volatile uint64_t lastTimer = get_timer_value();
	while (1){
		if (get_timer_value()>(lastTimer+32768)){
			puts("Hello World from RISC-V!\r\n");
			lastTimer = get_timer_value();
		}
	}
}
