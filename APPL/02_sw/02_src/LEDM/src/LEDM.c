/// @file LEDM.c
/// @brief Main file used for LED manipulation
/// @author Igor Krstic

#include "LEDM_cfg.h"
#include "LEDM.h"
#include "UARTM.h"
#include "MSGM.h"


void LEDM_v_Main()
{
  // Toggle pin value
  HAL_GPIO_TogglePin(LEDM_REGISTER_GROUP, LEDM_REGISTER_PIN);
  // Trigger delay for 1st time period
  HAL_Delay(LEDM_FIRST_TIME_DELAY_MS);
  // Toggle pin value
  HAL_GPIO_TogglePin(LEDM_REGISTER_GROUP, LEDM_REGISTER_PIN);
  // Trigger delay for 2nd time period
  HAL_Delay(LEDM_SECOND_TIME_DELAY_MS);
}

void LEDM_v_GetMessage()
{

  e_Message e_Msg = MSGM_e_MessageRetrieve(LEDM);
  switch (e_Msg)
  {
  case LED_ON____:
    REG32(GPIOB_ODR) |= ODR_LED_ON;
    break;
  case LED_OFF___:
    REG32(GPIOB_ODR) &= ~ODR_LED_ON;
    break;
  default:
    break;
  }
}
