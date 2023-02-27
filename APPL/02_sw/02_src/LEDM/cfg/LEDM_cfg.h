/// @file LEDM_cfg.h
/// @brief Contains configuration data used for manipulating with LED
/// @author Igor Krstic

#ifndef LEDM_CFG_H_
#define LEDM_CFG_H_

#include "stm32f439xx.h"
#include "stm32f4xx_hal.h"
#include "UARTM.h"

/// Time delay after toggling pin output in milliseconds
#define LEDM_FIRST_TIME_DELAY_MS 1000
/// Time delay after toggling pin output in milliseconds
#define LEDM_SECOND_TIME_DELAY_MS 750
/// Register address used for toggling pin output
#define LEDM_REGISTER_GROUP GPIOB
/// Pin position in register
#define LEDM_REGISTER_PIN GPIO_PIN_14
/// Register address for output LED
#define LEDM_REGISTER_GROUP_ODR (1u << 14u)

//#define REG32(x) (*(volatile uint32_t*)(x))

//#define LEDM_GPIOA_ODR (0x40020014)

#endif /* LEDM_CFG_H_ */
