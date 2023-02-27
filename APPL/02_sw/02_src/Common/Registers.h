/*
 * Registers.h
 *
 *  Created on: Jan 27, 2023
 *      Author: uif79130
 */

#ifndef COMMON_REGISTERS_H_
#define COMMON_REGISTERS_H_

//#include "Platform_cfg.h"


/// Definition of 32-bit registers
//#define REG32(address) (*((volatile uint32_t *) (address) ))
///// Definition of 16-bit registers
//#define REG16(address) (*((volatile uint16_t *) (address) ))
///// Peripheral base address in the alias region
//#define REG_PERIPH_BASE (0x40000000UL)
///// USART2 Clock enable
//#define RCC_AHB1ENR (RCC_BASE + 0x0030UL)
///// Advanced Peripheral Bus address
//#define RCC_APB1ENR (RCC_BASE + 0x0040UL)
///// USART2 base of APB1 peripheral
//#define USART2_BASE (APB1PERIPH_BASE + 0x4400UL)
///// GPIOA base of AHB1 peripheral
//#define GPIOA_BASE (AHB1PERIPH_BASE + 0x0000UL)
///// RCC register base
//#define RCC_BASE (AHB1PERIPH_BASE + 0x3800UL)
///// USART2->SR register
//#define USART2_SR (USART2_BASE + 0x0000UL)
///// USART2->DR register
//#define USART2_DR (USART2_BASE + 0x0004UL)
///// USART2->BRR register
//#define USART2_BRR (USART2_BASE + 0x0008UL)
///// USART2->CR1 register
//#define USART2_CR1 (USART2_BASE + 0x000CUL)
///// GPIOA->MODER register
//#define GPIOA_MODER (GPIOA_BASE + 0x0000UL)
///// GPIOA->SPEEDER register
//#define GPIOA_OSPEEDER (GPIOA_BASE + 0x0008UL)
///// GPIOA->AFR register
//#define GPIOA_AFR0 (GPIOA_BASE + 0x0020UL)
///// GPIO->ODR register
//#define GPIOA_ODR (GPIOA_BASE + 0x0014UL)

/// Definition of 32-bit registers
#define REG32(address) (*((volatile uint32_t *) (address) ))
/// Definition of 16-bit registers
#define REG16(address) (*((volatile uint16_t *) (address) ))
/// Peripheral base address in the alias region
#define REG_PERIPH_BASE (0x40000000UL)
/// RCC register base
#define RCC_BASE (AHB1PERIPH_BASE + 0x3800UL)
/// USART2 Clock enable
#define RCC_AHB1ENR (RCC_BASE + 0x0030UL)
/// Advanced Peripheral Bus address
#define RCC_APB1ENR (RCC_BASE + 0x0040UL)
/// USART2 base of APB1 peripheral
#define USART3_BASE (APB1PERIPH_BASE + 0x4800UL)
/// GPIOA base of AHB1 peripheral
#define GPIOD_BASE (AHB1PERIPH_BASE + 0x0C00UL)

#define GPIOB_BASE (AHB1PERIPH_BASE + 0x0400UL)
/// USART2->SR register
#define USART3_SR (USART3_BASE + 0x0000UL)
/// USART2->DR register
#define USART3_DR (USART3_BASE + 0x0004UL)
/// USART2->BRR register
#define USART3_BRR (USART3_BASE + 0x0008UL)
/// USART2->CR1 register
#define USART3_CR1 (USART3_BASE + 0x000CUL)
/// GPIOA->MODER register
#define GPIOD_MODER (GPIOD_BASE + 0x0000UL)
/// GPIOA->SPEEDER register
#define GPIOD_OSPEEDER (GPIOD_BASE + 0x0008UL)
/// GPIOA->AFR register
#define GPIOD_AFR1 (GPIOD_BASE + 0x0024UL)
/// GPIO->ODR register
#define GPIOB_ODR (GPIOB_BASE + 0x0014UL)
//
//#else
//#error "Platform configuration not defined!"
//#endif /* PLATFORM_CONFIG_STM32F4 */
#endif /* COMMON_REGISTERS_H_ */
