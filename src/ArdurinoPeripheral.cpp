#include <ArduinoPeripheral.h>

#if defined(__AVR_ATmega2560__)

#ifdef Arduino_Serial0

	ArduinoSerial0Class ArduinoSerial0;
	
	void (*ArduinoSerial0Class::UDRECallBack )() = ArduinoSerial0Class::ISRDefualt;
	void (*ArduinoSerial0Class::RXCallBack )() = ArduinoSerial0Class::ISRDefualt;
	
	uint8_t *ArduinoSerial0Class::OutputSerialBuffer =0;
	size_t ArduinoSerial0Class::SizeOfOutputSerialBuffer =0 ,ArduinoSerial0Class::SizeOfOutputSerialBufferCounter =0;

	uint8_t *ArduinoSerial0Class::InputSerialBuffer =0;
	size_t ArduinoSerial0Class::SizeOfInputSerialBuffer =0 ,ArduinoSerial0Class::SizeOfInputSerialBufferCounter =0;
	
	void ArduinoSerial0Class::SerialInitialize ( uint32_t BaudRate )
	{
		UCSR0A = (0<<RXC0)|(0<<TXC0)|(0<<UDRE0)|(0<<FE0)|(0<<DOR0)|(0<<UPE0)|(0<<U2X0)|(0<<MPCM0);
		UCSR0B = (1<<RXCIE0)|(0<<TXCIE0)|(0<<UDRIE0)|(1<<RXEN0)|(1<<TXEN0)|(0<<UCSZ02)|(0<<RXB80)|(0<<TXB80);
		UCSR0C = (0<<UMSEL01)|(0<<UMSEL00)|(0<<UPM01)|(0<<UPM00)|(0<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00)|(0<<UCPOL0);
		UBRR0 = F_CPU/(16*(BaudRate+1));

		InputSerialBuffer = (uint8_t *)malloc((sizeof(uint8_t) * 512));
	}
	
	uint16_t ArduinoSerial0Class::AvailableForRead ( void )
	{
		if  ( SizeOfInputSerialBufferCounter < SizeOfInputSerialBuffer )
			return SizeOfInputSerialBuffer - SizeOfInputSerialBufferCounter;
		return 0;	
	}
	
	static void ArduinoSerial0Class::Write ( uint8_t *BufferForTransmit , size_t SizeOfBufferForTransmit )
	{

		if ( !(UCSR0B & (1<<UDRIE0)) )
		{
			OutputSerialBuffer = (uint8_t *)malloc((sizeof(uint8_t) * SizeOfBufferForTransmit));
			memcpy(OutputSerialBuffer,BufferForTransmit,SizeOfBufferForTransmit);
			SizeOfOutputSerialBuffer = SizeOfBufferForTransmit;
			UCSR0B |= (1<<UDRIE0);
		}
		else if (SizeOfOutputSerialBuffer < 1024)
		{
			realloc(OutputSerialBuffer,(sizeof(uint8_t)) * (SizeOfBufferForTransmit + SizeOfOutputSerialBuffer) );
			memcpy(&OutputSerialBuffer[SizeOfOutputSerialBuffer] ,BufferForTransmit,SizeOfBufferForTransmit);
			SizeOfOutputSerialBuffer = SizeOfOutputSerialBuffer + SizeOfBufferForTransmit;
		}

	}

	uint8_t ArduinoSerial0Class::Read ( void )
	{
		if  ( SizeOfInputSerialBufferCounter < SizeOfInputSerialBuffer )
		{
			SizeOfInputSerialBufferCounter++;
			return InputSerialBuffer[SizeOfInputSerialBufferCounter-1];
		}
		else if ( (SizeOfInputSerialBuffer == SizeOfInputSerialBufferCounter) && ( SizeOfInputSerialBuffer != 0 ))
		{
		  SizeOfInputSerialBuffer =0;
		  SizeOfInputSerialBufferCounter =0;
		  realloc ( InputSerialBuffer , (sizeof(uint8_t)) * (SizeOfInputSerialBuffer + 512));
		}
		return 0;
	}
	
	void ArduinoSerial0Class::ReadBytes ( uint8_t *BufferForRecieve , size_t NumberOfBytesForRecieve )
	{
		while ( SizeOfInputSerialBufferCounter < NumberOfBytesForRecieve )
		{
			BufferForRecieve[SizeOfInputSerialBufferCounter]=InputSerialBuffer[SizeOfInputSerialBufferCounter];
			SizeOfInputSerialBufferCounter++;
		}
		if ( (SizeOfInputSerialBuffer == SizeOfInputSerialBufferCounter) && ( SizeOfInputSerialBuffer != 0 ))
		{
		  SizeOfInputSerialBuffer =0;
		  SizeOfInputSerialBufferCounter =0;
		  realloc ( InputSerialBuffer , (sizeof(uint8_t)) * (SizeOfInputSerialBuffer + 512));
		}
	}
	
	void ArduinoSerial0Class::ISRTransmitUDRE ( void )
	{

		if ( SizeOfOutputSerialBufferCounter < SizeOfOutputSerialBuffer )
		{
			UDR0 = OutputSerialBuffer[SizeOfOutputSerialBufferCounter];
			SizeOfOutputSerialBufferCounter++;
		}
		else
		{
			free (OutputSerialBuffer);
			SizeOfOutputSerialBufferCounter = 0;
			UCSR0B &= ~(1<<UDRIE0);
		}
	}
	
	void ArduinoSerial0Class::ISRRecieveRX ( void )
	{		
		InputSerialBuffer[SizeOfInputSerialBuffer] = UDR0;
		SizeOfInputSerialBuffer++;
		if ( SizeOfInputSerialBuffer >= 512 )
		realloc ( InputSerialBuffer , (sizeof(uint8_t)) * (SizeOfInputSerialBuffer + 1));
	}
	
#endif
#ifdef Arduino_Serial1

	ArduinoSerial1Class ArduinoSerial1;
	
	void (*ArduinoSerial1Class::UDRECallBack )() = ArduinoSerial1Class::ISRDefualt;
	void (*ArduinoSerial1Class::RXCallBack )() = ArduinoSerial1Class::ISRDefualt;

	uint8_t *ArduinoSerial1Class::OutputSerialBuffer =0;
	size_t ArduinoSerial1Class::SizeOfOutputSerialBuffer =0,ArduinoSerial1Class::SizeOfOutputSerialBufferCounter =0 ;

	uint8_t *ArduinoSerial1Class::InputSerialBuffer =0;
	size_t ArduinoSerial1Class::SizeOfInputSerialBuffer =0,ArduinoSerial1Class::SizeOfInputSerialBufferCounter =0;
	
	void ArduinoSerial1Class::SerialInitialize ( uint32_t BaudRate )
	{
		UCSR1A = (0<<RXC1)|(0<<TXC1)|(0<<UDRE1)|(0<<FE1)|(0<<DOR1)|(0<<UPE1)|(0<<U2X1)|(0<<MPCM1);
		UCSR1B = (1<<RXCIE1)|(0<<TXCIE1)|(0<<UDRIE1)|(1<<RXEN1)|(1<<TXEN1)|(0<<UCSZ12)|(0<<RXB81)|(0<<TXB81);
		UCSR1C = (0<<UMSEL11)|(0<<UMSEL10)|(0<<UPM11)|(0<<UPM10)|(0<<USBS1)|(1<<UCSZ11)|(1<<UCSZ10)|(0<<UCPOL1);
		UBRR1 = F_CPU/(16*(BaudRate+1));
		
		InputSerialBuffer = (uint8_t *)malloc((sizeof(uint8_t) * 512));
	}
	
	uint16_t ArduinoSerial1Class::AvailableForRead ( void )
	{
		if  ( SizeOfInputSerialBufferCounter < SizeOfInputSerialBuffer )
			return SizeOfInputSerialBuffer - SizeOfInputSerialBufferCounter;
		return 0;	
	}
	
	static void ArduinoSerial1Class::Write ( uint8_t *BufferForTransmit , size_t SizeOfBufferForTransmit )
	{
		if ( !(UCSR1B & (1<<UDRIE1)) )
		{
			OutputSerialBuffer = (uint8_t *)malloc((sizeof(uint8_t) * SizeOfBufferForTransmit));
			memcpy(OutputSerialBuffer,BufferForTransmit,SizeOfBufferForTransmit);
			SizeOfOutputSerialBuffer = SizeOfBufferForTransmit;
			UCSR1B |= (1<<UDRIE1);
		}
		else if (SizeOfOutputSerialBuffer < 1024)
		{
			realloc(OutputSerialBuffer,(sizeof(uint8_t)) * (SizeOfBufferForTransmit + SizeOfOutputSerialBuffer) );
			memcpy(&OutputSerialBuffer[SizeOfOutputSerialBuffer] ,BufferForTransmit,SizeOfBufferForTransmit);
			SizeOfOutputSerialBuffer = SizeOfOutputSerialBuffer + SizeOfBufferForTransmit;
		}
	}

	uint8_t ArduinoSerial1Class::Read ( void )
	{
		if  ( SizeOfInputSerialBufferCounter < SizeOfInputSerialBuffer )
		{
			SizeOfInputSerialBufferCounter++;
			return InputSerialBuffer[SizeOfInputSerialBufferCounter-1];
		}
		else if ( (SizeOfInputSerialBuffer == SizeOfInputSerialBufferCounter) && ( SizeOfInputSerialBuffer != 0 ))
		{
		  SizeOfInputSerialBuffer =0;
		  SizeOfInputSerialBufferCounter =0;
		  realloc ( InputSerialBuffer , (sizeof(uint8_t)) * (SizeOfInputSerialBuffer + 512));
		}
		return 0;
	}
	
	void ArduinoSerial1Class::ReadBytes ( uint8_t *BufferForRecieve , size_t NumberOfBytesForRecieve )
	{
		while ( SizeOfInputSerialBufferCounter < NumberOfBytesForRecieve )
		{
			BufferForRecieve[SizeOfInputSerialBufferCounter]=InputSerialBuffer[SizeOfInputSerialBufferCounter];
			SizeOfInputSerialBufferCounter++;
		}
		if ( (SizeOfInputSerialBuffer == SizeOfInputSerialBufferCounter) && ( SizeOfInputSerialBuffer != 0 ))
		{
		  SizeOfInputSerialBuffer =0;
		  SizeOfInputSerialBufferCounter =0;
		  realloc ( InputSerialBuffer , (sizeof(uint8_t)) * (SizeOfInputSerialBuffer + 512));
		}
	}
	
	void ArduinoSerial1Class::ISRTransmitUDRE ( void )
	{

		if ( SizeOfOutputSerialBufferCounter < SizeOfOutputSerialBuffer )
		{
			UDR1 = OutputSerialBuffer[SizeOfOutputSerialBufferCounter];
			SizeOfOutputSerialBufferCounter++;
		}
		else
		{
			free (OutputSerialBuffer);
			SizeOfOutputSerialBufferCounter = 0;
			UCSR1B &= ~(1<<UDRIE1);
		}			
	}
	
	void ArduinoSerial1Class::ISRRecieveRX ( void )
	{		
		InputSerialBuffer[SizeOfInputSerialBuffer] = UDR1;
		SizeOfInputSerialBuffer++;
		if ( SizeOfInputSerialBuffer >= 512 )
		realloc ( InputSerialBuffer , (sizeof(uint8_t)) * (SizeOfInputSerialBuffer + 1));
	}

#endif	
#ifdef Arduino_Serial2
	
	ArduinoSerial2Class ArduinoSerial2;
	
	void (*ArduinoSerial2Class::UDRECallBack )() = ArduinoSerial2Class::ISRDefualt;
	void (*ArduinoSerial2Class::RXCallBack )() = ArduinoSerial2Class::ISRDefualt;
	
	uint8_t *ArduinoSerial2Class::OutputSerialBuffer =0;
	size_t ArduinoSerial2Class::SizeOfOutputSerialBuffer =0,ArduinoSerial2Class::SizeOfOutputSerialBufferCounter =0;

	uint8_t *ArduinoSerial2Class::InputSerialBuffer =0;
	size_t ArduinoSerial2Class::SizeOfInputSerialBuffer =0,ArduinoSerial2Class::SizeOfInputSerialBufferCounter =0;
	
	void ArduinoSerial2Class::SerialInitialize ( uint32_t BaudRate )
	{
		UCSR2A = (0<<RXC2)|(0<<TXC2)|(0<<UDRE2)|(0<<FE2)|(0<<DOR2)|(0<<UPE2)|(0<<U2X2)|(0<<MPCM2);
		UCSR2B = (1<<RXCIE2)|(0<<TXCIE2)|(0<<UDRIE2)|(1<<RXEN2)|(1<<TXEN2)|(0<<UCSZ22)|(0<<RXB82)|(0<<TXB82);
		UCSR2C = (0<<UMSEL21)|(0<<UMSEL20)|(0<<UPM21)|(0<<UPM20)|(0<<USBS2)|(1<<UCSZ21)|(1<<UCSZ20)|(0<<UCPOL2);
		UBRR2 = F_CPU/(16*(BaudRate+1));
		
		InputSerialBuffer = (uint8_t *)malloc((sizeof(uint8_t) * 512));
	}
	
	uint16_t ArduinoSerial2Class::AvailableForRead ( void )
	{
		if  ( SizeOfInputSerialBufferCounter < SizeOfInputSerialBuffer )
			return SizeOfInputSerialBuffer - SizeOfInputSerialBufferCounter;
		return 0;	
	}
	
	static void ArduinoSerial2Class::Write ( uint8_t *BufferForTransmit , size_t SizeOfBufferForTransmit )
	{

		if ( !(UCSR2B & (1<<UDRIE2)) )
		{
			OutputSerialBuffer = (uint8_t *)malloc((sizeof(uint8_t) * SizeOfBufferForTransmit));
			memcpy(OutputSerialBuffer,BufferForTransmit,SizeOfBufferForTransmit);
			SizeOfOutputSerialBuffer = SizeOfBufferForTransmit;
			UCSR2B |= (1<<UDRIE2);
		}
		else if (SizeOfOutputSerialBuffer < 1024)
		{
			realloc(OutputSerialBuffer,(sizeof(uint8_t)) * (SizeOfBufferForTransmit + SizeOfOutputSerialBuffer) );
			memcpy(&OutputSerialBuffer[SizeOfOutputSerialBuffer] ,BufferForTransmit,SizeOfBufferForTransmit);
			SizeOfOutputSerialBuffer = SizeOfOutputSerialBuffer + SizeOfBufferForTransmit;
		}

	}

	uint8_t ArduinoSerial2Class::Read ( void )
	{
		if  ( SizeOfInputSerialBufferCounter < SizeOfInputSerialBuffer )
		{
			SizeOfInputSerialBufferCounter++;
			return InputSerialBuffer[SizeOfInputSerialBufferCounter-1];
		}
		else if ( (SizeOfInputSerialBuffer == SizeOfInputSerialBufferCounter) && ( SizeOfInputSerialBuffer != 0 ))
		{
		  SizeOfInputSerialBuffer =0;
		  SizeOfInputSerialBufferCounter =0;
		  realloc ( InputSerialBuffer , (sizeof(uint8_t)) * (SizeOfInputSerialBuffer + 512));
		}
		return 0;
	}
	
	void ArduinoSerial2Class::ReadBytes ( uint8_t *BufferForRecieve , size_t NumberOfBytesForRecieve )
	{
		while ( SizeOfInputSerialBufferCounter < NumberOfBytesForRecieve )
		{
			BufferForRecieve[SizeOfInputSerialBufferCounter]=InputSerialBuffer[SizeOfInputSerialBufferCounter];
			SizeOfInputSerialBufferCounter++;
		}
		if ( (SizeOfInputSerialBuffer == SizeOfInputSerialBufferCounter) && ( SizeOfInputSerialBuffer != 0 ))
		{
		  SizeOfInputSerialBuffer =0;
		  SizeOfInputSerialBufferCounter =0;
		  realloc ( InputSerialBuffer , (sizeof(uint8_t)) * (SizeOfInputSerialBuffer + 512));
		}
	}
	
	void ArduinoSerial2Class::ISRTransmitUDRE ( void )
	{

		if ( SizeOfOutputSerialBufferCounter < SizeOfOutputSerialBuffer )
		{
			UDR2 = OutputSerialBuffer[SizeOfOutputSerialBufferCounter];
			SizeOfOutputSerialBufferCounter++;
		}
		else
		{
			free (OutputSerialBuffer);
			SizeOfOutputSerialBufferCounter = 0;
			UCSR2B &= ~(1<<UDRIE2);
		}
			
	}
	
	void ArduinoSerial2Class::ISRRecieveRX ( void )
	{		
		InputSerialBuffer[SizeOfInputSerialBuffer] = UDR2;
		SizeOfInputSerialBuffer++;
		if ( SizeOfInputSerialBuffer >= 512 )
		realloc ( InputSerialBuffer , (sizeof(uint8_t)) * (SizeOfInputSerialBuffer + 1));
	}

#endif
#ifdef Arduino_Serial3

	ArduinoSerial3Class ArduinoSerial3;
	
	void (*ArduinoSerial3Class::UDRECallBack )() = ArduinoSerial3Class::ISRDefualt;
	void (*ArduinoSerial3Class::RXCallBack )() = ArduinoSerial3Class::ISRDefualt;

	uint8_t *ArduinoSerial3Class::OutputSerialBuffer =0;
	size_t ArduinoSerial3Class::SizeOfOutputSerialBuffer =0,ArduinoSerial3Class::SizeOfOutputSerialBufferCounter =0;

	uint8_t *ArduinoSerial3Class::InputSerialBuffer =0;
	size_t ArduinoSerial3Class::SizeOfInputSerialBuffer =0,ArduinoSerial3Class::SizeOfInputSerialBufferCounter =0;
	
	void ArduinoSerial3Class::SerialInitialize ( uint32_t BaudRate )
	{
		UCSR3A = (0<<RXC3)|(0<<TXC3)|(0<<UDRE3)|(0<<FE3)|(0<<DOR3)|(0<<UPE3)|(0<<U2X3)|(0<<MPCM3);
		UCSR3B = (1<<RXCIE3)|(0<<TXCIE3)|(0<<UDRIE3)|(1<<RXEN3)|(1<<TXEN3)|(0<<UCSZ32)|(0<<RXB83)|(0<<TXB83);
		UCSR3C = (0<<UMSEL31)|(0<<UMSEL30)|(0<<UPM31)|(0<<UPM30)|(0<<USBS3)|(1<<UCSZ31)|(1<<UCSZ30)|(0<<UCPOL3);
		UBRR3 = F_CPU/(16*(BaudRate+1));

		InputSerialBuffer = (uint8_t *)malloc((sizeof(uint8_t) * 512));
	}
	
	uint16_t ArduinoSerial3Class::AvailableForRead ( void )
	{
		if  ( SizeOfInputSerialBufferCounter < SizeOfInputSerialBuffer )
			return SizeOfInputSerialBuffer - SizeOfInputSerialBufferCounter;
		return 0;	
	}
	
	static void ArduinoSerial3Class::Write ( uint8_t *BufferForTransmit , size_t SizeOfBufferForTransmit )
	{

		if ( !(UCSR3B & (1<<UDRIE3)) )
		{
			OutputSerialBuffer = (uint8_t *)malloc((sizeof(uint8_t) * SizeOfBufferForTransmit));
			memcpy(OutputSerialBuffer,BufferForTransmit,SizeOfBufferForTransmit);
			SizeOfOutputSerialBuffer = SizeOfBufferForTransmit;
			UCSR3B |= (1<<UDRIE3);
		}
		else if (SizeOfOutputSerialBuffer < 1024)
		{
			realloc(OutputSerialBuffer,(sizeof(uint8_t)) * (SizeOfBufferForTransmit + SizeOfOutputSerialBuffer) );
			memcpy(&OutputSerialBuffer[SizeOfOutputSerialBuffer] ,BufferForTransmit,SizeOfBufferForTransmit);
			SizeOfOutputSerialBuffer = SizeOfOutputSerialBuffer + SizeOfBufferForTransmit;
		}

	}

	uint8_t ArduinoSerial3Class::Read ( void )
	{
		if  ( SizeOfInputSerialBufferCounter < SizeOfInputSerialBuffer )
		{
			SizeOfInputSerialBufferCounter++;
			return InputSerialBuffer[SizeOfInputSerialBufferCounter-1];
		}
		else if ( (SizeOfInputSerialBuffer == SizeOfInputSerialBufferCounter) && ( SizeOfInputSerialBuffer != 0 ))
		{
		  SizeOfInputSerialBuffer =0;
		  SizeOfInputSerialBufferCounter =0;
		  realloc ( InputSerialBuffer , (sizeof(uint8_t)) * (SizeOfInputSerialBuffer + 512));
		}
		return 0;
	}
	
	void ArduinoSerial3Class::ReadBytes ( uint8_t *BufferForRecieve , size_t NumberOfBytesForRecieve )
	{
		while ( SizeOfInputSerialBufferCounter < NumberOfBytesForRecieve )
		{
			BufferForRecieve[SizeOfInputSerialBufferCounter]=InputSerialBuffer[SizeOfInputSerialBufferCounter];
			SizeOfInputSerialBufferCounter++;
		}
		if ( (SizeOfInputSerialBuffer == SizeOfInputSerialBufferCounter) && ( SizeOfInputSerialBuffer != 0 ))
		{
		  SizeOfInputSerialBuffer =0;
		  SizeOfInputSerialBufferCounter =0;
		  realloc ( InputSerialBuffer , (sizeof(uint8_t)) * (SizeOfInputSerialBuffer + 512));
		}
	}
	
	void ArduinoSerial3Class::ISRTransmitUDRE ( void )
	{

		if ( SizeOfOutputSerialBufferCounter < SizeOfOutputSerialBuffer )
		{
			UDR3 = OutputSerialBuffer[SizeOfOutputSerialBufferCounter];
			SizeOfOutputSerialBufferCounter++;
		}
		else
		{
			free (OutputSerialBuffer);
			SizeOfOutputSerialBufferCounter = 0;
			UCSR3B &= ~(1<<UDRIE3);
		}
			
	}
	
	void ArduinoSerial3Class::ISRRecieveRX ( void )
	{		
		InputSerialBuffer[SizeOfInputSerialBuffer] = UDR3;
		SizeOfInputSerialBuffer++;
		if ( SizeOfInputSerialBuffer >= 512 )
		realloc ( InputSerialBuffer , (sizeof(uint8_t)) * (SizeOfInputSerialBuffer + 1));
	}
	
#endif
#ifdef Arduino_Timer4

	ArduinoTimer4Class ArduinoTimer4;
	
	void (*ArduinoTimer4Class::TimerOVFCallBack)() = ArduinoTimer4Class::ISRDefualt;
	void (*ArduinoTimer4Class::TimerCOMPACallBack)() = ArduinoTimer4Class::ISRDefualt;
	void (*ArduinoTimer4Class::TimerCAPTCallBack)() = ArduinoTimer4Class::ISRDefualt;

	void ArduinoTimer4Class::OverFlowModeInitilaize ( bool TimerOverFlowInterrupt = true )
	{
		OverFlowEnableFlag = TimerOverFlowInterrupt;
		TCCR4A = 0;
		TCCR4B = (0<<CS42)|(0<<CS41)|(1<<CS40);
		TimerFrequency = F_CPU;
		OCR4A = 0xffff;
	}
	void ArduinoTimer4Class::ComparisonModeInitialize ( uint32_t TimerPeriodMS = 1000 , bool TimerComparisionInterrupt = true )
	{
		ComparisionEnableFlag = TimerComparisionInterrupt;
		TCCR4A = (0<<WGM41)|(0<<WGM40);
		TCCR4B = (1<<WGM42);
		
		if ( (TimerPeriodMS*16000 - 1) <= 0xffff )
		{
			TimerFrequency = F_CPU/1;
			TCCR4B |= (0<<CS42)|(0<<CS41)|(1<<CS40);
			OCR4A = (TimerPeriodMS*16000 - 1);
		}
		else if ( (TimerPeriodMS*2000 - 1) <= 0xffff )
		{
			TimerFrequency = F_CPU/8;
			TCCR4B |= (0<<CS42)|(1<<CS41)|(0<<CS40);
			OCR4A = (TimerPeriodMS*2000 - 1);
		}
		else if ( (TimerPeriodMS*250 - 1) <= 0xffff )
		{
			TimerFrequency = F_CPU/64;
			TCCR4B |= (0<<CS42)|(1<<CS41)|(1<<CS40);
			OCR4A = (TimerPeriodMS*250 - 1);
		}
		else if ( (TimerPeriodMS*62.5 - 1) <= 0xffff )
		{
			TimerFrequency = F_CPU/256;
			TCCR4B |= (1<<CS42)|(0<<CS41)|(0<<CS40);
			OCR4A = (uint16_t)(TimerPeriodMS*62.5 - 1);
		}
		else if ( (TimerPeriodMS*15.625 - 1) <= 0xffff )
		{
			TimerFrequency = F_CPU/1024;
			TCCR4B |= (1<<CS42)|(1<<CS41)|(0<<CS40);
			OCR4A = (uint16_t)(TimerPeriodMS*15.625 - 1);
		}
		else
			OCR4A = 0xffff;
		
		TCNT4 = 0;
		// OCR4A = (uint16_t)(TimerPeriodMS*((double)(F_CPU/(Prescal*1000))) - 1);
		// TIMSK4 |= (TimerComparisionInterrupt<<OCIE4A);
	}
	void ArduinoTimer4Class::InputCaptureModeInitialize  ( bool InputCaptureInterrupt = true , bool RisingMode = true , bool NoiseCanceler = false)
	{
		InpubCaptureEnableFlag = InputCaptureInterrupt;
		TCCR4B |= (RisingMode<<ICES4)|(NoiseCanceler<<ICNC4);
		// TIMSK4 |= (InputCaptureInterrupt<<ICIE4);
	}
	void ArduinoTimer4Class::TimerStart ( void )
	{
		if (OverFlowEnableFlag)
			TIMSK4 |= (1<<TOIE4);       // Enable Timer comparison & InputCapture Intterupt
		if (ComparisionEnableFlag)
			TIMSK4 |= (1<<OCIE4A);
		if (InpubCaptureEnableFlag)
			TIMSK4 |= (1<<ICIE4);
		
		TCNT4 = 0;
		TimerOverFlowCounter = 0;
		PW = 0;
		SW = 0;  
	}
	void ArduinoTimer4Class::TimerStop ( void )
	{
		
		if (OverFlowEnableFlag)
			TIMSK4 &= ~(1<<TOIE4);
		if (ComparisionEnableFlag)
			TIMSK4 &= ~(1<<OCIE4A);
		if (InpubCaptureEnableFlag)
			TIMSK4 &= ~(1<<ICIE4);
		
		TCNT4 = 0;
		TimerOverFlowCounter = 0;
		PW = 0;
		SW = 0;
	}

#endif
#ifdef Arduino_Timer5

	ArduinoTimer5Class ArduinoTimer5;
	
	void (*ArduinoTimer5Class::TimerOVFCallBack)() = ArduinoTimer5Class::ISRDefualt;
	void (*ArduinoTimer5Class::TimerCOMPACallBack)() = ArduinoTimer5Class::ISRDefualt;
	void (*ArduinoTimer5Class::TimerCAPTCallBack)() = ArduinoTimer5Class::ISRDefualt;

	void ArduinoTimer5Class::OverFlowModeInitilaize ( bool TimerOverFlowInterrupt = true )
	{
		OverFlowEnableFlag = TimerOverFlowInterrupt;
		TCCR5A = 0;
		TCCR5B = (0<<CS52)|(0<<CS51)|(1<<CS50);
		TimerFrequency = F_CPU;
		OCR5A = 0xffff;
	}
	void ArduinoTimer5Class::PWMModeInitilize ( float DutyCycleInPercentage = 50, uint16_t PwmFrecuency = 25000) // Beta
	{
		DDRL |= (1<<3);
		TCCR5A = (1<<COM5A1)|(0<<COM5A0)|(0<<WGM51)|(1<<WGM50);
		if ( PwmFrecuency >= 16000000 )
		{
			TCCR5B = (0<<WGM53)|(1<<WGM52)|(0<<CS52)|(0<<CS51)|(1<<CS50);
			OCR5A = (uint16_t)(DutyCycleInPercentage/100*0xff);
			TimerFrequency = PwmFrecuency;
		}
		else if ( PwmFrecuency == 2000000 )
		{
			TCCR5B = (0<<WGM53)|(1<<WGM52)|(0<<CS52)|(1<<CS51)|(0<<CS50);
			OCR5A = (uint16_t)(DutyCycleInPercentage/100*0xff);
			TimerFrequency = PwmFrecuency;
		}
		else if ( PwmFrecuency == 25000 )
		{
			TCCR5B = (0<<WGM53)|(1<<WGM52)|(0<<CS52)|(1<<CS51)|(1<<CS50);
			OCR5A = (uint16_t)(DutyCycleInPercentage/100*0xff);
			TimerFrequency = PwmFrecuency;
		}
		else if ( PwmFrecuency == 62500 )
		{
			TCCR5B = (0<<WGM53)|(1<<WGM52)|(1<<CS52)|(0<<CS51)|(0<<CS50);
			OCR5A = (uint16_t)(DutyCycleInPercentage/100*0xff);
			TimerFrequency = PwmFrecuency;
		}
		else if ( PwmFrecuency == 15625 )
		{
			TCCR5B = (0<<WGM53)|(1<<WGM52)|(1<<CS52)|(0<<CS51)|(1<<CS50);
			OCR5A = (uint16_t)(DutyCycleInPercentage/100*0xff);
			TimerFrequency = PwmFrecuency;
		}
		else
		{
			TCCR5B = (0<<WGM53)|(1<<WGM52)|(1<<CS52)|(0<<CS51)|(1<<CS50);
			OCR5A = 0xffff;
			TimerFrequency = 1;
		}
	}
	void ArduinoTimer5Class::ComparisonModeInitialize ( uint32_t TimerPeriodMS = 1000 , bool TimerComparisionInterrupt = true)
	{
		ComparisionEnableFlag = TimerComparisionInterrupt;
		TCCR5A = (0<<WGM51)|(0<<WGM50);
		TCCR5B = (1<<WGM52);
		
		if ( (TimerPeriodMS*16000 - 1) <= 0xffff )
		{
			TimerFrequency = F_CPU/1;
			TCCR5B |= (0<<CS52)|(0<<CS51)|(1<<CS50);
			OCR5A = (TimerPeriodMS*16000 - 1);
		}
		else if ( (TimerPeriodMS*2000 - 1) <= 0xffff )
		{
			TimerFrequency = F_CPU/8;
			TCCR5B |= (0<<CS52)|(1<<CS51)|(0<<CS50);
			OCR5A = (TimerPeriodMS*2000 - 1);
		}
		else if ( (TimerPeriodMS*250 - 1) <= 0xffff )
		{
			TimerFrequency = F_CPU/64;
			TCCR5B = (0<<CS52)|(1<<CS51)|(1<<CS50);
			OCR5A = (TimerPeriodMS*250 - 1);
		}
		else if ( (TimerPeriodMS*62.5 - 1) <= 0xffff )
		{
			TimerFrequency = F_CPU/256;
			TCCR5B |= (1<<CS52)|(0<<CS51)|(0<<CS50);
			OCR5A = (uint16_t)(TimerPeriodMS*62.5 - 1);
		}
		else if ( (TimerPeriodMS*15.625 - 1) <= 0xffff )
		{
			TimerFrequency = F_CPU/1024;
			TCCR5B |= (1<<CS52)|(0<<CS51)|(1<<CS50);
			OCR5A = (uint16_t)(TimerPeriodMS*15.625 - 1);
		}
		else
			OCR5A = 0xffff;

		TCNT5 = 0;
	}
	void ArduinoTimer5Class::InputCaptureModeInitialize  ( bool InputCaptureInterrupt = true , bool RisingMode = true , bool NoiseCanceler = false)
	{
		InpubCaptureEnableFlag = InputCaptureInterrupt;
		TCCR5B |= (RisingMode<<ICES5)|(NoiseCanceler<<ICNC5);
		// TIMSK5 |= (InputCaptureInterrupt<<ICIE5);
	}
	void ArduinoTimer5Class::TimerStart ( void )
	{
		if (OverFlowEnableFlag)
			TIMSK5 |= (1<<TOIE5);       // Enable Timer comparison & InputCapture Intterupt
		if (ComparisionEnableFlag)
			TIMSK5 |= (1<<OCIE5A);
		if (InpubCaptureEnableFlag)
			TIMSK5 |= (1<<ICIE5);
		
		TCNT5 = 0;
		TimerOverFlowCounter = 0;
		PW = 0;
		SW = 0;  
	}
	void ArduinoTimer5Class::TimerStop ( void )
	{
		
		if (OverFlowEnableFlag)
			TIMSK5 &= ~(1<<TOIE5);
		if (ComparisionEnableFlag)
			TIMSK5 &= ~(1<<OCIE5A);
		if (InpubCaptureEnableFlag)
			TIMSK5 &= ~(1<<ICIE5);
	}

#endif
#ifdef Arduino_ADC

	ArduinoADCClass ArduinoADC;
	
	void (*ArduinoADCClass::ADCCallBack)() = ArduinoADCClass::ISRDefualt;

	void ArduinoADCClass::ADCInitialize ( uint8_t NumberOfAnalogChannel = 0 , uint8_t Prescaler = 2 , bool ADCInterrupt = true , bool ADCAutoTriger = false)
	{
		uint8_t presc = 0;
		for ( int __counterpre = Prescaler ; __counterpre > 1 ; __counterpre-- )
		{
			if ( __counterpre%2 == 0 )
				presc++;
		}
		if ( presc == 1 )
			presc=2;
		//          *** ADMUX (ADC Multiplexer Selection Register)  ***
		// REF[0..1] (Reference Selection Bits) : AVCC
		// ADLAR (ADC Left Adjust Result) : Right
		// MUX[0..4] (Analog Channel and Gain Selection Bits) : 0 ( initial )
		ADMUX = (0<<REFS1)|(1<<REFS0)|(0<<ADLAR)|NumberOfAnalogChannel; 

		//          *** ADCSRA (ADC Control and Status Register A)  ***
		// ADEN (ADC Enable) : Enable
		// ADSC (ADC Start Conversion) : stop
		// ADATE (ADC Auto Trigger Enable) : off
		// ADIE (ADC Interrupt Enable) : Enable
		// ADIF (ADC Interrupt Flag) : 0
		// ADPS2[0..2] (Prescaler Select Bits) : 2
		ADCSRA = (1<<ADEN)|(0<<ADSC)|(ADCAutoTriger<<ADATE)|(0<<ADATE)|(0<<ADIF)|(ADCInterrupt<<ADIE)|presc;
	}
	float ArduinoADCClass::CompleteStart (	uint8_t NumberOfAnalogChannel )
	{
		ADMUX = NumberOfAnalogChannel|(1<<REFS0);
		ADCSRA |= (1<<ADSC);
		while ( !(ADCSRA & (1<<ADIF)) );
		return ((float)ADCW*500/1023 );
	}

#endif
#ifdef Arduino_SoftwareFunctions

	ArduinoSoftwareFunctionsClass ArduinoSoftwareFunctions;
	
	float ArduinoSoftwareFunctionsClass::InputCaptureDutyCycleInPercentage ( uint8_t NumberOfPin )
	{
		uint32_t SavePreviousTime =0,PWval=0,SWval=0;
		while ( !digitalRead(NumberOfPin) );
		SavePreviousTime = micros();
		while ( digitalRead(NumberOfPin) );
		PWval = micros() - SavePreviousTime;
		SavePreviousTime = micros();
		while ( !digitalRead(NumberOfPin) );
		SWval = micros() - SavePreviousTime;
		
		return (float)PWval/(float)(PWval+SWval)*100;
	}
	uint32_t ArduinoSoftwareFunctionsClass::InputCaptureFrequency ( uint8_t NumberOfPin )
	{
		uint32_t TimePeriod=0;
		while ( !digitalRead(NumberOfPin) );
		TimePeriod = micros();
		while ( digitalRead(NumberOfPin) );
		while ( !digitalRead(NumberOfPin) );
		TimePeriod = micros() - TimePeriod;
		
		return 1000000/TimePeriod;
	}
	uint16_t ArduinoSoftwareFunctionsClass::EncoderSpeedRPM ( uint8_t NumberOfPin ,uint16_t TimeWaitingSec = 1)
	{
		uint32_t SavePreviousTime = millis(),EncoderCounter = 0;
		while ( (millis()-SavePreviousTime) < (TimeWaitingSec*1000) )
		{
			if ( digitalRead (NumberOfPin) )
				EncoderCounter++;
		}
		return (uint16_t)((60/(float)TimeWaitingSec * EncoderCounter));
	}

#endif	

#endif