#include "stm32f4xx_conf.h"
#include "src/HAL/shared/Can.h"

void CANPort::Init(){
  CAN_InitTypeDef CAN_InitStruct;
  GPIO_InitTypeDef GPIO_InitStruct;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);  
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_CAN1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_CAN1);

  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStruct);

  CAN_DeInit(CAN1);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
  


  CAN_Init(CAN1, &CAN_InitStruct);
  FilterInit();
}


void CANPort::Loop(){
  
}


void CANPort::FilterInit(){

}

void CANPort::Parse() {
  uint16_t target_id;
  parsed_len = p_parser->Parse(&target_id, recv_buff, parsed_buff, &read_tail, &read_head, sizeof(recv_buff));
  
}