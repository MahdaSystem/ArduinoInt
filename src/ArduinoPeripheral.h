#ifndef ARDUINOPERIPHERAL_H
#define ARDUINOPERIPHERAL_H

// Uncomment whichever you want :

//#define Arduino_Serial0
//#define Arduino_Serial1
#define Arduino_Serial2
//#define Arduino_Serial3
//#define Arduino_Timer1		// beta version. DO NOT USE
//#define Arduino_Timer3		// beta version. DO NOT USE
#define Arduino_Timer4
#define Arduino_Timer5
#define Arduino_ADC
//#define Arduino_SoftwareFunctions // beta version. HAS CONSIDERABLE ERROR

#if defined(__AVR_ATmega2560__)
#include "Arduino.h"

#ifdef Arduino_Serial0
class ArduinoSerial0Class
{
public:
	ArduinoSerial0Class;
	void SerialInitialize(uint32_t BaudRate);
	uint16_t AvailableForRead(void);
	static void Write(uint8_t *BufferForTransmit, size_t SizeOfBufferForTransmit);
	uint8_t Read(void);
	void ReadBytes(uint8_t *BufferForRecieve, size_t NumberOfBytesForRecieve);
	inline void AttachUDRE_ISRCallback(void (*UDREISRFunction)()) { UDRECallBack = UDREISRFunction; }
	inline void AttachRX_ISRCallback(void (*RXISRFunction)()) { RXCallBack = UDRECallBack; }

	void ISRTransmitUDRE(void);
	void ISRRecieveRX(void);

	static void (*UDRECallBack)();
	static void (*RXCallBack)();
	static void ISRDefualt() {}

	static uint8_t *OutputSerialBuffer;
	static size_t SizeOfOutputSerialBuffer, SizeOfOutputSerialBufferCounter;

	static uint8_t *InputSerialBuffer;
	static size_t SizeOfInputSerialBuffer, SizeOfInputSerialBufferCounter;
};
extern ArduinoSerial0Class ArduinoSerial0;
#endif
#ifdef Arduino_Serial1
class ArduinoSerial1Class
{
public:
	ArduinoSerial1Class;
	void SerialInitialize(uint32_t BaudRate);
	uint16_t AvailableForRead(void);
	static void Write(uint8_t *BufferForTransmit, size_t SizeOfBufferForTransmit);
	uint8_t Read(void);
	void ReadBytes(uint8_t *BufferForRecieve, size_t NumberOfBytesForRecieve);
	inline void AttachUDRE_ISRCallback(void (*UDREISRFunction)()) { UDRECallBack = UDREISRFunction; }
	inline void AttachRX_ISRCallback(void (*RXISRFunction)()) { RXCallBack = UDRECallBack; }

	void ISRTransmitUDRE(void);
	void ISRRecieveRX(void);

	static void (*UDRECallBack)();
	static void (*RXCallBack)();
	static void ISRDefualt() {}

	static uint8_t *OutputSerialBuffer;
	static size_t SizeOfOutputSerialBuffer, SizeOfOutputSerialBufferCounter;

	static uint8_t *InputSerialBuffer;
	static size_t SizeOfInputSerialBuffer, SizeOfInputSerialBufferCounter;
};
extern ArduinoSerial1Class ArduinoSerial1;
#endif
#ifdef Arduino_Serial2
class ArduinoSerial2Class
{
public:
	ArduinoSerial2Class;
	void SerialInitialize(uint32_t BaudRate);
	uint16_t AvailableForRead(void);
	static void Write(uint8_t *BufferForTransmit, size_t SizeOfBufferForTransmit);
	uint8_t Read(void);
	void ReadBytes(uint8_t *BufferForRecieve, size_t NumberOfBytesForRecieve);
	inline void AttachUDRE_ISRCallback(void (*UDREISRFunction)()) { UDRECallBack = UDREISRFunction; }
	inline void AttachRX_ISRCallback(void (*RXISRFunction)()) { RXCallBack = UDRECallBack; }

	void ISRTransmitUDRE(void);
	void ISRRecieveRX(void);

	static void (*UDRECallBack)();
	static void (*RXCallBack)();
	static void ISRDefualt() {}

	static uint8_t *OutputSerialBuffer;
	static size_t SizeOfOutputSerialBuffer, SizeOfOutputSerialBufferCounter;

	static uint8_t *InputSerialBuffer;
	static size_t SizeOfInputSerialBuffer, SizeOfInputSerialBufferCounter;
};

extern ArduinoSerial2Class ArduinoSerial2;
#endif
#ifdef Arduino_Serial3
class ArduinoSerial3Class
{
public:
	ArduinoSerial3Class;
	void SerialInitialize(uint32_t BaudRate);
	uint16_t AvailableForRead(void);
	static void Write(uint8_t *BufferForTransmit, size_t SizeOfBufferForTransmit);
	uint8_t Read(void);
	void ReadBytes(uint8_t *BufferForRecieve, size_t NumberOfBytesForRecieve);
	inline void AttachUDRE_ISRCallback(void (*UDREISRFunction)()) { UDRECallBack = UDREISRFunction; }
	inline void AttachRX_ISRCallback(void (*RXISRFunction)()) { RXCallBack = UDRECallBack; }

	void ISRTransmitUDRE(void);
	void ISRRecieveRX(void);

	static void (*UDRECallBack)();
	static void (*RXCallBack)();
	static void ISRDefualt() {}

	static uint8_t *OutputSerialBuffer;
	static size_t SizeOfOutputSerialBuffer, SizeOfOutputSerialBufferCounter;

	static uint8_t *InputSerialBuffer;
	static size_t SizeOfInputSerialBuffer, SizeOfInputSerialBufferCounter;
};
extern ArduinoSerial3Class ArduinoSerial3;
#endif
#ifdef Arduino_Timer4
class ArduinoTimer4Class
{
public:
	ArduinoTimer4Class;
	void OverFlowModeInitilaize(bool TimerOverFlowInterrupt = true);
	void ComparisonModeInitialize(uint32_t TimerPeriodMS = 1000, bool TimerComparisionInterrupt = true);
	void InputCaptureModeInitialize(bool InputCaptureInterrupt = true, bool RisingMode = true, bool NoiseCanceler = false);
	bool ComparisionDone(void) { return (TIFR5 & (1 << OCF5A)); }
	bool InputCaptureDone(void) { return (TIFR5 & (1 << ICF5)); }
	float InputCaptureDutyCycleInPercentage(void) { return ((float)PW / (float)(PW + SW) * 100); }
	uint32_t InputCaptureFrequency(void) { return ((float)TimerFrequency / ((float)(PW + SW) + 1)); }
	void TimerStart(void);
	void TimerStop(void);
	inline void ISRTimer(void) { TimerOverFlowCounter++; };
	inline void ISRInputCaptureCAPT(void)
	{
		if (TCCR4B & (1 << ICES4))
		{
			SW = ICR4 + TimerOverFlowCounter * OCR4A - PreviousICRValue;
			PreviousICRValue = ICR4;
			TimerOverFlowCounter = 0;
			TCCR4B &= ~(1 << ICES4);
			InputCaptureFlag = true;
		}
		else
		{
			PW = ICR4 + TimerOverFlowCounter * OCR4A - PreviousICRValue;
			PreviousICRValue = ICR4;
			TimerOverFlowCounter = 0;
			TCCR4B |= (1 << ICES4);
		}
	}

	inline void AttachTimerOVF_ISRCallback(void *TimerOVFISRFunction()) { TimerOVFCallBack = TimerOVFISRFunction; }
	inline void AttachTimerCOMPA_ISRCallback(void *TimerCOMPAISRFunction()) { TimerCOMPACallBack = TimerCOMPAISRFunction; }
	inline void AttachTimerCAPT_ISRCallback(void *TimerCAPTISRFunction()) { TimerCAPTCallBack = TimerCAPTISRFunction; }

	static void (*TimerOVFCallBack)();
	static void (*TimerCOMPACallBack)();
	static void (*TimerCAPTCallBack)();
	static void ISRDefualt() {}

private:
	bool OverFlowEnableFlag = false, ComparisionEnableFlag = false, InpubCaptureEnableFlag = false;
	uint32_t TimerFrequency;
	uint32_t PW = 0, SW = 0;
	uint16_t PreviousICRValue = 0;
	bool InputCaptureFlag = false;
	uint32_t TimerOverFlowCounter = 0;
};
extern ArduinoTimer4Class ArduinoTimer4;
#endif
#ifdef Arduino_Timer5
class ArduinoTimer5Class
{
public:
	ArduinoTimer5Class;
	void OverFlowModeInitilaize(bool TimerOverFlowInterrupt = true);
	void PWMModeInitilize(float DutyCycleInPercentage = 50, uint16_t PwmFrecuency = 25000); // beta
	void ComparisonModeInitialize(uint32_t TimerPeriodMS = 1000, bool TimerComparisionInterrupt = true);
	void InputCaptureModeInitialize(bool InputCaptureInterrupt = true, bool RisingMode = true, bool NoiseCanceler = false);
	bool ComparisionDone(void) { return (TIFR5 & (1 << OCF5A)); }
	bool InputCaptureDone(void) { return (TIFR5 & (1 << ICF5)); }
	float InputCaptureDutyCycleInPercentage(void) { return ((float)PW / (float)(PW + SW) * 100); }
	uint32_t InputCaptureFrequency(void) { return ((float)TimerFrequency / ((float)(PW + SW) + 1)); }
	void TimerStart(void);
	void TimerStop(void);
	inline void ISRTimer(void) { TimerOverFlowCounter++; }
	inline void ISRInputCaptureCAPT(void)
	{
		if (TCCR5B & (1 << ICES5))
		{
			SW = ICR5 + TimerOverFlowCounter * OCR5A - PreviousICRValue;
			PreviousICRValue = ICR5;
			TimerOverFlowCounter = 0;
			TCCR5B &= ~(1 << ICES5);
			InputCaptureFlag = true;
		}
		else
		{
			PW = ICR5 + TimerOverFlowCounter * OCR5A - PreviousICRValue;
			PreviousICRValue = ICR5;
			TimerOverFlowCounter = 0;
			TCCR5B |= (1 << ICES5);
		}
	}

	inline void AttachTimerOVF_ISRCallback(void (*TimerOVFISRFunction)()) { TimerOVFCallBack = TimerOVFISRFunction; }
	inline void AttachTimerCOMPA_ISRCallback(void (*TimerCOMPAISRFunction)()) { TimerCOMPACallBack = TimerCOMPAISRFunction; }
	inline void AttachTimerCAPT_ISRCallback(void (*TimerCAPTISRFunction)()) { TimerCAPTCallBack = TimerCAPTISRFunction; }

	static void (*TimerOVFCallBack)();
	static void (*TimerCOMPACallBack)();
	static void (*TimerCAPTCallBack)();
	static void ISRDefualt() {}

private:
	bool OverFlowEnableFlag = false, ComparisionEnableFlag = false, InpubCaptureEnableFlag = false;
	uint32_t TimerFrequency;
	uint32_t PW = 0, SW = 0;
	uint16_t PreviousICRValue = 0;
	bool InputCaptureFlag = false;
	uint32_t TimerOverFlowCounter = 0;
};
extern ArduinoTimer5Class ArduinoTimer5;
#endif
#ifdef Arduino_ADC
class ArduinoADCClass
{
public:
	ArduinoADCClass;
	void ADCInitialize(uint8_t NumberOfAnalogChannel = 0, uint8_t Prescaler = 2, bool ADCInterrupt = true, bool ADCAutoTriger = false);
	float CompleteStart(uint8_t NumberOfAnalogChannel);
	// below functions can be use in ADC ISR
	void StartConversion(uint8_t NumberOfAnalogChannel)
	{
		ADMUX = NumberOfAnalogChannel | (1 << REFS0);
		ADCSRA |= (1 << ADSC);
	}
	void StartConversion(void) { ADCSRA |= (1 << ADSC); }
	void ChooseChannel(uint8_t NumberOfAnalogChannel) { ADMUX = NumberOfAnalogChannel | (1 << REFS0); }
	void Stop(void) { ADCSRA &= ~(1 << ADSC); }
	// below functions are used in ADC ISR
	static uint16_t ISRADCReadInDigital(void) { return ADCW; }
	static float ISRADCRead(void) { return ((float)ADCW * 500 / 1023); }

	inline void AttachADC_ISRCallback(void (*ADCISRFunction)()) { ADCCallBack = ADCISRFunction; }
	static void (*ADCCallBack)();
	static void ISRDefualt() {}
};
extern ArduinoADCClass ArduinoADC;
#endif
#ifdef Arduino_SoftwareFunctions
class ArduinoSoftwareFunctionsClass
{
public:
	ArduinoSoftwareFunctionsClass;
	float InputCaptureDutyCycleInPercentage(uint8_t NumberOfPin);
	uint32_t InputCaptureFrequency(uint8_t NumberOfPin);
	//	uint16_t EncoderCounter ( uint8_t NumberOfPin );
	uint16_t EncoderSpeedRPM(uint8_t NumberOfPin, uint16_t TimeWaitingSec = 1);
};
extern ArduinoSoftwareFunctionsClass ArduinoSoftwareFunctions;
#endif
#elif
#warning "ArduinoPeripheral Library is just for Arduino Mega 2560"
#endif
#endif