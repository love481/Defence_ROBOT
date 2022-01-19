
#ifndef _A4988_H_
#define _A4988_H_

#include "tim.h"
#include "gpio.h"

struct A4988_config
{
        uint32_t steps_per_rev;
        GPIO_TypeDef *dir_port, *step_port;
        uint32_t dir_pin, step_pin;
        float omega;
};
class a4988
{

   private:
    A4988_config *stepper_;
    bool stepperActuate;
    uint32_t dt;
  public:
    a4988():stepper_(NULL),stepperActuate(false),dt(0){}
    a4988( A4988_config *_stepper):stepper_(_stepper){}
    void setConfig(A4988_config *_stepper){stepper_=_stepper;}
    a4988(a4988 &&) = default;
    a4988(const a4988 &) = default;
    a4988 &operator=(a4988 &&) = default;
    a4988 &operator=(const a4988 &) = default;
    void A4988_setDirection(uint32_t dir);
    void A4988_toggleDirection();
    void A4988_step();
    void A4988_stop();
    void update_stepperAction();
    void actuate(bool p_){stepperActuate=p_;}

};
#endif // !_A4988_H_