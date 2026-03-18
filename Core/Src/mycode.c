#include "main.h"
#include "stm32l4xx_hal.h"
#include <stdint.h>
#include <stdio.h>

uint32_t last_time = 0;

int log_time() {
    uint32_t time_now = HAL_GetTick();
    uint32_t time_delta = time_now - last_time;

    if (time_delta < 1000) {
        return 1;
    }

    printf("beep %ld\r\n", time_now / 1000);
    last_time = time_now;
    return 0;
}

/**
 * @brief Toggles the state of an LED at a specified interval.
 *
 * @param ms_period Blink interval in milliseconds.
 * @param last_blink Pointer to a variable storing the timestamp
 *                   of the last LED toggle. This variable is
 *                   updated by the function.
 *
 * @return int
 *   - 0: Success. The LED was toggled.
 *   - 1: No action taken. The time since the last blink is less than `ms_period`.
 */
int blink_period(uint32_t ms_period, uint32_t * last_blink){
    
    uint32_t time_now = HAL_GetTick();
    uint32_t time_delta = time_now - *last_blink;

    // Blinks following a given period
    if (time_delta > ms_period){
        *last_blink = time_now;
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        return 0;
    }
    return 1;
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == BTN_Pin)
    btn_pressed = 1;
}

// Input flags
uint8_t btn_pressed = 0;

// Handlers handling function
void handlers_polling(){
    handler_button();
}


void handler_button(){

    if(!btn_pressed)
        return;

    btn_pressed = 0;
    printf("Button pressed !\r\n");
}