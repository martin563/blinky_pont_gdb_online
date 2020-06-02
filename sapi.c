// sapi.c  ----------------------------------------------------------------------

#include "sapi.h"

bool pins[16] = {false};

bool_t gpioRead( GpioMap_t pin )
{
   printf("PIN%d readed value is %d\n", pin, pins[pin]);
   fflush(stdout);
   return pins[pin];
}

bool_t gpioWrite( GpioMap_t pin, bool_t value )
{
   pins[pin] = value;
   printf("PIN%d set to %d\n", pin, pins[pin]);
   fflush(stdout);
   return pins[pin];
}

bool_t gpioToggle( GpioMap_t pin )
{
   pins[pin] = !pins[pin];
   printf("PIN%d is toggle to %d\n", pin, pins[pin]);
   fflush(stdout);
   return pins[pin];
}



#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>

struct termios orig_termios;


static int kbhit()
{
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv);
}

static void disableRawMode()
{
   tcsetattr (STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

static void enableRawMode()
{
   tcgetattr (STDIN_FILENO, &orig_termios);
   atexit (disableRawMode);

   struct termios raw = orig_termios;
   raw.c_lflag &= ~(ECHO | ICANON);

   tcsetattr (STDIN_FILENO, TCSAFLUSH, &raw);
}

void uartInit( UartMap_t uart, uint32_t baudRate )
{
   enableRawMode();
}



bool_t uartReadByte( UartMap_t uart, uint8_t* data )
{
   char c;
   if( read (STDIN_FILENO, &c, 1) == 1 ){
      *data = c;
      return true;
   }
   return false;
}

void uartWriteByte( UartMap_t uart, uint8_t data )
{
   if( data == 10 ) {
      printf ( "\n" );
   } else if( iscntrl(data) ) {
      printf ( "%d\n", data );
   } else {
      printf ( "%c", data );
   }
   fflush(stdout);
}
