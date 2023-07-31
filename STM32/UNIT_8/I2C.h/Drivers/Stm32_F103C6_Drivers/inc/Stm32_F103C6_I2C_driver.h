/*
 * Stm32_F103C6_I2C_driver.h
 *
 *  Created on: Jul 31, 2023
 *      Author: ahmed osama
 */

#ifndef INC_STM32_F103C6_I2C_DRIVER_H_
#define INC_STM32_F103C6_I2C_DRIVER_H_

#include "Stm32_F103x6.h"
#include "Stm32_F103C6_gpio_driver.h"
#include "Stm32_F103C6_RCC_driver.h"

struct S_I2C_Slave_Address
{
	uint16_t	Dual_Address_Enable; //1:Enable 0:Disable
	uint16_t	Primary_slave_address;
	uint16_t	Secondary_Slave_address;
	uint16_t	I2C_Addressing_Slave_mode;//@ref I2C_Addressing_Slave_mode_define
};

typedef enum
{
	I2C_EV_STOP,
	I2C_ERROR_AF,
	I2C_EV_ADDR_Matched,
	I2C_EV_DATA_REQ,		//I2C Slave Send Data
	I2C_EV_DATA_RCV			//I2C Slave Receive Data
}Slave_State;

typedef struct
{
	uint32_t   						I2C_CLK_speed;			//specifies I2C clock speed
															//This parameter must be set based on @ref I2C_CLK_speed_define
	uint32_t						I2C_Mode;				//specifies I2C mode
															//This parameter must be set based on @ref I2C_Mode_define
	uint32_t						I2C_Stretch_Mode;		//specifies I2C enable or disable Stretch Mode
															//This parameter must be set based on @ref I2C_Stretch_Mode_define

	uint32_t						I2C_ACK_Control;		//specifies I2C enable or disable Acknowledge
															//This parameter must be set based on @ref I2C_ACK_Control_define

	struct S_I2C_Slave_Address      I2C_Slave_address;

	uint32_t 						General_Call_Address_Detection;  //@ref I2C_ENGC


	void(* P_Slave_Event_CallBack)(Slave_State state);

}I2C_Config;

/*
 * ===============================================================
 * 						Reference Macros
 * ===============================================================
 */

//@ref I2C_Stretch_Mode_define
//I2C_CR1
#define  I2C_Stretch_Mode_Enable	(0x00000000UL)			//0: Clock stretching enabled
#define  I2C_Stretch_Mode_Disable	I2C_CR1_NOSTRETCH       //1: Clock stretching disabled

/*
 *@ref I2C_CLK_speed_define
 */
//Bits 5:0 FREQ[5:0]: Set Peripheral clock frequency
//Configure the clock control registers --->>>     CCR[11:0]:Thigh = CCR * TPCLK1
//Configure the rise time register	------>>>	  TRISE[5:0]:(1000 ns / 125 ns = 8 + 1)
//enable the peripheral
#define I2C_CLK_speed_SM_50k		(0x50000UL)
#define I2C_CLK_speed_SM_100k		(0x100000UL)

//@ref I2C_Mode_define
//I2C_CR1
#define	 I2C_Mode_I2C				0
#define	 I2C_Mode_SMBus				I2C_CR1_SMBUS

//@ref I2C_Addressing_Slave_mode_define
#define I2C_Addressing_Slave_mode_7Bit		(0x00000000UL)
#define I2C_Addressing_Slave_mode_10Bit		(uint16_t)(1<<15)

//@ref I2C_ACK_Control_define
#define I2C_ACK_Control_Enable 				I2C_CR1_ACK
#define I2C_ACK_Control_Disable 			(uint16_t)(0x0UL)

//@ref I2C_ENGC
#define I2C_ENGC_Enable						I2C_CR1_ENGC
#define I2C_ENGC_Disable					0x00000000UL
/*========================================================
 * 						APIs
 *========================================================
 */
void MCAL_I2C_Init(I2C_TypeDef* I2Cx, I2C_Config* I2C_Config);
void MCAL_I2C_DeInit(I2C_TypeDef* I2cx);
void MCAL_I2C_GPIO_Set_Pins(I2C_TypeDef* I2cx);


#endif /* INC_STM32_F103C6_I2C_DRIVER_H_ */
