// código librería
// código para no repetir headers
#ifndef tempF_h
#define tempF_h
#include <Arduino.h>
//
class TempF
{
public:

  /*************************************************** /
  /********* metodos para SM y temporizadores ********/

  // usuario pone en marcha temporizadores
  void initTempo(); // usuario pone en marcha marcas temporizadores


  /** Fija valores preset para temporizador
   *@param _seg -> valor de los segundos a fijar (0-59)
   *@param _min -> valor minutos a fijar (0-59)
   *@param _hrs -> valor horas a fijar (0-1193) */
  void setTempo(byte _seg, byte _min, byte _hrs); // setpoin temporizador (Seg, minutos,Horas)
  /** Fija valores preset para temporizador
   *@param _seg -> valor de los segundos a fijar (0 - 4294967295)  */
  void setTempo(byte _seg); // setpoin temporizador (Seg)

  /** Obtiene milisegundos actuales del temporizador seleccionado
   *@return Milisegundos actuales */
  byte getMili(); // obtener milisegundos actuales
  /** fija milisegundos actuales al temporizador seleccionado
   *@param _val -> valor a fijar (0-999)(ms) */
  void setMili(byte _val); // setear milisegundos actuales(miliseg max 1000 )

  /** Obtiene segundos actuales del temporizador seleccionado
   *@return segundos actuales */
  byte getSegu(); // obtener segundos actuales()
  /** fija segundos actuales al temporizador seleccionado
   *@param _val -> valor a fijar (0-59)(seg) */
  void setSegu(byte _val); // setear segundos actuales(seg max 60)

  /** Obtiene minutos actuales del temporizador seleccionado
   *@return minutos actuales */
  byte getMinu(); // obtener minutos actuales()
  /** fija milisegundos actuales al temporizador seleccionado
   *@param _val -> valor a fijar (0-59)(min) */
  void setMinu(byte _val); // setear minutos actuales(minu max 60)

  /** Obtiene horas actuales del temporizador seleccionado
   *@return horas actuales */
  int getHora(); // obtener horas actuales(#temporizador)
  /** fija milisegundos actuales al temporizador seleccionado
   *@param _val -> valor a fijar (0-1193)(hrs) */
  void setHora(int _val); // setear horas actuales(horas max 1193)

  /** Obtiene estado de habilitación  del temporizador seleccionado
   *@return retorna los estado de habilitación del temp seleccionado */
  bool getEnable(); // obtiene estado temporizador()
  /** fija estado de habilitación del temporizador seleccionado
   *@param _val -> estado a fijar ( true: enable / false: disable ) */
  void setEnable(bool _val); // setea estado temporizador(true/enable    false/disable)

  /** limpiar por defecto parámetros del temporizador seleccionado*/
  void clear(); // borra valores ()

  /** estado cumplimiento tiempo temporizador seleccionado
   *@return estado ( true: tiempo cumplido  /  false: sin cumplir tiempo) */
  bool getStateTemp(); // estado cumplimiento tiempo temporizador()
  /** fija estado cumplimiento tiempo temporizador seleccionado
   *@param _val -> estado a fijar ( true: tiempo cumplido  /  false: sin cumplir tiempo) */
  void setStateTemp(bool _val); // estado cumplimiento tiempo temporizador(, estado)

  // constructor
  TempF();
  
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
  } t1 = {1, false, false, 0, 0}; // valor por defecto para el setpoint 5 milisegundos

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
  byte SM[1] = {0}; // vector de marcas especiales
  //void Temporizar();
  int par_miliseg = 0;              // variable para almacenar segundos contados
  byte segunderos = 0;               // variable para almacenar segundos contados
  byte minuteros = 0;                // array para almacenar minutos contados
  int horas = 0;                     // array para almacenar horas contados
  int S_par_miliseg = 0;                   // variable para almacenar segundos contados
  byte S_segunderos = 59;          // variable para almacenar segundos contados
  byte S_minuteros = 59;           // array para almacenar minutos contados
  int S_horas = 1193;          // array para almacenar horas contados
  bool Hab_tempor = false;   // array para almacenar si se habilita cada temporizador
  //int tam_Tim = sizeof(segunderos);             // tamaño para el vector de tiempo
  bool par_mili = false;                        // GARANYIZA QUE SE CUENTE SOLO UNA VEZ
  bool state_tempor = false; // array para  estados de tiempo cumplido temporizador

};     // fin clase temporizadores
#endif // Temp_h
