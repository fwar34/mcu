#include "hal_types.h"
#include "OSAL.h"
#include "OSAL_Tasks.h"

uint16 Application_ProcessEvent( uint8 task_id, uint16 events )
{
    return 0;
}

//任务表
const pTaskEventHandlerFn tasksArr[] =
{
      Application_ProcessEvent
};

const uint8 tasksCnt = sizeof( tasksArr ) / sizeof( tasksArr[0] );
uint16 *tasksEvents;


void osalInitTasks( void )
{
}

/*********************************************************************
 *********************************************************************/

