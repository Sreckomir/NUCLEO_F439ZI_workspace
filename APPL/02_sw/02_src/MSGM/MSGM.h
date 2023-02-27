/// @file MSGM.h
/// @brief Header file used for sorting of UART messages
/// @author Srecko Veselinovic

#ifndef MSGM_H_
#define MSGM_H_

#include "UARTM.h"

/// Used to define number of words in a dictionary
#define MSGM_DICTIONARY_LENGTH (2u)
/// Used as a number of slots for temporary buffer used to find words
#define MSGM_MESSAGE_BUFFER_LENGTH (10u)
/// Used as a last slot of a temporary message buffer
#define MSGM_MESSAGE_BUFFER_SLOT (9u)

/// This enum is used for different types of messages sent to modules from UART
typedef enum {
  DEFAULT_MSG,  ///< Default message in a buffer if no valid word is stored
  LED_ON____,   ///< Message of a buffer that signalizes that LED is ON
  LED_OFF___    ///< Message of a buffer that signalizes that LED is OFF
} e_Message;

/// This enum is used for different IDs and the modules where messages should be sent
typedef enum
{
  DEFAULT_ID,  ///< Default ID in a buffer if there is no specified module for an upcoming message
  LEDM,        ///< ID of messages used in LED module
  SIM          ///< ID of messages used in SIM 800L module
} e_ReceiverID;

typedef enum {
  b_TRUE,  ///< Value used when the condition is true
  b_FALSE  ///< Value used when the condition is false
} boolean;

/// This structure is used as a buffer in a function that sorts messages
typedef struct {
  uint8_t * u_RawMessage;  ///< Field used to receive a raw message from UART manager
  e_ReceiverID e_ID;       ///< Field used to store a message unique identification number
  e_Message e_Msg;         ///< Field used to store a message into the buffer
  uint8_t u_Length;        ///< Field used to store a length of a message
} t_MessageElement;

/// @brief Function used to sort a message taken from UART serial communication
///
/// @pre Raw message must be stored into a temporary buffer
/// @post None
/// @param uint8_t *UARTM_a_array
///
/// @return None
///
/// @globals UARTM_a_array
///
/// @InOutCorelation Function recieves a raw message and sorts it based on module ID
/// @callsequence
///   @startuml "MSGM_v_Sort.png"
///     title "Sequence diagram for function MSGM_v_Sort"
///     -> MSGM: MSGM_v_Sort(...)
///     MSGM++
///     loop waits for a special character to reach a temporary buffer
///       rnote over MSGM: goes through slots of a temporary buffer
///     end
///     loop goes through a dictionary of valid messages
///       opt if length of a valid word is the same as the length of a raw message
///         loop reads a word character by character
///           opt checks if the raw message is different to the dictionary valid word
///             rnote over MSGM: block the word and break out of the loop
///           else else
///             rnote over MSGM: approve of the word
///           end
///         end
///       end
///       opt if the word is valid and ready to be stored
///         opt if the number of free buffer slots reached it's limit
///           rnote over MSGM: Move the buffer slot until the limit is reached, then reset
///         else else
///           rnote over MSGM: Move the buffer slot
///         end
///       end
///     end
///       MSGM -> UARTM: UARTM_v_ClearBuffer()
///       MSGM--
///       UARTM++
///       rnote over UARTM: Clears global buffer for raw message
///       UARTM -> MSGM
///       UARTM--
///       MSGM++
///       <- MSGM
///       MSGM--
///   @enduml
void MSGM_v_Sort(uint8_t *UARTM_a_array);

/// @brief Function used to clear the buffer after sorting the messages
///
/// @pre Buffer is not empty
/// @post None
/// @param uint8_t u_Index used to navigate the slot for deletion
///
/// @return None
///
/// @globals None
///
/// @InOutCorelation Function detects the buffer slot and replaces message with the default
/// @callsequence
///   @startuml "MSGM_v_ClearMessage.png"
///     title "Sequence diagram for function MSGM_v_ClearMessage"
///     -> MSGM: MSGM_v_ClearMessage()
///     MSGM++
///         rnote over MSGM: Deletes raw message and replaces message and id template with defaults
///     <- MSGM
///     MSGM--
///   @enduml
void MSGM_v_ClearMessage(uint8_t index);

/// @brief Function used to retrieve the messages based on their ID number
///
/// @pre Buffer is not empty
/// @post Returns the message that is identical to predefined ID number
/// @param e_ReceiverID e_ID used to send an ID number
///
/// @return e_MessageReturn with the valid message from the dictionary
///
/// @globals None
///
/// @InOutCorelation Function that takes and ID and sends back messages that correlate with ID
/// @callsequence
///   @startuml "MSGM_e_MessageRetrieve.png"
///     title "Sequence diagram for function MSGM_messageRetrieve"
///     -> MSGM: MSGM_e_MessageRetrieve()
///     MSGM++
///         loop goes through predefined dictionary
///           opt if condition ID of a stored message is identical to modules ID
///             rnote over MSGM: Returns the message and clears the buffer slot
///             MSGM -> MSGM: MSGM_v_ClearMessage(...)
///           end
///         end
///     <- MSGM: Returns e_Message with the valid word and ID
///        MSGM--
///   @enduml
e_Message MSGM_e_MessageRetrieve(e_ReceiverID e_ID);

#endif /* MSGM_H_ */
