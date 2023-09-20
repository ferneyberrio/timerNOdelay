#include <Arduino.h>
#include <tempF.h>

/*************************Retardos (temporizadores sin delay)**************************/
/*************************se hace mejora: si se utiliza delay en el programa los TIM_FABZ siguen contando en "paralelo"**************************/
// se hace con Programación Orientada a Objetos

bool TempF::Temporizador()
{
        if (!t1.stateTim)
        {                                // mientras no se halla cumplido el tiempo  sigue contando asi evita desbordamiento
                valor_actual = millis(); // el valor de milisegundos del sistema se asigna a esta variable
                if (!t1.runTimer)
                {
                        t1.initValue = valor_actual; // inicia el conteo de tiempo
                        t1.runTimer = true;          // para que no vuelva a iniciar el conteo
                }                                    // fin if
                dif = valor_actual - t1.initValue;
                t1.initValue = valor_actual;
                
                // al valor máximo de millis le resto el valor del desbordamiento : si no asigno solo la diferncia
                t1.current += dif < 0 ? 4294967295 + dif  : dif ;
                
                if (t1.current >= t1.setPoint)
                {                           // si llego al valor del setpoint
                        t1.stateTim = true; // indicar que ya llego
                }

        } // fin if
        return t1.stateTim;
} // fin funcion

void TempF::Reinicio_Temp()
{
        // t1.setPoint = 0; // valor_fijado = 0 ;                                    // reinicia valor prefijado del temporizador
        t1.runTimer = false; // reinicia # de temporizador
        t1.stateTim = false; // reinicia estado temporizador
        t1.initValue = 0;    // reinicia valor actual del temporizador
        t1.current = 0;      // reinicia tiempo en el que esta el temporizador
        Fflag = false;       // reibniciar bandera
} // fin funcion

/* metodos para timers */
void TempF::update() // pone en marcha timer ms
{
        if (Temporizador())
        {

        }
}

void TempF::reset() // reinicia valores del timer
{
        Reinicio_Temp();
}

bool TempF::getState() // estado tiempo cumplido (salida)
{
        return t1.stateTim;
}

bool TempF::getState(int _Fflag) // estado tiempo cumplido (salida)
{
        bool ret = false;
        if (_Fflag == fBandera)
        {
                ret = Fflag ? false : t1.stateTim;
                Fflag = t1.stateTim;
        }
        else if (_Fflag == fRst && t1.stateTim)
        {
                ret = t1.stateTim;
                Reinicio_Temp();
        }

        return ret;
}

void TempF::setState(bool _state) // setear estado (salida)
{
        t1.stateTim = _state;
}

unsigned long TempF::getSetPoint() // obtener setpoiny timer
{
        return t1.setPoint;
}

void TempF::setSetPoint(unsigned long value)
{
        t1.setPoint = value;
}

unsigned long TempF::getTime()
{
        return t1.current;
}

void TempF::setTime(unsigned long value) /* value debe ser < len(unsigned long)*/
{
        t1.current = value;
}

/* metodos para temporizadores */
TempF::TempF()
{ // implementacion constructor
        setSetPoint(100);
} // fin constructor
void TempF::initTempo() // pone en marcha marcas especiales SM y temporizadores
{
        // Temporizar();
        // Temporizador(&t1.Sp, &t1.t, &t1.St, &t1.Sv, &t1.Sa); // temporizar
        update();
        // int val_tiempo = t1.Sa;                              // obtener el tiempo actual
        int val_tiempo = getTime(); // obtener el tiempo actual
        int val_t = 0;
        if (getSetPoint() < val_tiempo) // si setpoint es menor al tiempo actual
        {
                val_t = val_tiempo / getSetPoint();
        }
        else
        {
                val_t = 0;
        }

        if (getState())
        {
                SM[0] = !SM[0];
                // Reinicio_Temp(&t1.Sp, &t1.t, &t1.St, &t1.Sv, &t1.Sa);
                reset();
        }

        // temporizador para contar de periodo en periodo mientras este activado el temporizador de n periodo
        if (SM[0] == 1 || val_t >= 1)
        { // si temporizador de medio periodo se activa
                par_mili = true;
        } // indica que ya se cumplio un periodo
        if (SM[0] == 0 || val_t >= 1)
        {
                // val_tiempo = val_tiempo/t1.Sp;
                if (val_t < 1)
                {
                        val_t = 1;
                } // fin if val_tiempo
                for (int i = val_t; i >= 1; i--)
                {
                        val_t = 0;
                        if (par_mili == true)
                        { // si ya paso un segundo
                                if (i <= 1)
                                {
                                        par_mili = false;
                                } // garantiza que solo cuente el minuto una vez

                                //for (int r = 0; r < tam_Tim; r++)
                                //{ // ciclo para recorrer el arreglo
                                        if (Hab_tempor == true && !state_tempor)
                                        { // si se ha habilitado el conteo de este emporizador
                                                par_miliseg++; // aumentar 10 milisegundos

                                                if (par_miliseg >= 5)
                                                {                           // si se han contado 1000 milisegundos
                                                        segunderos++;    // aumente una unidad los segundos
                                                        par_miliseg = 0; // reinicie los 100 10_milisegundos contados
                                                } // fin if

                                                if (segunderos >= 60)
                                                {                          // si se han contado 60 segundos
                                                        minuteros++;    // aumente una unidad los minutos
                                                        segunderos = 0; // reinicie los segundos contados
                                                } // fin if

                                                if (minuteros >= 60)
                                                {                         // si se han contado 60 segundos
                                                        horas++;       // aumente una unidad los minutos
                                                        minuteros = 0; // reinicie los segundos contados
                                                        if (horas >= 1193)
                                                        {
                                                                horas = 0;
                                                        } // fin if
                                                } // fin if

                                                if (horas >= S_horas && minuteros >= S_minuteros && segunderos >= S_segunderos)
                                                {
                                                        state_tempor = true;
                                                } // fin if

                                        } // fin if                     // si se ha cumplido tiempo indica que lleva un segundo
                                //}         // fin for

                        } // fin if
                }         // fin for
        }                 // FIN ELSE
}
void TempF::setTempo(byte _seg, byte _min, byte _hrs)
{                                   // setpoin temporizador(Horas, minutos, Seg)
        S_segunderos = _seg; // setpoint segundos
        S_minuteros = _min;  // setpoint minutos
        S_horas = _hrs;      // setpoint horas
}
void TempF::setTempo(byte _seg)
{ // setpoin temporizador(Seg)
        int sec = _seg;
        S_horas = sec / 3600;    //  horas en n segundos
        sec %= 3600;                    // modulo a 60*60
        S_minuteros = sec / 60;  //  minutos
        S_segunderos = sec % 60; //  segundos
}
byte TempF::getMili()
{                                      // obtiene milisegundos   (# temporizador)
        return par_miliseg * 2; // retorna los miliseg del temp seleccionado
}
void TempF::setMili(byte _val)
{                                      // setpoin temporizador (#,milisegundos)
        par_miliseg = _val / 2; // setea los miliseg del temp seleccionado
}
byte TempF::getSegu()
{                                 // obtiene segundos (# temporizador)
        return segunderos; // retorna los segundos del temp seleccionado
}
void TempF::setSegu(byte _val)
{                                 // setpoin temporizador (#,Segundos)
        segunderos = _val; // setea los segundos del temp seleccionado
}
byte TempF::getMinu()
{                                // obtiene segundos (# temporizador)
        return minuteros; // retorna los minutos del temp seleccionado
}
void TempF::setMinu(byte _val)
{                                // setpoin temporizador (#,minutos)
        minuteros = _val; // setea los minutos del temp seleccionado
}
int TempF::getHora()
{                            // obtiene horas (# temporizador)
        return horas; // retorna los horas del temp seleccionado
}
void TempF::setHora(int _val)
{                            // setpoin temporizador (#,horas)
        horas = _val; // setea los horas del temp seleccionado
}
bool TempF::getEnable()
{
        return Hab_tempor; // retorna los estado de habilitación del temp seleccionado
}
void TempF::setEnable(bool _val)
{                                 // setpoin temporizador (estado)
        Hab_tempor = _val; // setea estado del temp seleccionado
}
void TempF::clear()
{                                    // borra datos (# temporizador)
        par_miliseg = 0; // reinicie los milisegundos contados
        segunderos = 0;  // reinicie los segundos contados
        minuteros = 0;   // reinicie los minutos contados
        horas = 0;       // reinicie las horas contadas
        state_tempor = false;
}
bool TempF::getStateTemp()
{ // estado cumplimiento tiempo temporizador(# temporizador)
        return state_tempor;
}
void TempF::setStateTemp(bool estado)
{ // estado cumplimiento tiempo temporizador(# temporizador, estado)
        state_tempor = estado;
}

/*****************************************final Geter and seter **************************************************************/
