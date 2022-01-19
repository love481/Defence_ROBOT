
#include "a4988.h"

void a4988::A4988_setDirection(uint32_t dir)
{
        if (dir) {
                HAL_GPIO_WritePin(stepper_->dir_port, stepper_->dir_pin, GPIO_PIN_SET);
        }
        else {
                HAL_GPIO_WritePin(stepper_->dir_port, stepper_->dir_pin, GPIO_PIN_RESET);
        }
}

void a4988:: A4988_toggleDirection()
{
        HAL_GPIO_TogglePin(stepper_->dir_port, stepper_->dir_pin);
}

void a4988::A4988_step()
{
        for(int i=0;i<stepper_->steps_per_rev;i++)
        {
              HAL_GPIO_WritePin(stepper_->step_port, stepper_->step_pin, GPIO_PIN_SET);
              HAL_Delay(0.1);
              HAL_GPIO_WritePin(stepper_->step_port, stepper_->step_pin, GPIO_PIN_RESET);
              HAL_Delay(0.1);           
        }
}
void a4988::A4988_stop()
{
HAL_GPIO_WritePin(stepper_->step_port, stepper_->step_pin, GPIO_PIN_RESET);

}
void a4988::update_stepperAction()
{
 if(stepperActuate)
   {  
        if((HAL_GetTick()-dt)>5000)
            stepperActuate=false;
        A4988_step();
   }
 else
   {
     A4988_stop();
     HAL_GPIO_WritePin(GPIOE,GPIO_PIN_13,GPIO_PIN_RESET);
   }
}
