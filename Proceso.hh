/** @file Proceso.hh
    @brief Especificación de la clase Prenda 
*/


#ifndef _PROCESO_HH_
#define _PROCESO_HH_

#ifndef NO_DIAGRAM          
#include <iostream>    
using namespace std;     
#endif                      

/** @class Proceso
    @brief Representa un proceso con identificador, ocupa una memoria y tiene una durada 
*/
class Proceso
{
public:
//Constructoras

  /** @brief Creadora por defecto. 

      Se ejecuta automáticamente al declarar un proceso.
      \pre <em>cierto</em>
      \post El resultado es un proceso no inicializado
  */   
Proceso();


//Modificadoras

  /** @brief Inicializa los atributos
      \pre <em>Cierto</em>
      \post El parámetro implícito se inicializa con sus características
  */
void inicializar();

  /** @brief Actualiza el tiempo de ejecucion restante del proceso
      \pre <em>Cierto</em>
      \post Actualiza el tiempo de ejecucion restante del parámetro implícito
  */
void modificar_tiempo_restante(const int& tiempo);

//Consultoras

  /** @brief Escribe el proceso con sus atributos
      \pre <em>Cierto</em>
      \post Se escriben los atributos del parámetro implícito
  */
void imprimir_proceso();

  /** @brief Escribe el proceso con sus atributos pero con el tiempo restante
      \pre <em>Cierto</em>
      \post Se escriben los atributos del parámetro implícito
  */
void imprimir_proceso_tiempo_dif();

  /** @brief Comprueba el identificador
      \pre <em>Cierto</em>
      \post Comprueba el identificador del parámetro implícito
  */
int identificador_del_proceso();

  /** @brief Comprueba la memoria que ocupa el proceso
      \pre <em>Cierto</em>
      \post Comprueba la memoria que ocupa el parámetro implícito
  */
int memoria_ocupada();

  /** @brief Comprueba el tiempo de ejecución del proceso
      \pre <em>Cierto</em>
      \post Comprueba el tiempo de ejecución del parámetro implícito
  */
int tiempo_ejecucion();

  /** @brief Comprueba el tiempo restante de ejecución del proceso
      \pre <em>Cierto</em>
      \post Comprueba el tiempo de ejecución restante del parámetro implícito
  */
int tiempo_ejecucion_restante();

private: 
    int identificador_proceso;
    int memoria_que_ocupa;
    int tiempo;
    int tiempo_restante;
};
#endif
