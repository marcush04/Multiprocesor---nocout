/** @file Areadeespera.hh
    @brief Especificación de la clase Area de espera
*/

#ifndef _AREA_DE_ESPERA_HH_
#define _AREA_DE_ESPERA_HH_

#include "Proceso.hh" 

#ifndef NO_DIAGRAM 
#include <list>
#include <map>
#include <iostream>
#include <string>
#include "Cluster.hh"
using namespace std;
#endif


/** @class Areadeespera
    @brief Representa una area de espera de procesos. 

    Puede contener procesos. Puede usarse para enviar los procesos al cluster; en ese caso, los procesos se sacan de la area de espera en funcion de su prioridad
*/
class Areadeespera
{
public:
    //Constructoras

    /** @brief Creadora por defecto.

        Se ejecuta automáticamente al declarar una cubeta.
        \pre <em>cierto</em>
        \post El resultado es una area de espera sin ningún proceso ni prioridad
    */
    Areadeespera();


    //Modificadoras
    /** @brief Inicializa los valores de la area de espera
        \pre El parámetro implícito existe
        \post Inicializa los valores del parámatro implícito
    */
    void inicializar();

    /** @brief Agrega un proceso pendiente a la area de espera
        \pre El proceso no existe en la prioridad y la prioridad existe
        \post Agrega el proceso en la prioridad al parámatro implícito
    */
    void alta_proceso_espera(const string& prioridad, Proceso& proceso);

    /** @brief Elimina un proceso pendiente de la area de espera
        \pre El proceso existe 
        \post Elimina el proceso de mayor antiguedad de la prioridad del parámatro implícito
    */
    void eliminar_proceso_pendiente(const string& prioridad, Proceso& proceso);

    /** @brief Añade una prioridad a la area de espera
        \pre La prioridad no existe
        \post Añade la prioridad al parámatro implícito
    */
    void alta_prioridad(const string& prioridad);

    /** @brief Elimina una prioridad de la area de espera
        \pre La prioridad existe
        \post Elimina la prioridad del parámatro implícito
    */
    void baja_prioridad(const string& prioridad);

    /** @brief Envia n procesos de la area de espera al cluster en orden de prioridad
        \pre n es un entero no negativo
        \post Envia n procesos al cluster en orden de prioridad y los intenta colocar
    */
    void enviar_procesos_cluster(int n, Cluster& cluster);


    //Consultoras

    /** @brief Comprueba si existe una prioridad en la area de espera
        \pre <em>cierto</em>
        \post True si la prioridad existe en el parámetro implícito, false si contrario
    */
    bool existe_prioridad(const string& prioridad);

    /** @brief Comprueba si hay procesos pendientes
        \pre <em>cierto</em>
        \post True si existen procesos pendientes, false si no.
    */
    bool hay_procesos_pendientes(const string& prioridad);

    /** @brief Comprueba si existe un proceso en una prioridad
        \pre La prioridad existe
        \post True si el proceso existe en la prioridad del parámetro implícito, false si contrario
    */
    bool existe_proceso(const string& prioridad, Proceso& proceso);

    /** @brief Escribe todas las prioridades
        \pre <em>cierto</em>
        \post Escribe las prioridades del parámetro implícito
    */
    void imprimir_prioridad(const string& prioridad);

    /** @brief Escribe todos los procesos en el area de espera
        \pre <em>cierto</em>
        \post Escribe todos los procesos en espera del parámetro implícito
    */
    void imprimir_area_espera();

private:
    struct contenido {
        int colocados;
        int rechazados;
        list<Proceso> lista;
    };
    map<string, contenido> procesos_pendientes;
};
#endif
