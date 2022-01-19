#include"uart_communication.h"
rotation_wheel rotation_wheel_;
arm arm_;
extern conveyer_encoder conveyer_encoder_;
struct JoyStick_Data gJoy;
static CRC_Hash gJoyStick_CRC(7);
static uint8_t gRx4Data;
static uint8_t gJoy_Data_Arr[NUM_JOYSTICK_BYTES];
static uint16_t gRx4_Data_num = 0;
static bool gStart_Byte_Rx4 = false;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{__HAL_UART_FLUSH_DRREGISTER(huart);
        if (!gStart_Byte_Rx4)
        {
                if (gRx4Data == JOYSTICK_START_BYTE)
                {
                       // printf("started\n");
                        gStart_Byte_Rx4 = true;
                }
        }
        else if(gRx4Data != JOYSTICK_START_BYTE)
        {
                if (gRx4_Data_num < NUM_JOYSTICK_BYTES)
                {
                        gJoy_Data_Arr[gRx4_Data_num] = gRx4Data;
                       // printf("data%d  %d\n",gRx4_Data_num,gJoy_Data_Arr[gRx4_Data_num]);
                        ++gRx4_Data_num;
                }
                else {
                        uint8_t rem = gRx4Data;
                        gStart_Byte_Rx4 = false;
                        gRx4_Data_num = 0;
                        uint8_t hash = gJoyStick_CRC.get_Hash(gJoy_Data_Arr, NUM_JOYSTICK_BYTES);
                       // printf("rem %d hash %d\n",rem,hash);
                       //fill_JoyData(&gJoy,gJoy_Data_Arr);
                       if (hash == rem) {
                                fill_JoyData(&gJoy,gJoy_Data_Arr);
                        }
                        else {
                                printf("Error\n");
                        }
                }
}  
}
void fill_JoyData(JoyStick_Data *joy, uint8_t data[NUM_JOYSTICK_BYTES])
{
        joy->button1 = data[0];
        joy->button2 = data[1];
}
void communication_init()
{
 HAL_UART_Receive_DMA(&huart4,&gRx4Data,1);
}
void parse_joyData()
{ 
 if(gJoy.button1 ==1)

      {       //printf("Wheel sarted\n");
              rotation_wheel_.set_wheelCommand(true);
      }
   else if(gJoy.button1 ==2)
     
     {       //printf("Wheel stoppedd\n");
             rotation_wheel_.set_wheelCommand(false);
     }
   if(gJoy.button1 ==4)
       
       {
        arm_.set_joint0Direction(Direction::CLOCKWISE);
       }

   else if(gJoy.button1 ==8)
     arm_.set_joint0Direction(Direction::ANTICLOCKWISE);
     
   else if(gJoy.button1 ==16)
        {
        arm_.set_joint1Direction(Direction::ANTICLOCKWISE);
        gJoy.button1=0;
        }
   else if(gJoy.button1 ==32)
       {
       arm_.set_joint1Direction(Direction::CLOCKWISE);
       gJoy.button1=0;
       }
   else if(gJoy.button1 ==64)
       {   //printf("pneu actuated\n");
               rotation_wheel_.set_pneuCommand(true);
               rotation_wheel_.set_PneuArrowHold(true);
               gJoy.button1=0;
       }
   else if(gJoy.button1 ==128)
        {   
                arm_.set_pneuReleaseCommand(true);
        }
    else if(gJoy.button2 ==128)
        
        {
         arm_.set_startLoadArrow(true);
              
        }
       else if(gJoy.button2==64)
        
        {
         arm_.set_pneuHoldCommand(true);
              
        }
      else if(gJoy.button2 ==32)
          arm_.reset_armState(true);
        
}
