#include "Procesador.hh"

Procesador::Procesador() {
    size = 0;
}

void Procesador::inicializar() {
    cin >> size;
    set<int> nou_set;
    nou_set.insert(0);
    size_pos_memoria[size] = nou_set; 
    memoria_restante = size;
}

void Procesador::agregar_proceso_activo(Proceso& proceso) {
    
    // cout << "llego" << endl;

    //  map<int,set<int>>::iterator it_bucle = size_pos_memoria.begin();
    // // cout << "no llego" << endl;

    // cout << "antes app:" << endl;
    //  while (it_bucle != size_pos_memoria.end()) {
    //      cout << "tamaño:" << it_bucle->first << endl;
    //      cout << "pos:";
    //      set<int>::iterator it_set_bucle = it_bucle->second.begin();
    //      while (it_set_bucle != it_bucle->second.end()) {
    //          cout << *it_set_bucle << ' ';
    //          ++it_set_bucle;
    //      }
    //      ++it_bucle;
    //      cout << endl;
    //  }
    //busca el agujero mas pequeño que quepa y el iterador queda apuntando a él
    // cout << "que memoria:" << memoria_restante << endl;
    //si no hay nada
    
    if (memoria_restante < proceso.memoria_ocupada()) cout << "error: no cabe proceso" << endl;
    else {
        map<int,set<int>>::iterator it = size_pos_memoria.lower_bound(proceso.memoria_ocupada());
        if (it == size_pos_memoria.end()) cout << "error: no cabe proceso" << endl;
        else {
            set<int>::iterator it_set = it->second.begin();
            int pos_inicial = *it_set;
            pos_proceso[pos_inicial] = proceso;
            id_pos_memoria[proceso.identificador_del_proceso()] = pos_inicial;
            
            map<int, Proceso>::iterator it_pos_proceso = pos_proceso.begin();
            
            int restante = 0;
            restante = it->first - proceso.memoria_ocupada();
            if(it->second.size() == 1) {
                size_pos_memoria.erase(it);
            }
            else it->second.erase(it_set);  //borra la pos inicial de ese agujero
            it = size_pos_memoria.find(restante); //busca el agujero 
            
            if (it == size_pos_memoria.end() and restante != 0) {//no existe agujero de tal tamaño
                set<int> pos_restantes;
                pos_restantes.insert(pos_inicial + proceso.memoria_ocupada());
                size_pos_memoria[restante] = pos_restantes;
            }
            else { //existe agujero de tal tamaño
                if(restante != 0) it->second.insert(pos_inicial + proceso.memoria_ocupada());
            }
            actualizar_memoria_restante_sub(proceso);
        }
    }
    // it_bucle = size_pos_memoria.begin();
    // // // // cout << "no llego" << endl;
    //     cout << "despues app:" << endl;

    //   while (it_bucle != size_pos_memoria.end()) {
    //       cout << "tamaño:" << it_bucle->first << endl;
    //       cout << "pos:";
    //       set<int>::iterator it_set_bucle = it_bucle->second.begin();
    //       while (it_set_bucle != it_bucle->second.end()) {
    //           cout << *it_set_bucle << ' ';
    //           ++it_set_bucle;
    //       }
    //       ++it_bucle;
    //       cout << endl;
    //   }
}

void Procesador::elimina_proceso_activo_directo(const int& identificador_proceso) {
    map<int, Proceso>::iterator it_pos_proceso;
    map<int, int>::iterator it_id_memoria;
    map<int,set<int>>::iterator it_huecos;

    //   map<int,set<int>>::iterator it_bucle = size_pos_memoria.begin();
    // // // // cout << "no llego" << endl;

    //   while (it_bucle != size_pos_memoria.end()) {
    //       cout << "tamaño:" << it_bucle->first << endl;
    //       cout << "pos:";
    //       set<int>::iterator it_set_bucle = it_bucle->second.begin();
    //       while (it_set_bucle != it_bucle->second.end()) {
    //           cout << *it_set_bucle << ' ';
    //           ++it_set_bucle;
    //       }
    //       ++it_bucle;
    //       cout << endl;
    //   }


    //tiene mas de un proceso
    if(pos_proceso.size() > 1) {
        map<int, Proceso>::iterator it_movil;
        it_id_memoria = id_pos_memoria.find(identificador_proceso); //encontrar la posicion del que queremos borrar
        it_pos_proceso = pos_proceso.find(it_id_memoria->second); //encontrar el proceso del que queremos borrar
        set<int>::iterator it_set;
        int size_nou_forat = 0;
        int nou_pos;

        //si la posicion del proceso es igual a 0 significa que esta al principio de todo
        if(it_pos_proceso->first == 0) {
            it_movil = ++it_pos_proceso; //estara apuntando al siguiente elemento 
            --it_pos_proceso;
            //si es mas grande que 0 significa que entre ellos hay un agujero
            if((it_movil->first - (it_pos_proceso->first + it_pos_proceso->second.memoria_ocupada())) > 0) {
                size_nou_forat = (it_movil->first - (it_pos_proceso->first + it_pos_proceso->second.memoria_ocupada())) + it_pos_proceso->second.memoria_ocupada();
                // cout << "first" << ' ' << memoria_restante << endl;

                //agrega el nuevo agujero
                it_huecos = size_pos_memoria.find(size_nou_forat);
                if (it_huecos != size_pos_memoria.end()) {
                    it_huecos->second.insert(0);
                }
                else {
                    set<int> nou_set;
                    nou_set.insert(0);
                    size_pos_memoria[size_nou_forat] = nou_set;
                }

                //lo borra
                it_huecos = size_pos_memoria.find(it_movil->first - (it_pos_proceso->first+it_pos_proceso->second.memoria_ocupada()));
                if(it_huecos->second.size() == 1)  {
                    size_pos_memoria.erase(it_huecos);
                }
                else {
                    it_set = it_huecos->second.find((it_pos_proceso->first+it_pos_proceso->second.memoria_ocupada()));
                    it_huecos->second.erase(it_set);
                }
            }
            //si es 0 significa que no hay agujero
            else {
                size_nou_forat = it_pos_proceso->second.memoria_ocupada();
                // cout << "first else" << ' ' << memoria_restante << endl;
                it_huecos = size_pos_memoria.find(size_nou_forat);
                if (it_huecos != size_pos_memoria.end()) {
                    it_huecos->second.insert(0);
                }
                else {
                    set<int> nou_set;
                    nou_set.insert(0);
                    size_pos_memoria[size_nou_forat] = nou_set;
                }
            }
            actualizar_memoria_restante_add(it_pos_proceso->second.memoria_ocupada());
        }
        //si el proceso al que apuntamos, su posicion + su tamaño = al size significa que es el ultimo
        else if((it_pos_proceso->first + it_pos_proceso->second.memoria_ocupada()) == size) {
            it_movil = --it_pos_proceso;
            ++it_pos_proceso;
            //hay agujero
            if((it_pos_proceso->first - (it_movil->first + it_movil->second.memoria_ocupada())) > 0) {
                size_nou_forat = (it_pos_proceso->first - (it_movil->first + it_movil->second.memoria_ocupada())) + it_pos_proceso->second.memoria_ocupada();
                // cout << "final agujero" << ' ' << memoria_restante << endl;
                it_huecos  = size_pos_memoria.find(size_nou_forat);
                nou_pos = it_movil->first + it_movil->second.memoria_ocupada();
                if (it_huecos != size_pos_memoria.end()) {
                    it_huecos->second.insert(nou_pos);
                }
                else {
                    set<int> nou_set;
                    nou_set.insert(nou_pos);
                    size_pos_memoria[size_nou_forat] = nou_set;
                }

                it_huecos = size_pos_memoria.find(it_pos_proceso->first - (it_movil->first+it_movil->second.memoria_ocupada()));
                if(it_huecos->second.size() == 1)  {
                    size_pos_memoria.erase(it_huecos);
                }
                else {
                    it_set = it_huecos->second.find((it_movil->first+it_movil->second.memoria_ocupada()));
                    it_huecos->second.erase(it_set);
                }
            }
        
            //no hay agujero
            else {
                size_nou_forat = it_pos_proceso->second.memoria_ocupada();
                // cout << "final no hay agujero" << ' ' << memoria_restante << endl;
                it_huecos  = size_pos_memoria.find(size_nou_forat);
                nou_pos = it_pos_proceso->first;
                if (it_huecos != size_pos_memoria.end()) {
                    it_huecos->second.insert(nou_pos);
                }
                else {
                    set<int> nou_set;
                    nou_set.insert(nou_pos);
                    size_pos_memoria[size_nou_forat] = nou_set;
                }
            }
            actualizar_memoria_restante_add(it_pos_proceso->second.memoria_ocupada());
        }
        //cualquier otro caso estara en medio del vector y tendra alguno delante o alguno detras o los dos
        else {
            // cout << "medio" << endl;
            map<int, Proceso>::iterator it_movil2;
            bool before = false;
            bool after = false;
            it_movil2 = pos_proceso.end();
            --it_movil2;
            it_movil = pos_proceso.begin();
        
            if(it_movil2 != it_pos_proceso) {
                after = true;
            }
            if(it_movil != it_pos_proceso) {
                before = true;
            }
            //hay un proceso antes y uno despues
            if(before and after) {
                // cout << "estoy aqui" << endl;
                it_movil = --it_pos_proceso;
                ++it_pos_proceso;
                it_movil2 = ++it_pos_proceso;
                --it_pos_proceso;
                bool agujero_antes = false;
                bool agujero_despues = false;

                if((it_pos_proceso->first - (it_movil->first + it_movil->second.memoria_ocupada())) > 0) agujero_antes = true;
                if((it_movil2->first -(it_pos_proceso->first + it_pos_proceso->second.memoria_ocupada())) > 0) agujero_despues = true;
                
                //borrar agujero anterior
                if(agujero_antes and agujero_despues) {
                    //borrar el anterior
                    it_huecos = size_pos_memoria.find(it_pos_proceso->first - (it_movil->first+it_movil->second.memoria_ocupada()));
                    if(it_huecos->second.size() == 1)  {
                        size_pos_memoria.erase(it_huecos);
                    }
                    else {
                        it_set = it_huecos->second.find((it_movil->first+it_movil->second.memoria_ocupada()));
                        it_huecos->second.erase(it_set);
                    }
                    //borrar el siguiente
                    it_huecos = size_pos_memoria.find((it_movil2->first -(it_pos_proceso->first + it_pos_proceso->second.memoria_ocupada())));
                    if(it_huecos->second.size() == 1)  {
                        size_pos_memoria.erase(it_huecos);
                    }
                    else {
                        it_set = it_huecos->second.find((it_pos_proceso->first+it_pos_proceso->second.memoria_ocupada()));
                        it_huecos->second.erase(it_set);
                    }
                }
                else if(agujero_antes) {
                    //borrar el anterior
                    it_huecos = size_pos_memoria.find(it_pos_proceso->first - (it_movil->first+it_movil->second.memoria_ocupada()));
                    if(it_huecos->second.size() == 1)  {
                        size_pos_memoria.erase(it_huecos);
                    }
                    else {
                        it_set = it_huecos->second.find((it_movil->first+it_movil->second.memoria_ocupada()));
                        it_huecos->second.erase(it_set);
                    }
                }
                else if(agujero_despues) {
                    //borrar el siguiente
                    it_huecos = size_pos_memoria.find((it_movil2->first -(it_pos_proceso->first + it_pos_proceso->second.memoria_ocupada())));
                    if(it_huecos->second.size() == 1)  {
                        size_pos_memoria.erase(it_huecos);
                    }
                    else {
                        it_set = it_huecos->second.find((it_pos_proceso->first+it_pos_proceso->second.memoria_ocupada()));
                        it_huecos->second.erase(it_set);
                    }
                }

                if(agujero_antes) {
                    nou_pos = it_movil->first + it_movil->second.memoria_ocupada();
                }
                else {
                    nou_pos = it_pos_proceso->first;
                }

                size_nou_forat = it_movil2->first - (it_movil->first + it_movil->second.memoria_ocupada());
                it_huecos  = size_pos_memoria.find(size_nou_forat);
                
                if (it_huecos != size_pos_memoria.end()) {
                    it_huecos->second.insert(nou_pos);
                }
                else {
                    set<int> nou_set;
                    nou_set.insert(nou_pos);
                    size_pos_memoria[size_nou_forat] = nou_set;
                }
            }
            else if(before) {
                it_movil = --it_pos_proceso;
                ++it_pos_proceso;
                bool agujero_antes = false;
                
                // cout << it_pos_proceso->second.identificador_del_proceso() << endl;
                // cout << it_movil->second.identificador_del_proceso() << endl;

                //borrar agujero
                if((it_pos_proceso->first - (it_movil->first + it_movil->second.memoria_ocupada())) > 0) agujero_antes = true;
                if(agujero_antes) {
                    //borrar el anterior
                    it_huecos = size_pos_memoria.find(it_pos_proceso->first - (it_movil->first+it_movil->second.memoria_ocupada()));
                    if(it_huecos->second.size() == 1)  {
                        size_pos_memoria.erase(it_huecos);
                    }
                    else {
                        it_set = it_huecos->second.find((it_movil->first+it_movil->second.memoria_ocupada()));
                        it_huecos->second.erase(it_set);
                    }
                    //borrar el del final
                    it_huecos = size_pos_memoria.find(size - (it_pos_proceso->first + it_pos_proceso->second.memoria_ocupada()));
                    if(it_huecos->second.size() == 1)  {
                        size_pos_memoria.erase(it_huecos);
                    }
                    else {
                        it_set = it_huecos->second.find((it_pos_proceso->first+it_pos_proceso->second.memoria_ocupada()));
                        it_huecos->second.erase(it_set);
                    }
                }
                else {
                    //borrar el del final
                    // cout << "size:" << size << endl;
                    it_huecos = size_pos_memoria.find(size - (it_pos_proceso->first + it_pos_proceso->second.memoria_ocupada()));
                    if(it_huecos->second.size() == 1)  {
                        size_pos_memoria.erase(it_huecos);
                    }
                    else {
                        it_set = it_huecos->second.find((it_pos_proceso->first+it_pos_proceso->second.memoria_ocupada()));
                        it_huecos->second.erase(it_set);
                    }
                }
                size_nou_forat = size - it_pos_proceso->first;
                // cout << "size nou forat: " << size_nou_forat << endl;
                it_huecos = size_pos_memoria.find(size_nou_forat);
                if(size_nou_forat > 0) {
                    nou_pos = it_movil->first + it_movil->second.memoria_ocupada();
                }
                else nou_pos = it_pos_proceso->first;
                
                if(it_huecos != size_pos_memoria.end()) {
                    it_huecos->second.insert(nou_pos);
                }
                else {
                    set<int> nou_set;
                    nou_set.insert(nou_pos);
                    size_pos_memoria[size_nou_forat] = nou_set;
                }
            }
            else {
                it_movil = ++it_pos_proceso;
                --it_pos_proceso;
                bool agujero_despues = false;

                //borrar agujero
                if((it_movil->first -(it_pos_proceso->first + it_pos_proceso->second.memoria_ocupada())) > 0) agujero_despues = true;
                if(agujero_despues) {
                    //borrar el despues
                    it_huecos = size_pos_memoria.find(it_movil->first - (it_pos_proceso->first+it_pos_proceso->second.memoria_ocupada()));
                    if(it_huecos->second.size() == 1)  {
                        size_pos_memoria.erase(it_huecos);
                    }
                    else {
                        it_set = it_huecos->second.find((it_pos_proceso->first+it_pos_proceso->second.memoria_ocupada()));
                        it_huecos->second.erase(it_set);
                    }
                    //borrar el del inicio
                    it_huecos = size_pos_memoria.find(it_pos_proceso->first);
                    if(it_huecos->second.size() == 1)  {
                        size_pos_memoria.erase(it_huecos);
                    }
                    else {
                        it_set = it_huecos->second.find(0);
                        it_huecos->second.erase(it_set);
                    }
                }
                else {
                    //borrar el del inicio
                    it_huecos = size_pos_memoria.find(it_pos_proceso->first);
                    if(it_huecos->second.size() == 1)  {
                        // cout << it_huecos->first << endl;
                        size_pos_memoria.erase(it_huecos);
                        // cout << "puta" << endl;
                    }
                    else {
                        it_set = it_huecos->second.find(0);
                        it_huecos->second.erase(it_set);
                    }
                }

                size_nou_forat = it_movil->first;
                it_huecos = size_pos_memoria.find(size_nou_forat);
                nou_pos = 0;
                
                if(it_huecos != size_pos_memoria.end()) {
                    it_huecos->second.insert(nou_pos);
                }
                else {
                    set<int> nou_set;
                    nou_set.insert(nou_pos);
                    size_pos_memoria[size_nou_forat] = nou_set;
                }
            }
            actualizar_memoria_restante_add(it_pos_proceso->second.memoria_ocupada());
        }
        pos_proceso.erase(it_pos_proceso);
        id_pos_memoria.erase(it_id_memoria);
    }
    //solo tiene un proceso
    else {
        // cout << "solo uno" << endl;
        it_id_memoria = id_pos_memoria.find(identificador_proceso); //encontrar la posicion
        it_pos_proceso = pos_proceso.find(it_id_memoria->second); //encontrar el proceso

        size_pos_memoria.clear();
        actualizar_memoria_restante_add(it_pos_proceso->second.memoria_ocupada());
        set<int> nou_set;
        nou_set.insert(0);
        size_pos_memoria[size] = nou_set;

        pos_proceso.erase(it_pos_proceso);
        id_pos_memoria.erase(it_id_memoria);
    }

    // it_bucle = size_pos_memoria.begin();
    //  while (it_bucle != size_pos_memoria.end()) {
    //      cout << "tamaño:" << it_bucle->first << endl;
    //      cout << "pos:";
    //      set<int>::iterator it_set_bucle = it_bucle->second.begin();
    //      while (it_set_bucle != it_bucle->second.end()) {
    //          cout << *it_set_bucle << ' ';
    //          ++it_set_bucle;
    //      }
    //      ++it_bucle;
    //      cout << endl;
    //  }
}

void Procesador::elimina_proceso_activo_tiempo(const int& tiempo_actual) {
    map<int,Proceso>::iterator it = pos_proceso.begin();

    while (it != pos_proceso.end()) {
        Proceso &p = it->second;
        ++it;
        p.modificar_tiempo_restante(tiempo_actual);
        if (p.tiempo_ejecucion_restante() <= 0) {
            elimina_proceso_activo_directo(p.identificador_del_proceso());
        }
    }
}

//Consultoras

bool Procesador::procesador_activo() {
    if (pos_proceso.size() == 0) return false;
    return true;
}

bool Procesador::contiene_proceso(const int& identificador_proceso) {
    map<int,int>::iterator it = id_pos_memoria.find(identificador_proceso);
    if (it != id_pos_memoria.end()) return true;
    return false;
}

void Procesador::imprimir_procesador_procesador() {
    map<int,Proceso>::iterator it = pos_proceso.begin();
    while (it != pos_proceso.end()) {
        cout << it->first << ' ';
        it->second.imprimir_proceso_tiempo_dif();
        cout << endl;
        ++it;
    }
}

void Procesador::actualizar_memoria_restante_add(int size) {
    memoria_restante = memoria_restante + size;
}

void Procesador::actualizar_memoria_restante_sub(Proceso& proceso) {
    memoria_restante = memoria_restante - proceso.memoria_ocupada();
}

void Procesador::compactar() {
    if(pos_proceso.size() > 0) {
        map<int, Proceso>::iterator it_pos_proceso = pos_proceso.begin();
        map<int,int>::iterator it_id_memoria =  id_pos_memoria.find(it_pos_proceso->second.identificador_del_proceso());
        int nou_pos = 0;

        //el primero no esta justamente al principio
        if (it_pos_proceso->first != 0) {
            pos_proceso[0] = it_pos_proceso->second;
            id_pos_memoria[it_pos_proceso->second.identificador_del_proceso()] = 0;
            // cout << it_pos_proceso->second.identificador_del_proceso() << endl;
            it_pos_proceso = pos_proceso.erase(it_pos_proceso);
            --it_pos_proceso;
            // cout << it_pos_proceso->second.identificador_del_proceso() << endl;

        }
        nou_pos = it_pos_proceso->second.memoria_ocupada();
        if (pos_proceso.size() > 1){
            ++it_pos_proceso;
            // cout << it_pos_proceso->second.identificador_del_proceso() << endl;
        }

        //casos siguientes
        while (it_pos_proceso != pos_proceso.end() and pos_proceso.size() > 1) {
            if (it_pos_proceso->first != nou_pos) {
                pos_proceso[nou_pos] = it_pos_proceso->second;
                id_pos_memoria[it_pos_proceso->second.identificador_del_proceso()] = nou_pos;
                nou_pos = nou_pos + it_pos_proceso->second.memoria_ocupada();

                it_pos_proceso = pos_proceso.erase(it_pos_proceso);
            }
            else {
                nou_pos = nou_pos + it_pos_proceso->second.memoria_ocupada();
                ++it_pos_proceso;
            }
        }
        size_pos_memoria.clear();
        set<int> nou_set;
        // cout << "nou pos: " << nou_pos << endl;
        nou_set.insert(nou_pos);
        size_pos_memoria[size - nou_pos] = nou_set;
    }
}

int Procesador::cantidad_memoria_libre() {
    return memoria_restante;
}

int Procesador::revisar_agujeros(const int& memoria_proceso) {
    map<int, set<int>>::iterator it = size_pos_memoria.lower_bound(memoria_proceso);
    if(it == size_pos_memoria.end()) return -1;
    return it->first;
}

void Procesador::imprimirmapa() {
    map<int,Proceso>::iterator it = pos_proceso.begin();
    while(it != pos_proceso.end()) {
        cout << it->second.identificador_del_proceso() << endl;
        ++it;
    }
}