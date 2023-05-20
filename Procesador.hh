/** @file Procesador.hh
    @brief Especificación de la clase Procesador 
*/


#ifndef _PROCESADOR_HH_
#define _PROCESADOR_HH_

#include "Proceso.hh"

#ifndef NO_DIAGRAM          
#include <list>      
#include <iostream>   
#include <string>
#include <map>
#include <set>
using namespace std;
#endif                      

/** @class Procesador
    @brief Representa un procesador con memoria
*/
class Procesador
{
public:
//Constructoras 

  /** @brief Creadora por defecto. 

      Se ejecuta automáticamente al declarar un procesador.
      \pre <em>Cierto</em>
      \post El resultado es un procesador vacio
  */   
Procesador();


//Modificadoras

  /** @brief Inicializa los parámetros del procesador 

      \pre El parámetro implícito no está inicializado
      \post El parámetro implícito pasa a estar inicializado
  */   
void inicializar();

  /** @brief Comprueba que el proceso cabe y lo agrega al procesador

      \pre <em>Cierto</em>
      \post El proceso se ejecuta en el parámetro implícito y ocupa memoria
  */  
void agregar_proceso_activo(Proceso& proceso);

  /** @brief Elimina un proceso del procesador

      \pre <em>Cierto</em>
      \post El proceso deja de ejecutarse en el parámetro implícito y libera memoria
  */  
void elimina_proceso_activo_directo(const int& identificador_proceso);

  /** @brief Elimina un proceso del procesador si ha transcurrido el suficiente tiempo

      \pre <em>Cierto</em>, el tiempo es un entero no negativo
      \post El proceso deja de ejecutarse en el parámetro implícito y libera memoria si solo si ha superado o igualado el tiempo del cluster
  */  
void elimina_proceso_activo_tiempo(const int& tiempo_actual);

  /** @brief Compacta los procesos activos en el procesador

      \pre Hay memoria libre
      \post Se han compactado los procesos del parámetro implícito
  */  
void compactar();

  /** @brief Ocupa memoria del procesador
      \pre <em>Cierto</em>
      \post Ocupa memoria del parámetro implícito
  */
void ocupar_memoria();

  /** @brief Libera memoria del procesador
      \pre <em>Cierto</em>
      \post Libera memoria del parámetro implícito
  */
void liberar_memoria();

//Consultoras

  /** @brief Comprueba si el procesador tiene procesos activos
      \pre <em>Cierto</em>
      \post Comprueba si el parámetro implícito tiene procesos activos, true si tiene, false contrario
  */
bool procesador_activo();

  /** @brief Comprueba si el procesador es hoja
      \pre <em>Cierto</em>
      \post Comprueba si el parámetro implícito es hoja, true si es hoja, false contrario
  */
bool es_hoja();

  /** @brief Comprueba si el procesador tiene activo ese proceso
      \pre <em>Cierto</em>
      \post Comprueba si el parámetro implícito tiene activo el proceso
  */
bool contiene_proceso(const int& identificador_proceso);

  /** @brief Escribe los procesos activos del procesador
      \pre El parámetro implícito no está vacio
      \post Escribe los procesos activos del parámtro implícito en orden creciente y con los datos de cada proceso
  */
void imprimir_procesador_procesador(); //falta hacer una funcion en el proceso

  /** @brief Comprueba la cantidad de memoria del procesador
      \pre <em>Cierto</em>
      \post Comprueba la memoria del parámetro implícito
  */
int que_size();

  /** @brief Comprueba la cantidad de memoria libre del procesador
      \pre <em>Cierto</em>
      \post Comprueba la memoria libre del parámetro implícito
  */
int cantidad_memoria_libre();

  /** @brief Comprueba la cantidad de memoria ocupada del procesador
      \pre <em>Cierto</em>
      \post Comprueba la memoria ocupada del parámetro implícito
  */
int cantidad_memoria_ocupada();

  /** @brief Actualiza el espacio de memoria restante cuando borremos un proceso
      \pre <em>Cierto</em>
      \post Actualiza el espacio de memoria restante del parámetro implícito cuando borremos un proceso
  */
void actualizar_memoria_restante_add(int size);

  /** @brief Actualiza el espacio de memoria restante cuando añadamos un proceso
      \pre <em>Cierto</em>
      \post Actualiza el espacio de memoria restante del parámetro implícito cuando añadamos un proceso
  */
void actualizar_memoria_restante_sub(Proceso& proceso);

  /** @brief Devuelve el tamaño del agujero más pequeño y a la vez mas grande o igual que lo que ocupa el proceso
      \pre memoria_proceso > 0
      \post Devuelve el tamaño del agujero más pequeño y a la vez mas grande o igual que lo que ocupa el proceso del parámetro implícito
  */
int revisar_agujeros(const int& memoria_proceso);

void imprimirmapa();


private:
      int size;
      int memoria_restante;
      map<int, Proceso> pos_proceso;//Pos inicial y proceso
      map<int,int> id_pos_memoria;//Id proceso y posicion proceso
      map<int,set<int>> size_pos_memoria;//tamaño del hueco y posiciones donde esta 
  };
#endif
