
#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_

#include <stdint.h>


// processor details
#define NVIC_ISER0 ((volatile uint32_t*) 0xE000E100)
#define NVIC_ISER1 ((volatile uint32_t*) 0xE000E104)
#define NVIC_ISER2 ((volatile uint32_t*) 0xE000E108)
#define NVIC_ISER3 ((volatile uint32_t*) 0xE000E10C)


#define NVIC_PR_BASEADDR ((volatile uint32_t*) 0xE000E400)


#define  NO_PR_BITS 4


#define NVIC_ICER0 ((volatile uint32_t*) 0xE000E180)
#define NVIC_ICER1 ((volatile uint32_t*) 0xE000E184)
#define NVIC_ICER2 ((volatile uint32_t*) 0xE000E188)
#define NVIC_ICER3 ((volatile uint32_t*) 0xE000E18C)

#define FLASH_BASEADDR  0x08000000U
#define SRAM1_BASEADDR  0x20000000U
#define SRAM2_BASEADDR  0x2001C000U
#define ROM_BASEADDR    0x1FFF0000U
#define SRAM SRAM1_BASEADDR

#define  PERIPH_BASE 0x40000000U
#define APB1_PERIPH_BASE PERIPH_BASE
#define APB2_PERIPH_BASE 0x40010000U
#define AHB1_PERIPH_BASE 0x40020000U
#define AHB2_PERIPH_BASE 0x50000000U

#define GPIOA_BASEADDR (AHB1_PERIPH_BASE + 0x0000)
#define GPIOB_BASEADDR (AHB1_PERIPH_BASE + 0x0400)
#define GPIOC_BASEADDR (AHB1_PERIPH_BASE + 0x0800)
#define GPIOD_BASEADDR (AHB1_PERIPH_BASE + 0x0C00)
#define GPIOE_BASEADDR (AHB1_PERIPH_BASE + 0x1000)
#define GPIOF_BASEADDR (AHB1_PERIPH_BASE + 0x1400)
#define GPIOG_BASEADDR (AHB1_PERIPH_BASE + 0x1800)
#define GPIOH_BASEADDR (AHB1_PERIPH_BASE + 0x1C00)
#define GPIOI_BASEADDR (AHB1_PERIPH_BASE + 0x2000)

#define RCC_BASEADDR (AHB1_PERIPH_BASE + 0x3800)


#define I2C1 ((I2C_RegDef_t*)I2C1_BASEADDR)
#define I2C2 ((I2C_RegDef_t*)I2C2_BASEADDR)
#define I2C3 ((I2C_RegDef_t*)I2C3_BASEADDR)



#define I2C1_BASEADDR (APB1_PERIPH_BASE + 0x5400)
#define I2C2_BASEADDR (APB1_PERIPH_BASE + 0x5800)
#define I2C3_BASEADDR (APB1_PERIPH_BASE + 0x5C00)


#define SPI1_BASEADDR (APB2_PERIPH_BASE + 0x3000)
#define SPI2_BASEADDR (APB1_PERIPH_BASE + 0x3800)
#define SPI3_BASEADDR (APB1_PERIPH_BASE + 0x3C00)


#define USART2_BASEADDR (APB1_PERIPH_BASE + 0x4400)
#define USART3_BASEADDR (APB1_PERIPH_BASE + 0x4800)
#define UART4_BASEADDR (APB1_PERIPH_BASE + 0x4C00)
#define UART5_BASEADDR (APB1_PERIPH_BASE + 0x5000)


#define EXTI_BASEADDR (APB2_PERIPH_BASE + 0x3C00)
#define USART1_BASEADDR (APB2_PERIPH_BASE + 0x1000)
#define USART6_BASEADDR (APB2_PERIPH_BASE + 0x1400)
#define SYSCFG_BASEADDR (APB2_PERIPH_BASE + 0x3800)





typedef struct {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;   // <-- FIX
    volatile uint32_t LCKR;
    volatile uint32_t AFR[2];
} GPIO_RegDef_t;


typedef struct
{
   volatile uint32_t CR1;    /* Address offset: 0x00 */
   volatile uint32_t CR2;
   volatile  uint32_t SR;
   volatile  uint32_t DR;
   volatile  uint32_t CRCPR;  /* Address offset: 0x08 */
   volatile  uint32_t RXCRCR;
   volatile  uint32_t TXCRCR;
   volatile  uint32_t I2SCFGR;
   volatile  uint32_t I2SPR;

} SPI_RegDef_t;

#define SPI ((SPI_RegDef_t*)SPI1_BASEADDR)


#define SPI1 ((SPI_RegDef_t*)SPI1_BASEADDR)
#define SPI2 ((SPI_RegDef_t*)SPI2_BASEADDR)
#define SPI3 ((SPI_RegDef_t*)SPI3_BASEADDR)


#define GPIOA ((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB ((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC ((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD ((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE ((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF ((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG ((GPIO_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH ((GPIO_RegDef_t*)GPIOH_BASEADDR)
#define GPIOI ((GPIO_RegDef_t*)GPIOI_BASEADDR)

//GPIO_RegDef_t *pGPIOA = GPIOA;




typedef struct
{
	volatile uint32_t CR;
	    volatile uint32_t PLLCFGR;
	    volatile uint32_t CFGR;
	    volatile uint32_t CIR;
	    volatile uint32_t AHB1RSTR;
	    volatile uint32_t AHB2RSTR;
	    volatile uint32_t AHB3RSTR;
	    uint32_t RESERVED0;
	    volatile uint32_t APB1RSTR;
	    volatile uint32_t APB2RSTR;
	    uint32_t RESERVED1[2];
	    volatile uint32_t AHB1ENR;
	    volatile uint32_t AHB2ENR;
	    volatile uint32_t AHB3ENR;
	    uint32_t RESERVED2;
	    volatile uint32_t APB1ENR;
	    volatile uint32_t APB2ENR;
	    uint32_t RESERVED3[2];
	    volatile uint32_t AHB1LPENR;
	    volatile uint32_t AHB2LPENR;
	    volatile uint32_t AHB3LPENR;
	    uint32_t RESERVED4;
	    volatile uint32_t APB1LPENR;
	    volatile uint32_t APB2LPENR;
	    uint32_t RESERVED5[2];
	    volatile uint32_t BDCR;
	    volatile uint32_t CSR;
	    uint32_t RESERVED6[2];
	    volatile uint32_t SSCGR;
	    volatile uint32_t PLLI2SCFGR;
	    volatile uint32_t PLLSAICFGR;
	    volatile uint32_t DCKCFGR;
	    volatile uint32_t CKGATENR;
        volatile uint32_t DCKCFGR2;

}RCC_Reg_Def_t;

#define RCC ((RCC_Reg_Def_t*)RCC_BASEADDR )



// peripheral definetion structer for EXTI

typedef struct
{
   volatile uint32_t IMR;    /* Address offset: 0x00 */
   volatile  uint32_t EMR;
   volatile  uint32_t RTSR;  /* Address offset: 0x08 */
   volatile  uint32_t FTSR;
   volatile  uint32_t SWIER;
   volatile  uint32_t PR;

} EXTI_RegDef_t;


typedef struct {
	uint32_t CR1;
	uint32_t CR2;
	uint32_t OAR1;
	uint32_t OAR2;
	uint32_t DR;
	uint32_t SR1;
	uint32_t SR2;
	uint32_t CCR;
	uint32_t TRISE;
	uint32_t FLTR;

}I2C_RegDef_t;


#define EXTI  ((EXTI_RegDef_t*)EXTI_BASEADDR )

//RCC_Reg_Def_t *pRCC = RCC;




// peripheral definetion structer for SYSCFG

typedef struct
{
   volatile uint32_t MEMRMP;    /* Address offset: 0x00 */
   volatile  uint32_t PMC;
   volatile  uint32_t EXTICR[4];  /* Address offset: 0x08 */

   volatile uint32_t RESERVED1[2];
   volatile  uint32_t CMPCR;
   volatile uint32_t RESERVED2[2];
} SYSCFG_RegDef_t;

#define SYSCFG  ((SYSCFG_RegDef_t*)SYSCFG_BASEADDR )



#define GPIOA_PCLCK_EN() ( RCC-> AHB1ENR |= (1 << 0))
#define GPIOB_PCLCK_EN() ( RCC-> AHB1ENR |= (1 << 1))
#define GPIOC_PCLCK_EN() ( RCC-> AHB1ENR |= (1 << 2))
#define GPIOD_PCLCK_EN() ( RCC-> AHB1ENR |= (1 << 3))


#define  SYSCFG_PCLK_EN()  ( RCC-> APB2ENR |= (1 << 14))


#define I2C1_EN() ( RCC-> APB1ENR |= (1 << 21))
#define I2C2_EN() ( RCC-> APB1ENR |= (1 << 22))
#define I2C3_EN() ( RCC-> APB1ENR |= (1 << 23))



#define I2C1_DI() ( RCC-> APB1ENR &= ~(1 << 21))
#define I2C2_DI() ( RCC-> APB1ENR &= ~(1 << 22))
#define I2C3_DI() ( RCC-> APB1ENR &= ~(1 << 23))


#define GPIOA_PCLCK_DI() ( RCC-> AHB1ENR &= (0 << 0))
#define GPIOB_PCLCK_DI() ( RCC-> AHB1ENR &= (0 << 1))
#define GPIOC_PCLCK_DI() ( RCC-> AHB1ENR &= (0 << 2))
#define GPIOD_PCLCK_DI() ( RCC-> AHB1ENR &= (0<< 3))


#define GPIOA_REG_RESET()   do { RCC-> AHB1RSTR |= (1 << 0) ;  RCC-> AHB1RSTR &= ~(1 << 0);} while(0)
#define GPIOB_REG_RESET()   do { RCC-> AHB1RSTR |= (1 << 1) ;  RCC-> AHB1RSTR &= ~(1 << 1);} while(0)
#define GPIOC_REG_RESET()   do { RCC-> AHB1RSTR |= (1 << 2) ;  RCC-> AHB1RSTR &= ~(1 << 2);} while(0)
//SPI clock enable and disable
#define SPI1_PCLK_EN()   ( RCC-> APB2ENR |= (1 << 12))
#define SPI2_PCLK_EN()  ( RCC-> APB1ENR |= (1 << 14))
#define SPI3_PCLK_EN()  ( RCC-> APB1ENR |= (1 << 15))

#define SPI1_PCLK_DI()   ( RCC-> APB2ENR &= (0 << 12))
#define SPI2_PCLK_DI()  ( RCC-> APB1ENR &= (0 << 14))
#define SPI3_PCLK_DI()  ( RCC-> APB1ENR &= (0 << 15))


#define SPI1_REG_RESET()   do { RCC->APB2RSTR |= (1 << 12); RCC->APB2RSTR &= ~(1 << 12); } while(0)
#define SPI2_REG_RESET()   do { RCC->APB1RSTR |= (1 << 14); RCC->APB1RSTR &= ~(1 << 14); } while(0)
#define SPI3_REG_RESET()   do { RCC->APB1RSTR |= (1 << 15); RCC->APB1RSTR &= ~(1 << 15); } while(0)


#define ENABLE 1
#define DISABLE 0
#define SET 1
#define RESET 0

#define IRQ_NO_EXTI0        6
#define IRQ_NO_EXTI1        7
#define IRQ_NO_EXTI2        8
#define IRQ_NO_EXTI3        9
#define IRQ_NO_EXTI4        10
#define IRQ_NO_EXTI9_5      23
#define IRQ_NO_EXTI15_10    40


//Bit position definition of SPI peripheral
// SPI_CR1 bits
#define SPI_CR1_CPHA 0
#define SPI_CR1_CPOL 1
#define SPI_CR1_SPE 6
#define SPI_CR1_SPEED 3
#define SPI_CR1_DFF 11

#define SPI_CR1_SSM 9
#define SPI_CR1_SSI 8

//SPI_CR2 bits
#define SPI_CR2_RXDMAEN 0
#define SPI_CR2_TXDMAEN 1
#define SPI_CR2_SSOE 2
#define SPI_CR2_FRF 4
#define SPI_CR2_ERRIE 5
#define SPI_CR2_RXNEIE 6
#define SPI_CR2_TXEIE 7

//SPI_SR bits
#define SPI_SR_RXNE    0
#define SPI_SR_TXE     1
#define SPI_SR_CHSIDE  2
#define SPI_SR_UDR     3
#define SPI_SR_CRCERR  4
#define SPI_SR_MODF    5
#define SPI_SR_OVR     6
#define SPI_SR_BSY     7
#define SPI_SR_FRE     8



// I2C_CR1 structure
#define I2C_CR1_PE 0
#define I2C_CR1_SMBUS 1
#define I2C_CR1_SMBTYPE 3
#define I2C_CR1_ENARP 4
#define I2C_CR1_ENPEC 5
#define I2C_CR1_ENGC 6
#define I2C_CR1_NOSTRETCH 7
#define I2C_CR1_START 8
#define I2C_CR1_STOP 9
#define I2C_CR1_ACK 10
#define I2C_CR1_POS 11
#define I2C_CR1_PEC 12
#define I2C_CR1_ALERT 13
#define I2C_CR1_SWRST 15

//I2C_CR2 structure

#define I2C_CR2_ITERREN 8
#define I2C_CR2_ITEVTEN 9
#define I2C_CR2_ITBUFEN 10
#define I2C_CR2_DMAEN 11
#define I2C_CR2_LAST 12

//I2C_DR structure


//I2C_SR1 structure
#define I2C_SR1_SB  0
#define I2C_SR1_ADDR  1
#define I2C_SR1_BTF 2
#define I2C_SR1_ADD10 3
#define I2C_SR1_STOPF 4
#define I2C_SR1_RxNE 6
#define I2C_SR1_TxE 7
#define I2C_SR1_ BERR 8
#define I2C_SR1_ARLO 9
#define I2C_SR1_AF 10
#define I2C_SR1_OVR 11
#define I2C_SR1_PECERR 12
#define I2C_SR1_TIMEOUT 14
#define I2C_SR1_SMBALERT 15

//I2C_SR2 structure
#define I2C_SR2_MSL 0
#define I2C_SR2_BUSY 1
#define I2C_SR2_TRA 2
#define I2C_SR2_GENCALL 4
#define I2C_SR2_SMBDEFAULT 5
#define I2C_SR2_SMBHOST 6
#define I2C_SR2_DUALF 7







#endif /* INC_STM32F407XX_H_ */
