#include "CommBase.h"

bool CommData::StoreOneByte(uint8_t byte_to_store) {
  uint16_t next_head;

  next_head = (read_head + 1) % sizeof(recv_buff);
  if(next_head == read_tail) {
    return false;
  }
  else {
    recv_buff[read_head] = byte_to_store;
    read_head = next_head;
    return true;
  }
}


int CommData::StoreBytes(uint8_t *pData, uint8_t Len) {
  uint32_t i;
  int byte_stored;
  uint16_t next_head;

  byte_stored = 0;
  for(i=0;i<Len;i++) {
    next_head = (read_head + 1) % sizeof(recv_buff);
    if(next_head == read_tail) {
      break;
    }
    else {
      recv_buff[read_head] = pData[i];
      read_head = next_head;
      byte_stored++;
    }
  }
  return byte_stored;
}


int CommData::SendBytes(uint8_t *pData, uint16_t Len) {
  uint32_t i;
  int byte_stored;
  uint16_t next_head;

  byte_stored = 0;
  for(i=0;i<Len;i++) {
    next_head = (send_head + 1) % sizeof(send_buff);
    if(next_head == send_tail)
      break;
    send_buff[send_head] = pData[i];
    send_head = next_head;
    byte_stored++;
  }
  return byte_stored;
}

