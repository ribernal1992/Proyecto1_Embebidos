/*******************************************************************************/
/**
\file       SchM.c
\brief      Multi-thread Task scheduler.
   \~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   \version       1.1
   \author        Francisco Martinez
   \description   Scheduler updates
   \date          20/Aug/2018
   \~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   \version       1.0
   \author        Abraham Tezmol
   \description   Initial version
   \date          09/Sep/2008
*/

/** Standard Types */
#include "Std_Types.h"
/** Scheduler function prototypes definitions */
#include "SchM.h"
/** Scheduler Type definitions */
#include "SchM_Types.h"
/** Tasks definition */
#include "SchM_Tasks.h"
#include "tc.h"

/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/
/* Global Task Scheduler Status definitions */

#define    SCHM_TASK_SCHEDULER_BASE_FREQ		 2000u
#define    SCHM_TASK_SCH_MAX_NUMBER_TIME_TASKS   0x06u

#define    SCHM_TASK_SCHEDULER_INIT              0x00u
#define    SCHM_TASK_SCHEDULER_RUNNING           0x01u
#define    SCHM_TASK_SCHEDULER_OVERLOAD_1MS      0x02u
#define    SCHM_TASK_SCHEDULER_OVERLOAD_2MS_A    0x03u
#define    SCHM_TASK_SCHEDULER_OVERLOAD_2MS_B    0x04u
#define    SCHM_TASK_SCHEDULER_HALTED            0xAAu
#define    MaximumTasks                          7

/*****************************************************************************************************
* Definition of  VARIABLEs - 
*****************************************************************************************************/

/* Global pointer used to invoke callback function upon Timer event*/
SchM_CallbackType pfctnSysTick = (SchM_CallbackType)NULL;

unsigned int Dummy ;
uint8_t SchM_Status;
uint8_t SchM_Counter;
uint32_t StartTimer;
uint32_t StopTimer;
uint32_t TotalTimer;

SchMTaskCtrlType TaskCtrl[MaximumTasks];

SchMTasksIdType SchM_Task_ID_Activated;
SchMTasksIdType SchM_Task_ID_Running;
SchMTasksIdType SchM_Task_ID_Backup;

SchMTasksIdType SchedulerTaskID;

uint8_t SchM_10ms_Counter;
uint8_t SchM_50ms_Counter;
uint8_t SchM_100ms_Counter;

/*****************************************************************************************************
* Code of module wide private FUNCTIONS
*****************************************************************************************************/
/*******************************************************************************/
/**
* \brief    Periodic Interrupt Timer Service routine.                            \n
            This interrupt is the core of the task scheduler.                   \n
            It is executed every 500us                                          \n
            It defines 3 basic threads from which other 3 threads are derived:  \n
            a) 1ms thread (basic) ->  100ms thread (derived)                    \n
            b) 2ms A thread (basic)-> 50ms thread (derived)                     \n
            c) 2ms B thread (basic)-> 10ms thread (derived)                     \n
            It partitions core execution time into time slices (500us each one).\n 
            This arrangement assures core will have equal task loading across time.\n   
            For more information on how time slice is assigned to each thread,  \n
            refer to file "S12X Task Scheduler Layout.xls"
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo
*/

void SchM_Callback(void)
{
    /*-- Update scheduler control variable --*/
    SchM_Counter++;

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*  1ms execution thread - used to derive two execution threads:                */
    /*  a) 1ms thread (highest priority tasks)                                      */
    /*  b) 100ms thread (lowest priority tasks)                                     */
    /*  As any other thread on this scheduling scheme,                              */
    /*  all tasks must be executed in <= 500us                                      */
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    if( ( SchM_Counter & 0x01u ) == 0x01u )
    {
        SchM_100ms_Counter++;
         SchM_ActiveTask(TASKS_1_MS);
        /*-- Allow 100 ms periodic tasks to be executed --*/
        if( SchM_100ms_Counter >= 100u )
        {
            /* Indicate that Task is Ready to be executed */ 

             SchM_ActiveTask(TASKS_100_MS);
            //SchM_Task_ID_Activated = TASKS_100_MS;
            SchM_100ms_Counter       = 0u;
        }
        /*-- Allow 1 ms periodic tasks to be executed --*/
        else
        {
            
           // SchM_ActiveTask(TASKS_1_MS);
            //SchM_Task_ID_Activated = TASKS_1_MS;
        }
    }
    else
    {
        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        /*  2ms execution thread - used to derive two execution threads:                */
        /*  a) 2ms group A thread (high priority tasks)                                 */
        /*  b) 50ms thread (second lowest priority tasks)                               */
        /*  As any other thread on this scheduling scheme,                              */
        /*  all tasks must be executed in <= 500us                                      */
        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        if( ( SchM_Counter & 0x02u ) == 0x02u )
        {
            SchM_50ms_Counter++;
            /*-- Allow 50 ms periodic tasks to be executed --*/
            if( SchM_50ms_Counter >= 25u )
            {
                SchM_ActiveTask(TASKS_50_MS);
                SchM_50ms_Counter        = 0u;
            }
            /*-- Allow 2 ms group A periodic tasks to be executed --*/
            else
            {
                SchM_ActiveTask(TASKS_2_MS_A);
            }
        }
        else
        {
            /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            /*  2ms execution thread - used to derive two execution threads:                */
            /*  a) 2ms group B thread (high priority tasks)                                 */
            /*  b) 10ms thread (medium priority tasks)                                      */
            /*  As any other thread on this scheduling scheme,                              */
            /*  all tasks must be executed in <= 500us                                      */
            /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            if( ( SchM_Counter & 0x03u ) == 0x00u )
            {
                SchM_10ms_Counter++;
                /*-- Allow 10 ms periodic tasks to be executed --*/
                if( SchM_10ms_Counter >= 5u )
                {
                    SchM_ActiveTask(TASKS_10_MS);
                    SchM_10ms_Counter        = 0u;
                }
                /*-- Allow 2 ms group B periodic tasks to be executed --*/
                else
                {
                   SchM_ActiveTask(TASKS_2_MS_B);
                }
            }
        }
    }
}

/****************************************************************************************************/
/**
* \brief    SysTick - Initialization
* \author   Abraham Tezmol
* \param    int32_t base_freq	--> Requested SysTick interrupt frequency
* \param    SchM_CallbackType sysTick_handler	--> Callback function to handle SysTick ISR.
* \return   uint8_t --> 0 - Successful configuration of SysTick IRQ and SysTick Timer, 1 - Invalid configuration
* \todo
*/

uint8_t SysTick_init(uint32_t base_freq, SchM_CallbackType sysTick_handler)
{
	pfctnSysTick = sysTick_handler;
	return SysTick_Config(BOARD_MCK / base_freq);
}

/*******************************************************************************/
/**
* \brief    Scheduler Start - Once time base is armed, start execution of   \n
            Multi-thread Round Robin scheduling scheme.                     \n
            This function requires prior execution of "vfnScheduler_Init"
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo     
*/

void SchM_Start(void)
{
	if (SysTick_init(SCHM_TASK_SCHEDULER_BASE_FREQ, SchM_Callback)) 
	{
		while (1);
	}
	SchM_Status = SCHM_TASK_SCHEDULER_RUNNING;
	/* Once all the basic services have been started, go to infinite loop to serviced activated tasks */
	while(1)
  {
		SchM_Scheduler();
	}
}

/*******************************************************************************/
/**
* \brief    Multi-thread round robin task Scheduler  (non-preemtive)        \n
            It calls the different tasks based on the status of             \n   
            List of tasks shall be defined @ "tasks.h" file
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo     
*/

void SchM_Scheduler(void)
{
    uint8_t ISR_Activated = 0;
    //SchM_CallbackType currentTask;
    if(TaskCtrl[TASKS_ISR].TaskState == READY)
    {
        ISR_Activated = 1;
    }
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /*  1ms execution thread - used to derive two execution threads:                */
    /*  a) 1ms thread (high priority tasks)                                         */
    /*  b) 100ms thread (lowest priority tasks)                                     */
    /*  As any other thread on this scheduler, all tasks must be executed in <=500us*/
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
     if( ( TaskCtrl[TASKS_1_MS].TaskState == READY )
         || ( TaskCtrl[TASKS_100_MS].TaskState == READY) )
    {
        /* Make a copy of scheduled task ID */
        SchM_Task_ID_Backup = TaskCtrl[TASKS_1_MS].TaskInfo->TaskId; 
        if(ISR_Activated)
        {
            SchedulerTaskID = TASKS_1_MS;
            SchM_SchedulePoint();
        }
        else
        {
            (*(TaskCtrl[TASKS_1_MS].TaskInfo->TaskFcnPtr))();
            
        }
		//SchM_Task_1ms();
        if( TaskCtrl[TASKS_100_MS].TaskState == READY)
        {
            SchM_Task_ID_Backup = TaskCtrl[TASKS_100_MS].TaskInfo->TaskId; 
          if(ISR_Activated)
            {
                SchedulerTaskID =  TASKS_100_MS;
                SchM_SchedulePoint();
            }
            else
            {
                (*(TaskCtrl[TASKS_100_MS].TaskInfo->TaskFcnPtr))();
            }
        }
        /* Verify that thread execution took less than 500 us */
        if( SchM_Task_ID_Backup == TASKS_1_MS || SchM_Task_ID_Backup == TASKS_100_MS)
        {
             /* In case execution of all thread took less than 500us */
           TaskCtrl[TASKS_1_MS].TaskState = SUSPENDED;
           TaskCtrl[TASKS_100_MS].TaskState = SUSPENDED;
           
        }
        else
        {
           TaskCtrl[TASKS_1_MS].TaskOverload = 1;
           // SchM_Status = SCHM_TASK_SCHEDULER_OVERLOAD_1MS;
        }
    }
    else
    {
        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        /*  2ms execution thread - used to derive two execution threads:                */
        /*  a) 2ms group A thread (high priority tasks)                                 */
        /*  b) 50ms thread (second lowest priority tasks)                               */
        /*  As any other thread on this scheduler, all tasks must be executed in <=500us*/
        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        if( ( TaskCtrl[TASKS_2_MS_A].TaskState == READY )
                || ( TaskCtrl[TASKS_50_MS].TaskState == READY))
        {
            /* Make a copy of scheduled task ID */
             SchM_Task_ID_Backup = TaskCtrl[TASKS_2_MS_A].TaskInfo->TaskId; 
             if(ISR_Activated)
            {
                SchedulerTaskID =  TASKS_2_MS_A;
                SchM_SchedulePoint();
            }
            else
            {
                 (*(TaskCtrl[TASKS_2_MS_A].TaskInfo->TaskFcnPtr))();
            }
            if( TaskCtrl[TASKS_50_MS].TaskState == READY)
            {
                 if(ISR_Activated)
                {
                    SchedulerTaskID =  TASKS_50_MS;
                    SchM_SchedulePoint();
                }
                else
                {
                     (*(TaskCtrl[TASKS_50_MS].TaskInfo->TaskFcnPtr))();
                }
            }
            /* Verify that thread execution took less than 500 us */
             if( SchM_Task_ID_Backup == TASKS_2_MS_A || SchM_Task_ID_Backup == TASKS_50_MS)
            {
                /* In case execution of all thread took less than 500us */
                TaskCtrl[TASKS_2_MS_A].TaskState = SUSPENDED;
                TaskCtrl[TASKS_50_MS].TaskState = SUSPENDED;
            
            }
            else
            {
                TaskCtrl[TASKS_2_MS_A].TaskOverload = 1;
            }
        }
        else
        {
            /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            /*  2ms execution thread - used to derive two execution threads:                */
            /*  a) 2ms group B thread (high priority tasks)                                 */
            /*  b) 10ms thread (medium priority tasks)                                      */
            /*  As any other thread on this scheduler, all tasks must be executed in <=500us*/
            /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            if( ( TaskCtrl[TASKS_2_MS_B].TaskState == READY )
                || ( TaskCtrl[TASKS_10_MS].TaskState == READY) )
            {
                /* Make a copy of scheduled task ID */
                SchM_Task_ID_Backup = TaskCtrl[TASKS_2_MS_B].TaskInfo->TaskId; 
                if(ISR_Activated)
                {
                    SchedulerTaskID =  TASKS_2_MS_B;
                    SchM_SchedulePoint();
                }
                else
                {
                    (*(TaskCtrl[TASKS_2_MS_B].TaskInfo->TaskFcnPtr))();
                }
                if( TaskCtrl[TASKS_10_MS].TaskState == READY)
                {
                    if(ISR_Activated)
                    {
                        SchedulerTaskID =  TASKS_10_MS;
                        SchM_SchedulePoint();
                    }
                    else
                    {
                        (*(TaskCtrl[TASKS_10_MS].TaskInfo->TaskFcnPtr))();
                    }
                }
                 /* Verify that thread execution took less than 500 us */
                if( SchM_Task_ID_Backup == TASKS_2_MS_B || SchM_Task_ID_Backup == TASKS_10_MS)
                {
                    /* In case execution of all thread took less than 500us */
                    TaskCtrl[TASKS_2_MS_B].TaskState = SUSPENDED;
                    TaskCtrl[TASKS_10_MS].TaskState = SUSPENDED;
                
                }
                else
                {
                    TaskCtrl[TASKS_2_MS_B].TaskOverload = 1;
                }
            }
        }
    }         
}

/*****************************************************************************************************
* Code of public FUNCTIONS
*****************************************************************************************************/

/****************************************************************************************************/
/**
* \brief    Scheduler - Initialization
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo     
*/
void SchM_Init(void)
{    
    /* Init Global and local Task Scheduler variables */
    SchM_Counter   = 0u;
    SchM_Task_ID_Activated = TASK_NULL;
    SchM_Task_ID_Running = TASK_NULL;
    SchM_Task_ID_Backup = TASK_NULL;
    SchM_10ms_Counter        = 0u;
    SchM_50ms_Counter        = 0u;
    SchM_100ms_Counter       = 0u;
    SchM_Status    = SCHM_TASK_SCHEDULER_INIT;
    /* Start scheduler */
    SchMTaskType Array[]={
  {5, TASKS_1_MS, SchM_Task_1ms},
	{4, TASKS_2_MS_A, SchM_Task_2ms_A},
	{4, TASKS_2_MS_B, SchM_Task_2ms_B},
	{3, TASKS_10_MS, SchM_Task_10ms},
	{2, TASKS_50_MS, SchM_Task_50ms},
	{1, TASKS_100_MS, SchM_Task_100ms},
  {3, TASKS_ISR, SchM_Task_ISR} //ISR priority, task id and function pointer
    };
    SchM_InitTasks(Array);
	/* Start scheduler */
	SchM_Start();
}

/*******************************************************************************/
/**
* \brief    Scheduler Stop - stop execution of Multi-thread Round Robin scheduling scheme.
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo     
*/
void SchM_Stop(void)
{  
    /* Update scheduler status accordingly */
    SchM_Status = SCHM_TASK_SCHEDULER_HALTED;
}

/***************************************************************************************************/

/****************************************************************************************************/
/**
* \brief    SysTick - interrupt handling
* \author   Abraham Tezmol
* \param    void
* \return   void
* \todo
*/
/* SysTick interrupt handler */
void SysTick_Handler(void)
{
	if (pfctnSysTick)
	{
		(*pfctnSysTick)();
	}
}


void SchM_ActiveTask(SchMTasksIdType TaskID){

    
    TaskCtrl[TaskID].TaskState = READY;
    //TaskCtrl[].TaskInfo->TaskId = TaskID;
}

void SchM_InitializeStruct(SchMTasksIdType TaskID, SchMTaskType *Array)
{
    TaskCtrl[TaskID].TickCounter = 0u;
    TaskCtrl[TaskID].TaskRunning = 0u;
    TaskCtrl[TaskID].TaskOverload = 0u;
    TaskCtrl[TaskID].TaskState = SUSPENDED;
    TaskCtrl[TaskID].TaskInfo = Array;
}

void SchM_InitTasks(SchMTaskType* Array)
{
    for(int i = 0; i <= TASKS_ISR; i++)
    {
        SchM_InitializeStruct(i, &Array[i]);
    }
}


void SchM_SchedulePoint()
{
        if((TaskCtrl[SchedulerTaskID].TaskInfo->TaskPriority > TaskCtrl[TASKS_ISR].TaskInfo->TaskPriority))
        {
               
                TaskCtrl[SchedulerTaskID].TaskInfo->TaskFcnPtr();     
                TaskCtrl[TASKS_ISR].TaskInfo->TaskFcnPtr();
                TC_Stop(TC3,2);
                StopTimer = TC3->TC_CHANNEL[2].TC_CV;
        }
        else
        {
                
                TaskCtrl[TASKS_ISR].TaskInfo->TaskFcnPtr();
                TC_Stop(TC3,2);
                StopTimer = TC3->TC_CHANNEL[2].TC_CV;
                TaskCtrl[SchedulerTaskID].TaskInfo->TaskFcnPtr();
        }
        
        TotalTimer = StopTimer - StartTimer;
        TaskCtrl[TASKS_ISR].TaskState = SUSPENDED;
       

}

void PIOA_Handler (void)
{
     unsigned int *Register;
     Register = (unsigned int *)(0x400E0E00 + 0x004C);
    //Lectura Dummy para limpiar las banderas de Interupcion del PIOA
     Dummy =  *Register;
     SchM_ActiveTask(TASKS_ISR);
     TC_Start(TC3,2);
     StartTimer = TC3->TC_CHANNEL[2].TC_CV;

}