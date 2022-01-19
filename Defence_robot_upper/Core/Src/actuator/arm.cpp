#include"arm.h"
extern pid_Algorithm pid_algo_joint[2];
extern encoder e_joint[2];
extern motor m_joint[2];
bool first_entered=false;
void arm::motor_actuate()
{   
 //HAL_GPIO_WritePin(GPIOE,GPIO_PIN_3,GPIO_PIN_RESET);
   // printf("%f %f \n",e_joint[1].get_angle(),e_joint[1].get_omega());
 if(pneuHoldState==true)
  {
   HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
   pneuHoldState=false;
  }
  if(joint[0]==Direction::ANTICLOCKWISE)
   { float tunedOmega;
   if(first_entered==false)
   {
      //tunedOmega = m_joint[0].computeOmega(-10, e_joint[0].get_omega(),pid_algo_joint[0]);
		m_joint[0].set_omega(-5);
   }
   else  if(first_entered==true)
   {
      //tunedOmega = m_joint[0].computeOmega(-10, e_joint[0].get_omega(),pid_algo_joint[0]);
		m_joint[0].set_omega(-5);
   }
      if(e_joint[0].get_angle()>=1.4 && first_entered==false)
   {
      e_joint[0].reset_angle();
      m_joint[0].set_omega(0);
      joint[0]=Direction::STOP;
      first_entered=true;
   }
     if(e_joint[0].get_angle()>=0.3 && first_entered==true)
   {
      e_joint[0].reset_angle();
      m_joint[0].set_omega(0);
      joint[0]=Direction::STOP;
      first_entered=false;
   }
   }
    else if(joint[0]==Direction::CLOCKWISE)
  { 
      float tunedOmega = m_joint[0].computeOmega(5, e_joint[0].get_omega(),pid_algo_joint[0]);
		m_joint[0].set_omega(tunedOmega);
      if(e_joint[0].get_angle()<=-1.7)
   {
      e_joint[0].reset_angle();
      m_joint[0].set_omega(0);
      joint[0]=Direction::STOP;
   }
  }
  else if(joint[1]==Direction::ANTICLOCKWISE)
   {
  // float tunedOmega = m_joint[1].computeOmega(1.57, e_joint[1].get_angle(),pid_algo_joint[1]);
	m_joint[1].set_omega(2);
    if(e_joint[1].get_angle()>1.57)
   {
      e_joint[1].reset_angle();
      m_joint[1].set_omega(0);
      joint[1]=Direction::STOP;
   }
   }
   else if(joint[1]==Direction::CLOCKWISE)
   {
   //float tunedOmega = m_joint[1].computeOmega(-1.57, e_joint[1].get_angle(),pid_algo_joint[1]);
	m_joint[1].set_omega(-2);
    if(e_joint[1].get_angle()<-1.57)
   {
      e_joint[1].reset_angle();
      m_joint[1].set_omega(0);
      joint[1]=Direction::STOP;
      
   }
   }
   else{
      e_joint[1].reset_angle();
      m_joint[1].set_omega(0);
  }
  if(pneuReleaseState==true)
  {
   HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET);
   pneuReleaseState=false;
  // HAL_TIM_Base_Start_IT(&htim10);
  }
  if(armState==true)
  {
   e_joint[0].reset_angle();
   m_joint[0].set_omega(0);
   joint[0]=Direction::STOP;
   e_joint[1].reset_angle();
   m_joint[1].set_omega(0);
   joint[1]=Direction::STOP;
   armState=false;

  }
  if(startLoadArrow==true)
  {
       HAL_GPIO_WritePin(GPIOE,GPIO_PIN_3,GPIO_PIN_SET);
       HAL_Delay(1000);
       HAL_GPIO_WritePin(GPIOE,GPIO_PIN_5,GPIO_PIN_SET);
       HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET);
       HAL_Delay(1000);
       HAL_GPIO_WritePin(GPIOE,GPIO_PIN_3,GPIO_PIN_RESET);
       startLoadArrow=false;
  }
}
void arm::start_commands(void)
{	if ((HAL_GetTick() - currTime) > 10)
   {
    motor_actuate();
   currTime = HAL_GetTick();
   }
}
