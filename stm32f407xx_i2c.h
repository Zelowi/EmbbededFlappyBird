/*
 * stm32f407xx_i2c.h
 *
 *  Created on: Apr 18, 2026
 *      Author: Zelowi
 */

#ifndef INC_STM32F407XX_I2C_H_
#define INC_STM32F407XX_I2C_H_


#include"stm32f407xx.h"

typedef struct{
	uint32_t I2C_SLCSpeed;
	uint8_t I2C_DeviceAddress;
	uint8_t I2C_ACKControl;
	uint16_t I2C_FMDutyCycle;
} I2C_Config_t;

typedef struct{
	I2C_RegDef_t *pI2Cx;
	I2C_Config_t I2C_Config;
}I2C_Handle_t;


//i2c speed mode
#define I2C_SLC_SPEED_SM 100000U // speed standard mode
#define I2C_SLC_SPEED_FM 400000U // fast mode

//i2c ACKCONTROL

#define I2C_ACK_ENABLE 1
#define I2C_ACK_DINABLE  0


//i2c fmDutyCycle

#define  I2C_FM_DUTY_2       0 // for standard mode
#define  I2C_FM_DUTY_16    1 // for fast mode


//i2c flag section
#define I2C_SB_FLAG (1 << I2C_SR1_SB)
#define I2C_TXE_FLAG (1 << I2C_SR1_TxE)
#define I2C_RXNE_FLAG (1 <<I2C_SR1_RxNE)
#define I2C_ADDR_FLAG (1 <<I2C_SR1_ADDR)
#define I2C_BTF_FLAG (1 <<I2C_SR1_BTF)
#define I2C_STOPF_FLAG (1 <<I2C_SR1_STOPF)
#define I2C_BERR_FLAG (1 <<I2C_SR1_BERR)
#define I2C_ARLO_FLAG (1 <<I2C_SR1_ARLO)
#define I2C_AF_FLAG (1 <<I2C_SR1_AF)
#define I2C_OVR_FLAG (1 <<I2C_SR1_OVR)
#define I2C_TIMEOUT_FLAG (1 <<I2C_SR1_TIMEOUT)

#define I2C_BUSY_FLAG (1 << I2C_SR2_BUSY)




 void I2C_MasterSendData(I2C_Handle_t *pI2CHandle,uint8_t *TxBuffer,uint32_t Len,uint8_t SlaveAddress);

void I2C_PeripheralControl(I2C_RegDef_t* pI2Cx,uint8_t EnOrDi);

void I2C_PCLKControl(I2C_RegDef_t *pI2Cx,uint8_t EnOrDi);

void I2C_Init(I2C_Handle_t *pI2CHandle);
void I2C_DeInit(I2C_RegDef_t *pI2Cx);




void I2C_IRQConfig(uint8_t IRQNumber,uint8_t EnOrDi);
void I2C_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);



#endif /* INC_STM32F407XX_I2C_H_ */
