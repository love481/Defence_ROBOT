#include "robot_operation.h"
extern arm arm_;
extern rotation_wheel rotation_wheel_;
extern encoder e_joint[2];
extern motor m_joint[2];
//extern a4988 stepper;
void robo_play()
{
 while(1)
 {communication_init();
  parse_joyData();
  rotation_wheel_.start_commands();
  arm_.start_commands();
 }
 /*uint16_t d=HAL_GetTick();
 while(1)
 {
   //printf("hello\n");
  stepper.A4988_step();
  stepper.A4988_toggleDirection();
 while(HAL_GetTick()-d>5000)
  {
    stepper.A4988_stop();
  }
 }
 }
