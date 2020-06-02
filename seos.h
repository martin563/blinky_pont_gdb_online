#ifndef _SEOS_PONT_H_
#define _SEOS_PONT_H_


#include "sapi.h"

#include <stdio.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

/* The maximum number of tasks required at any one time during the execution
   of the program. MUST BE ADJUSTED FOR EACH NEW PROJECT */
#ifndef SCHEDULER_MAX_TASKS
   #define SCHEDULER_MAX_TASKS   (10)
#endif

/*==================[typedef]================================================*/

/* Store in DATA area, if possible, for rapid access.
   Total memory per task is 7 bytes. */
typedef struct{
   // Pointer to the task (must be a 'void (void)' function)
   void (* pTask)(void);
   // Delay (ticks) until the function will (next) be run
   // - see schedulerAddTask() for further details
   void* taskParam; // Parametro de tarea
   // Delay (ticks) until the function will (next) be run
   // - see schedulerAddTask() for further details
   int32_t delay;
   // Interval (ticks) between subsequent runs.
   // - see schedulerAddTask() for further details
   int32_t period;
   // Incremented (by scheduler) when task is due to execute
   int32_t runMe;
} sTask_t;

/*==================[external functions declaration]=========================*/

// FUNCION que contiene el despachador de tareas.
void schedulerDispatchTasks( void );

// FUNCION que añade una tarea al planificador.
int32_t schedulerAddTask( void (* pFunction)(void),
                          const int32_t DELAY,
                          const int32_t PERIOD
                        );

// FUNCION que remueve una tarea del planificador.
int8_t schedulerDeleteTask( int32_t taskIndex );

// FUNCION que reporta el estado del sistema.
void schedulerReportStatus( void );



// FUNCION que inicializa el planificador de tareas.
void schedulerInit( void );

// FUNCION que inicializa la interrupcion que ejecuta el planificador de
// tareas.
void schedulerStart( tick_t );

// FUNCION que contiene el planificador de tareas.
void schedulerUpdate( int );

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif


#endif /* #ifndef _COOPERATIVE_OS_ISR_H_ */
