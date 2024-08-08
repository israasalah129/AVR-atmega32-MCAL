
#include "../../../LIB/STD_TYPES.h"
#include "../../../LIB/BIT_MATH.h"

#define F_CPU  8000000UL
#include <util/delay.h>


#include "../Header/UART_Private.h"
#include "../Header/UART_Config.h"
#include "../Header/UART_Interface.h"


/*
 * UART_voidInit: Initializes the UART and sets:
 * 												Data bits number,
 * 												Stop bits number,
 * 												Parity mode,
 * 												Enables/Disables the UART interrupts,
 * 												Enables/Disables Transmission,
 * 												Enables/Disables Receiving,
 * 												Sets the UART mode,
 * 												Sets the Baud rate
 */
void UART_voidInit(void){

	// Setting Data bits number
	UCSRB = UART_DATA_BITS & 0b100;
	UCSRC = (1 << 7)|((UART_DATA_BITS & 0b011) << 1);

	// Setting Stop bits number
	UCSRC |= (UART_STOP_BITS << 3);

	// Setting Parity mode
	UCSRC |= (UART_PARITY_MODE << 4);

	// Enabling/Disabling the UART interrupts
	UCSRB |= (UART_INTERRUPT_STATE_RXC << 7);
	UCSRB |= (UART_INTERRUPT_STATE_TXC << 6);
	UCSRB |= (UART_INTERRUPT_STATE_UDRE<< 5);

	// Enables/Disables Transmission
	UCSRB |= (UART_TRANSMIT_ENABLE << 3);


	// Enables/Disables Receiving
	UCSRB |= (UART_RECEIVE_ENABLE << 4);

	// Setting the UART mode
	UCSRC |= (UART_MODE << 6);

	// Setting the Baud rate
	u16 Local_u16UBRR = (F_CPU/(16*UART_BAUD_RATE))-1;
	UBRRH = (~(1<<7)) & (Local_u16UBRR >> 8);
	UBRRL = (u8)Local_u16UBRR;
}

/*
 * UART_voidSendByte: Sends 1 byte
 */
void UART_voidSendByte(u8 Copy_u8Data){
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<5)) );
	/* Put data into buffer, sends the data */
	UDR = Copy_u8Data;
}


/*
 * UART_voidReceiveByte: Receive 1 byte
 */
void UART_voidReceiveByte(u8 * Ptr_u8Buffer){
	/* Wait for data to be received */
	while ( !(UCSRA & (1<<7)) );
	/* Get and return received data from buffer */
	*Ptr_u8Buffer = UDR;

}

/*
 * UART_voidSendString: Sends a string
 */
void UART_voidSendString(u8 * Ptr_u8Data){


}

/*
 * UART_voidReceiveString: Receives a string
 */
void UART_voidReceiveString(u8 * Ptr_u8Buffer){


}
