#pragma once
#ifndef _ARM_H_
#define _ARM_H_
#include"encoder.h"
#include"motor.h"
class arm
{
 private:
   Direction joint[2];
   bool pneuHoldState;
   bool pneuReleaseState;
   bool armState;
   bool startLoadArrow;
   uint32_t currTime;
 public:
   arm(){
       pneuHoldState=false;
       pneuHoldState=false;
       armState=false;
       startLoadArrow=false;
       currTime = HAL_GetTick();
       joint[0]=Direction::STOP;
       joint[1]=Direction::STOP;

   }
   arm(arm &&) = default;
   arm(const arm &) = default;
   arm &operator=(arm &&) = default;
   arm &operator=(const arm &) = default;
   void set_pneuHoldCommand(bool p_){ pneuHoldState=p_;}
   void set_pneuReleaseCommand(bool p_){ pneuReleaseState=p_;}
   void set_startLoadArrow(bool p_){ startLoadArrow=p_;}
   void set_joint0Direction(Direction d_){joint[0]=d_;}
   void set_joint1Direction(Direction d_){joint[1]=d_;}
   void reset_armState(bool p_){armState=p_;}
   void motor_actuate();
   void start_commands();
   
};

#endif // ! _ARM_H_