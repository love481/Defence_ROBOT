#include "motor.h"
float tar;
float inp;
static uint16_t time_period(uint16_t PWM_frequency)
{
        if (PWM_frequency < 2000)
        { //MIN PWM_FREQUENCY = 1281.738 for time period to be 16 bit
                //_Error_Handler(__FILE__, __LINE__);
        }
        return ((168000000 / 2) / PWM_frequency) - 1; // In Center aligned mode period doubles hence we divide by 2
}

/* SET DUTYCYCLE primary function */
static void set_DutyCycle_Primary(TIM_HandleTypeDef *htim, uint32_t Channel, uint16_t dutyCycle)
{
        uint16_t mapped_value;
        mapped_value = (time_period(8000) * dutyCycle) / 65535;
        __HAL_TIM_SET_COMPARE(htim, Channel, mapped_value);
}

static void set_DutyCycle(Motor_config *m, uint16_t dutyCycle)
{
        set_DutyCycle_Primary(m->htim, m->channel, dutyCycle);
}
static void set_motorDirection(Motor_config *m, Direction d)
{
         if (d == Direction::CLOCKWISE)
        {
                HAL_GPIO_WritePin(m->in_port, m->in_pin, GPIO_PIN_SET);
        }
        else if (d == Direction::ANTICLOCKWISE)
        {
                HAL_GPIO_WritePin(m->in_port, m->in_pin, GPIO_PIN_RESET);
        }
}
static void set_motorOmega(Motor_config *m, float omega)
{
        uint16_t new_omega = (65535.0 / m->max_omega) * (omega);
        set_DutyCycle(m, new_omega);
}
float motor::computeOmega(float setpoint, float input,pid_Algorithm pid)
{       tar=setpoint;
        inp=input;
        //printf("tar:%f\n",setpoint);
       // printf("%f\n",input);
        if (pid==pid_Algorithm::CONTINOUS)
           return c_pid.Compute(setpoint, input);  
        else if(pid==pid_Algorithm::DISCRETE)
           return d_pid.Compute(setpoint, input); 
        else if(pid==pid_Algorithm::FUZZY)
           return f_pid.compute_fuzzy_selfTuning_PID(setpoint,input);
        else return setpoint;
}
void motor::set_omega(float omega)
{
        if (omega > motor_->max_omega)
        {
                omega = motor_->max_omega;
        }
        else if (omega < -motor_->max_omega)
        {
                omega = -motor_->max_omega;
        }
        if (omega < -motor_->tolerance)
        {
                set_motorDirection(motor_, Direction::ANTICLOCKWISE);
                set_motorOmega(motor_, fabs(omega));
        }
        else if (omega > motor_->tolerance)
        {
                set_motorDirection(motor_, Direction::CLOCKWISE);
                set_motorOmega(motor_, fabs(omega));
        }
        else
        {
                set_motorDirection(motor_, Direction::STOP);
                set_motorOmega(motor_, 0);
        }
}