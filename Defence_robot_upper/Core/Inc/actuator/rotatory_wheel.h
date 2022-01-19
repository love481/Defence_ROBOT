#pragma once
#ifndef _ROTATORY_WHEEL_
#define _ROTATORY_WHEEL_
#include"robo_init.h"
class rotation_wheel
{
 private:
   bool PneuActuate;
   bool WheelActuate; 
   bool PneuArrowHold;
   uint32_t pneuDelay;
   uint32_t currTime;
   uint32_t totalTime;
 public:
   rotation_wheel(){
       PneuActuate=false;
       WheelActuate=false;
       PneuArrowHold=false;
       pneuDelay=HAL_GetTick();
       currTime = HAL_GetTick();
       totalTime=0;

   }
   rotation_wheel(rotation_wheel &&) = default;
   rotation_wheel(const rotation_wheel &) = default;
   rotation_wheel &operator=(rotation_wheel &&) = default;
   rotation_wheel &operator=(const rotation_wheel &) = default;
   void motorWheel_actuate(float);
   void set_pneuCommand(bool p_){ PneuActuate=p_;}
   void set_wheelCommand(bool p_){ WheelActuate=p_;}
   void set_PneuArrowHold(bool p_){ PneuArrowHold=p_;}
   void start_commands();
   
};


#endif // !_ROTATORY_WHEEL_