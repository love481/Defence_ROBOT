#pragma once
#ifndef CONVEYER_H_
#define CONVEYER_H_
#include"robo_init.h"
class conveyer_encoder
{  private:
   uint8_t  ppr;
   float omega;
   float angle;
   float prevAngle;
   bool conveyerActuate;
   uint32_t dt;
   public:
   conveyer_encoder() 
   {
     ppr=0;
     omega=0;
     angle=0;
     prevAngle=0;
     conveyerActuate=0;
     dt=0;
   }
   conveyer_encoder(conveyer_encoder &&) = default;
	conveyer_encoder(const conveyer_encoder &) = default;
	conveyer_encoder &operator=(conveyer_encoder &&) = default;
	conveyer_encoder &operator=(const conveyer_encoder &) = default;
	~conveyer_encoder() {}
   void set_ppr(uint8_t ppr_){ppr=ppr_;}
   void conveyer_init(void);
   float get_conveyerAngle(void);
   void reset_conveyerAngle(void);
   void start_conveyer(void);
   void actuate(bool p_){conveyerActuate=p_;}
};
#endif // !CONVEYER_H_