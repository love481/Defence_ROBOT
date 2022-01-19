#pragma once
#ifndef _UART_COMMUNICATION_
#include"arm.h"
#include"rotatory_wheel.h"
#include"crc_hash.h"
#define START_BYTE      (0xA5)
#define JOYSTICK_START_BYTE (START_BYTE)
#define NUM_JOYSTICK_BYTES (2)
#define B_X             (7)
#define B_Y             (6)
#define B_A             (5)
#define B_B             (4)
#define B_UP            (3)
#define B_DOWN          (2)
#define B_LB            (1)
#define B_RB            (0)

#define B_START         (7)
#define B_BACK          (6)
#define B_XBOX          (5)
#define B_LEFT          (4)
#define B_RIGHT         (3)
struct JoyStick_Data
{       
        uint8_t button1;
        uint8_t button2;
};
void fill_JoyData(JoyStick_Data *joy,uint8_t data[NUM_JOYSTICK_BYTES]);
void communication_init(void);
void parse_joyData(void);
#endif // !_UART_COMMUNICATION_