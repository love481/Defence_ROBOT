#pragma once
#ifndef _ROBO_INIT_H_
#define _ROBO_INIT_H_
#include"tim.h"
#include"motor.h"
#include"encoder.h"
#include"uart_communication.h"
#include"a4988.h"
#include"conveyer.h"
//initilze all functions for their respective objects
void motorAllInitilize(void);
void encoderAllInitilize(void);
void pidAllInitilize(void);
void robo_init(void);
void interruptInit(void);
void Stepper_Init(void);

#endif //!_ROBO_INIT_H_

