/* ejemplo uso de multiples timer con retardos sin delay, a diferentes
  frecuencias y con el uso de callback.
  @autor: Ferney Berrio Z
 */
#include <timFabz.h>  // libreria para retardos sin delay
TimFabz tim1;         // declaración objeto de la clase
TimFabz tim2;         // declaración objeto de la clase
TimFabz tim3;         // declaración objeto de la clase
TimFabz tim4;         // declaración objeto de la clase

void blink1();  //declarar función a ejecutar cunado cumpla tiempo
void blink2();  //declarar función a ejecutar cunado cumpla tiempo
void blink3();  //declarar función a ejecutar cunado cumpla tiempo
void blink4();  //declarar función a ejecutar cunado cumpla tiempo

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  tim1.setSetPoint(1000);    // fijar periodo antirrebote
  tim1.setCallBack(blink1);  //definir función a ejecutar cunato cumpla tiempo timer
  tim2.setSetPoint(2000);    // fijar periodo antirrebote
  tim2.setCallBack(blink2);  //definir función a ejecutar cunato cumpla tiempo timer
  tim3.setSetPoint(3000);    // fijar periodo antirrebote
  tim3.setCallBack(blink3);  //definir función a ejecutar cunato cumpla tiempo timer
  tim4.setSetPoint(4000);    // fijar periodo antirrebote
  tim4.setCallBack(blink4);  //definir función a ejecutar cunato cumpla tiempo timer
}

// the loop function runs over and over again forever
void loop() {
  tim1.update();  // siempre contando
  tim2.update();  // siempre contando
  tim3.update();  // siempre contando
  tim4.update();  // siempre contando
}

void blink1() {
  Serial.println("blink 1");
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));  // turn the LED on/off
  tim1.standBy();                                        // detener timer
}

void blink2() {
  Serial.println("blink 2");
  tim2.standBy();  // detener timer
}

void blink3() {
  Serial.println("blink 3");
  tim3.standBy();  // detener timer
}

void blink4() {
  Serial.println("blink 4");
  tim1.reset();  //reiniciar timer
  tim2.reset();  //reiniciar timer
  tim3.reset();  //reiniciar timer
  tim4.reset();  //reiniciar timer
}
