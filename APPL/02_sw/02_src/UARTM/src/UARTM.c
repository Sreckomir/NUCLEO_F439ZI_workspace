/// @file UARTM.c
/// @brief Main file used to send messages through UART serial communication
/// @author Srecko Veselinovic

#include "UARTM.h"
#include "MSGM.h"


static uint8_t UARTM_a_array[TEMP_BUFFER] = {0u};
uint8_t        UARTM_u_index              = 0u;

void UARTM_v_Uart3Config()
{
  // 1. Enable the UART CLOCK and GPIO CLOCK
  REG32(RCC_APB1ENR) |= APB1ENR_UART3_CLOCK;  // Enable UART2 CLOCK
  REG32(RCC_AHB1ENR) |= AHB1ENR_GPIOD_CLOCK;  // Enable GPIOA CLOCK

  // 2. Configure the UART PINs for Alternate Functions
  REG32(GPIOD_MODER) |= MODER_PIN_PD8; // Bits (5:4) = 1:0 --> Alternate Function for Pin PA2
  REG32(GPIOD_MODER) |= MODER_PIN_PD9; // Bits (7:6) = 1:0 --> Alternate Function for Pin PA3

  REG32(GPIOD_OSPEEDER) |= OSPEEDR_PIN_PD8 | OSPEEDR_PIN_PD9;// Bits (5:4) = 1:1 and Bits (7:6) = 1:1 --> High Speed for PIN PA2 and PA3

  REG32(GPIOD_AFR1) |= AFR_PIN_PD8; // Bytes 11:10:9:8) = 0:1:1:1 --> AF7 Alternate Function for USART2 at Pin PA2
  REG32(GPIOD_AFR1) |= AFR_PIN_PD9; // Bytes (15:14:13:12) = 0:1:1:1 --> AF7 Alternate function for USART2 at Pin PA3

  // 3. Enable the USART by writing the UE bit in USART_CR1 register to 1.
  REG32(USART3_CR1) = 0x00u; // clear all
  REG32(USART3_CR1) |= CR1_USART_ENABLE; // UE = 1... Enable USART

  // 4. Program the M bit in USART_CR1 to define the word length.
  REG32(USART3_CR1) &= ~(CR1_WORD_LENGTH); // M = 0; 8 bit word length

  // 5. Select the desired baud rate using the USAR_BRR register.
  REG32(USART3_BRR) = (BRR_BAUD_RATE) | (BRR_PCLK1); // Baud rate of 115200, PCLK1 at 45Mhz

  // 6. Enable the Transmitter/Receiver by Settin1g the TE and RE bits in USART_CR1 Register
  REG32(USART3_CR1) |= CR1_RECEIVER_ENABLE; // RE=1... Enable the Receiver
  REG32(USART3_CR1) |= CR1_TRANSMITTER_ENABLE; // TE=1... Enable the Receiver

  // 7. Enable Interrupt routine for receiving
  REG32(USART3_CR1) |= CR1_RXNEIE_ENABLE; // Enable RX interrupt
  NVIC_EnableIRQ(USART3_IRQn); // Enable Global interrupt for USART2
}

/// @brief Function used to transmit a character using UART protocol
///
/// @pre UART must be configured
/// @post Sending character through serial monitor
/// @param uint8_t u_character
///
/// @return None
///
/// @globals None
///
/// @InOutCorelation Function sends character through serial monitor.
/// @callsequence
///@startuml "UARTM_v_SendChar.png"
///  title "Sequence diagram for function UARTM_v_SendChar"
///  UARTM++
///    -> UARTM: UARTM_v_SendChar()
///      loop // Wait for TC register to SET.. This indicates that the data has been transmitted //
///      end
///    <- UARTM
///  UARTM--
///@enduml
static void UARTM_v_SendChar(uint8_t u_character)
{
  while (!(REG32(USART3_SR) & (USART_SR_TC)))
  {
    // Wait for TC to SET.. This indicates that the data has been transmitted
  }

  REG32(USART3_DR) = u_character;  // Load the data into DR register
}

void UARTM_v_SendString (uint8_t* u_string)
{
  while(*u_string != 0)
  {
    UARTM_v_SendChar(*u_string);
    u_string++;
  }
}

uint8_t UARTM_u_GetChar()
{
  uint8_t temp;

  while(!(REG32(USART3_SR) & USART_SR_RXNE))
  {
  }

  temp = REG32(USART3_DR);
  return temp;
}

void USART3_IRQHandler(void)
{
  boolean b_TransmitionComplete = b_FALSE;

  // Check if interrupt happened because of RXNEIE register
  if (REG32(USART3_SR) & USART_SR_RXNE) // If RX register is not empty
  {
    uint8_t temp = REG32(USART3_DR); // Fetch the data received

    while (!(REG32(USART3_SR) & USART_SR_TXE))
    {
    }

    UARTM_a_array[UARTM_u_index] = temp;

    if (temp == '*')
    {
      b_TransmitionComplete = b_TRUE;
    }
    else
    {
      UARTM_u_index++;
      if (UARTM_u_index == TEMP_BUFFER)
      {
        UARTM_v_ClearBuffer();
      }
    }

    if (b_TransmitionComplete == b_TRUE)
    {
      MSGM_v_Sort(UARTM_a_array);
    }
  }
}

void UARTM_v_ClearBuffer()
{
  uint8_t u_Cnt;

  for (u_Cnt = 0u; u_Cnt < UARTM_u_index; u_Cnt++)
  {
    UARTM_a_array[u_Cnt] = 0u;
  }
  UARTM_u_index = 0u;
}
