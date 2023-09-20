/* librería para uso de multiples timer con retardos sin delay, a diferentes
  frecuencias de oscilación.
  @autor: Ferney Berrio Z
 */
#ifndef sMarkF_h
#define sMarkF_h
#include <Arduino.h>
//
class SMarkF
{
public:
    /*************************************************** /
    /********* metodos para SM y temporizadores ********/
    //constructor
    SMarkF();
    /** Iniciar cuenta Marcas Especiales */
    void initSM(); // usuario pone en marcha marcas especiales SM

    /** retorna valor de la Marca special
     *\0=50ms, 1=100ms, 2=250ms, 3=500ms, 4=1000ms
     * @param _SM -> número de SM (0-4)
     * @return valor SM (0 / 1) */
    byte getSM(byte _SM); // rango de marcas especiales a usar
    
    /** fija frecuencias oscilación NOTA: deben ser en orden acendente
     * @param _SM0 -> frecuencia oscilación 0
     * @param _SM1 -> frecuencia oscilación 1
     * @param _SM2 -> frecuencia oscilación 2
     * @param _SM3 -> frecuencia oscilación 3
     * @param _SM4 -> frecuencia oscilación 4 */
    void setFcia(byte _SM0, byte _SM1, byte _SM2, byte _SM3, byte _SM4); // valores frecuencia para cada marca especial

private:

 /*************************+ DECLARACION DE FUNCIONES**************************/
  // estructura para definir los temporizadores
  /** structura timers
   *@param setPoint -> set point
   *@param runTimer -> indica si ya empezo a contar
   *@param stateTim -> estado salida temporizador
   *@param initValue -> millis iniciales
   *@param current -> current time */
  struct Timp
  {
    unsigned long setPoint;       // valor prefijado del temporizador
    bool runTimer;                // 1= inicio conteo , 0= no esta contando
    bool stateTim;                // estado temporizador 0= salida apagada, 1= salida encendida ya que conto el tiempo prefijado
    unsigned long initValue;      // valor actual del temporizador
    unsigned long current;        // tiempo en el que esta el temporizador
  } t2 = {1, false, false, 0, 0}; // valor por defecto para el setpoint 5 milisegundos

  /** temporizar sin delay
   *@return retorna estado true=tiempo cumplido, false= no cumplido    */
  bool Temporizador(); // funcion para que temporizador empiece a correr

  /** reiniciar temporizador t20*/
  void Reinicio_Temp(); // pone en cero todos los elementos del vector

  unsigned long valor_actual = 0;
  unsigned long dif = 0;
  bool Fflag = false;
  bool Frst = true;
  #define fBandera 1
  #define fRst 2
  /*************************+ DECLARACION DE FUNCIONES**************************/

/***************************************** Geter and seter **************************************************************/
 /* metodos para timers */

  /** poner en marcha cuenta timer 0 */
  void update();

  /** reiniciar timer 0 */
  void reset(); // reinicia timer (#timer)

  /** Obtener estado salida del timer 0
   *@return estado salida timer 0 */
  bool getState(); // estado timer (#timer)

  /** Obtener estado salida del timer 0
   *@param _Fflag -> 1= garanatiza estado una única vez , 2 =reinicia
   *@return estado salida timer 0 */
  bool getState(int _Fflag); // estado timer (#timer)

  /** fijar estado salida del timer 0
   *@param  _state -> estado a fijar */
  void setState(bool _state); // estado timer (#timer, valor true activo  /  false inactivo)

  /** Obtener valor setpoint del timer 0 */
  unsigned long getSetPoint(); // setpoin timer (#timer)

  /** fijar el setpoint timer 0
   *@param value -> valor a asignar en (ms) entre (0 - 4294967295) */
  void setSetPoint(unsigned long value); // fijar setpoint timer (#timer, valor ms)

  /** Obtener valor actual que esta corriendo del timer 0
   *@return valor actual (0 - 4294967295)(ms) */
  unsigned long getTime(); // tiempo corrido timer (#timer)

  /** fijar el tiempo actual
   *@param value -> valor a asignar en (ms) entre (0 - 4294967295) */
  void setTime(unsigned long value); // fijar tiempo corrido timer (#timer) /* parametro debe ser < len(unsigned long)*/

    // temporizadores
    byte SM[5] = {0, 0, 0, 0, 0}; // vector de marcas especiales
    void runSM();

};     // fin clase temporizadores
#endif // Temp_h
