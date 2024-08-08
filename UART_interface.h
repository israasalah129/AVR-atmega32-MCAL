#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

// UART modes options
#define UART_MODE_ASYNCHRONOUS	0
#define UART_MODE_SYNCHRONOUS	1

// UART parity options
#define UART_PARITY_NO			0
#define UART_PARITY_EVEN		2
#define UART_PARITY_ODD			3

// UART stop bits options
#define UART_STOP_BITS_1		0
#define UART_STOP_BITS_2		1

// UART Enable options
#define UART_DISABLE			0
#define UART_ENABLE				1

// UART data bits options
typedef enum{
	UART_DATA_BITS_5,
	UART_DATA_BITS_6,
	UART_DATA_BITS_7,
	UART_DATA_BITS_8,
	UART_DATA_BITS_9 = 7
}UART_DataBits_t;



/* Public functions */

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
void UART_voidInit(void);

/*
 * UART_voidSendByte: Sends 1 byte
 */
void UART_voidSendByte(u8 Copy_u8Data);


/*
 * UART_voidReceiveByte: Receive 1 byte
 */
void UART_voidReceiveByte(u8 * Ptr_u8Buffer);

/*
 * UART_voidSendString: Sends a string
 */
void UART_voidSendString(u8 * Ptr_u8Data);

/*
 * UART_voidReceiveString: Receives a string
 */
void UART_voidReceiveString(u8 * Ptr_u8Buffer);


#endif /* UART_INTERFACE_H_ */
