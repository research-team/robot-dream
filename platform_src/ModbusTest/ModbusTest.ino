#include <SimpleModbusSlave.h>
#include <ArduinoRobot.h>
#include <Wire.h>
#include <SPI.h>

enum
{
  // just add or remove registers and your good to go...
  // The first register starts at address 0
  ADC0,
  CTRLRD,
  CTRL,  
  TOTAL_ERRORS,
  // leave this one
  TOTAL_REGS_SIZE
  // total number of registers for function 3 and 16 share the same register array
};

unsigned int holdingRegs[TOTAL_REGS_SIZE];
void setup() {
  Robot.begin();
  modbus_configure(115200, 1, 0, TOTAL_REGS_SIZE, 0);  
}

void loop() {
  holdingRegs[TOTAL_ERRORS] = modbus_update(holdingRegs);
  holdingRegs[ADC0] = Robot.knobRead();
  holdingRegs[CTRLRD]=holdingRegs[CTRL];
}
