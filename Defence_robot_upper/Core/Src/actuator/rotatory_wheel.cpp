#include"rotatory_wheel.h"
extern pid_Algorithm pid_algo_rotatory_wheel[2];
extern encoder e_rotatory_wheel[2];
extern motor m_rotatory_wheel[2];
static bool entered=false;
extern TIM_HandleTypeDef htim10;
void rotation_wheel::motorWheel_actuate(float speed)
{
/*float tunedOmega = motor_[3].computeOmega(speed, encoder_[3].get_omega(),pid_Algorithm_[3]);
		motor_[3].set_omega(tunedOmega);*/
 for (int i = 0; i < 2; i++)
	{
		float tunedOmega = m_rotatory_wheel[i].computeOmega(speed*(1-2*i), e_rotatory_wheel[i].get_omega(),pid_algo_rotatory_wheel[i]);
		m_rotatory_wheel[i].set_omega(tunedOmega);
	}
}
void rotation_wheel::start_commands(void)
{
   if(WheelActuate==true)
		{  
        if ((HAL_GetTick() - currTime) > 10)
		 { 	
			motorWheel_actuate(20);
         currTime = HAL_GetTick();
		  }
        if(PneuActuate==true && entered==false)
        {  
           HAL_GPIO_WritePin(GPIOE,GPIO_PIN_5,GPIO_PIN_RESET);
           HAL_Delay(50);
           HAL_GPIO_WritePin(GPIOE,GPIO_PIN_1,GPIO_PIN_SET);
           totalTime=HAL_GetTick();
           PneuActuate=false;
           entered=true;
           //HAL_Delay(60);
           //HAL_GPIO_WritePin(GPIOE,GPIO_PIN_3,GPIO_PIN_RESET);
        }
        else if((HAL_GetTick()-totalTime)>2000 && entered==true)
        {
           entered=false;
           PneuActuate=false;
        }
         else if((HAL_GetTick()-totalTime)>100 && entered==true)
        {
            HAL_GPIO_WritePin(GPIOE,GPIO_PIN_1,GPIO_PIN_RESET);           
        }
      }
      else
       {
        motorWheel_actuate(0);
       }
       //motor actuate at the interval of 5 ,5 seconds
  /*   if(WheelActuate==true)  
   {  
    if ((HAL_GetTick() - currTime) > 10)

		 { 	
			motorWheel_actuate(21);
        currTime = HAL_GetTick();
		  }
         if((HAL_GetTick()-pneuDelay)>5000)
           {
              HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_SET);
             HAL_Delay(60);
             {
               HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_RESET); 
                pneuDelay=HAL_GetTick();
             }
            }
}
else
       {
        motorWheel_actuate(0);
       }*/
}
