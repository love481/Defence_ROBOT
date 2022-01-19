#include"conveyer.h"
uint16_t count=0;
extern motor conveyer_motor_;
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin==GPIO_PIN_5)
    {
      count++;
    }
}
void conveyer_encoder::conveyer_init()
{
  prevAngle =((2 * PI * (count)) /ppr);
  angle=0;
  count=0;
  dt=HAL_GetTick();
}
float conveyer_encoder::get_conveyerAngle()
{
    float newAngle = ((2 * PI *count) / ppr);
	float dx=newAngle-prevAngle;
	dx = normalizeAngle(dx);
	angle+= dx;
	prevAngle = newAngle;
	return angle;

}
void conveyer_encoder::reset_conveyerAngle()
{
count=0;
angle=0;
prevAngle=0;
}
void conveyer_encoder:: start_conveyer(void)
{
  printf("%u\n",count);
if(conveyerActuate==true)
{
   conveyer_motor_.set_omega(10);
   if(get_conveyerAngle()>3)
     {
     reset_conveyerAngle();
     conveyer_init();
     conveyerActuate=false;
     }
}
else
  conveyer_motor_.set_omega(0);

}