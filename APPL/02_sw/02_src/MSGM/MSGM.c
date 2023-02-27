/// @file MSGM.c
/// @brief Main file used for sorting of UART messages
/// @author Srecko Veselinovic

#include "MSGM.h"
#include "UARTM.h"
#include "UARTM_cfg.h"

t_MessageElement MSGM_t_MessageBuffer[MSGM_MESSAGE_BUFFER_LENGTH] = {0u};

t_MessageElement MSGM_t_Dictionary[MSGM_DICTIONARY_LENGTH] =
{
  {
      (uint8_t*)"LED_ON____",
      LEDM,
      LED_ON____,
      6u
  },
  {
      (uint8_t*)"LED_OFF___",
      LEDM,
      LED_OFF___,
      7u
  }
};

void MSGM_v_Sort(uint8_t *UARTM_a_array)
{
  boolean b_WordFound        = b_FALSE;
  uint8_t u_Index            = 0u;
  uint8_t u_Length           = 0u;
  uint8_t u_Cnt              = 0u;
  static uint8_t Buffer_slot = 0u;

  while (UARTM_a_array[u_Index] != '*')
  {
    u_Index++;
  }

  u_Length = u_Index;

  for (u_Cnt = 0u; u_Cnt < MSGM_DICTIONARY_LENGTH; u_Cnt++)
  {
    if (MSGM_t_Dictionary[u_Cnt].u_Length == u_Length)
    {
      for (u_Index = 0u; u_Index < u_Length; u_Index++)
      {
        if (UARTM_a_array[u_Index] != MSGM_t_Dictionary[u_Cnt].u_RawMessage[u_Index])
        {
          b_WordFound = b_FALSE;
          break;
        }
        else
        {
          b_WordFound = b_TRUE;
        }
      }
    }
    if (b_WordFound == b_TRUE)
    {
      MSGM_t_MessageBuffer[Buffer_slot].e_ID = MSGM_t_Dictionary[u_Cnt].e_ID;
      MSGM_t_MessageBuffer[Buffer_slot].e_Msg = MSGM_t_Dictionary[u_Cnt].e_Msg;

      if (Buffer_slot == MSGM_MESSAGE_BUFFER_SLOT)
      {
        Buffer_slot++;
        Buffer_slot = 0u;
      }
      else
      {
        Buffer_slot++;
      }
      b_WordFound = b_FALSE;
    }
  }
  UARTM_v_ClearBuffer();
}

void MSGM_v_ClearMessage(uint8_t u_Index)
{
  MSGM_t_MessageBuffer[u_Index].u_RawMessage = (uint8_t *)"";
  MSGM_t_MessageBuffer[u_Index].e_Msg        = DEFAULT_MSG;
  MSGM_t_MessageBuffer[u_Index].e_ID         = DEFAULT_ID;
  MSGM_t_MessageBuffer[u_Index].u_Length     = 0u;
}

e_Message MSGM_e_MessageRetrieve(e_ReceiverID e_ID)
{
  uint8_t u_Index = 0u;
  e_Message e_MessageReturn;

  for(u_Index = 0; u_Index < MSGM_MESSAGE_BUFFER_LENGTH; u_Index++)
  {
    if(MSGM_t_MessageBuffer[u_Index].e_ID == e_ID)
    {
      e_MessageReturn = MSGM_t_MessageBuffer[u_Index].e_Msg;
      MSGM_v_ClearMessage(u_Index);
      break;
    }
  }
  return e_MessageReturn;
}
