/*
  Blink whit timer no delay, whit callback

  Turns an LED on for one second, then off for n time, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.
  Used and modified by Ferney Berrio

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/
#include <timFabz.h>  // libreria para retardos sin delay
TimFabz timBlink;     // declaración objeto de la clase
void blink();         //declarar función a ejecutar cunado cumpla tiempo

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  //timBlink.setSetPoint(500);  // fijar periodo antirrebote
  timBlink.setCallBack(blink);  //definir función a ejecutar cunato cumpla tiempo timer
}

// the loop function runs over and over again forever
void loop() {
  timBlink.update();  // siempre contando
}

void blink() {
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));  // turn the LED on/off
  timBlink.reset();                                      //reiniciar timer
}

