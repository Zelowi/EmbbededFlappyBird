/*
 * stm32f407xx_gpio.c
 *
 *  Created on: Mar 23, 2026
 *      Author: Zelowi
 */
#include"stm32f407xx_gpio.h"

void GPIO_Init(GPIO_HANDLE_t *pGPIOHandle)
{
	GPIO_PCLKCoontrol(pGPIOHandle->pGPIOx,ENABLE);




uint32_t temp = 0;// temp register
if(pGPIOHandle->GPIO_PinGonfig.GPIO_PinMode <= GPIO_MODE_ANALOG){
temp = (pGPIOHandle->GPIO_PinGonfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinGonfig.GPIO_PinNumber));

pGPIOHandle->pGPIOx->MODER &= ~(0x3 << pGPIOHandle->GPIO_PinGonfig.GPIO_PinNumber * 2);//clearing
pGPIOHandle->pGPIOx->MODER |= temp;//setting
}
else if(pGPIOHandle->GPIO_PinGonfig.GPIO_PinMode == GPIO_MODE_IT_FT){
	// configure the FTSR
	EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinGonfig.GPIO_PinNumber);
	// clear the coresponding RTSR bit
	EXTI->RTSR &= ~(1 << pGPIOHandle->GPIO_PinGonfig.GPIO_PinNumber);

}

else if(pGPIOHandle->GPIO_PinGonfig.GPIO_PinMode == GPIO_MODE_IT_RT){
	// configure the RTSR
	EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinGonfig.GPIO_PinNumber);
	// clear the coresponding FTSR bit
	EXTI->FTSR &= ~(1 << pGPIOHandle->GPIO_PinGonfig.GPIO_PinNumber);
	// configure the FTSR
}

else if(pGPIOHandle->GPIO_PinGonfig.GPIO_PinMode == GPIO_MODE_IT_RFT){
	// configure both the FTSR and RTSR
	// configure the FTSR
	EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinGonfig.GPIO_PinNumber);
	// configure the RTSR
	EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinGonfig.GPIO_PinNumber);

}


if(pGPIOHandle->GPIO_PinGonfig.GPIO_PinMode == GPIO_MODE_ALTFN){
uint32_t temp1,temp2;
temp1 = pGPIOHandle->GPIO_PinGonfig.GPIO_PinNumber / 8;
temp2 = pGPIOHandle->GPIO_PinGonfig.GPIO_PinNumber % 8;
pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xf << (4 * temp2));//clearing
pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinGonfig.GPIO_PinAltFunMode << (4 * temp2));

}
// configure the gpio port in syscfg_exticr

uint8_t temp1 = pGPIOHandle->GPIO_PinGonfig.GPIO_PinNumber / 4;
uint8_t temp2 = pGPIOHandle->GPIO_PinGonfig.GPIO_PinNumber % 4;
uint8_t portcode = GPIO_BASED_ADDRESS_TO_CODE(pGPIOHandle->pGPIOx);
SYSCFG_PCLK_EN();
SYSCFG->EXTICR[temp1] = portcode << (temp2 * 4);

// eneble the extr resisters using IMR
EXTI->IMR |= (1 << pGPIOHandle->GPIO_PinGonfig.GPIO_PinNumber);
temp = 0;

temp = (pGPIOHandle->GPIO_PinGonfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinGonfig.GPIO_PinNumber));
pGPIOHandle->pGPIOx->OSPEEDR  &= ~(0x3 << pGPIOHandle->GPIO_PinGonfig.GPIO_PinNumber * 2);//clearing
pGPIOHandle->pGPIOx->OSPEEDR |= temp;
temp = 0;

temp = (pGPIOHandle->GPIO_PinGonfig.GPIO_PinPuPdControl << (2 * pGPIOHandle->GPIO_PinGonfig.GPIO_PinNumber));
pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << pGPIOHandle->GPIO_PinGonfig.GPIO_PinNumber * 2);//clearing
pGPIOHandle->pGPIOx->PUPDR |= temp;
temp = 0;


temp = (pGPIOHandle->GPIO_PinGonfig.GPIO_OPType << (pGPIOHandle->GPIO_PinGonfig.GPIO_PinNumber));
pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 << pGPIOHandle->GPIO_PinGonfig.GPIO_PinNumber);//clearing
pGPIOHandle->pGPIOx->OTYPER |= temp;
temp = 0;

}
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx){
	if(pGPIOx == GPIOA){
		GPIOA_REG_RESET();
	}
}

void GPIO_PCLKCoontrol(GPIO_RegDef_t *pGPIOx,uint8_t EnOrDi)
{
if(EnOrDi == ENABLE){
	if(pGPIOx == GPIOA){
		GPIOA_PCLCK_EN();
	}
	else if(pGPIOx == GPIOB){
		GPIOB_PCLCK_EN();
	}
	else if(pGPIOx == GPIOC){
			GPIOC_PCLCK_EN();
		}
	else if(pGPIOx == GPIOD){
			GPIOD_PCLCK_EN();
		}
}
else{
	if(pGPIOx == GPIOA){
			GPIOA_PCLCK_DI();
		}
		else if(pGPIOx == GPIOB){
			GPIOB_PCLCK_DI();
		}
		else if(pGPIOx == GPIOC){
				GPIOC_PCLCK_DI();
			}
		else if(pGPIOx == GPIOD){
				GPIOD_PCLCK_DI();
			}
	}
}







uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber){
	uint8_t Value;
	Value = (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x00000001);
	return Value;
}
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx){
	uint16_t Value;
	Value = (uint16_t)pGPIOx->IDR;
	return Value;
}
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber,uint8_t Value){
	if(Value == SET){
		pGPIOx->ODR |= (1 << PinNumber);
	}
	else{
		pGPIOx->ODR &= ~(1 << PinNumber);
	}
}
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx,uint16_t Value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber){
	pGPIOx->ODR ^= (1 << PinNumber);
}
void IRQConfig(uint8_t IRQNumber,uint8_t EnOrDi){
	if(EnOrDi == ENABLE){
		if(IRQNumber <= 31){
			//iser0
			*NVIC_ISER0 |= (1 << IRQNumber);
		}

		else if(IRQNumber > 31 && IRQNumber < 64){
			//iser1
			*NVIC_ISER1 |= (1 << IRQNumber % 32);
		}

		else if(IRQNumber >= 64 && IRQNumber < 96){
		 // iser2
			*NVIC_ISER2 |= (1 << IRQNumber % 64);
				}
	}

	if(EnOrDi == DISABLE){
			if(IRQNumber <= 31){
				//iser0
				*NVIC_ICER0 |= (1 << IRQNumber);
			}

			else if(IRQNumber > 31 && IRQNumber < 64){
				//iser1
				*NVIC_ICER1 |= (1 << IRQNumber % 32);
			}

			else if(IRQNumber >= 64 && IRQNumber < 96){
			 // iser2
				*NVIC_ICER2 |= (1 << IRQNumber % 64);
					}
		}
}

void GPIO_IRQPriorityConfig(uint8_t IRQNumber,uint8_t IRQPriority){
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section = (IRQNumber % 4);
	uint8_t shift_amount = (iprx_section * 8) + (8 - NO_PR_BITS);
    *(NVIC_PR_BASEADDR + iprx * 4)  |= IRQPriority << shift_amount;

}
void IRQHandling(uint8_t PinNumber)
{
if(EXTI->PR & (1 << PinNumber))
{
	EXTI->PR &= (1 << PinNumber);
}
}



