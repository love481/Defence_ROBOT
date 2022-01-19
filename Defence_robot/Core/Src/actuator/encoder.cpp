#include "encoder.h"
void encoder::encoderInitilize()
{
	prevAngle =((2 * PI * ((int16_t)encoder_config_->henc->Instance->CNT)) / encoder_config_->ppr);
	angle=0;
}
float encoder::get_omega(void)
{
    omega = ((2 * PI * (int16_t)encoder_config_->henc->Instance->CNT * 1000.0) / (encoder_config_->ppr * SAMPLE_TIME));
    count+=(int16_t)encoder_config_->henc->Instance->CNT;
    encoder_config_->henc->Instance->CNT = 0;
    return omega;
    
}
float encoder::get_angle(void)
{
    float newAngle = ((2 * PI * ((int16_t)encoder_config_->henc->Instance->CNT+count)) / encoder_config_->ppr);
	float dx=newAngle-prevAngle;
	dx = normalizeAngle(dx);
	angle+= dx;
	prevAngle = newAngle;
	return angle;

}
uint16_t encoder::get_count(void)
{
	return count;
}

