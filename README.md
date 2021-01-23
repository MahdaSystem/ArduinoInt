# ArduinoPeripheral Library
This is a library for Arduino peripherals works with Interrupt!!! includes :
* Timers, Input Capture
* Serial
* ADC
* ...

## How to use
It's very simple just add it to your projects as the same as other Arduino libraries and Uncomment each peripheral you want in *ArduinoPeripheral.h* :
```c
//#define Arduino_Serial0
//#define Arduino_Serial1
#define Arduino_Serial2
//#define Arduino_Serial3
//#define Arduino_Timer1		    // beta version. DO NOT USE
//#define Arduino_Timer3		    // beta version. DO NOT USE
#define Arduino_Timer4
#define Arduino_Timer5
#define Arduino_ADC
//#define Arduino_SoftwareFunctions // beta version. HAS CONSIDERABLE ERROR
```

## Works For
* [ ] Arduino Uno
* [x] Arduino Mega
* [ ] Arduino Due
* [ ] Arduino Zero
* [ ] Arduino Leonard