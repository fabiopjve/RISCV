#include <stdio.h>
#include <stdint.h>
#include "platform.h"

void RISCV_DelayMs(uint32_t time)
{
	uint64_t targetTime = ((time * 32768) / 1000) + get_timer_value();
	while (get_timer_value() < targetTime);
}

int main()
{
	while (1){
		printf("Hello World from RISC-V!\r\n");
		RISCV_DelayMs(1000);
	}
}
