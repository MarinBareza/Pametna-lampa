#ifndef BLE_LED_H_
#define BLE_LED_H_

/*********************************INCLUDES******************************************/
#include "stm32l0xx_hal.h"

/**********************************DEFINES******************************************/


/*********************************STRUCTURES****************************************/

//CMD ID
typedef enum
{
	SINGLE = 0xaf,
	DOUBLE = 0xbc
}cmd_id_t;

//MSG ID1
typedef enum
{
	GPIO_LED1 = 0x0701,
	GPIO_LED2= 0x0702,
	GPIO_TOGGLE = 0x0703,
	LED_SHUT_DOWN = 0x0704,
	PWM_LED1 = 0x0601,
	PWM_LED2 = 0x0602,
	PWM_TOGGLE = 0x0603,
	VOLTAGE_QUERY = 0x0801,
	VOLTAGE_REPORTING = 0x0802
}msg_id_t;

/******************************EXTERN VARIABLES*************************************/

extern uint8_t g_toggle_led[4];
extern uint8_t g_toggle_pwm[2];
extern uint8_t g_toggle_led_number;
extern uint8_t g_pwm_flag;

/****************************FUNCTION PROTOTYPES************************************/

HAL_StatusTypeDef ble_send_text(UART_HandleTypeDef *uart, uint32_t timeout, char *text);

void ble_check_for_input(UART_HandleTypeDef *uart, uint32_t timeout);

void ble_protocol();

void ble_led_shut_down();

void led_toggle();

void timer_start_with_counter(TIM_HandleTypeDef *htim, uint8_t seconds);

void timer_stop(TIM_HandleTypeDef *htim);

#endif /* BLE_LED_H_ */
