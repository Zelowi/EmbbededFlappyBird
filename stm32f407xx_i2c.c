/*
 * stm32f407xx_i2c.c
 *
 *  Created on: Apr 19, 2026
 *      Author: Zelowi
 */


#include"stm32f407xx_i2c.h"
#define RCC_AHB1ENR   (*(volatile uint32_t*)0x40023830)
#define GPIOD_MODER   (*(volatile uint32_t*)0x40020C00)
#define GPIOD_ODR     (*(volatile uint32_t*)0x40020C14)


void LED_ON(){
	   RCC_AHB1ENR |= (1 << 3);

	    // 2. Set PD12 as output (MODER12 = 01)
	    GPIOD_MODER &= ~(3 << (12 * 2)); // clear
	    GPIOD_MODER |=  (1 << (12 * 2)); // output mode

	    // 3. Set PD12 HIGH → LED ON
	    GPIOD_ODR |= (1 << 12);
}

static void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx){
	pI2Cx->CR1 |= (1 << I2C_CR1_STOP);
}

static void I2C_ClearADDRFlag(I2C_RegDef_t *pI2Cx){
	uint32_t readToClear = pI2Cx->SR1;// to clear that bit we need to read sr1 and sr2 so i do it here
	readToClear = pI2Cx->SR2;
	(void)readToClear;// do type cast to ignore warning and to show that we dont use variable and we dont care about value
}

static void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx){
	pI2Cx->CR1 |= (1 << I2C_CR1_START);
}

static void I2C_ExecuteAddressPhase(I2C_RegDef_t *pI2Cx,uint8_t SlaveAddress){
	SlaveAddress = SlaveAddress << 1;// create space for r/w bit
	SlaveAddress &= ~(1);// clear zero bit it means we set to write mode
	pI2Cx->DR = SlaveAddress;
}

uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx,uint32_t FlagName){
	if(pI2Cx->SR1 & (FlagName)){
		return SET;
	}
	else {
	    return RESET;
	}
}

uint8_t I2C_GetFlagStatusSR2(I2C_RegDef_t *pI2Cx,uint32_t FlagName){
	if(pI2Cx->SR2 & (FlagName)){
		return SET;
	}
	else {
	    return RESET;
	}
}


uint32_t RCC_GetPCLKValue(){
	uint32_t pclk1;
	uint8_t clksrc; // clock source
	clksrc = (RCC->CFGR >> 2) & 0x3;;// we do shift because we move bits 2 and 3 to postion 0 and 1
	if(clksrc == 0){
		pclk1 = 16000000;
	}
	else if(clksrc == 1){
		pclk1 = 8000000;
	}
	else if(clksrc == 2)// that for pll i dont use it in my project
	{

	}
	return pclk1;
}



void I2C_PCLKControl(I2C_RegDef_t *pI2Cx,uint8_t EnOrDi){
	if(EnOrDi == ENABLE){
		if(pI2Cx == I2C1){
			I2C1_EN();
		}
		else if(pI2Cx == I2C2){
			I2C2_EN();
		}
		else if(pI2Cx == I2C3){
			I2C3_EN();
		}
	}
	else if(EnOrDi == DISABLE){
		if(pI2Cx == I2C1){
			I2C1_DI();
		}
		else if(pI2Cx == I2C2){
			I2C2_DI();
		}
		else if(pI2Cx == I2C3){
			I2C3_DI();
		}
	}
}

void I2C_PeripheralControl(I2C_RegDef_t* pI2Cx,uint8_t EnOrDi){
	if(EnOrDi == ENABLE){
			pI2Cx->CR1 |= (1 << I2C_CR1_PE);
		}
		else{
			pI2Cx->CR1 &= ~(1 << I2C_CR1_PE);
		}
}

void I2C_Init(I2C_Handle_t *pI2CHandle){


	I2C_PCLKControl(pI2CHandle->pI2Cx,ENABLE);
	uint32_t pclk1 = RCC_GetPCLKValue();
	//uint32_t pclk1 = 42000000U;

	uint32_t tempreg = 0;
	//ask controll bit
	tempreg |= pI2CHandle->I2C_Config.I2C_ACKControl << I2C_CR1_ACK;
	pI2CHandle->pI2Cx->CR1 |= tempreg;

	//configure FREQ of CR2
	tempreg = 0;
	tempreg = pclk1/ 1000000U;
	pI2CHandle->pI2Cx->CR2 = (tempreg & 0x3F);

	//configure OAR1 device own address
	tempreg = 0;
	tempreg |= pI2CHandle->I2C_Config.I2C_DeviceAddress << 1;
	tempreg |= (1 << 14);
	pI2CHandle->pI2Cx->OAR1 |= tempreg ;

	//CCR calculations
	uint16_t ccr_value = 0;
	tempreg = 0;
	if(pI2CHandle->I2C_Config.I2C_SLCSpeed <= I2C_SLC_SPEED_SM ){
		//mode is standard mode
		ccr_value = (pclk1/ ( 2 * pI2CHandle->I2C_Config.I2C_SLCSpeed));
		tempreg = (ccr_value & 0xFFF);
	}
	else{
		//mode is fast mode
		tempreg |= (1 << 15);

		if(pI2CHandle->I2C_Config.I2C_FMDutyCycle == I2C_FM_DUTY_2  ){
			ccr_value = (pclk1 / ( 3 * pI2CHandle->I2C_Config.I2C_SLCSpeed));
		}
		else{
			tempreg |= pI2CHandle->I2C_Config.I2C_FMDutyCycle << 14;
			ccr_value = (pclk1 / ( 25 * pI2CHandle->I2C_Config.I2C_SLCSpeed));
		}

		tempreg |= (ccr_value & 0xFFF);
	}
	pI2CHandle->pI2Cx->CCR = tempreg ;

	//TRISE
		if(pI2CHandle->I2C_Config.I2C_SLCSpeed <= I2C_SLC_SPEED_SM ){
			//mode is standard

			tempreg = (pclk1 / 1000000U) + 1;
		}
		else{
			//fast mode
			tempreg = (pclk1 * 300 / 1000000000U) + 1;
		}
		pI2CHandle->pI2Cx->TRISE = (tempreg & 0x3F);

		//////hardcore for test
		//I2C1->CR2   = 42;
		//I2C1->CCR   = ((1 << 15) | 35);//210 for standard mode
		//I2C1->TRISE = 13;


}
void I2C_DeInit(I2C_RegDef_t *pI2Cx);



void I2C_MasterSendData(I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer,uint32_t Len,uint8_t SlaveAddress){
	while(I2C_GetFlagStatusSR2(pI2CHandle->pI2Cx, I2C_BUSY_FLAG));
	//Generate start condition
	I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

	// confirm start by checking SB flag in SR1
	while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_SB_FLAG));//work when reset because !reset is set it means when set it stops.it waits until flag is set

	//send address to slave and set r/w bit to 0
	I2C_ExecuteAddressPhase(pI2CHandle->pI2Cx,SlaveAddress);

	//confirm that address phase is done be checking ADDR flag in SR1
	while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_ADDR_FLAG));

	/////i need to turn on led here to confirm ack
	LED_ON();

	// clear ADDR flag
	I2C_ClearADDRFlag(pI2CHandle->pI2Cx);

	//send data until len is 0
	while(Len > 0){
		while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_TXE_FLAG));// wait until txe is set
		pI2CHandle->pI2Cx->DR = *pTxBuffer;
		pTxBuffer++;
		Len--;
	}

	//wait unit Txe set(dr is empty) and btf set(transmition done so shift register empty)
	while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_TXE_FLAG));
		while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_BTF_FLAG));

	//generate stop condition

		I2C_GenerateStopCondition(pI2CHandle->pI2Cx);
		while(I2C_GetFlagStatusSR2(pI2CHandle->pI2Cx, I2C_BUSY_FLAG));



}




