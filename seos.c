#include "seos.h"
#include "sapi.h"

static void schedulerGoToSleep(void);


sTask_t schedulerTasks[SCHEDULER_MAX_TASKS];
char errorCode = 0;


void schedulerDispatchTasks( void ){ // Despachador (corre en el main)

   int32_t index;
   // Dispatches (runs) the next task (if one is ready)
   for (index = 0; index < SCHEDULER_MAX_TASKS; index++){

      if (schedulerTasks[index].runMe > 0){

         (*schedulerTasks[index].pTask)(); // Run the task
         schedulerTasks[index].runMe -= 1;  // Reset/reduce runMe flag

         // Periodic tasks will automatically run again
         // - if this is a 'one shot' task, remove it from the array
         if (schedulerTasks[index].period == 0){
            schedulerDeleteTask(index);
         }

      }
   }

   // Report system status
   //schedulerReportStatus();
   // The scheduler enters idle mode at this point32_t
   schedulerGoToSleep();
}

int32_t schedulerAddTask( void (* pFunction)(void),
                          const int32_t DELAY,
                          const int32_t PERIOD
                        ){

   int32_t index = 0;

   // First find a gap in the array (if there is one)
   while( (schedulerTasks[index].pTask != 0) && (index < SCHEDULER_MAX_TASKS) ){
      index++;
   }

   // Have we reached the end of the list?
   if( index == SCHEDULER_MAX_TASKS ){
      // Task list is full
      // Set the global error variable
      errorCode = 2; // ERROR_schedulerTOO_MANYTasks;
      // Also return an error code
      return SCHEDULER_MAX_TASKS;
   }

   // If we're here, there is a space in the task array
   schedulerTasks[index].pTask  = pFunction;
   schedulerTasks[index].delay  = DELAY;
   schedulerTasks[index].period = PERIOD;
   schedulerTasks[index].runMe  = 0;

   return index; // return position of task (to allow later deletion)
}

int8_t schedulerDeleteTask( int32_t taskIndex ){

   int8_t returnCode;

   if(schedulerTasks[taskIndex].pTask == 0){
      // No task at this location...
      // Set the global error variable
      errorCode = 2; // ERROR_SCH_CANNOT_DELETE_TASK;
      // ...also return an error code
      returnCode = -1; // RETURN_ERROR;
   }
   else{
      returnCode = 0; // RETURN_NORMAL;
   }
   schedulerTasks[taskIndex].pTask = 0x0000;
   schedulerTasks[taskIndex].delay = (int32_t)0;
   schedulerTasks[taskIndex].period = (int32_t)0;
   schedulerTasks[taskIndex].runMe = (int8_t)0;
   schedulerTasks[taskIndex].taskParam = 0;
   return returnCode; // return status
}

static void schedulerGoToSleep(){
}



void schedulerInit( void ){

   uint32_t i;
   for( i = 0; i < SCHEDULER_MAX_TASKS; i++ ){
      schedulerDeleteTask(i);
   }
   /* Reset the global error variable
      - schedulerDelete_Task() will generate an error code,
        (because the task array is empty) */
   errorCode = 0;
}

void schedulerUpdate(int sig)
{
   signal(sig, schedulerUpdate);

   int32_t index;
   //serialDebugPrintLnString( "schedulerUpdate." );

   // NOTE: calculations are in *TICKS* (not milliseconds)
   for( index = 0; index < SCHEDULER_MAX_TASKS; index++ ){
      // Check if there is a task at this location
      if( schedulerTasks[index].pTask ){
         if( --schedulerTasks[index].delay <= 0 ){   /* if (schedulerTasks[index].delay == 0) */
            // The task is due to run
            schedulerTasks[index].runMe += 1; // Inc. the 'runMe' flag
            if( schedulerTasks[index].period ){
               // Schedule regular tasks to run again
               schedulerTasks[index].delay = schedulerTasks[index].period;
            }
         }/*
         else{
            // Not yet ready to run: just decrement the delay
            schedulerTasks[Index].delay -= 1;
         }*/
      }
   }
}

void schedulerStart( tick_t tickRateMs ){
  signal(14, schedulerUpdate);
  printf("Iniciando Tick [mseg]: %d\n",tickRateMs );
  ualarm (tickRateMs*1000,tickRateMs*1000); //tickrate en useg
  //alarm(1); //cada 1seg
}
