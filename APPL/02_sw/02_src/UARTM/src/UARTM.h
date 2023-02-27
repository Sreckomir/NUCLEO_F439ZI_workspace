/// @file UARTM.h
/// @brief Header file used for UART serial communication
/// @author Srecko Veselinovic

#ifndef UARTM_H_
#define UARTM_H_

#include "UARTM_cfg.h"

/// @brief Function used to transmit a string using UART protocol
///
/// @pre UART must be configured
/// @post Sending a string of characters through serial monitor
/// @param uint8_t* u_string
///
/// @return None
///
/// @globals None
///
/// @InOutCorelation Function sends string of characters through serial monitor.
/// @callsequence
///   @startuml "UARTM_v_SendString.png"
///     title "Sequence diagram for function UARTM_v_SendString"
///     -> UARTM: UARTM_v_SendString()
///     UARTM++
///     loop //loop that loads input characters into a buffer//
///       rnote over UARTM: fetches character by character while moving through buffer
///           UARTM -> UARTM: UARTM_v_GetChar()
///              rnote over UARTM: Function that gets character and loads it into a buffer
///           <- UARTM:// Returns a 32-bit value that represents the character from UART data buffer//
///           UARTM--
///     end
///   @enduml
void UARTM_v_SendString (uint8_t* u_string);

/// @brief Function used to receive a character using UART protocol
///
/// @pre UART must be configured
/// @post Funcion receives a character through UART communication
/// @param None
///
/// @return uint8_t character
///
/// @globals None
///
/// @InOutCorelation Function receives a character through UART communication
/// @callsequence
///   @startuml "UARTM_u_GetChar.png"
///     title "Sequence diagram for function UARTM_u_GetChar"
///     -> UARTM: UARTM_u_GetChar()
///     UARTM++
///     loop //stay in the loop while waiting for buffer to fetch a character//
///       rnote over UARTM: body of the loop is empty
///     end
///     <- UARTM: returns u32 value of a data output register
///     UARTM--
///   @enduml
uint8_t UARTM_u_GetChar ();

/// @brief Main function used for LED manipulation
///
/// @pre None
/// @post UART2 port is set to UART serial communication
/// @param None
///
/// @return None
///
/// @globals None
///
/// @InOutCorelation Function sets up registers for UART communication using ISR
/// @callsequence
///   @startuml "UARTM_v_Uart3Config.png"
///     title "Sequence diagram for function UARTM_v_Uart2Config"
///     -> UARTM: UARTM_v_Uart3Config()
///     UARTM++
///     UARTM -> core_cm4: NVIC_EnableIRQ(....)
///     UARTM--
///     core_cm4++
///     rnote over core_cm4: Enables global interrupt for USART 2 serial communication
///     core_cm4 -> UARTM
///     core_cm4--
///     UARTM++
///     <- UARTM
///     UARTM--
///   @enduml
void UARTM_v_Uart3Config();

/// @brief Function used to clear a temporary buffer after performing an IRQ
///
/// @pre Interrupt Service Routine must be finished
/// @post Function clear a temporary buffer used for data
/// @param None
///
/// @return None
///
/// @globals None
///
/// @InOutCorelation Function clears temporary buffer used for IRQ
/// @callsequence
///   @startuml "UARTM_v_ClearBuffer.png"
///     title "Sequence diagram for function UARTM_v_ClearBuffer"
///     -> UARTM: UARTM_v_ClearBuffer()
///     UARTM++
///     loop //Used to set all buffer values to 0//
///       rnote over UARTM: Set the value of every position in the temporary buffer to 0
///     end
///     <- UARTM:
///     UARTM--
///   @enduml
void UARTM_v_ClearBuffer();


#endif /* UARTM_H_ */
