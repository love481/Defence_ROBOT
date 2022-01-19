#include"robo_init.h"
//initilize all objects and their configurations
static Motor_config motor_configurations[4];
static  encoder_config encoder_configurations[4];
motor m_rotatory_wheel[2];
motor m_joint[2];
encoder e_rotatory_wheel[2];
encoder e_joint[2];
A4988_config A4988_config_;
a4988 stepper;
pid_Algorithm pid_algo_rotatory_wheel[2];
pid_Algorithm pid_algo_joint[2];
static Motor_config conveyer_motor_config_;
motor conveyer_motor_;
conveyer_encoder conveyer_encoder_;
void robo_init()
{
	communication_init();
	motorAllInitilize();
	encoderAllInitilize();
	pidAllInitilize();
	interruptInit();
	Stepper_Init();
}
void motorAllInitilize()
{
	motor_configurations[0].htim = &htim8;
	motor_configurations[0].in_port = GPIOA;
	motor_configurations[0].in_pin = GPIO_PIN_10;
	motor_configurations[0].channel = TIM_CHANNEL_1;
	motor_configurations[0].max_omega = 22;
	motor_configurations[0].tolerance = 1;

	motor_configurations[1].htim = &htim8;
	motor_configurations[1].in_port = GPIOD;
	motor_configurations[1].in_pin = GPIO_PIN_0;
	motor_configurations[1].channel = TIM_CHANNEL_2;
	motor_configurations[1].max_omega = 5;
	motor_configurations[1].tolerance = 1;

	motor_configurations[2].htim = &htim8;
	motor_configurations[2].in_port = GPIOD;
	motor_configurations[2].in_pin = GPIO_PIN_2;
	motor_configurations[2].channel = TIM_CHANNEL_3;
	motor_configurations[2].max_omega = 20;
	motor_configurations[2].tolerance = 1;

	motor_configurations[3].htim = &htim8;
	motor_configurations[3].in_port = GPIOB;
	motor_configurations[3].in_pin = GPIO_PIN_5;
	motor_configurations[3].channel = TIM_CHANNEL_4;
	motor_configurations[3].max_omega = 20;
	motor_configurations[3].tolerance = 1;

	HAL_TIM_Base_Start(&htim8);
	HAL_TIM_PWM_Start(motor_configurations[0].htim, motor_configurations[0].channel);
	HAL_TIM_PWM_Start(motor_configurations[1].htim, motor_configurations[1].channel);
	HAL_TIM_PWM_Start(motor_configurations[2].htim, motor_configurations[2].channel);
	HAL_TIM_PWM_Start(motor_configurations[3].htim, motor_configurations[3].channel);


    m_joint[0].set_config(&motor_configurations[0]);
	m_joint[1].set_config(&motor_configurations[1]);
	m_rotatory_wheel[0].set_config(&motor_configurations[2]);
	m_rotatory_wheel[1].set_config(&motor_configurations[3]);


	/*conveyer_motor_config_.htim = &htim9;
	conveyer_motor_config_.in_port = GPIOC;
	conveyer_motor_config_.in_pin = GPIO_PIN_2;
	conveyer_motor_config_.in1_port = GPIOC;
	conveyer_motor_config_.in1_pin = GPIO_PIN_3;
	conveyer_motor_config_.channel = TIM_CHANNEL_1;
	conveyer_motor_config_.max_omega = 10;
	conveyer_motor_config_.tolerance = 1;

	HAL_TIM_Base_Start(&htim9);
	HAL_TIM_PWM_Start(conveyer_motor_config_.htim,conveyer_motor_config_.channel);
	conveyer_motor_.set_config(&conveyer_motor_config_);*/

}
void encoderAllInitilize()
{    //set all handles for all motors
	encoder_configurations[0].id = 0;
	encoder_configurations[0].ppr =3500;
	encoder_configurations[0].henc = &htim1;

	encoder_configurations[1].id = 1;
	encoder_configurations[1].ppr =  175*4;
	encoder_configurations[1].henc = &htim2;
	
	encoder_configurations[2].id = 2;
	encoder_configurations[2].ppr =  400;
	encoder_configurations[2].henc = &htim3;

	encoder_configurations[3].id = 3;
	encoder_configurations[3].ppr = 400;
	encoder_configurations[3].henc = &htim4;

    HAL_TIM_Encoder_Start(encoder_configurations[0].henc, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(encoder_configurations[1].henc, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(encoder_configurations[2].henc, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(encoder_configurations[3].henc, TIM_CHANNEL_ALL);

	e_joint[0].set_config(&encoder_configurations[0]);
	e_joint[1].set_config(&encoder_configurations[1]);
	e_rotatory_wheel[0].set_config(&encoder_configurations[2]);
	e_rotatory_wheel[1].set_config(&encoder_configurations[3]);
	 
	//start measuring specific parameters
	e_joint[0].encoderInitilize();
	e_joint[1].encoderInitilize();
	e_rotatory_wheel[0].encoderInitilize();
	e_rotatory_wheel[1].encoderInitilize();

	conveyer_encoder_.set_ppr(550);
	conveyer_encoder_.conveyer_init();

}
void pidAllInitilize()
{
    pid_algo_joint[0]=CONTINOUS;
	m_joint[0].setContinousPIDConstrain(2,0,0,-7,7);
	// pid_algo_joint[1]=CONTINOUS;
	pid_algo_joint[1]=FUZZY;
	// m_joint[1].setContinousPIDConstrain(2,0,0,-5,5);
	m_joint[1].setFuzzyPIDConstrain(1,0.1,0,-5,5);
	pid_algo_rotatory_wheel[0]=CONTINOUS;
	m_rotatory_wheel[0].setContinousPIDConstrain(1.01,0,0,-22, 22);
	pid_algo_rotatory_wheel[1]=CONTINOUS;
	m_rotatory_wheel[1].setContinousPIDConstrain(1.01,0,0,-22, 22);
}
void interruptInit()
{
 HAL_TIM_Base_Start_IT(&htim10);
}
void Stepper_Init(void)
{

        A4988_config_.steps_per_rev = 200;
        A4988_config_.dir_port = GPIOD;
        A4988_config_.dir_pin = GPIO_PIN_10;
        A4988_config_.step_port = GPIOB;
        A4988_config_.step_pin = GPIO_PIN_14;
        stepper.setConfig(&A4988_config_);
		stepper.A4988_setDirection(1);
}
