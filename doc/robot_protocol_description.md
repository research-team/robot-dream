# In-robot communication protocol
This is a description for communication protocol between host PC (master) and Arduino Robot platform (slave)

## MODBUS 
 * [MODBUS specification.](http://www.modbus.org/docs/Modbus_Application_Protocol_V1_1b3.pdf)
 * [Simple MODBUS description](https://ru.wikipedia.org/wiki/Modbus)
 * [FreeMODBUS library.](http://www.freemodbus.org/index.php?idx=32)
 * [C++ MODUBUS library.](http://libmodbus.org/)

MODBUS RTU version via STM32F401C-DISCO UART2 will be used. 

|Function|Code|
|:--------|:----|
|Read Multiple Holding Registers|3 (0x03)|
|Write Single Holding Register|6 (0x06)|
|Write Multiple Holding Registers|16 (0x10)|

### Connection information
 * Baudrate : 115200 baud/sec
 * Data bits : 8
 * Parity : None
 * Stop bits : 1

## Next information may change within next versions of robots

### Platform description
[Arduino robot](https://www.arduino.cc/en/Main/Robot)

### Robot sensors description
 * Infrared distance sensor - Sharp 2Y0A02 - measures distance using infrared light. Measures distance from 20 to 150 cm.
 * Battery voltage is measured by using 2 resistors, making voltage divider from 6 to 5 volts(Need to check 4 NiMh accumulators max voltage).
 * Floor control is the result of analysis from 5 IR sensors at front bottom side of the robot. 1 means there is floor, 0  means no floor. Used to prevent robot from falling of edges.
 * Compass - digital compass Honeywell HMC6352 -built in Arduino Robot is used to measure turn angle from north
 * Ultrasonic distance sensor - **unknown model** - used to measure distance to objects, closer, than 20 cm.
 * Bumper - used to detect objects by touching it. Based on end stop switches.
 * Internal Measurement Unit - **unknown model** - unit with accelerometers, gyroscopes and magnetometers(optional), used to detect orientation of robot;

### Robot register configuration
**Read-only registers**

|Description|Address|
|:--------|:----|
|IR distance sensor value in cm| 0x00 |
|Battery voltage in volts |0x01|
|Floor control|0x02|
|Compass|0x03|
|Empty reg|0x04|
|Empty reg|0x05|
|Empty reg|0x06|
|Empty reg|0x07|
|Empty reg|0x08|
|Empty reg|0x09|
|Empty reg|0x0A|
|Empty reg|0x0B|
|Empty reg|0x0C|
|Empty reg|0x0D|
|Empty reg|0x0E|
|Empty reg|0x0F|

**Read-write registers**

|Description|Address|
|:--------|:----|
|Left wheel Speed | 0x10 |
|Right wheel Speed| 0x11 |
|Empty reg| 0x12 |
|Empty reg| 0x13 |
|Empty reg| 0x14 |
|Empty reg| 0x15 |
add desc for speed later

**Write-only registers**

|Description|Address|
|:--------|:----|
|Move command | 0x16 |
|Empty reg| 0x17 |
|Empty reg| 0x18 |
|Empty reg| 0x19 |
|Empty reg| 0x1A |
0 - stop, 1 - forward, 2 - turn left, 3 - turn right