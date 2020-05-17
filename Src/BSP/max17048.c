

/*********************************INCLUDES******************************************/
#include <BSP/max17048.h>
#include "i2c.h"
#include "usart.h"

/**********************GLOBAL VARIABLES AND CONSTANTS*******************************/

uint8_t g_vcell_reg_addr = 0x02;
uint8_t g_i2c_received_data[2] = {0};

/****************************FORWARD DECLARATIONS***********************************/


/*********************************FUNCTIONS*****************************************/

void read_voltage()
{
	if (HAL_I2C_Master_Transmit(&hi2c1, g_max1048_addr_write, &g_vcell_reg_addr, 1, 10) == HAL_OK)
	{
	  	if (HAL_I2C_Master_Receive(&hi2c1, g_max1048_addr_read, g_i2c_received_data, 2, 10) == HAL_OK)
	  	{
	  		volatile uint16_t voltage = (g_i2c_received_data[0] << 8) | g_i2c_received_data[1];

	  		float voltage_f = voltage * mi_volts;

	  		char message[40];
	  		sprintf(message, "Napon baterije je: %.2f volti!\r\n", voltage_f);
	  		ble_send_text(&huart1, 50, message);
	  	}
	}
}
