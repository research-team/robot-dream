//robot libs
#include <ArduinoRobot.h>
#include <Wire.h>
#include <SPI.h>

//other libs
#include <SimpleModbusSlave.h>
#include <math.h>

enum
{
  // just add or remove registers and your good to go...
  // The first register starts at address 0
  IR,
  VOLTS,
  FLOOR, 
  COMPASS,
  E4,
  E5,
  E6,
  E7,
  E8,
  E9,
  EA,
  EB,
  EC,
  ED,
  EE,
  EF,
  LWS,//left wheel speed
  RWD,//right wheel speed
  E12,
  E13,
  E14,
  E15,
  MVCMD,//move command, see protocol description, write only
  E17,
  E18,
  E19,
  E20,
  TOTAL_ERRORS,
  // leave this one
  TOTAL_REGS_SIZE
  // total number of registers for function 3 and 16 share the same register array
};

unsigned int holdingRegs[TOTAL_REGS_SIZE];
byte prevfloor=1;
void setup() {
  Robot.begin();
  modbus_configure(115200, 1, 0, TOTAL_REGS_SIZE, 0);  
}

void loop() {
  holdingRegs[TOTAL_ERRORS] = modbus_update(holdingRegs);
  IR_update();
  Floor_update();
  Compass_update();
  delay(50);
}

void IR_update(){
  double data = Robot.analogRead(TK2);
  data*=5;data/=1024;//transform readed data to volts
  holdingRegs[IR]=(unsigned int)round(-115+205*data-29*data*data-216*log(data));//transform to distance, using magic formula
}

void Floor_update(){
  Robot.updateIR();
  byte sum=0;//count how many sensor on floor
  for(int i=0;i<=4;i++){
    if(Robot.IRarray[i]>455)
      sum+=1;
  }
  if(prevfloor==1){//if robot was on floor
    if(sum<=3)//if 3 or less sensors on floor
      holdingRegs[FLOOR]=0;//whole robot not on floor
    else
      holdingRegs[FLOOR]=1;//on floor
  }
  else if(prevfloor==0){//if robot was not on floor
    if(sum>=4)//if 4 or more on floor
      holdingRegs[FLOOR]=1;//whole robot on floor
    else
      holdingRegs[FLOOR]=0;//off floor
  }    
  prevfloor=holdingRegs[FLOOR];
}

void Compass_update(){
  holdingRegs[COMPASS]=Robot.compassRead();
}
