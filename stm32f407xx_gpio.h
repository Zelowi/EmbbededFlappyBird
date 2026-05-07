/*
 * stm32f407xx_gpio.h
 *
 *  Created on: Mar 23, 2026
 *      Author: Zelowi
 */

#ifndef INC_STM32F407XX_GPIO_H_
#define INC_STM32F407XX_GPIO_H_

#include"stm32f407xx.h"

//@GPIO PIN MODES

#define GPIO_MODE_IN 0
#define GPIO_MODE_OUT 1
#define GPIO_MODE_ALTFN 2
#define GPIO_MODE_ANALOG 3
#define GPIO_MODE_IT_FT 4
#define GPIO_MODE_IT_RT 5
#define GPIO_MODE_IT_RFT 6

#define GPIO_OP_TYPE_PP        0
#define GPIO_OP_TYPE_OD        1

#define GPIO_SPEED_LOW        0
#define GPIO_SPEED_MEDIUM     1
#define GPIO_SPEED_FAST       2
#define GPIO_SPEED_HIGH       3

#define GPIO_NO_PUPD          0
#define GPIO_PIN_PU               1
#define GPIO_PIN_PD               2


#define GPIO_PIN_NUMBER_0 0
#define GPIO_PIN_NUMBER_1 1
#define GPIO_PIN_NUMBER_2 2
#define GPIO_PIN_NUMBER_3 3
#define GPIO_PIN_NUMBER_4 4
#define GPIO_PIN_NUMBER_5 5
#define GPIO_PIN_NUMBER_6 6
#define GPIO_PIN_NUMBER_7 7
#define GPIO_PIN_NUMBER_8 8
#define GPIO_PIN_NUMBER_9 9
#define GPIO_PIN_NUMBER_10 10
#define GPIO_PIN_NUMBER_11 11
#define GPIO_PIN_NUMBER_12 12
#define GPIO_PIN_NUMBER_13 13
#define GPIO_PIN_NUMBER_14 14
#define GPIO_PIN_NUMBER_15 15


#define GPIO_BASED_ADDRESS_TO_CODE(x)    ((x == GPIOA) ? 0 :\
									     (x == GPIOB) ? 1 :\
									     (x == GPIOC) ? 2 :\
									     (x == GPIOD) ? 3 :\
									     (x == GPIOE) ? 4 :\
										 (x == GPIOF) ? 5 :\
			    						 (x == GPIOG) ? 6 :\
			    					     (x == GPIOH) ? 7 :0)



typedef struct
{
	uint8_t GPIO_PinNumber;
	uint8_t GPIO_PinMode;  // possible pin modes @GPIO PIN MODES
	uint8_t GPIO_PinSpeed;// possible pin modes @GPIO PIN SPEED
	uint8_t GPIO_PinPuPdControl;
	uint8_t GPIO_OPType;
	uint8_t GPIO_PinAltFunMode;
}GPIO_PinConfig_t;


typedef struct
{
	GPIO_RegDef_t* pGPIOx;
	GPIO_PinConfig_t GPIO_PinGonfig;
}GPIO_HANDLE_t;




void GPIO_Init(GPIO_HANDLE_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

void GPIO_PCLKCoontrol(GPIO_RegDef_t *pGPIOx,uint8_t EnOrDi);



uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber,uint8_t value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx,uint16_t Value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx,uint8_t Value);
void IRQConfig(uint8_t IRQNumber,uint8_t EnOrDi);
void IRQHandling(uint8_t PinNumber);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);


#endif /* INC_STM32F407XX_GPIO_H_ */
