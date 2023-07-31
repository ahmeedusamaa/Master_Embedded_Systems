/*
 * Stm32_F103C6_I2C_driver.c
 *
 *  Created on: Jul 31, 2023
 *      Author: ahmed osama
 */

#include "Stm32_F103C6_I2C_driver.h"
//Master Polling Mechanism
//Slave interrupt Mechanism

/*========================================================
 * 				   Generic Variables
 *========================================================
 */
I2C_Config Global_I2C_Config[2]={NULL, NULL};

/*========================================================
 * 				   Generic Macros
 *========================================================
 */
#define I2C1_INDEX			0
#define I2C2_INDEX			1



/*========================================================
 * 			APIs Supported by "MCAL I2C DRIVER"
 *========================================================
 */
void MCAL_I2C_Init(I2C_TypeDef* I2Cx, I2C_Config* I2C_Config)
{
	uint16_t pclk1= 8000000UL;
	uint16_t tempReg=0 , freqRange=0;
	uint16_t result=0;
	if(I2Cx==I2C1)
	{
		Global_I2C_Config[I2C1_INDEX]= *I2C_Config;
		RCC_I2C1_CLK_EN();
	}
	else if(I2Cx==I2C2)
	{
		Global_I2C_Config[I2C2_INDEX]= *I2C_Config;
		RCC_I2C2_CLK_EN();
	}
    /*
	 *   Bits 5:0 FREQ[5:0]: Set Peripheral clock frequency
	 */
	//Get the I2Cx_CR2 value
	tempReg= I2Cx->CR2;
	//Clear frequency FREQ[5:0] bits
	tempReg &= ~(I2C_CR2_FREQ);
	//Get the pclk1 frequency value
	pclk1= MCAL_RCC_GetPCLK1Freq();
	//Set frequency FREQ[5:0] bits
	freqRange= (uint16_t)(pclk1/1000000);
	tempReg |= freqRange;
	I2Cx->CR2= tempReg;

	//Disable the selected I2C peripheral
	I2Cx->CR1 &=~(I2C_CR1_PE);

	tempReg=0;
	/*
	 * Configure the clock control registers --->>>CCR[11:0]:Thigh = CCR * TPCLK1
	 */
	//Configure the Speed in Standard mode
	if((I2C_Config->I2C_CLK_speed==I2C_CLK_speed_SM_50k) || (I2C_Config->I2C_CLK_speed==I2C_CLK_speed_SM_100k) )
	{
		//Bit 15 already 0 (0:Sm mode I2C)
		// Tclk/2= CRR * Tpclk1
		// CRR= Tclk/(2*Tpclk1)
		// CRR= Fpclk1/(2*I2C_clk_speed)
		result= (uint16_t)(pclk1/(I2C_Config->I2C_CLK_speed << 1));
		tempReg|=result;
		I2Cx->CCR= tempReg;

		/*
		 * Configure the rise time register	------>>>TRISE[5:0]:(1000 ns / 125 ns = 8 + 1)
		 */
		I2Cx->TRISE=freqRange+1;

		tempReg=I2Cx->CR1;
		tempReg |= I2C_Config->I2C_ACK_Control;
		tempReg |= I2C_Config->I2C_Mode;
		tempReg |= I2C_Config->I2C_Stretch_Mode;
		tempReg |= I2C_Config->General_Call_Address_Detection;
		I2Cx->CR1=tempReg;

		tempReg=0;
		if(I2C_Config->I2C_Slave_address.Dual_Address_Enable==1)
		{
			//Dual addressing mode enable
			tempReg=I2C_OAR2_ENDUAL;

			tempReg |=I2C_Config->I2C_Slave_address.Secondary_Slave_address << I2C_OAR2_ADD2_Pos;
			I2Cx->OAR2=tempReg;
		}
		tempReg= 0;

		tempReg |=I2C_Config->I2C_Slave_address.Primary_slave_address << 1;
		tempReg |=I2C_Config->I2C_Slave_address.I2C_Addressing_Slave_mode ;
		I2Cx->OAR1=tempReg;
	}
	else
	{
		//Fast Mode not supported
	}

/*
 * enable the peripheral
 */


}
void MCAL_I2C_DeInit(I2C_TypeDef* I2cx);
void MCAL_I2C_GPIO_Set_Pins(I2C_TypeDef* I2cx);
