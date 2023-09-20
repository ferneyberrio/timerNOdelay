/* ejemplo uso de marcas especiales a diferentes frecuencias de oscilación.
  Típicamente para usar en salidas o elementos que requieren oscilar
  periodicamente de manera independiente y autonoma al programa principal
  @autor: Ferney Berrio Z
 */

#include <sMarkF.h>  // libreria pulsos ciclicos
SMarkF SMBlink;      // declaración objeto de la clase

int entrada = 8, Led1 = 13, Led2 = 12, Led3 = 11, Led4 = 10, Led5 = 9;
int Led[5] = { Led1, Led2, Led3, Led4, Led5 };  // matriz Led se le asignan numeros que coincidan con numero de pines ardu5

void setup() {
  // put your setup code here, to run once:
  // asignacion pines de ardu5
  pinMode(entrada, INPUT);
  for (int i = 0; i < 5; i++)  // para las 5 salidas que se estan manejando
  {
    pinMode(Led[i], OUTPUT);  // declarar como salida
    digitalWrite(Led[i], LOW);  // poner salida en bajo
  }                           //fin for

  // configuración de timers
  // SMBlink.setFcia(4,8,20,30,40);  // fija frecuencia oscilación
}

void loop() {
  SMBlink.initSM(); // iniciar timer
  for (int f = 0; f < 5; f++)  // para las 5 salidas que se estan manejando
  {
    digitalWrite(Led[f], SMBlink.getSM(f));
  }  //fin for
}

