//BENEMERITA UNIVERSIDAD AUTONOMA DE PUEBLA
//FACULTAD DE CIENCIAS DE LA COMPUTACION
// - - - EQUIPO 6 "ASDASDASD" - - -
#include <iostream>
#include <conio.h>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

//Pausa
int pause;
int totalnodos = 0;

//Nodos de la lista principal
struct nodo {
    char    info;//nombre del vertice o nodo
    bool    visitado;
    struct  nodo* sig;
    struct  nodito* ady;//puntero hacia la primera arista del nodo
};

//Uniones a otros nodos de la lista principal
struct nodito {
    int    peso;
    struct nodo* destino;//puntero al nodo de llegada
    struct nodito* sig;
};

//Redefiniciones
typedef struct nodo* Nodo;//  Tipo Nodo
typedef struct nodito* Arista; //Tipo Arista

Nodo head; //puntero cabeza

// - - > PROTOTIPOS
void menu();
void insertarNodo();
void agregarArista(Nodo&, Nodo&, Arista&,int);
void insertarArista();
void showMultilista();
void clearCola(queue<Nodo>&);
void clearTrueVisit(Nodo);
void RecorridoAncho(char);
void RecorridoProfundo(char);
void BPP(Nodo);
void kruskal(char);
void Ayuda(Nodo);
void exit();

// - - > MAIN
int main() {
    head = NULL;
    int  op;
    char BFS;

    do {
        menu();
        cin >> op;

        switch (op) {
        case 1:
            insertarNodo();
            break;
        case 2:
            insertarArista();
            break;
        case 3:
            showMultilista();
            break;
        case 4:
            cout << " NODO PARA INICIAR: ";
            cin >> BFS;
            RecorridoAncho(BFS);
            break;
        case 5:
            cout << " NODO PARA INICIAR: ";
            cin >> BFS;
            RecorridoProfundo(BFS);
            break;
        case 6:
            cout << " NODO PARA INICIAR: ";
            cin >> BFS;
            kruskal(BFS);
            break;
        case 7:
            exit();
            break;
        default:
            cout << "[!] ERROR: INGRESA UNA OPCION VALIDA [!]";
            break;
        }
        cout << endl << endl;
        system("pause");
        system("cls");

    } while (op != 7);
    pause = cin.get(); //Pausa
    return 0;
}

// - - > MENU DE OPCIONES
void menu() {
    cout << "\n\t - - - - LISTA DE LISTAS - MULTILISTAS - - - -" << endl;
    cout << "\t\t\t   (+ KRUSKAN)\n" << endl;

    cout << " [1] INSERTAR UN NODO" << endl;
    cout << " [2] INSERTAR UNA ARISTA" << endl;
    cout << " [3] MOSTRAR  GRAFO" << endl;
    cout << " [4] RECORRIDO A LO ANCHO" << endl;
    cout << " [5] RECORRIDO A LO PROFUNDO" << endl;
    cout << " [6] KRUSKAN" << endl;
    cout << " [7] SALIR" << endl;

    cout << "\n INGRESE OPCION: ";
}

// - - > INSERTAR NUEVO NODO
void insertarNodo() {
    Nodo aux, new_nodo = new struct nodo;
    //Definiciones para el nuevo nodo
    cout << "\n VALOR DEL NODO: ";
    cin >> new_nodo->info;
    new_nodo->sig = NULL;
    new_nodo->ady = NULL;
    new_nodo->visitado = false;

    //Si la lista esta vacia...
    if (head == NULL) {
        head = new_nodo; //PRIMER NODO EN EL PUNTERO DE CABEZA
        //Con este nodo podemos recorrer todos los siguientes
        //nodos hasta llegar a NULL (osea el ultimo)
    }
    else {
        //Recorremos todos los nodos hasta llegar al final
        aux = head; //Reestablecemos el puntero al incio de la multilista
        while (aux->sig != NULL) { //Mientras el siguiente nodo no sea NULL...
            aux = aux->sig; //Pasamos al siguiente nodo
        }
        //Cuando el siguiente sea NULL...
        aux->sig = new_nodo; //Insertamos el nuevo nodo
    }
    totalnodos++; //Aumenta contador de nodos totales
}

// - - > AGREGAR UNIONES
void agregarArista(Nodo& aux, Nodo& aux2, Arista& nuevo,int peso) {
    Arista saveNoditos;
    if (aux->ady == NULL) { //Si el nodo no tiene nodos adyacentes...
        aux->ady = nuevo; //Agregamos un nodito al nodo actual
        nuevo->destino = aux2; //El nombre del nodito sera el mismo que uno de los nodos principales
        nuevo->peso = peso;
    }
    else { //Si el nodo ya tiene 1 o mas nodos adyacentes...
        saveNoditos = aux->ady; //Guardamos todos los noditos del nodo en saveNoditos
        while (saveNoditos->sig != NULL) { //Mientras no estemos en el ultimon nodito...
            saveNoditos = saveNoditos->sig; //Pasamos al siguiente nodito
        }
        //Cuando estamos en el ultimo nodito...
        nuevo->destino = aux2; //El nombre del nodito sera el mismo que uno de los nodos principales
        nuevo->peso = peso;
        saveNoditos->sig = nuevo; //Guardamos el nuevo nodito en la posicion siguiente al actual
    }
    cout << "\n [!] UNION AGREGADA CORRECTAMENTE [!]";
}

// - - > INSERTAR UNION
// Busca un nodo padre (primer dato) y le asigna un hijo (segundo dato)
void insertarArista() {
    char inicio, fin;
    int peso;
    Arista nuevo = new struct nodito;
    Nodo aux, aux2;
    //Verificar lista vacia
    if (head == NULL) {
        cout << "\n [!] LA LISTA ESTA VACIA [!]";
        return;
    }
    nuevo->sig = NULL;
    //Entrada de nodos a ligar
    cout << "\n NODO INICIAL: ";
    cin >> inicio;
    cout << " NODO FINAL: ";
    cin >> fin;
    cout << " PESO: ";
    cin >> peso;
    //Apuntadores auxiliares
    aux = head;
    aux2 = head;
    //Recorremos desde la cabezera hasta encontrar el valor FINAL
    while (aux2 != NULL) {
        if (aux2->info == fin) {
            break;
        }
        aux2 = aux2->sig;
    }
    //Recorremos desde la cabezera hasta encontrar el valor INICIO
    while (aux != NULL) {
        if (aux->info == inicio) {
            agregarArista(aux, aux2, nuevo, peso);
            return;
        }
        aux = aux->sig;
    }
}

// - - > MOSTRAR LISTA DE LISTAS
void showMultilista() {
    Nodo ndo;
    Arista ndito;
    ndo = head;
    //Verificar lista vacia
    if (head == NULL) {
        cout << "\n [!] LA LISTA ESTA VACIA [!]";
        pause = cin.get(); //Pausa
        return;
    }
    //Mostrar tabla
    cout << "\n\tNODO | LISTA DE ADYACENCIA\n";
    while (ndo != NULL) {
        cout << "\t   " << ndo->info << " | ";
        if (ndo->ady != NULL) {
            ndito = ndo->ady;
            while (ndito != NULL) {
                cout << " " << ndito->destino->info;
                ndito = ndito->sig; //Pasamos al siguiente nodito
            }
        }
        ndo = ndo->sig; //Pasamos al siguiente nodo
        cout << endl;
    }
    pause = cin.get(); //Pausa
}

//
// ░█─── ▀█▀ ░█▀▄▀█ ░█▀▀█ ▀█▀ ░█▀▀▀ ░█▀▀▀█ ─█▀▀█ 
// ░█─── ░█─ ░█░█░█ ░█▄▄█ ░█─ ░█▀▀▀ ─▄▄▄▀▀ ░█▄▄█
// ░█▄▄█ ▄█▄ ░█──░█ ░█─── ▄█▄ ░█▄▄▄ ░█▄▄▄█ ░█─░█
//

// - - > CLEAN COLA
void clearCola(queue<Nodo>& cola) {
    queue<Nodo> vacio; //Creamos una cola vacia (de tipo Nodo)
    swap(cola, vacio); //Invertimos su contenido
}

//PASAR TODOS LOS TRUE A FALSE
void clearTrueVisit(Nodo aux) {
    while (aux != NULL) { //Mientras no lleguemos al final...
        if (aux->visitado == true) { //Si esta visitado...
            aux->visitado = false; //Marcamos como no visitado
        }
        aux = aux->sig; //Pasamos al siguiente nodo
    }
}


// ░█▀▀█ ░█▀▀▀ ░█▀▀▀█
// ░█▀▀▄ ░█▀▀▀ ─▀▀▀▄▄
// ░█▄▄█ ░█─── ░█▄▄▄█
// RECORRIDO A LO ANCHO (BFS)

void RecorridoAncho(char raiz) {
    queue<Nodo> cola;
    Nodo aux, x, y;
    Arista aux2, ndito = NULL;
    aux = head;
    //LIMPIEZA DE LA COLA (xd)
    clearCola(cola);
    //PASAR TODOS LOS TRUE A FALSE
    clearTrueVisit(aux);
    //Detecta el char en la multilista
    while (aux != NULL) {
        if (aux->info == raiz) {
            break;
        }
        aux = aux->sig;
    }
    y = head;
    //Marcamos como visitado el nodo de entrada
    aux->visitado = true;
    cola.push(aux); //Lo metemos a la cola
    cout << "\n BFS: ";

    while (!cola.empty()) {
        x = cola.front(); //Guardamos el frente de la cola (NO SE ELIMINA)
        //Guardamos la direccion del inicio de los nodos adyacentes
        aux2 = x->ady;
        //Imprimimos el frente de la cola
        cout << x->info << "  ";
        cola.pop(); //Eliminamos el primero

        //Para cada nodo Y adyacente a X
        while (x->ady != NULL) {
            ndito = x->ady;
            //Recorremos todos los noditos del Nodo
            while (ndito != NULL) {
                //Recorremos todos los nodos buscando un valor igual a Nodito
                while (y != NULL) {
                    //Si el nodo tiene el mimso nombre que el nodito...
                    if (y->info == ndito->destino->info) {
                        if (y->visitado == false) { //Verificamos si no esta visitado
                            y->visitado = true; //En el NODO marcamos visitado
                            cola.push(y); //Entra a la cola
                        }
                    }
                    y = y->sig; //Pasamos al siguiente NODO (del iterador)
                }
                ndito = ndito->sig; //Pasamos al siguiente NODITO
                y = head; // Reestablecemos el inicio de los NODOS
            }
            x->ady = x->ady->sig; //Pasamos al siguiente NODITO
        }
        //Reestablecemos la direccion del inicio de los nodos adyacentes
        x->ady = aux2;
    }


}

// ░█▀▀▄ ░█▀▀▀ ░█▀▀▀█
// ░█─░█ ░█▀▀▀ ─▀▀▀▄▄
// ░█▄▄▀ ░█─── ░█▄▄▄█
// RECORRIDO A LO PROFUNDO

// Busqueda primero en profundidad
void RecorridoProfundo(char raiz) {
    Nodo aux;
    Arista ndito = NULL;
    aux = head;
    //PASAR TODOS LOS TRUE A FALSE
    clearTrueVisit(aux);
    //Detecta el char en la multilista
    while (aux != NULL) {
        if (aux->info == raiz) {
            break;
        }
        aux = aux->sig;
    }
    //Si el nodo no esta visitado...
    if (aux->visitado == false) {
        cout << "\n DFS: ";
        BPP(aux); //Entramos al recorrido a lo profundo
    }
}

// - - > BPP
void BPP(Nodo in) {
    Nodo y = head;
    Arista aux2, ndito = NULL;
    //Marcamos como visitado el nodo de entrada
    in->visitado = true;
    //Imprimimos el nodo de entrada
    cout << in->info << "  ";
    //Guardamos el apuntador al inicio de sus nodos (noditos) adyacentes
    aux2 = in->ady;
    //RECORRIDO
    //Para cada nodo Y adyacente a X
    while (in->ady != NULL) {
        ndito = in->ady;
        //Recorremos todos los noditos del Nodo
        while (ndito != NULL) {
            //Recorremos todos los nodos buscando un valor igual a Nodito
            while (y != NULL) {
                //Si el nodo tiene el mismo nombre que el nodito...
                if (y->info == ndito->destino->info) {
                    if (y->visitado == false) { //Verificamos si no esta visitado
                        BPP(y);
                    }
                }
                y = y->sig; //Pasamos al siguiente NODO (del iterador)
            }
            ndito = ndito->sig; //Pasamos al siguiente NODITO
            y = head; // Reestablecemos el inicio de los NODOS
        }
        in->ady = in->ady->sig; //Pasamos al siguiente NODITO
    }
    //Reestablecemos la direccion del inicio de los nodos adyacentes
    in->ady = aux2;
}


// ░█─▄▀ ░█▀▀█ ░█─░█ ░█▀▀▀█ ░█─▄▀ ─█▀▀█ ░█───
// ░█▀▄─ ░█▄▄▀ ░█─░█ ─▀▀▀▄▄ ░█▀▄─ ░█▄▄█ ░█───
// ░█─░█ ░█─░█ ─▀▄▄▀ ░█▄▄▄█ ░█─░█ ░█─░█ ░█▄▄█
// Algoritmo de Kruskal
void kruskal(char raiz) {
    Nodo aux;
    Arista ndito = NULL;
    aux = head;
    //PASAR TODOS LOS TRUE A FALSE
    clearTrueVisit(aux);
    //Detecta el char en la multilista
    while (aux != NULL) {
        if (aux->info == raiz) {
            break;
        }
        aux = aux->sig;
    }
    //Si el nodo no esta visitado...
    if (aux->visitado == false) {
        cout << "\n KRUSKAL: ";
        Ayuda(aux); //Entramos al recorrido a lo profundo
    }
}

// - - > BPP
void Ayuda(Nodo in) {
    //VECTOR DONDE SE ALMACENARAN LAS ARISTAS
    vector<int> ALista;
    Nodo y = head;
    
    

    int i;

    Arista aux2, ndito = NULL;
    Arista aux = NULL;
    Arista pesos,inicio,inversor = NULL;
    Arista guardadito = NULL;
    //Marcamos como visitado el nodo de entrada
    in->visitado = true;
    //Imprimimos el nodo de entrada
    cout << in->info << "  ";
    //Guardamos el apuntador al inicio de sus nodos (noditos) adyacentes
    aux2 = in->ady;



    //RECORRIDO
    //Para cada nodo Y adyacente a X
    

    while (in->ady != NULL) {

        ALista.clear();
        i = 0;
        inicio = in->ady;
        pesos = in->ady;
        ndito = in->ady;
        inversor = in->ady;
        aux = in->ady;

        while (pesos != NULL) {
            ALista.push_back(pesos->peso);
            pesos = pesos->sig;
        }

        
        sort(ALista.begin(), ALista.end());


        //Buscando los pesos
        while (i+1 != ALista.size()){
            while (aux != NULL) {
                if (aux->peso == ALista[i]) {
                    guardadito = aux;
                    aux = inversor;
                    inversor = guardadito;
                    inversor = inversor->sig;
                    aux = inversor;
                }
                else {
                    aux = aux->sig;
                }
            }
            i++;
        }





        //ndito = in->ady;
        ndito = inversor;
        //Recorremos todos los noditos del Nodo
        while (ndito != NULL) {
            //Recorremos todos los nodos buscando un valor igual a Nodito
            while (y != NULL) {
                //Si el nodo tiene el mismo nombre que el nodito...
                if (y->info == ndito->destino->info) {
                    if (y->visitado == false) { //Verificamos si no esta visitado
                        Ayuda(y);
                    }
                }
                y = y->sig; //Pasamos al siguiente NODO (del iterador)
            }
            ndito = ndito->sig; //Pasamos al siguiente NODITO
            y = head; // Reestablecemos el inicio de los NODOS
        }
        in->ady = in->ady->sig; //Pasamos al siguiente NODITO
    }
    //Reestablecemos la direccion del inicio de los nodos adyacentes
    in->ady = aux2;
}

// - - > Salir
void exit() {
    cout << "\tGRACIAS POR USAR NUESTROS SERVICIOS =)" << endl;
    cout << "\t *ASDASDASDAS* - BUAP / FCC";
}
