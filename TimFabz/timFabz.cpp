#include <Arduino.h>
#include <timFabz.h>
// timFabz Tiemp; // crear objeto tim de la clase timFabz

/*************************Retardos (temporizadores sin delay)**************************/
/*************************se hace mejora: si se utiliza delay en el programa los TIM_FABZ siguen contando en "paralelo"**************************/
// se hace con Programación Orientada a Objetos

bool TimFabz::Temporizador() {
  if (!t0.stateTim) {         // mientras no se halla cumplido el tiempo  sigue contando asi evita desbordamiento
    valor_actual = millis();  // el valor de milisegundos del sistema se asigna a esta variable
    if (!t0.runTimer) {
      t0.initValue = valor_actual;  // inicia el conteo de tiempo
      t0.runTimer = true;           // para que no vuelva a iniciar el conteo
    }                               // fin if
    dif = valor_actual - t0.initValue;
    t0.initValue = valor_actual;

    // if (dif < 0)
    // {                                      // si se desborda el tiempo por millis pasar a cero
    //         t0.current = 4294967295 + dif; // al valor máximo de millis le resto el valor del desbordamiento
    // }
    // else
    // {
    //         t0.current = dif;
    // }

    // si se desborda el tiempo por millis pasar a cero ?
    // al valor máximo de millis le resto el valor del desbordamiento : si no asigno solo la diferncia
    t0.current += dif < 0 ? 4294967295 + dif : dif;

    if (t0.current >= t0.setPoint) {  // si llego al valor del setpoint
      t0.stateTim = true;             // indicar que ya llego
    }

  }  // fin if
  return t0.stateTim;
}  // fin funcion

void TimFabz::Reinicio_Temp() {
  // t0.setPoint = 0; // valor_fijado = 0 ;                                    // reinicia valor prefijado del temporizador
  t0.runTimer = false;  // reinicia # de temporizador
  t0.stateTim = false;  // reinicia estado temporizador
  t0.initValue = 0;     // reinicia valor actual del temporizador
  t0.current = 0;       // reinicia tiempo en el que esta el temporizador
  Fflag = false;        // reiniciar bandera
  Fstop = false;        // reiniciar estado de stop
}  // fin funcion

// TimFabz timer;
TimFabz::TimFabz() {  // implementacion constructor
  function_callback0 = NULL;
}  // fin constructor

/***************************************** Geter and seter **************************************************************/

/* metodos para timers */
void TimFabz::update()  // pone en marcha timer ms
{
  if (!Fstop) {
    if (Temporizador()) {
      if (function_callback0 != NULL) {
        function_callback0();
      }  // ejecutar función
    }    // fin if Temporizador
  }      // fin if Fstop
}

void TimFabz::standBy()  // detener timer
{
  t0.runTimer = false;  // reinicia # de temporizador
  Fstop = true;         //detener timer
}

void TimFabz::run()  // iniciar timer
{
  Fstop = false;         //detener timer
}

void TimFabz::reset()  // reinicia valores del timer
{
  Reinicio_Temp();
}

bool TimFabz::getState()  // estado tiempo cumplido (salida)
{
  return t0.stateTim;
}

bool TimFabz::getState(int _Fflag)  // estado tiempo cumplido (salida)
{
  bool ret = false;
  if (_Fflag == fBandera) {
    ret = Fflag ? false : t0.stateTim;
    Fflag = t0.stateTim;
  } else if (_Fflag == fRst && t0.stateTim) {
    ret = t0.stateTim;
    Reinicio_Temp();
  }

  return ret;
}

void TimFabz::setState(bool _state)  // setear estado (salida)
{
  t0.stateTim = _state;
}

unsigned long TimFabz::getSetPoint()  // obtener setpoint timer
{
  return t0.setPoint;
}

void TimFabz::setSetPoint(unsigned long value)  // fijar Setpoint
{
  t0.setPoint = value;
}

unsigned long TimFabz::getTime()  // btener tiempo actual
{
  return t0.current;
}

void TimFabz::setTime(unsigned long value) /* value debe ser < len(unsigned long)*/
{
  t0.current = value;
  // if (millis() - value < 0)
  // {
  // t0.initValue = millis() - value + 4294967295;
  // } // fin if
  // else
  // {
  // t0.initValue = millis() - value;
  // } // fin else

  // si se puede presentar desbordamiento
  //t0.initValue = millis() - value < 0 ? millis() - value + 4294967295 : millis() - value;
}

/*****************************************final Geter and seter **************************************************************/
