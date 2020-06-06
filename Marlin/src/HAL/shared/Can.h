#pragma once

#include "CommBase.h"
#include "../../SelfModule/protocal.h"
#include <stdint.h>

class CANPort : CommData , CommPort {
public:
  void Init();
  void Loop();
private:
  void FilterInit();
  void Parse();
private:
  Protocal *p_parser;
};

extern CANPort hw_can_port;