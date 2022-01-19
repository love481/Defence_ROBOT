#pragma once
#ifndef _ROBO_INIT_H_
#define _ROBO_INIT_H_
#include"tim.h"
#include"motor.h"
#include"encoder.h"
#include"inversekinematics.h"
#include"robo_state.h"
//initilze all functions for their respective objects
void motorAllInitilize(void);
void encoderAllInitilize(void);
void pidAllInitilize(void);
void joystickInitilize(void);
void robo_init(void);
#endif //!_ROBO_INIT_H_

