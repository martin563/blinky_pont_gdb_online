// sapi.h  ----------------------------------------------------------------------

#ifndef __SAPI_H__
#define __SAPI_H__

#include <stdbool.h> // https://www.onlinegdb.com/#_editor_2967853411e 
#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
   extern "C" {
#endif


#ifdef bool
   typedef bool bool_t;
#else
   typedef uint8_t bool_t;
#endif

typedef uint64_t tick_t;


typedef enum{
    PIN0 =  0,
    PIN1 =  1,
    PIN2 =  2,
    PIN3 =  3,
    PIN4 =  4,
    PIN5 =  5,
    PIN6 =  6,
    PIN7 =  7,
    PIN8 =  8,
    PIN9 =  9,
   PIN10 = 10,
   PIN11 = 11,
   PIN12 = 12,
   PIN13 = 13,
   PIN14 = 14,
   PIN15 = 15,
} GpioMap_t;

bool_t gpioRead( GpioMap_t pin );
bool_t gpioWrite( GpioMap_t pin, bool_t value );
bool_t gpioToggle( GpioMap_t pin );


typedef enum{
    UART0,
    UART_USB,
    UART_DEBUG,
} UartMap_t;


void uartInit( UartMap_t uart, uint32_t baudRate );
bool_t uartReadByte( UartMap_t uart, uint8_t* data );
void uartWriteByte( UartMap_t uart, uint8_t data );



#ifdef __cplusplus
   }
#endif

#endif // __SAPI_H__