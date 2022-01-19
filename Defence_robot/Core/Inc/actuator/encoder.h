#ifndef _ENCODER_H_
#define _ENCODER_H_
#include"defines.h"
struct encoder_config{
    TIM_HandleTypeDef *henc;
    uint16_t ppr;
    uint8_t id;
};
class encoder
{
private:
    encoder_config *encoder_config_;
    float omega;
    float angle,prevAngle;
    int16_t count;
public:
    encoder() 
    {   omega=0;
        count=0;
        angle=0;
        prevAngle=0;
    }
    encoder(encoder_config *_encoder_config) : encoder_config_(_encoder_config) {}
    encoder(encoder &&) = default;
    encoder(const encoder &) = default;
    encoder &operator=(encoder &&) = default;
    encoder &operator=(const encoder &) = default;
    ~encoder() {}
    void encoderInitilize(void);
    void set_config(encoder_config *_encoder_config) {encoder_config_=_encoder_config;}
    float get_omega(void);
    uint16_t get_count(void);
    float get_angle(void);
};
#endif //!_ENCODER_H_