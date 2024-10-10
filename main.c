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
void PORTE_Initialisation(void) {
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGC2_GPIOE; // Enable GPIO Port E clock
    SYSCTL_RCGCUART_R |= (1<<5);             // Enable UART5 clock

    GPIO_PORTE_LOCK_R = GPIO_LOCK_KEY;      // Unlock Port E
    GPIO_PORTE_CR_R = 0xFF;                 // Commit changes
    GPIO_PORTE_DEN_R = 0x30;                // Digital enable PE4 and PE5
    GPIO_PORTE_AFSEL_R = 0x30;              // Enable alternate function
    GPIO_PORTE_AMSEL_R = 0x00;              // Turn off analog function
    GPIO_PORTE_PCTL_R &= ~0x00FF0000;
    GPIO_PORTE_PCTL_R |= 0x00110000;       // Set PE4 and PE5 for UART
}
void UART5_Initialisation(void) {
    UART5_CTL_R = 0x00;                     // Disable UART before configuration
    UART5_IBRD_R = 104;                     // Integer part of BRD
    UART5_FBRD_R = 11;                      // Fractional part of BRD
    UART5_CC_R = 0x00;                      // Use system clock
    UART5_LCRH_R = 0x72;                    // 8 bits, odd parity, 1 stop bit
    UART5_CTL_R = 0x301;                    // Enable UART
}

uint8_t UART5_ReceiveByte(void) {
    while ((UART5_FR_R & 0x10) != 0); // Wait until RXFE is 0
    return UART5_DR_R; // Read data
}
void UART5_Read(void) {
    if (dataReceivedFlag) {
        receivedByte = UART5_ReceiveByte();

        if (receivedByte == 0xAA) {
            GPIO_PORTF_DATA_R = 0x08;  // Green LED
        } else if (receivedByte == 0xF0) {
            GPIO_PORTF_DATA_R = 0x04;  // Blue LED
        } else {
            GPIO_PORTF_DATA_R = 0x02;  // Red LED for error
        }
        dataReceivedFlag = false; // Reset flag after processing
    }
}
