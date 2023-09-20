/* ejemplo uso de timer con retardo sin delay, 
  generando una secuencia periodica variando el
  valor del periodo.
  @autor: Ferney Berrio Z
 */
#include <timFabz.h>  // libreria para retardos sin delay
TimFabz tim;          // declaración objeto de la clase

int entrada = 43, Led1 = 45, Led2 = 47, Led3 = 49, Led4 = 51, Led5 = 53;
int Led[5] = { Led1, Led2, Led3, Led4, Led5 };  // matriz Led se le asignan numeros que coincidan con numero de pines ardu5
int Secuencia = 0;
int f = 0;
int ciclo = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(entrada, INPUT);
  for (int i = 0; i < 5; i++)  // para las 5 salidas que se estan manejando
  {
    pinMode(Led[i], OUTPUT);    // declarar como salida
    digitalWrite(Led[i], LOW);  // poner salida en bajo
  }
}

void loop() {
  tim.update();  // iniciar

  if (tim.getState()) {  // si el temporizador cumplio el tiempo
    if (f < 5 & Secuencia == 0) {
      f++;
    }  // AUMENTAR SECUENCIA
    else {
      Secuencia = 1;  // que no repita la secuencia
      f--;            // disminuir secuencia
      if (f < 0) {
        Secuencia = 0;
      }
    }                                  // secuencia termino
    digitalWrite(Led[f], !Secuencia);  // active salida segun pocicion
    if (tim.getSetPoint() > 10 & ciclo == 0) {
      tim.setSetPoint(tim.getSetPoint() - 1);
    }  // valor set poin temp
    else {
      tim.setSetPoint(tim.getSetPoint() + 1);  // aumentar set point
      if (tim.getSetPoint() >= 500) {
        ciclo = 0;
      } else {
        ciclo = 1;
      }
    }

    tim.reset();  // reiniciar timer
  }
}
