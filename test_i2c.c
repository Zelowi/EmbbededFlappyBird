/*
 * test_i2c.c
 *
 *  Created on: Apr 25, 2026
 *      Author: Zelowi
 */

#include "stm32f407xx_i2c.h"


#include "stm32f407xx_gpio.h"
#include "ssd1306.h"
#include <flappy.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>




////just to know that we start
#define RCC_AHB1ENR   (*(volatile uint32_t*)0x40023830)
#define GPIOD_MODER   (*(volatile uint32_t*)0x40020C00)
#define GPIOD_ODR     (*(volatile uint32_t*)0x40020C14)
//////////



void delay()
{
    for(volatile int i = 0; i < 100000; i++);
}

I2C_Handle_t I2C_Handle;

void I2C1_GPIOInit(){
	GPIO_HANDLE_t I2CPins;
	I2CPins.pGPIOx = GPIOB;
	I2CPins.GPIO_PinGonfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	I2CPins.GPIO_PinGonfig.GPIO_PinAltFunMode = 4;
	I2CPins.GPIO_PinGonfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	I2CPins.GPIO_PinGonfig.GPIO_OPType = GPIO_OP_TYPE_OD;
	I2CPins.GPIO_PinGonfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;


	I2CPins.GPIO_PinGonfig.GPIO_PinNumber = GPIO_PIN_NUMBER_6;// slc
	GPIO_Init(&I2CPins);

	I2CPins.GPIO_PinGonfig.GPIO_PinNumber = GPIO_PIN_NUMBER_7;// sda
	GPIO_Init(&I2CPins);

}

void I2C1_Inits(){

	I2C_Handle.pI2Cx = I2C1;
	I2C_Handle.I2C_Config.I2C_DeviceAddress = 0x61;
	I2C_Handle.I2C_Config.I2C_ACKControl = I2C_ACK_ENABLE;
	I2C_Handle.I2C_Config.I2C_SLCSpeed = I2C_SLC_SPEED_FM;
	I2C_Handle.I2C_Config.I2C_FMDutyCycle = I2C_FM_DUTY_2;

	I2C_Init(&I2C_Handle);

}

void Button_Init()
{
    GPIO_HANDLE_t button;

    button.pGPIOx = GPIOA;
    button.GPIO_PinGonfig.GPIO_PinNumber = GPIO_PIN_NUMBER_0;
    button.GPIO_PinGonfig.GPIO_PinMode = GPIO_MODE_IN;
    button.GPIO_PinGonfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

    GPIO_Init(&button);
}



int main(){



	I2C1_GPIOInit();

	I2C1_Inits();

	I2C_PeripheralControl(I2C1,ENABLE);

	Button_Init();



	Pipe_t pipes[PIPE_COUNT];

	Pipes_Init(pipes);

	Bird_t bird;
	bird.x = 15;
	bird.y = 56;
	uint8_t start = 1;

	I2C_MasterSendData(&I2C_Handle,(uint8_t*)ssd1306_init_cmds,SSD1306_INIT_SIZE,OLED_ADDR);//i send init configuration
	delay();

	while(start){


	clear(buffer);
	uint8_t state = ReadButton();
	int direction = HandleInput(state);




	MoveBird(&bird,buffer,direction);
	MovePipes(pipes,buffer);


	I2C_MasterSendData(&I2C_Handle, buffer, sizeof(buffer), OLED_ADDR);
	start = Collision(&bird,pipes);
	delay();


	}
	return 0;

}
