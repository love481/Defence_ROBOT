#include"robo_init.h"
#include"joystick.h"
//initilize all objects and their configurations

static Motor_config motor_configurations[4];
motor motor_[4];
static  encoder_config encoder_configurations[4];
encoder encoder_[4];

JoyStick_Handle gJoyStick;
JoyStick joystick;
robo_state robo_state_;
pid_Algorithm pid_Algorithm_[4];
void robo_init()
{
	motorAllInitilize();
	encoderAllInitilize();
	pidAllInitilize();
	joystickInitilize();
}
void motorAllInitilize()
{
	motor_configurations[0].htim = &htim8;
	motor_configurations[0].in_port = GPIOD;
	motor_configurations[0].in_pin = GPIO_PIN_0;
	motor_configurations[0].channel = TIM_CHANNEL_1;
	motor_configurations[0].max_omega =55.29;
	motor_configurations[0].tolerance = 0.1;

	motor_configurations[1].htim = &htim8;
	motor_configurations[1].in_port = GPIOD;
	motor_configurations[1].in_pin = GPIO_PIN_2;
	motor_configurations[1].channel = TIM_CHANNEL_2;
	motor_configurations[1].max_omega = 53.405;
	motor_configurations[1].tolerance = 0.1;

	motor_configurations[2].htim = &htim8;
	motor_configurations[2].in_port = GPIOA;
	motor_configurations[2].in_pin = GPIO_PIN_10;
	motor_configurations[2].channel = TIM_CHANNEL_3;
	motor_configurations[2].max_omega =52.77;
	motor_configurations[2].tolerance = 0.1;

	motor_configurations[3].htim = &htim8;
	motor_configurations[3].in_port = GPIOE;
	motor_configurations[3].in_pin = GPIO_PIN_3;
	motor_configurations[3].channel = TIM_CHANNEL_4;
	motor_configurations[3].max_omega =58;//54.03;
	motor_configurations[3].tolerance = 0.1;

	HAL_TIM_Base_Start(&htim8);
	HAL_TIM_PWM_Start(motor_configurations[0].htim, motor_configurations[0].channel);
	HAL_TIM_PWM_Start(motor_configurations[1].htim, motor_configurations[1].channel);
	HAL_TIM_PWM_Start(motor_configurations[2].htim, motor_configurations[2].channel);
	HAL_TIM_PWM_Start(motor_configurations[3].htim, motor_configurations[3].channel);
	for (int i = 0; i < 4; i++)
	{
		motor_[i].set_config(&motor_configurations[i]);
	}
}
void encoderAllInitilize()
{    //set all handles for all motors
	encoder_configurations[0].id = 0;
	encoder_configurations[0].ppr = 1000;
	encoder_configurations[0].henc = &htim1;

	encoder_configurations[1].id = 1;
	encoder_configurations[1].ppr =  1000;
	encoder_configurations[1].henc = &htim2;
	
	encoder_configurations[2].id = 2;
	encoder_configurations[2].ppr =  1000;
	encoder_configurations[2].henc = &htim3;

	encoder_configurations[3].id = 3;
	encoder_configurations[3].ppr = 1000;
	encoder_configurations[3].henc = &htim4;

    HAL_TIM_Encoder_Start(encoder_configurations[0].henc, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(encoder_configurations[1].henc, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(encoder_configurations[2].henc, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(encoder_configurations[3].henc, TIM_CHANNEL_ALL);

	for(int i=0;i<4;i++)
	
	{
		encoder_[i].set_config(&encoder_configurations[i]);
	}
	 
	//start measuring specific parameters
	encoder_[0].encoderInitilize();
	encoder_[1].encoderInitilize();
	encoder_[2].encoderInitilize();
	encoder_[3].encoderInitilize();

}
void pidAllInitilize()
{
// 	pid_Algorithm_[0]=CONTINOUS;
// 	motor_[0].setContinousPIDConstrain(2.1,55,0,-61, 61);
// 	pid_Algorithm_[1]=CONTINOUS;
// 	motor_[1].setContinousPIDConstrain(2.1,55,0, -60, 60);
// 	pid_Algorithm_[2]=CONTINOUS;
// 	motor_[2].setContinousPIDConstrain(2.1,55,0, -58, 58);
// 	pid_Algorithm_[3]=CONTINOUS;
// 	motor_[3].setContinousPIDConstrain(2.1,60,0,-57, 57);
	pid_Algorithm_[0]=FUZZY;
	motor_[0].setFuzzyPIDConstrain(5,30,0,-20.21,20.21);
	pid_Algorithm_[1]=FUZZY;
	motor_[1].setFuzzyPIDConstrain(5,30,0,-20.21,20.21);
	pid_Algorithm_[2]=FUZZY;
    motor_[2].setFuzzyPIDConstrain(5,30,0,-20.21,20.21);
    pid_Algorithm_[3]=FUZZY;
	motor_[3].setFuzzyPIDConstrain(5,30,0,-20.21,20.21);
	/*motor_[0].setPIDConstrain(0.23933,15.183,0,-88, 88);
	motor_[1].setPIDConstrain(0.23933,15.183,0, -87, 87);
	motor_[2].setPIDConstrain(0.23933,15.183,0.0,-78, 78);
	motor_[3].setPIDConstrain(0.23933,15.183,0.0,-78, 78);*/

	//robo_state_.setPIDConstrain(0.5, 0, 0, -10, 10);
}
void joystickInitilize()
{
  gJoyStick.huart=&huart2;
  joystick.set_config(&gJoyStick);
  joystick.init();
}
