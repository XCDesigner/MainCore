#pragma once

#include "CommBase.h"
#include <stdint.h>

class Uart2 : CommData , CommPort {
public:
  void Init();
  void Loop();
private:

};

extern Uart2 hw_uart2_port;