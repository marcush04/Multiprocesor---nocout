/** @file Cluster.hh
    @brief Especificación de la clase Cluster 
*/

#ifndef _CLUSTER_HH_
#define _CLUSTER_HH_

#include "Procesador.hh"

#ifndef NO_DIAGRAM  
#include <map>
#include "BinTree.hh"
#include <iostream>
#include <queue>
using namespace std;
#endif

/** @class Cluster
    @brief Representa un cluster 

    Dispone de una serie de procesadores ubicados en forma de árbol y un tiempo pasivo.
*/
class Cluster
  {

public:
//Constructoras

  /** @brief Creadora por defecto. 

      Se ejecuta automáticamente al declarar un cluster.
      \pre <em>cierto</em>
      \post El resultado es un cluster no inicializado
  */  
Cluster();


//Modificadoras

  /** @brief Inicializa el cluster
      \pre El parámetro implícito no está inicializado
      \post El parámetro implícito pasa a estar inicializado 
  */
void configurar_cluster();

  /** @brief Inicializa el cluster
      \pre El procesador existe, no tiene procesos en ejecución y no tiene procesadores auxiliares
      \post El nuevo cluster se coloca en el lugar de el procesador del parámetro implícito
  */
void modificar_cluster(const string& identificador_procesador);

  /** @brief Substituye una hoja del parámetro implícito con otro cluster
      \pre El parámetro implícito esta inicializado, y no habra repetición de identificadores y la hoja existe y esta inactiva.
      \post Agrega el nuevo cluster al P.I.
  */
void agregar_rama(const Cluster& cluster_nuevo);

  /** @brief El proceso se ejecuta en el procesador y ocupa memoria
      \pre El procesador existe y el proceso se puede colocar 
      \post El proceso pasa a ejecutarse en el procesador y ocupa una memoria en él
  */
void alta_proceso_procesador(const string& identificador_procesador, Proceso proceso);

  /** @brief El proceso deja de ejecutarse en el procesador y libera memoria
      \pre El procesador existe y el proceso se esta ejecutando
      \post El proceso deja de ejecutarse en el procesador
  */
void baja_proceso_procesador(const string& identificador_procesador,const int& identificador_proceso);

  /** @brief Elimina los procesos activos que hayan acabado en un intervalo de tiempo (t)
      \pre t es un entero no negativo
      \post Elimina los procesos activos del parámetro implícito que hayan acabado en un tiempo(t)
  */
void avanzar_tiempo(const int& tiempo);

  /** @brief Mueve todos los procesos hacia el principio de la memoria del procesador
      \pre El procesador existe
      \post Mueve todos los procesos hacia el principio de la memoria del procesador del parámetro implícito, sin dejar huecos, sin solaparse y respetando el orden inicial
  */
void compactar_memoria_procesador(const string& identificador_procesador);

  /** @brief Mueve todos los procesos hacia el principio de la memoria de todos los procesadores del cluster
      \pre <em>cierto</em>
      \post Mueve todos los procesos hacia el principio de la memoria de todos los procesadores del parámetro implícito, sin dejar huecos, sin solaparse y respetando el orden inicial
  */
void compactar_memoria_cluster();

//Consultoras

  /** @brief Comprueba si existe un procesador en el cluster
      \pre <em>Cierto</em>
      \post Comprueba si el procesador existe en el parámetro implícito
  */
bool existe_procesador(const string& identificador_procesador);

  /** @brief Escribe la estructura del cluster
      \pre El cluster esta inicializado
      \post Escribe la estructura del parámetro implícito
  */
void imprimir_arbol_i(const BinTree<string>& a);

  /** @brief Llama a la función imprimir_arbol_i
      \pre El cluster esta inicializado
      \post Llama a la función imprimir_arbol_i
  */
void imprimir_arbol();

  /** @brief Escribe los procesos de el procesador 
      \pre El procesador existe en el parámetro implícit
      \post Escribe los procesos de dicho procesador por orden creciente de primera posición de memoria, incluyendo dicha posición y el resto de datos de cada proceso
  */
void imprimir_procesador(const string& identificador_procesador);

  /** @brief Escribe los procesos de todos los procesadores 
      \pre El procesador existe en el parámetro implícit
      \post Escribe los procesos de todos los procesadores del parámetro implícito por orden creciente de primera posición de memoria, incluyendo dicha posición y el resto de datos de cada proceso
  */
void imprimir_procesadores_cluster();

  /** @brief Comprueba el tiempo transcurrido del cluster
      \pre <em>Cierto</em>
      \post Comprueba el tiempo transcurrido del parámetro implícito
  */
int que_tiempo_procesadores();

  /** @brief Devuelve el identificador del procesador en que se tendra que colocar el proceso si no cabe devuelve -1
      \pre <em>Cierto</em>
      \post Devuelve el identificador del procesador del parámetro implícito donde se tendrá que colocar el proceso
  */
string agujero_ajustado(Proceso& proceso);

  /** @brief Devuelve el iterador apuntando al iterador con id = procesador_id
      \pre <em>Cierto</em>
      \post Devuelve el iterador apuntando al iterador del parámetro implícito con id = procesador_id
  */
map<string, Procesador>::iterator devuelve_iterator(const string& procesador_id);

private:
    int cantidad_procesadores;
    BinTree<string> estructura_procesadores;
    map<string, Procesador> procesadores;
    int tiempo_procesadores;
};
#endif
