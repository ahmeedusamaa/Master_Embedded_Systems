//embedded C Code of ARM-CORTEX-M3 TO TOGGLE A LED CONNECTED TO PA13
typedef volatile unsigned int vuint32_t ;
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


//define addresses
//RCC address (open clk of peripheral)
#define RCC_BASE  0x40021000
#define RCC_APB2ENR *(volatile uint32_t *)(RCC_BASE   +  0x18)
//to enable GPIO PORTA
#define RCC_IOPAEN (1<<2)
#define RCC_IOPBEN (1<<3)

//GPIO address
#define GPIOA_BASE 0x40010800
#define GPIOA_CRL    *(volatile uint32_t *)(GPIOA_BASE + 0x00)
#define GPIOA_CRH    *(volatile uint32_t *)(GPIOA_BASE + 0x04)
#define GPIOA_IDR    *(volatile uint32_t *)(GPIOA_BASE + 0x08)
#define GPIOA_ODR    *(volatile uint32_t *)(GPIOA_BASE + 0x0C)


#define GPIOB_BASE 0x40010C00
#define GPIOB_CRL    *(volatile uint32_t *)(GPIOB_BASE + 0x00)
#define GPIOB_CRH    *(volatile uint32_t *)(GPIOB_BASE + 0x04)
#define GPIOB_IDR    *(volatile uint32_t *)(GPIOB_BASE + 0x08)
#define GPIOB_ODR    *(volatile uint32_t *)(GPIOB_BASE + 0x0C)

void clock_init()
{
	// TO ENABLE CLOCK SIGNAL FOR GPIOA
	RCC_APB2ENR  |= RCC_IOPAEN ;
	// TO ENABLE CLOCK SIGNAL FOR GPIOB
	RCC_APB2ENR  |= RCC_IOPBEN ;


}
void GPIO_init()
{
	GPIOA_CRL = 0x0;
	GPIOA_CRH = 0x0;
	GPIOB_CRL = 0x0;
	GPIOB_CRH = 0x0;

	//PA1 input HighZ
	GPIOA_CRL |=(1<<6);
	//PA13 input HighZ
	GPIOA_CRH &= ~(0b11<<20);
	GPIOA_CRH |=  (0b01<<22);
	//PB1 output push pull mode
	GPIOB_CRL &= ~(0b11<<6);
	GPIOB_CRL |=  (0b01<<4);

	//PB13 output push pull mode
	GPIOB_CRH &=~(0b11<<22);
	GPIOB_CRH |= (0b01<<20);
}

void wait(int x)
{
	unsigned int i , j;
	for(i=0 ; i<x ; i++)
		for(j=0 ; j<255 ; j++);
}

int main(void)
{
	clock_init();
	GPIO_init();


	while(1)
	{
		//PA1 > connected to external PUR
		if(((GPIOA_IDR & (1<<1)) >>1) == 0 ) //press
		{
			GPIOB_ODR ^= (1<<1);
			while(((GPIOA_IDR & (1<<1)) >>1) == 0 ); //Single press
		}

		//PA13 > connected to external PDR
		if(((GPIOA_IDR & (1<<13)) >>13) ) // Multi pressing
		{
			GPIOB_ODR ^= (1<<13);
		}

		wait(1);
	}

}

