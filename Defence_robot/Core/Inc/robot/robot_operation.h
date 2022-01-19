#pragma once
#ifndef _ROBOT_OPERATION_
#define _ROBOT_OPERATION_
#include "robo_init.h"
#include"joystick.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "semphr.h"
void robo_play(void);
void motor_actuate(void);
#endif //!_ROBOT_OPERATION_
