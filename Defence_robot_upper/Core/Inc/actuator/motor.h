#pragma once
#ifndef _MOTOR_H_
#define _MOTOR_H_
#include "pid.h"
#include"fuzzy_pid.h"
enum Direction
{
	CLOCKWISE,
	ANTICLOCKWISE,
	STOP
};
enum pid_Algorithm
{
   CONTINOUS,
   DISCRETE,
   FUZZY
};
struct Motor_config
{
	float max_omega;
	float tolerance;

	GPIO_TypeDef *in_port;
	uint16_t in_pin;
	GPIO_TypeDef *in1_port;
	uint16_t in1_pin;
	TIM_HandleTypeDef *htim; // PWM Generating Timer
	uint32_t channel;			 // PWM Channel
};

class motor
{
public:
	motor() 
	{ 
	  motor_ = 0;
	}
	motor(Motor_config *Motor_config_) { motor_ = Motor_config_; }
	motor(motor &&) = default;
	motor(const motor &) = default;
	motor &operator=(motor &&) = default;
	motor &operator=(const motor &) = default;
	~motor() {}
	void set_config(Motor_config *Motor_config_) { motor_ = Motor_config_; }
	float get_max_omega() { return motor_->max_omega; }
	void set_omega(float omega);
	void setContinousPIDConstrain(float kp, float ki, float kd, float Min, float Max,int pon= P_ON_E, int Mode = AUTOMATIC, int Direction = DIRECT)
	{
		c_pid.SetOutputLimits(Min, Max);
		c_pid.SetMode(Mode);
		c_pid.SetControllerDirection(Direction);
		c_pid.SetTunings(kp, ki, kd,pon);
	}
	void setDiscretePIDConstrain(float kp, float ki, float kd, float Min, float Max)
	{
		d_pid.SetOutputLimits(Min, Max);
		d_pid.SetTunings(kp, ki, kd);
	}
	void setFuzzyPIDConstrain(float kpMax,float kiMax,float kdMax,float e_max,float de_max)
	{
		f_pid.set_parameter(kpMax,kiMax,kdMax,e_max, de_max);
	}
	float computeOmega(float, float,pid_Algorithm);
private:
	Motor_config *motor_;
	discrete_PID d_pid;
	fuzzy_pid f_pid;
	continuous_PID c_pid;
};

#endif //!_MOTOR_H_