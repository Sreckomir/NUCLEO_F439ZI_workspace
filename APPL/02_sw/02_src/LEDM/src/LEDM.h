/// @file LEDM.h
/// @brief Header file used for LED manipulation
/// @author Igor Krstic

#ifndef LEDM_H_
#define LEDM_H_

/// @brief Main function used for LED manipulation
///
/// @pre None
/// @post LED is toggled after delay
/// @param None
///
/// @return None
///
/// @globals None
///
/// @InOutCorelation Function toggles output pin which is attached to the LED.
///                  There is a time delay between each toggle.
/// @callsequence
///   @startuml "LEDM_v_Main.png"
///     title "Sequence diagram for function LEDM_v_Main"
///     -> LEDM: LEDM_v_Main()
///     LEDM++
///     LEDM -> HAL: HAL_GPIO_TogglePin(...)
///     LEDM--
///     HAL++
///     rnote over HAL: Toggle LED pin.
///     HAL -> LEDM
///     HAL--
///     LEDM++
///     LEDM -> HAL: HAL_Delay(LEDM_FIRST_TIME_DELAY_MS)
///     LEDM--
///     HAL++
///     rnote over HAL: Device stays in delay.
///     HAL -> LEDM
///     HAL--
///     LEDM++
///     LEDM -> HAL: HAL_GPIO_TogglePin(...)
///     LEDM--
///     HAL++
///     rnote over HAL: Toggle LED pin.
///     HAL -> LEDM
///     HAL--
///     LEDM++
///     LEDM -> HAL: HAL_Delay(LEDM_SECOND_TIME_DELAY_MS)
///     LEDM--
///     HAL++
///     rnote over HAL: Device stays in delay.
///     HAL -> LEDM
///     HAL--
///     LEDM++
///     <- LEDM
///     LEDM--
///   @enduml
void LEDM_v_Main();

/// @brief Function used to read the message and manipulate the LEDs
///
/// @pre Message with adequate ID is received
/// @post Led is toggled
/// @param None
///
/// @return None
///
/// @globals None
///
/// @InOutCorelation Function receives a message based on an ID and controls the LED module
/// @callsequence
///   @startuml "LEDM_v_GetMessage.png"
///     title "Sequence diagram for function LEDM_v_GetMessage"
///       -> LEDM: Calls a function\n to get a message and manipulate the module
///       LEDM++
///         LEDM -> MSGM: MSGM_e_MessageRetreive(...)
///         LEDM--
///         MSGM++
///         rnote over MSGM: Retrieves a message \nbased on an ID parameter
///         MSGM -> LEDM: Returns e_MessageReturn type with a valid word
///         MSGM--
///         LEDM++
///           alt LED_ON case
///             rnote over LEDM: Turns on LED using UART2
///           else LED_OFF case
///             rnote over LEDM: Turns off LED using UART2
///           else default case
///             rnote over LEDM: Breaks out of the switch case
///           end
///             <- LEDM
///             LEDM--
///   @enduml
void LEDM_v_GetMessage();

#endif /* LEDM_H_ */
