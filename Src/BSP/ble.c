

/*********************************INCLUDES******************************************/
#include <BSP/ble.h>
#include <BSP/max17048.h>
#include <BSP/led.h>
#include "string.h"
#include "tim.h"
#include "usart.h"
#include "i2c.h"
/**********************GLOBAL VARIABLES AND CONSTANTS*******************************/

uint8_t message[10];

uint8_t g_toggle_led[4];
uint8_t g_toggle_pwm[2];
uint8_t g_toggle_led_number = 0;
uint8_t g_pwm_flag = 0;

/****************************FORWARD DECLARATIONS***********************************/


/*********************************FUNCTIONS*****************************************/

HAL_StatusTypeDef ble_send_text(UART_HandleTypeDef *uart, uint32_t timeout, char *text)
{

  HAL_UART_Transmit(uart, (uint8_t*)text, strlen(text), timeout);

  return HAL_OK;
}

void ble_check_for_input(UART_HandleTypeDef *uart, uint32_t timeout)
{
  if(HAL_UART_Receive(uart, &message[0], 10, timeout) == HAL_OK)
  {
	  ble_protocol(message);
  }
}

void ble_protocol(uint8_t *message)
{
	uint8_t Cmd_ID = message[0];
	msg_id_t Msg_ID = (message[1] << 8) | message[2];
	//uint8_t Data_Length = message[3];
	uint8_t Data1 = message[4];
	uint8_t Data2 = message[5];
	uint8_t Data3 = message[6];
	uint8_t Data4 = message[7];
	uint8_t Data5 = message[8];
	//volatile uint8_t g_End_ID = message[9];

	switch (Cmd_ID)
	{
		case SINGLE:
			switch (Msg_ID)
			{
				case GPIO_LED1:
					if ((Data2 == OFF || Data2 == ON) && (Data1 <= 0x04) && (Data3 == 0) && (Data4 == 0) && (Data5 == 0))
					{
						ble_led_shut_down();

						Data2 ? led_on(Data1) : led_off(Data1);
					}
					break;
				case GPIO_LED2:
					if ((Data2 == OFF || Data2 == ON) && (Data4 == OFF || Data4 == ON) && (Data1 <= 0x04) && (Data3 <= 0x04) && (Data5 == 0))
					{
						ble_led_shut_down();

						Data2 ? led_on(Data1) : led_off(Data1);
					  	Data4 ? led_on(Data3) : led_off(Data3);
					}
					break;
				case GPIO_TOGGLE:
					if ((Data1 <= 0x04) && (Data2 <= 0x04) && (Data3 <= 0x04) && (Data4 <= 0x04))
					{
						ble_led_shut_down();

						g_toggle_led[0] = Data2;
						g_toggle_led[1] = Data3;
						g_toggle_led[2] = Data4;
						g_toggle_led[3] = Data1;
						led_on(Data1);
						timer_start_with_counter(&htim7, Data5);
					}
					break;
				case LED_SHUT_DOWN:
					if ((Data1 == 0xAA) && ((Data2 == 0) && (Data3 == 0) && (Data4 == 0) && (Data5 == 0)))
					{
						ble_led_shut_down();
					}
					break;
				case PWM_LED1:
					if ((Data1 <= 0x04) && (Data2 <= 0x64) && (Data3 == 0) && (Data4 == 0) && (Data5 == 0))
					{
						ble_led_shut_down();

						led_PWM(Data1, Data2);
					}
					break;
				case PWM_LED2:
					if ((Data1 <= 0x04) && (Data2 <= 0x64) && (Data3 <= 0x04) && (Data4 <= 0x64) && (Data5 == 0))
					{
						ble_led_shut_down();

						led_PWM(Data1, Data2);
						led_PWM(Data3, Data4);
					}
					break;
				case PWM_TOGGLE:
					if ((Data1 <= 0x04) && (Data2 <= 0x64) && (Data3 <= 0x04) && (Data4 <= 0x64))
					{
						ble_led_shut_down();

						g_pwm_flag = 1;

						g_toggle_led[0] = Data3;
						g_toggle_led[1] = Data4;
						g_toggle_led[2] = Data1;
						g_toggle_led[3] = Data2;
						led_PWM(Data1, Data2);
						timer_start_with_counter(&htim7, Data5);
					}
					break;
				default:
					break;
			}
			break;
		case DOUBLE:
			switch (Msg_ID)
			{
				case VOLTAGE_QUERY:
					if ((Data1 == 0xAA) && ((Data2 == 0) && (Data3 == 0) && (Data4 == 0) && (Data5 == 0)))
					{
						if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11) == GPIO_PIN_SET)
						{
							read_voltage();
						}
					}
					break;
				case VOLTAGE_REPORTING:
					if (((Data2 == 0) && (Data3 == 0) && (Data4 == 0) && (Data5 == 0)))
					{
						timer_stop(&htim6);
						timer_start_with_counter(&htim6, Data1);
					}
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
}

void ble_led_shut_down()
{
	led_shut_down();
	timer_stop(&htim7);
	g_pwm_flag = 0;
}

void led_toggle()
{

	if (g_pwm_flag == 1)
	{
		if (g_toggle_led_number == 0)
		{
			led_off(g_toggle_led[2]);
			led_PWM(g_toggle_led[0], g_toggle_led[1]);

			g_toggle_led_number = 2;
		}
		else if (g_toggle_led_number == 2)
		{
			led_off(g_toggle_led[0]);
			led_PWM(g_toggle_led[2], g_toggle_led[3]);

			g_toggle_led_number = 0;
		}
	}
	else
	{
		if (g_toggle_led_number == 0)
		{
			led_off(g_toggle_led[3]);
		}
		else
		{
			led_off(g_toggle_led[g_toggle_led_number-1]);
		}

		led_on(g_toggle_led[g_toggle_led_number]);

		if (g_toggle_led_number == 3)
		{
			g_toggle_led_number = 0;
		}
		else
		{
			g_toggle_led_number++;
		}
	}
}

void timer_start_with_counter(TIM_HandleTypeDef *htim, uint8_t seconds)
{
	htim->Instance->ARR = seconds * 1000;
	HAL_TIM_Base_Start_IT(htim);
}

void timer_stop(TIM_HandleTypeDef *htim)
{
	HAL_TIM_Base_Stop_IT(htim);
}
