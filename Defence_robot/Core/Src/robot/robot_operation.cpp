#include "robot_operation.h"
extern encoder encoder_[4];
extern motor motor_[4];
extern robo_state robo_state_;
inversekinematics inversekinematics_;
extern pid_Algorithm pid_Algorithm_[4];
extern JoyStick joystick;
void robo_play()
{
	uint32_t currTime = HAL_GetTick();
	while(1)
	{
	      joystick.parse_JoyData();
		if ((HAL_GetTick() - currTime) > 10)
		{ 	
			//taskENTER_CRITICAL();
			inversekinematics_.set_robotVelocity(robo_state_.velocity, robo_state_.direction, robo_state_.omega);
			motor_actuate();
			//taskEXIT_CRITICAL();
           currTime = HAL_GetTick();
		}
	}
}
int i=3;
void motor_actuate()
{  
// float tunedOmega = motor_[i].computeOmega(inversekinematics_.get_motorOmegaFromInvKin(i), encoder_[i].get_omega(),pid_Algorithm_[i]);
//  motor_[i].set_omega(inversekinematics_.get_motorOmegaFromInvKin(i));
// printf("%f   %f   %f   %f\n",encoder_[0].get_omega(),encoder_[1].get_omega(),encoder_[0].get_omega(),encoder_[0].get_omega());
for (int i = 0; i < 4; i++)
	{ 
		//printf("%d\n",i);
		float tunedOmega = motor_[i].computeOmega(inversekinematics_.get_motorOmegaFromInvKin(i), encoder_[i].get_omega(),pid_Algorithm_[i]);
		motor_[i].set_omega(tunedOmega);
	}
// }
}

