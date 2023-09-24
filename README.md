# 📒 timerNOdelay /  Ferney Berrio Zuleta

## 🇨🇴 :es: ![Badge](https://img.shields.io/badge/Licence-%20MIT-green) ![Badge](https://img.shields.io/badge/Version-%201.0-blue) ![Badge](https://img.shields.io/badge/release_date-%20Sep/2020-yellow) ![Badge](https://img.shields.io/badge/Status-%20En_desarrollo-magenta)
----------
### Temporizadores sin retardo haciendo uso de millis / timers without delay using millis.
+ Librerias de creación propia para el manejo de retardos sin delay,
haciendo uso de la función millis.
+ Mejaras apoyando en código de https://github.com/brunocalou, https://github.com/casaautomacao/timerwithoutdelay,https://www.youtube.com/watch?v=RZPhrSQ2soo y libreria machine.time de #micropython https://docs.micropython.org/en/latest/library/time.html.
+ Esta libreria pueden ser usada entre otras cosas para manejo de temporizadores simples, ondelay, ofdelay, ciclicos, acumuladores.
+ Para manejo de marcas especiales que tienen un periodo de oscilación periodico a diferentes frecuencias utilizable.
para hacer que salidas tipo blink.
+ Manejo de temporizadores del orden de segundos, minutos y horas en diferentes modos de operación.

-----------------
### :speech_balloon: Lenguajes utilizados
### :busts_in_silhouette: Contribuyentes
### :construction_worker: Autores
### :page_facing_up: Ejemplos

## :zap:class TimFabz:
  * > Librerias de creación propia para el manejo de retardos sin delay,
     haciendo uso de la función millis()
  * > ### palabras claves:
    > temporizador, setpoint, tiempo cumplido.
  
      ```cpp
      struct Temp
      {
        unsigned long setPoint;       // valor prefijado del temporizador
        bool runTimer;                // true= inicio conteo , false= no esta contando
        bool stateTim;                // estado temporizador 0= salida apagada, 1= salida encendida ya que conto el tiempo prefijado
        unsigned long initValue;      // valor actual del temporizador
        unsigned long current;        // tiempo en el que esta el temporizador
      } t = {100, false, false, 0, 0}; // valores por defecto
      ```
  * ### :clipboard: Funciones
     * **`void setCallBack(void (*function)(void))`** define la función que se va a ejecutar una vez se halla cumplido el tiempo fijado en el temporizador y es llamada
       recurrentemente mientras este estado se mantenga
     * **`void update()`** Actualiza la cuenta del temporizador **debe ser llamada siempre que se desee que se realice la cuenta**
     * **`void standBy()`** Pone en receso la cuenta del temporizador
     * **`void run()`** Pone en marcha la cuenta del temporizador
     * **`void reset()`** Reestablece por defecto los valores de la estructura Temp(a excepción de setpoint)
     * **`bool getState()`** Obtiene el estado del temporizador -> true: tiempo cumplido y llama la función callback / false: no cumplido
     * **`bool getState(int _Fflag)`** Obtiene el estado del timer -> retoorno: 1(fBandera) = retorna estado True una única vez , 2(fRst) = retorna True y reinicia
     * **`void setState(bool _state)`** Asigna el estado del timer -> parámetro :valor true activo  /  false inactivo)
     * **`unsigned long getSetPoint()`** Obtiene el valor del setpoint del temporizador
     * **`void setSetPoint(unsigned long value)`** Asignar setpoint del temporizador (100ms por defecto) : value -> valor a asignar en (ms) entre (0 - 4294967295) 
     * **`unsigned long getTime()`** Obtener valor actual que esta corriendo del timer(ms)
     * **`setTime(unsigned long value)`** fijar el tiempo actual del temporizador : value -> valor a asignar en (ms) entre (0 - 4294967295)

## :zap:class TempF:
  * > * Esta libreria pueden ser usada entre otras cosas para manejo de temporizadores simples, ondelay, ofdelay, ciclicos, acumuladores.
    > * Manejo de temporizadores del orden de segundos, minutos y horas en diferentes modos de operación.
  * ### :clipboard: Funciones
     * **`void initTempo()`** Pone en marcha temporizadores
     * **`void setTempo(byte _seg, byte _min, byte _hrs)`** Fijar setpoint temporizador (Seg, minutos,Horas) : _seg -> valor de los segundos a fijar (0-59), _min -> valor minutos a fijar (0-59), _hrs -> valor horas a fijar (0-1193) */
     * **`void setTempo(byte _seg)`** Fija valor setpoint para temporizador (seg)
     * **`byte getMili()`** Obtiene milisegundos actuales del temporizador
     * **`void setMili(byte _val)`** Fija milisegundos actuales al temporizador : _val -> valor a fijar (0-999)(ms)
     * **`byte getSegu()`** Obtiene segundos actuales del temporizador
     * **`void setSegu(byte _val)`** Fija segundos actuales al temporizador : _val -> valor a fijar (0-59)(seg)
     * **`byte getMinu()`** Obtiene minutos actuales del temporizado
     * **`void setMinu(byte _val)`** Fija milisegundos actuales al temporizador : _val -> valor a fijar (0-59)(min)
     * **`int getHora()`** Obtiene horas actuales del temporizador
     * **`void setHora(int _val)`** Fija milisegundos actuales al temporizador : _val -> valor a fijar (0-1193)(hrs)
     * **`bool getEnable()`** Obtiene estado de habilitación  del temporizador seleccionado
     * **`void setEnable(bool _val)`** fija estado de habilitación del temporizador : _val -> estado a fijar ( true: enable / false: disable 
     * **`void clear()`** limpiar por defecto parámetros del temporizador
     * **`bool getStateTemp()`** Estado cumplimiento tiempo temporizador : ( true: tiempo cumplido  /  false: sin cumplir tiempo)
     * **`void setStateTemp(bool _val)`** fija estado cumplimiento tiempo temporizador : _val -> estado a fijar ( true: tiempo cumplido  /  false: sin cumplir tiempo)

## :zap:class SMarkF:
  * > Manejo de marcas especiales que tienen un periodo de oscilación periodico a diferentes frecuencias utilizable.
    para hacer que salidas tipo blink.

  * ### :clipboard: Funciones
     * **`void initSM()`** Pone en marcha marcas especiales SM
     * **`byte getSM(byte _SM)`** retorna valor de la Marca special : 0=50ms, 1=100ms, 2=250ms, 3=500ms, 4=1000ms(valores blink por defecto) : _SM -> número de SM (0-4), retorno SM (0 / 1)
     * **`void setFcia(byte _SM0, byte _SM1, byte _SM2, byte _SM3, byte _SM4)`** fija frecuencias oscilación de cada marca especial SM (en milisegundos)
## :us:
