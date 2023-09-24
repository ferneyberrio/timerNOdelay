#include <Arduino.h>
#include <sMarkF.h>

byte cont_ticks = 0;
int modulo = 1;
int modu[5] = { 2, 4, 10, 20, 40 };  // periodo de repetición cambio estado marcas 50ms, 100ms,250ms,500ms,1000ms
int mayor = 40;                      // numero mayor de modulo
//int marca[5] = {0, 1, 2, 3, 4};  // número de marca especial

/***************************************** Geter and seter **************************************************************/

/*************************Retardos (temporizadores sin delay)**************************/
/*************************se hace mejora: si se utiliza delay en el programa los TIM_FABZ siguen contando en "paralelo"**************************/
// se hace con Programación Orientada a Objetos

bool SMarkF::Temporizador() {
  if (!t2.stateTim) {         // mientras no se halla cumplido el tiempo  sigue contando asi evita desbordamiento
    valor_actual = millis();  // el valor de milisegundos del sistema se asigna a esta variable
    if (!t2.runTimer) {
      t2.initValue = valor_actual;  // inicia el conteo de tiempo
      t2.runTimer = true;           // para que no vuelva a iniciar el conteo
    }                               // fin if
    dif = valor_actual - t2.initValue;
    t2.initValue = valor_actual;

    // al valor máximo de millis le resto el valor del desbordamiento : si no asigno solo la diferncia
    t2.current += dif < 0 ? 4294967295 + dif : dif;

    if (t2.current >= t2.setPoint) {  // si llego al valor del setpoint
      t2.stateTim = true;             // indicar que ya llego
    }

  }  // fin if
  return t2.stateTim;
}  // fin funcion

void SMarkF::Reinicio_Temp() {
  // t2.setPoint = 0; // valor_fijado = 0 ;                                    // reinicia valor prefijado del temporizador
  t2.runTimer = false;  // reinicia # de temporizador
  t2.stateTim = false;  // reinicia estado temporizador
  t2.initValue = 0;     // reinicia valor actual del temporizador
  t2.current = 0;       // reinicia tiempo en el que esta el temporizador
  Fflag = false;        // reibniciar bandera
}  // fin funcion

/* metodos para timers */
void SMarkF::update()  // pone en marcha timer ms
{
  if (Temporizador()) {
  }
}

void SMarkF::reset()  // reinicia valores del timer
{
  Reinicio_Temp();
}

bool SMarkF::getState()  // estado tiempo cumplido (salida)
{
  return t2.stateTim;
}

bool SMarkF::getState(int _Fflag)  // estado tiempo cumplido (salida)
{
  bool ret = false;
  if (_Fflag == fBandera) {
    ret = Fflag ? false : t2.stateTim;
    Fflag = t2.stateTim;
  } else if (_Fflag == fRst && t2.stateTim) {
    ret = t2.stateTim;
    Reinicio_Temp();
  }

  return ret;
}

void SMarkF::setState(bool _state)  // setear estado (salida)
{
  t2.stateTim = _state;
}

unsigned long SMarkF::getSetPoint()  // obtener setpoiny timer
{
  return t2.setPoint;
}

void SMarkF::setSetPoint(unsigned long value) {
  t2.setPoint = value;
}

unsigned long SMarkF::getTime() {
  return t2.current;
}

void SMarkF::setTime(unsigned long value) /* value debe ser < len(unsigned long)*/
{
  t2.current = value;
}
SMarkF::SMarkF() {  // implementacion constructor
  setSetPoint(25);
}  // fin constructor

/* metodos para temporizadores */
void SMarkF::initSM()  // pone en marcha marcas especiales SM y temporizadores
{
  runSM();  // pone en marcha marcas especiales SM
}
byte SMarkF::getSM(byte _SM) {
  return SM[_SM];  // retorna valor de la Marca special
}

void SMarkF::setFcia(byte _SM0, byte _SM1, byte _SM2, byte _SM3, byte _SM4)  // valores frecuencia para cada marca especial
{
  modu[0] = _SM0;
  modu[1] = _SM1;
  modu[2] = _SM2;
  modu[3] = _SM3;
  modu[4] = _SM4;
  for (int j = 0; j < 5; j++) {
    if (modu[j] > mayor) mayor = modu[j];
  }  // fin for
}  //fin función setFcia

void SMarkF::runSM() {
  update();
  // Temporizador
  if (getState()) {
    cont_ticks += 1;
    //SM[0] = !SM[0];

    for (int i = 0; i < 5; i++) {
      modulo = cont_ticks % modu[i];
      if (modulo == 0) {
        SM[i] = !SM[i];
      }  // fin if
    }    // fin for

    // Reinicio_Temp
    reset();

    if (cont_ticks >= mayor) {
      cont_ticks = 1;
    }  // fin if

  }  // fin if

}  // fin funcion runSM

/*****************************************final Geter and seter **************************************************************/
