



#include "cdc_core.h"

int main(void)
{
    cdc_init();
    while (1) {
        if (cdc_isConfigured()) {
            uint8_t buf[64];
            cdc_process();
            uint8_t rxLength = cdc_getReceivedData(buf);
            if (rxLength) {
                cdc_sendData(buf, rxLength);
            }
        }
    }
}