/* Librería para uso de retardos sin delay (con millis)
  @autor: Ferney Berrio Z
 */
#ifndef timFabz_h
#define timFabz_h
#include <Arduino.h>
//
class TimFabz
{
public:
  /* metodos para timers */
  // constructor
  TimFabz();
  /** función a ejecutar al cumplir tiempo timer
   *@param function -> nombre de la función que será llamada para timer 0 */
  void setCallBack(void (*function)(void))
  {
    this->function_callback0 = function;
  } /*declaración update*/

  /** poner en marcha cuenta timer */
  void update();
  
  /** poner en receso cuenta timer */
  void standBy();

  /** poner en marcha cuenta timer */
  void run();
  
  /** reiniciar timer 0 */
  void reset(); // reinicia timer ()

  /** Obtener estado salida del timer
   *@return estado salida timer */
  bool getState(); // estado timer ()

  /** Obtener estado salida del timer 0
   *@param _Fflag -> 1(fBandera) = retorna estado True una única vez , 2(fRst) =reinicia
   *@return estado salida timer */
  bool getState(int _Fflag); // estado timer ()

  /** fijar estado salida del timer
   *@param  _state -> estado a fijar */
  void setState(bool _state); // estado timer (, valor true activo  /  false inactivo)

  /** Obtener valor setpoint del timer */
  unsigned long getSetPoint(); // setpoin timer ()

  /** fijar el setpoint (100ms por defecto)
   *@param value -> valor a asignar en (ms) entre (0 - 4294967295) */
  void setSetPoint(unsigned long value); // fijar setpoint timer (valor ms)

  /** Obtener valor actual que esta corriendo del timer
   *@return valor actual (0 - 4294967295)(ms) */
  unsigned long getTime(); // tiempo corrido timer ()

  /** fijar el tiempo actual
   *@param value -> valor a asignar en (ms) entre (0 - 4294967295) */
  void setTime(unsigned long value); // fijar tiempo corrido timer (valor ms) /* parametro debe ser < len(unsigned long)*/

private:
  // constructor
  /** función callback
   *@param function_callback0 > (*function_callback0)(void) */
  void (*function_callback0)(void);

  /*************************+ DECLARACION DE FUNCIONES**************************/
  // estructura para definir los temporizadores
  /** structura timers
   *@param setPoint -> set point
   *@param runTimer -> indica si ya empezo a contar
   *@param stateTim -> estado salida temporizador
   *@param initValue -> millis iniciales
   *@param current -> current time */
  struct Temp
  {
    unsigned long setPoint;       // valor prefijado del temporizador
    bool runTimer;                // 1= inicio conteo , 0= no esta contando
    bool stateTim;                // estado temporizador 0= salida apagada, 1= salida encendida ya que conto el tiempo prefijado
    unsigned long initValue;      // valor actual del temporizador
    unsigned long current;        // tiempo en el que esta el temporizador
  } t0 = {100, false, false, 0, 0}; // valor por defecto para el setpoint 5 milisegundos

  /** temporizar sin delay
   *@return retorna estado true=tiempo cumplido, false= no cumplido    */
  bool Temporizador(); // funcion para que temporizador empiece a correr

  /** reiniciar temporizador t0*/
  void Reinicio_Temp(); // pone en cero todos los elementos del vector

  unsigned long valor_actual = 0;
  unsigned long dif = 0;
  bool Fflag = false;
  bool Frst = true;
  bool Fstop = false;
  #define fBandera 1 //se obtiene True una única vez despues de cumplir tiempo
  #define fRst 2 //reinicia una vez se obtenga su estado despues de cumplir tiempo
  /*************************+ DECLARACION DE FUNCIONES**************************/

}; // fin clase timer

#endif // timFabz_h
