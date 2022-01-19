#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "semphr.h"
#include"robot_operation.h"
extern SemaphoreHandle_t binSem;
extern arm arm_;
extern rotation_wheel rotation_wheel_;
extern a4988 stepper;
extern conveyer_encoder conveyer_encoder_;
extern "C" void rotatoryWheelTask(void const * argument);
extern "C"  void armTask(void const * argument);
extern "C" void updateTask(void const * argument);
extern  "C" void ConveyerTask(void const * argument);
void rotatoryWheelTask(void const * argument)
{
    for(;;){
    rotation_wheel_.start_commands();
    }
}
void armTask(void const * argument)
{
    for(;;){
    arm_.start_commands();
    osDelay(SAMPLE_TIME);
    }
}
void updateTask(void const * argument)
{
  for(;;)
  {
    parse_joyData();
    osDelay(1);
    }
  }
void ConveyerTask(void const * argument)
{
  for(;;)
  {
   conveyer_encoder_.start_conveyer();
  }
}