#include "joystick.h"
#include "array.h"
#include <math.h>
#include"robo_state.h"
static float vel=1.5;
#define JOYSTICK_START_BYTE (START_BYTE)
#define NUM_JOYSTICK_BYTES (8)

extern JoyStick_Handle gJoyStick;
struct JoyStick_Data gJoy;
static JoyStick_Data gNull_JData;
extern robo_state robo_state_;

static uint8_t sending_byte[2];
static CRC_Hash gJoyStick_CRC(7);

static uint8_t gRx2Data;
static uint8_t gJoy_Data_Arr[NUM_JOYSTICK_BYTES];
static uint16_t gRx2_Data_num = 0;
static bool gStart_Byte_Rx2 = false;
static void fill_JoyData(JoyStick_Data *joy, uint8_t data[NUM_JOYSTICK_BYTES]);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
        __HAL_UART_FLUSH_DRREGISTER(huart);
        if (!gStart_Byte_Rx2)
        {
                if (gRx2Data == JOYSTICK_START_BYTE)
                {
                        gStart_Byte_Rx2 = true;
                       HAL_UART_Transmit_DMA(&huart4,&gRx2Data,1);
                }
        }
        else
        {
                if (gRx2_Data_num < NUM_JOYSTICK_BYTES)
                {      
                        gJoy_Data_Arr[gRx2_Data_num] = gRx2Data;
                        //printf(" data%d %d\n",gRx2_Data_num,sending_byte[gRx2_Data_num]);
                      if(gRx2_Data_num==0 || gRx2_Data_num==1)
                        {
                          sending_byte[gRx2_Data_num]=gJoy_Data_Arr[gRx2_Data_num];
                          //printf(" data%d %d\n",gRx2_Data_num,sending_byte[gRx2_Data_num]);
                          HAL_UART_Transmit_DMA(&huart4,&sending_byte[gRx2_Data_num],1);
                        }
                       else if(gRx2_Data_num==2)
                        {      
                                uint8_t hash_sending=gJoyStick_CRC.get_Hash(sending_byte, 2);
                              // printf(" hash %d\n",hash_sending);
                                HAL_UART_Transmit_DMA(&huart4,&hash_sending,1);
                        }
                        ++gRx2_Data_num;
                }
                else {
                        uint8_t rem = gRx2Data;
                        gStart_Byte_Rx2 = false;
                        gRx2_Data_num = 0;
                        uint8_t hash = gJoyStick_CRC.get_Hash(gJoy_Data_Arr, NUM_JOYSTICK_BYTES);
                        if (hash == rem) {
                                fill_JoyData(&gJoy, gJoy_Data_Arr);
                                // printf("No Error!!");
                        }
                        else {
                                printf("Error");
                        }
                }
        }
}
void JoyStick::init()
{
        gNull_JData.button1 = 0;
        gNull_JData.button2 = 0;
        gNull_JData.lt = 0;
        gNull_JData.rt = 0;
        gNull_JData.l_hatx = 0;
        gNull_JData.l_haty = 0;
        gNull_JData.r_hatx = 0;
        gNull_JData.r_haty = 0;
}

void fill_JoyData(JoyStick_Data *joy, uint8_t data[NUM_JOYSTICK_BYTES])
{
        //joy->button1 = data[0];
        //joy->button2 = data[1];
        joy->lt = data[2];
        joy->rt = data[3];
        joy->l_hatx = data[4];
        joy->l_haty = data[5];
        joy->r_hatx = data[6];
        joy->r_haty = data[7];
}
void JoyStick:: parse_JoyData()
{
         HAL_UART_Receive_DMA(hjoy_->huart, &gRx2Data, 1);
        if (gJoy.l_haty <= 127 && gJoy.l_hatx == 0 && gJoy.l_haty != 0 )
        {
           // printf("F \n");
            robo_state_.velocity =vel;
            robo_state_.direction=90;
            robo_state_.omega=0;
        }
        else if(gJoy.l_haty >= 127 && gJoy.l_hatx == 0 )
        {
           // printf("B \n");
            robo_state_.velocity =vel;
            robo_state_.direction=-90;
            robo_state_.omega=0;
        }
         else if (gJoy.r_hatx <= 127 && gJoy.r_haty == 0 && gJoy.r_hatx != 0)
        {
            // printf("R \n");
            robo_state_.velocity =vel;
            robo_state_.direction=0;
            robo_state_.omega=0;
        }
        else if (gJoy.r_hatx >= 127 && gJoy.r_haty == 0 )
        {
            // printf("L \n");
            robo_state_.velocity =vel;
            robo_state_.direction=180;
            robo_state_.omega=0;
        }
         else if (gJoy.lt==255)
        {
              //printf("CW \n");
            robo_state_.velocity =0;
            robo_state_.direction=0;
            robo_state_.omega=-0.5;
        }
         else if (gJoy.rt==255)
        {
               // printf("ACW \n");
            robo_state_.velocity =0;
            robo_state_.direction=0;
            robo_state_.omega=0.5;
        }
        else
        {   //printf("STOP \n");
            robo_state_.velocity =0;
            robo_state_.direction=0;
            robo_state_.omega=0;
        }
}
