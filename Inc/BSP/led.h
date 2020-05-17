#ifndef LED_H_
#define LED_H_

/*********************************INCLUDES******************************************/

#include "stm32l0xx_hal.h"

/**********************************DEFINES******************************************/

#define ON 1
#define OFF 0

/*********************************STRUCTURES****************************************/

typedef enum
{
	RED = 0x01,
	GREEN = 0x02,
	BLUE = 0x03,
	WHITE = 0x04
}led_t;

/******************************EXTERN VARIABLES*************************************/


/****************************FUNCTION PROTOTYPES************************************/

void led_PWM(led_t led, uint8_t duty_cycle);

void led_shut_down();

void led_on(led_t led_id);

void led_off(led_t led_id);

#endif /* LED_H_ */
