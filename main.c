#define SCHEDULER_MAX_TASKS   (3)

#include "sapi.h"
#include "seos.h"

void tarea1( void );
void tarea2( void );
void tarea3( void );

int main( void ){
   schedulerInit();

   schedulerAddTask( tarea1, // funcion de tarea a agregar
                     0,      // offset de ejecucion en ticks
                     100     // periodicidad de ejecucion en ticks
                   );
				 
   schedulerAddTask( tarea2, 1, 500 );
   schedulerAddTask( tarea3, 2, 1000 );

   schedulerStart(10);

   while( true )
   {
      schedulerDispatchTasks();
   }
   return 0;
}


void tarea1( void ){
   gpioToggle( PIN1 );
}

void tarea2( void ){
   gpioToggle( PIN2 );
}

void tarea3( void ){
   gpioToggle( PIN3 );
}



///-------------------------------------------------

/*

#include "sapi.h"

int main(void){
   // Inicicializaciones
   uartInit( UART_USB, 115200 );

   uint8_t data = 0;
   uint32_t cont=0;
   
   printf("presione tecla:\n");

   while(1){
       
      
     if ( uartReadByte(UART_USB, &data) ) {
         uartWriteByte(UART_USB, data-32);
      }
    
    sleep(1);
    printf("cont:%d\n",cont++);
      
   }
   return 0; 
}
*/