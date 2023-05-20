#include "Cluster.hh"

Cluster::Cluster() {

}

//Modificadoras
void leer_arbol(BinTree<string>& a, map<string, Procesador>& p) {
    string nom_procesador;
    cin >> nom_procesador;
    if (nom_procesador != "*") {
       Procesador procesador;
       procesador.inicializar();
       BinTree<string> left;
       BinTree<string> right;
       leer_arbol(left, p);
       leer_arbol(right, p);
       a = BinTree<string>(nom_procesador, left, right);
       p[nom_procesador] = procesador;
    }
}

void Cluster::configurar_cluster() {
    procesadores.clear();
    tiempo_procesadores = 0;
    leer_arbol(estructura_procesadores, procesadores);
}

bool grapar(const string& identificador_procesador, BinTree<string>& arbol_previo, BinTree<string>& arbol_grapar) {
    if(arbol_previo.empty()) return true;
    else {
        BinTree<string>left = arbol_previo.left();
        BinTree<string>right = arbol_previo.right();
        //si lo encuentra
        if(arbol_previo.value() == identificador_procesador) {
            //si no tiene hijos
            if(left.empty() and right.empty()) {
                arbol_previo = arbol_grapar;
                return true;
            }
            else return false;
        }
        bool left_bool = grapar(identificador_procesador, left, arbol_grapar);
        bool right_bool = grapar(identificador_procesador, right, arbol_grapar);
        string id = arbol_previo.value();
        arbol_previo = BinTree<string>(id, left, right);
        return left_bool and right_bool;
    }
    return true;
}

void Cluster::modificar_cluster(const string& identificador_procesador){
    map<string, Procesador> procesador_nuevo;
    BinTree<string> estructura_procesadores_nuevo;
    leer_arbol(estructura_procesadores_nuevo, procesador_nuevo);
    map<string, Procesador>::iterator it = procesadores.find(identificador_procesador);
    if(it  != procesadores.end()) {
        if (not it->second.procesador_activo()) {
            if(grapar(identificador_procesador, estructura_procesadores, estructura_procesadores_nuevo)) {
                procesadores.erase(it);
                procesadores.insert(procesador_nuevo.begin(), procesador_nuevo.end());
            }
            else cout << "error: procesador con auxiliares" << endl;
        }
        else  cout << "error: procesador con procesos" << endl;
    }
    else cout << "error: no existe procesador" << endl;
}

void Cluster::alta_proceso_procesador(const string& identificador_procesador, Proceso proceso) {
    map<string, Procesador>::iterator it = procesadores.find(identificador_procesador);
    if (it != procesadores.end()) {
        if(it->second.contiene_proceso(proceso.identificador_del_proceso())) {
            cout << "error: ya existe proceso" << endl;
        }
        else {
            it->second.agregar_proceso_activo(proceso);
        } 
    }
    else cout << "error: no existe procesador" << endl;
}

void Cluster::baja_proceso_procesador(const string& identificador_procesador, const int& identificador_proceso) {
    map<string, Procesador>::iterator it = procesadores.find(identificador_procesador);
    if (it != procesadores.end()) {
        if(it->second.contiene_proceso(identificador_proceso)) {
            it->second.elimina_proceso_activo_directo(identificador_proceso);
        }
        else cout << "error: no existe proceso" << endl;
    }
    else cout << "error: no existe procesador" << endl;
}

string Cluster::agujero_ajustado(Proceso& proceso) {
    map<string, Procesador>::iterator it = procesadores.begin();
    queue<BinTree<string>> cola;
    cola.push(estructura_procesadores);
        
    string id_procesador_temp = "0";
    int agujero_min = -1;
    bool primera = true;
    
    while (not cola.empty()) {
        //copia el arbol
        BinTree<string> arbol(cola.front());
        map <string, Procesador>::iterator it2 = procesadores.find(arbol.value());
        int agujero = it2->second.revisar_agujeros(proceso.memoria_ocupada());
       

        if(not arbol.left().empty()) cola.push(arbol.left());
        if(not arbol.right().empty()) cola.push(arbol.right());
        
        if(agujero != -1 and not it2->second.contiene_proceso(proceso.identificador_del_proceso())) {
            if(primera or agujero < agujero_min) {
                id_procesador_temp = it2->first;
                agujero_min = agujero;
                it = it2;
                primera = false;
            }
            else if((agujero == agujero_min) and (it2->second.cantidad_memoria_libre() > it->second.cantidad_memoria_libre())) {
                id_procesador_temp = it2->first;
            }
        }
        cola.pop();
    }
    if (agujero_min != -1) {
        return id_procesador_temp;
    } 
    else return "-1";
    // //comprobar los siguientes
    // while(it != procesadores.end()) {
    //     //mira si almenos cabe el proceso sino hace skip
    //     if (it->second.cantidad_memoria_libre() >= proceso.memoria_ocupada()) {
    //         int agujero = it->second.revisar_agujeros(proceso.memoria_ocupada());
    //         //si el agujero es del tamaño del proceso lo devuelve
    //         if(agujero == proceso.memoria_ocupada()) {
    //             return it->first;
    //         }
    //         //este procesador sera el nuevo
    //         else {
    //             if(agujero < agujero_min and agujero != -1) {
    //                 id_procesador_temp = it->first;
    //                 agujero_min = agujero;
    //             }
    //         }
    //     }
    //     ++it;
    // }
    
    // return id_procesador_temp;
}

void Cluster::avanzar_tiempo(const int& tiempo) {
    map<string, Procesador>::iterator it = procesadores.begin();
    while (it != procesadores.end()) {
        it->second.elimina_proceso_activo_tiempo(tiempo);
        ++it;
    }
}

void Cluster::compactar_memoria_procesador(const string& identificador_procesador) {
    if(existe_procesador(identificador_procesador)) {
        map<string, Procesador>::iterator it = procesadores.find(identificador_procesador);
        it->second.compactar();
    }
    else cout << "error: no existe procesador" << endl;
}

void Cluster::compactar_memoria_cluster() {
    map<string, Procesador>::iterator it = procesadores.begin();
    while (it != procesadores.end()) {
        compactar_memoria_procesador(it->first);
        ++it;
    }
}

//Consultoras
bool Cluster::existe_procesador(const string& identificador_procesador) {
    map<string, Procesador>::iterator it = procesadores.find(identificador_procesador);
    if(it != procesadores.end()) return true;
    return false;
}


void Cluster::imprimir_arbol_i(const BinTree<string>& a) {
    if (not a.empty()) {
        cout << "(" << a.value();
        imprimir_arbol_i(a.left());
        imprimir_arbol_i(a.right());
        cout << ")";
    }
    else cout << " ";
}

void Cluster::imprimir_arbol() {
    imprimir_arbol_i(estructura_procesadores);
    cout << endl;
}


void Cluster::imprimir_procesador(const string& identificador_procesador) {
    map<string, Procesador>::iterator it = procesadores.find(identificador_procesador);
    if(not existe_procesador(identificador_procesador)) cout << "error: no existe procesador" << endl;
    else it->second.imprimir_procesador_procesador();
}

void Cluster::imprimir_procesadores_cluster() {
    map<string, Procesador>::iterator it = procesadores.begin();
    while (it != procesadores.end()) {
        cout << it->first << endl;
        imprimir_procesador(it->first);
        ++it;
    }
}

int Cluster::que_tiempo_procesadores() {
    return tiempo_procesadores;
}

map<string, Procesador>::iterator Cluster::devuelve_iterator(const string& procesador_id) {
  map<string, Procesador>::iterator it = procesadores.find(procesador_id);
  return it;
}