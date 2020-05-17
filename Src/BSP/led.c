

/*********************************INCLUDES******************************************/
#include "BSP/led.h"
#include "tim.h"
/**********************GLOBAL VARIABLES AND CONSTANTS*******************************/


/****************************FORWARD DECLARATIONS***********************************/


/*********************************FUNCTIONS*****************************************/

void led_PWM(led_t led, uint8_t duty_cycle)
{
	volatile uint16_t pulse = duty_cycle * 100;
	switch (led) {
		case RED:
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, pulse);
			break;
		case GREEN:
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, pulse);
			break;
		case BLUE:
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, pulse);
			break;
		case WHITE:
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, pulse);
			break;
		default:
			break;
	}
}

void led_shut_down()
{
	led_off(RED);
	led_off(GREEN);
	led_off(BLUE);
	led_off(WHITE);
}

void led_on(led_t led)
{
	switch (led)
	{
		case RED:
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 10000);
			break;
		case GREEN:
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 10000);
			break;
		case BLUE:
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 10000);
			break;
		case WHITE:
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 10000);
			break;
		default:
			break;
	}
}

void led_off(led_t led)
{
	switch (led)
	{
		case RED:
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
			break;
		case GREEN:
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0);
			break;
		case BLUE:
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0);
			break;
		case WHITE:
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);
			break;
		default:
			break;
	}
}
