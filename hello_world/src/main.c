/**
* \brief This module contains the main function and basic tasks
*/
#include <stdint.h>
#include "stm32f303xe.h"

/* -- Defines ------------------------------------------------------------- */
#define LED_PORT     GPIOA
#define LED_PIN      5
/* -- Types --------------------------------------------------------------- */
/* -- Local Globals (not for libraries with application instantiation) ---- */
/* -- Functions------------------------------------------------------------ */

/**
 * @brief Initializes the LED on the Nucleo board STM32F303XE (PA5).
 *
 * This function must be called before any of the other LED functions.
 */
void jock_sys_LEDInit(void);

/**
 * @brief Toggle the LED on the Nucleo board
 *
 * The LED is toggled on and off by calling this function.
 */
void jock_sys_LEDToggle(void);

/**
 * @brief Basic main.c function
 * 
 */
int main(void)
{
    int16_t errorStatus = 0;

    jock_sys_LEDInit();
    while (1)
    {
        jock_sys_LEDToggle();
    }
    
}

void jock_sys_LEDInit(void)
{
    // Enable clock for GPIO Port A and set the 0th pin (PA0) to be general purpose output mode
    RCC->AHBENR         |= RCC_AHBENR_GPIOAEN;  // Enable clock for GPIO Port A
    LED_PORT->MODER     |= GPIO_MODER_MODER5_0; // Set the 5th pin (PA5) to be general purpose output mode

    /* Set pin 5 of Port A to be a push-pull, low-speed output */
    /* Clear bits 0-1 of the MODER register to reset the pin to input mode */
    LED_PORT->MODER  &= ~(0x3 << (LED_PIN*2));
    /* Set bits 0-1 of the MODER register to set the pin to output mode */
    LED_PORT->MODER  |=  (0x1 << (LED_PIN*2));
    /* Clear the OTYPER bit to set the pin to push-pull mode */
    LED_PORT->OTYPER &= ~(1 << LED_PIN);
}

void jock_sys_LEDToggle(void){
    // Toggle the LED pin
    LED_PORT->ODR ^= (1 << LED_PIN);
}