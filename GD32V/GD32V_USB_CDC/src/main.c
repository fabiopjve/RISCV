/*
    CDC example on GD32VF103 on Longan Nano using PlatformIO and modified
    CDC ACM library

    This very basic example will echo all received characters back to the
    host computer.

    Author: Fábio Pereira
    www.embeddedsystems.io
    Date: August, 29th, 2020
*/

#include "cdc_core.h"
#include "GD32V_systick.h"

int main(void)
{
    cdc_init();
    while (1) {
        if (cdc_isConfigured()) {
            uint8_t buf[64];
            cdc_process();
            uint32_t rxLength = cdc_getReceivedData(buf, 64);
            if (rxLength) {
                cdc_sendData(buf, rxLength);
            }
        }
    }
}