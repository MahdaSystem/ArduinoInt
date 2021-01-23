#include <ArduinoPeripheral.h>

#ifdef Arduino_Serial0
ISR (USART0_RX_vect)
{
	ArduinoSerial0.ISRRecieveRX();
	ArduinoSerial0.RXCallBack();
}
ISR (USART0_UDRE_vect)
{
	ArduinoSerial0.ISRTransmitUDRE ();
	ArduinoSerial0.UDRECallBack();
}
#endif
#ifdef Arduino_Serial1
ISR (USART1_RX_vect)
{
	ArduinoSerial1.ISRRecieveRX();
	ArduinoSerial1.RXCallBack();
}
ISR (USART2_UDRE_vect)
{
	ArduinoSerial1.ISRTransmitUDRE ();
	ArduinoSerial1.UDRECallBack();
}
#endif
#ifdef Arduino_Serial2
ISR (USART2_RX_vect)
{
	ArduinoSerial2.ISRRecieveRX();
	ArduinoSerial2.RXCallBack();
}
ISR (USART2_UDRE_vect)
{
	ArduinoSerial2.ISRTransmitUDRE ();
	ArduinoSerial2.UDRECallBack();
}
#endif
#ifdef Arduino_Serial3
ISR (USART3_RX_vect)
{
	ArduinoSerial3.ISRRecieveRX();
	ArduinoSerial3.RXCallBack();
}
ISR (USART3_UDRE_vect)
{
	ArduinoSerial3.ISRTransmitUDRE ();
	ArduinoSerial3.UDRECallBack();
}
#endif
#ifdef Arduino_Timer4
ISR (TIMER4_OVF_vect)
{ 
  ArduinoTimer4.ISRTimer();
  ArduinoTimer4.TimerOVFCallBack();
}
ISR (TIMER4_COMPA_vect)
{
  ArduinoTimer4.ISRTimer();
  ArduinoTimer4.TimerCOMPACallBack();
}
ISR (TIMER4_CAPT_vect) 
{
  ArduinoTimer4.ISRInputCaptureCAPT();
  ArduinoTimer4.TimerCAPTCallBack();
}
#endif
#ifdef Arduino_Timer5
ISR (TIMER5_OVF_vect)
{ 
  ArduinoTimer5.ISRTimer();
  ArduinoTimer5.TimerOVFCallBack();
}
ISR (TIMER5_COMPA_vect) 
{     
//  ArduinoADC.StartConversion();     // Start converting ADC
  ArduinoTimer5.ISRTimer();
  ArduinoTimer5.TimerCOMPACallBack();
}
ISR (TIMER5_CAPT_vect) 
{
  ArduinoTimer5.ISRInputCaptureCAPT();
  ArduinoTimer5.TimerCAPTCallBack();
}
#endif
#ifdef Arduino_ADC
ISR (ADC_vect)
{ 
	ArduinoADC.ADCCallBack();
}
#endif