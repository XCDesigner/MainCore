#pragma once

#include <stdint.h>

class CommData {
public:
  virtual bool StoreOneByte(uint8_t byte_to_store);
  virtual int StoreBytes(uint8_t *pData, uint8_t Len);
  virtual int SendBytes(uint8_t *pData, uint16_t Len);
public:
  uint8_t recv_buff[2048];
  uint16_t read_tail, read_head;
  uint8_t send_buff[2048];
  uint16_t send_tail, send_head;
  uint8_t parsed_buff[1024];
  uint16_t parsed_len;
};

class CommPort {
  virtual void Loop();

};
