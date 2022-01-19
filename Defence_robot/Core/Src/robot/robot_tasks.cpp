#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "semphr.h"
#include"robot_operation.h"
extern SemaphoreHandle_t binSem;
extern JoyStick joystick;
extern "C" void DefaultTask(void const * argument);
extern "C"  void StartUpdateTask(void const * argument);
extern "C" void StartRunningTask(void const * argument);
void StartRunningTask(void const * argument)
{
     robo_init();
     osDelay(10);
    for(;;){
    //uint8_t dt=HAL_GetTick();
    //printf("entered runing tasks\n");
   //xSemaphoreTake(binSem, osWaitForever);
    robo_play();
    osDelay(SAMPLE_TIME);
   // xSemaphoreGive(binSem);
   /* uint16_t ellapsed_time=HAL_GetTick()-dt;
   if(ellapsed_time<SAMPLE_TIME)
      {
          osDelay(SAMPLE_TIME-ellapsed_time);

      }
    else
    {
     printf("Timing delay occurs at running portion\n");

    }*/
    }
}
void StartUpdateTask(void const * argument)
{
  for(;;)
  {
    //printf("entered update tasks\n");
    joystick.parse_JoyData();
    osDelay(1);
    }
  }