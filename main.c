#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
void UART5_send(void);
void UART5_Transmit(uint8_t data);

void PortF_Initialisation(void) {
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;   // Enable clock for Port F
    GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;      // Unlock Port F
    GPIO_PORTF_CR_R = 0x1F;                 // Commit changes
    GPIO_PORTF_DEN_R = 0x1F;                // Digital function enable
    GPIO_PORTF_DIR_R = 0x0E;                // Set output/input
    GPIO_PORTF_PUR_R = 0x11;                // Enable pull-up resistor
    GPIO_PORTF_DATA_R = 0x00;               // Reset the data register
}
