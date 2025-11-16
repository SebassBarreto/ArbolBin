#ifndef ARBOLBINORDENADO_H
#define ARBOLBINORDENADO_H

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <stack>
#include <sstream>

using namespace std;

/**
 * Estructura Nodo: Representa cada elemento del arbol binario ordenado
 * 
 * CAMPOS:
 * - clave: La clave que determina la posicion en el arbol (criterio de ordenamiento)
 * - id_info: ID unico que identifica la informacion en el archivo de datos
 * - izq: indice del hijo izquierdo en el arreglo (-1 si no tiene)
 * - der: indice del hijo derecho en el arreglo (-1 si no tiene)
 * - activo: Bandera que indica si el nodo esta en uso (facilita eliminacion y reutilizacion)
 */
struct Nodo{
    int clave;      // Clave de ordenamiento del nodo
    int id_info;    // ID para buscar informacion en el archivo
    int izq;        // indice del hijo izquierdo
    int der;        // indice del hijo derecho
    bool activo;    // Estado del nodo (true = en uso, false = eliminado)

    // Constructor por defecto: inicializa todos los valores
    Nodo(): clave(0), id_info(-1), izq(-1), der(-1), activo(false) {}
};

/**
 * Clase ArbolBinarioOrdenado
 * 
 * Implementa un arbol binario de busqueda usando un arreglo estatico.
 * La informacion asociada a cada nodo se almacena en un archivo externo.
 * 
 * CARACTERiSTICAS:
 * - Utiliza arreglo estatico para almacenar nodos
 * - Posicion 0 del arreglo es de control
 * - Persistencia: guarda/carga el arbol en archivo binario
 * - Informacion externa: datos en archivo de texto separado
 */
class ArbolBinarioOrdenado{
private:
    // ATRIBUTOS PRINCIPALES
    Nodo* arreglo;          // Arreglo que contiene todos los nodos del arbol
    int tamaño;             // Tamaño maximo del arreglo (sin contar posicion 0)
    int raiz;               // indice del nodo raiz (-1 si arbol vacio)
    int siguienteLibre;     // Proxima posicion disponible en el arreglo
    string archivoDatos;    // Nombre del archivo que contiene la informacion
    string archivoArbol;    // Nombre del archivo que guarda la estructura del arbol
    
    // MeTODOS AUXILIARES PRIVADOS
    
    /**
     * Genera un ID unico para la informacion que se guardara en el archivo
     * RETORNA: Entero unico que identifica un registro en el archivo
     */
    int obtenerIdUnico();
    
    /**
     * Guarda informacion en el archivo de datos
     * PARaMETROS:
     * - id: Identificador unico del registro
     * - informacion: Cadena con los datos a guardar
     */
    void guardarEnArchivo(int id, string informacion);
    
    /**
     * Lee informacion del archivo usando el ID
     * PARaMETROS:
     * - id: Identificador del registro a leer
     * RETORNA: String con la informacion o mensaje de error
     */
    string leerDelArchivo(int id);
    
    /**
     * Marca un registro como eliminado en el archivo
     * PARaMETROS:
     * - id: Identificador del registro a marcar como borrado
     */
    void marcarBorradoEnArchivo(int id);
    
    /**
     * Busca la posicion donde deberia insertarse una clave
     * PARaMETROS:
     * - clave: Valor a buscar
     * - padre: Referencia que se llenara con el indice del padre
     * RETORNA: indice donde esta la clave o -1 si no existe
     */
    int buscarPosicion(int clave, int& padre);
    
    /**
     * Encuentra el nodo con valor minimo en un subarbol
     * PARaMETROS:
     * - indice: Raiz del subarbol donde buscar
     * RETORNA: indice del nodo con valor minimo
     */
    int encontrarMinimo(int indice);
    
    /**
     * Implementa el recorrido inorden de forma iterativa
     * RETORNA: Cola con los indices de nodos en orden inorden
     */
    queue<int> recorridoInorden();
    
    /**
     * Implementa el recorrido preorden de forma iterativa
     * RETORNA: Cola con los indices de nodos en orden preorden
     */
    queue<int> recorridoPreorden();
    
    /**
     * Implementa el recorrido postorden de forma iterativa
     * RETORNA: Cola con los indices de nodos en orden postorden
     */
    queue<int> recorridoPostorden();
    
    /**
     * Implementa el recorrido por niveles de forma iterativa
     * RETORNA: Cola con los indices de nodos por niveles
     */
    queue<int> recorridoPorNiveles();

public:
    // MeTODOS PuBLICOS
    
    /**
     * Constructor: Inicializa el arbol con un tamaño especifico
     * PARaMETROS:
     * - n: Numero maximo de elementos que puede contener el arbol
     * 
     * FUNCIONAMIENTO:
     * 1. Crea arreglo de tamaño n+1 (posicion 0 es de control)
     * 2. Inicializa variables de control
     * 3. Carga arbol desde archivo si existe
     */
    ArbolBinarioOrdenado(int n);
    
    /**
     * Destructor: Limpia memoria y guarda estado actual
     * 
     * FUNCIONAMIENTO:
     * 1. Guarda el arbol actual en archivo
     * 2. Libera memoria del arreglo
     */
    ~ArbolBinarioOrdenado();
    
    /**
     * Inserta un nuevo nodo en el arbol
     * PARaMETROS:
     * - clave: Valor que determinara la posicion en el arbol
     * - informacion: Datos asociados que se guardaran en archivo
     * RETORNA: true si se inserto correctamente, false si fallo
     * 
     * CASOS DE FALLA:
     * - arbol lleno (siguienteLibre > tamaño)
     * - Clave ya existe en el arbol
     * 
     * ALGORITMO:
     * 1. Verificar que hay espacio disponible
     * 2. Buscar posicion correcta segun orden BST
     * 3. Verificar que clave no existe
     * 4. Generar ID unico y guardar informacion en archivo
     * 5. Crear nodo en siguienteLibre
     * 6. Enlazar con padre segun valor de clave
     * 7. Incrementar siguienteLibre
     */
    bool insertar(int clave, string informacion);
    
    /**
     * Busca una clave en el arbol y retorna su informacion
     * PARaMETROS:
     * - clave: Valor a buscar
     * RETORNA: String con informacion asociada o mensaje de error
     * 
     * ALGORITMO BST:
     * 1. Comenzar desde la raiz
     * 2. Comparar clave con nodo actual
     * 3. Si es igual: encontrado, leer informacion del archivo
     * 4. Si es menor: ir al hijo izquierdo
     * 5. Si es mayor: ir al hijo derecho
     * 6. Repetir hasta encontrar o llegar a null
     */
    string buscar(int clave);
    
    /**
     * Modifica la informacion asociada a una clave
     * PARaMETROS:
     * - clave: Clave del nodo a modificar
     * - nuevaInformacion: Nueva informacion a guardar
     * RETORNA: true si se modifico, false si la clave no existe
     * 
     * FUNCIONAMIENTO:
     * 1. Buscar la clave en el arbol
     * 2. Si existe, actualizar informacion en archivo
     * 3. Mantener misma estructura del arbol
     */
    bool modificar(int clave, string nuevaInformacion);
    
    /**
     * Elimina un nodo del arbol
     * PARaMETROS:
     * - clave: Valor del nodo a eliminar
     * RETORNA: true si se elimino, false si no existe
     * 
     * CASOS DE ELIMINACIoN:
     * 
     * CASO 1 - NODO HOJA (sin hijos):
     * - Actualizar puntero del padre a -1
     * - Marcar nodo como inactivo
     * 
     * CASO 2 - UN HIJO:
     * - Conectar padre directamente con el unico hijo
     * - Marcar nodo como inactivo
     * 
     * CASO 3 - DOS HIJOS:
     * - Encontrar sucesor inorden (minimo del subarbol derecho)
     * - Reemplazar datos del nodo con los del sucesor
     * - Eliminar el nodo sucesor (sera caso 1 o 2)
     * 
     * NOTA: Al eliminar, imprime informacion y marca como borrado en archivo
     */
    bool eliminar(int clave);
    
    /**
     * Realiza recorrido inorden e imprime resultados
     * ORDEN: Izquierdo -> Raiz -> Derecho
     * RESULTADO: Elementos en orden ascendente
     */
    void inorden();
    
    /**
     * Realiza recorrido preorden e imprime resultados
     * ORDEN: Raiz -> Izquierdo -> Derecho
     * RESULTADO: Raiz aparece antes que sus hijos
     */
    void preorden();
    
    /**
     * Realiza recorrido postorden e imprime resultados
     * ORDEN: Izquierdo -> Derecho -> Raiz
     * RESULTADO: Raiz aparece despues que sus hijos
     */
    void posorden();
    
    /**
     * Realiza recorrido por niveles e imprime resultados
     * ORDEN: Nivel por nivel, de izquierda a derecha
     * RESULTADO: Breadth-First Search del arbol
     */
    void porNiveles();
    
    /**
     * Guarda la estructura actual del arbol en archivo binario
     * 
     * INFORMACIoN GUARDADA:
     * - Tamaño del arreglo
     * - indice de la raiz
     * - Siguiente posicion libre
     * - Array completo de nodos
     * 
     * FORMATO: Archivo binario para eficiencia y precision
     */
    void guardarArbol();
    
    /**
     * Carga la estructura del arbol desde archivo binario
     * 
     * FUNCIONAMIENTO:
     * 1. Verificar si archivo existe
     * 2. Leer metadatos (tamaño, raiz, siguienteLibre)
     * 3. Cargar arreglo completo de nodos
     * 4. Reconstruir estado exacto anterior
     */
    void cargarArbol();
};

// ===============================
// IMPLEMENTACIoN DE LA CLASE
// ===============================

/**
 * CONSTRUCTOR
 * Inicializa todas las estructuras necesarias para el arbol
 */
ArbolBinarioOrdenado::ArbolBinarioOrdenado(int n){
    // Configuracion inicial del arreglo
    tamaño = n;                                    // Tamaño maximo de nodos
    arreglo = new Nodo[tamaño + 1];               // +1 porque posicion 0 es control
    raiz = -1;                                    // arbol inicialmente vacio
    siguienteLibre = 1;                           // Primera posicion disponible (0 es control)
    
    // Configuracion de archivos
    archivoDatos = "estudiantes.txt";             // Archivo con informacion de nodos
    archivoArbol = "arbol_guardado.dat";         // Archivo para persistencia del arbol un binario
    
    // Inicializacion del arreglo: todos los nodos en estado por defecto
    for(int i = 0; i <= tamaño; i++){
        arreglo[i] = Nodo();                      // Constructor por defecto de Nodo
    }
    
    // Intentar cargar arbol previo si existe
    cargarArbol();
}

/**
 * DESTRUCTOR
 * Limpia memoria y persiste estado actual
 */
ArbolBinarioOrdenado::~ArbolBinarioOrdenado() {
    guardarArbol();                               // Guardar estado antes de destruir
    delete[] arreglo;                             // Liberar memoria del arreglo
}

/**
 * FUNCIoN INSERTAR
 * Algoritmo completo para insertar un nuevo nodo manteniendo orden BST
 */
bool ArbolBinarioOrdenado::insertar(int clave, string informacion){
    
    // PASO 1: Verificar disponibilidad de espacio
    if(siguienteLibre > tamaño){
        return false;                             // No hay mas espacio en el arreglo
    }
    
    // PASO 2: Buscar posicion donde insertar y obtener padre
    int padre = -1;                               // Almacenara indice del padre
    int posicion = buscarPosicion(clave, padre);  // Busca donde va y guarda padre
    
    // PASO 3: Verificar que la clave no exista ya
    if(posicion != -1 && arreglo[posicion].activo){
        return false;                             // Clave duplicada, no insertar
    }
    
    // PASO 4: Preparar informacion externa
    int id = obtenerIdUnico();                    // Generar ID unico para archivo
    guardarEnArchivo(id, informacion);            // Guardar datos en archivo externo
    
    // PASO 5: Crear el nuevo nodo en siguienteLibre
    arreglo[siguienteLibre].clave = clave;        // Asignar clave
    arreglo[siguienteLibre].id_info = id;         // Vincular con informacion en archivo
    arreglo[siguienteLibre].izq = -1;             // Inicialmente sin hijo izquierdo
    arreglo[siguienteLibre].der = -1;             // Inicialmente sin hijo derecho
    arreglo[siguienteLibre].activo = true;        // Marcar como nodo activo
    
    // PASO 6: Enlazar en el arbol
    if(raiz == -1){                               // CASO: arbol vacio
        raiz = siguienteLibre;                    // Este nodo se convierte en raiz
    }
    else{                                         // CASO: Enlazar con padre existente
        if(clave < arreglo[padre].clave){         // Determinar si va a izquierda o derecha
            arreglo[padre].izq = siguienteLibre;  // Insertar como hijo izquierdo
        }
        else{
            arreglo[padre].der = siguienteLibre;  // Insertar como hijo derecho
        }
    }
    
    // PASO 7: Actualizar control de espacio
    siguienteLibre++;                             // Marcar siguiente posicion disponible
    return true;                                  // Insercion exitosa
}

/**
 * FUNCIoN BUSCAR
 * Implementa busqueda BST estandar de forma iterativa
 */
string ArbolBinarioOrdenado::buscar(int clave){
    int actual = raiz;                            // Comenzar busqueda desde la raiz
    
    // Recorrer arbol siguiendo propiedades BST
    while(actual != -1 && arreglo[actual].activo){
        
        if(clave == arreglo[actual].clave){       // CASO: Clave encontrada
            return leerDelArchivo(arreglo[actual].id_info);  // Retornar informacion del archivo
        }
        else if(clave < arreglo[actual].clave){   // CASO: Buscar en subarbol izquierdo
            actual = arreglo[actual].izq;         // Moverse al hijo izquierdo
        }
        else{                                     // CASO: Buscar en subarbol derecho
            actual = arreglo[actual].der;         // Moverse al hijo derecho
        }
    }
    
    return "Clave no encontrada";                 // No se encontro la clave
}

/**
 * FUNCIoN ELIMINAR
 * Implementa los tres casos de eliminacion en BST
 */
bool ArbolBinarioOrdenado::eliminar(int clave){
    
    // PASO 1: Buscar nodo a eliminar y su padre
    int padre = -1;                               // indice del padre del nodo a eliminar
    int actual = raiz;                            // Comenzar busqueda desde raiz
    bool encontrado = false;                      // Bandera de busqueda
    
    // Busqueda del nodo manteniendo referencia al padre
    while(actual != -1 && arreglo[actual].activo){
        if(clave == arreglo[actual].clave){
            encontrado = true;                    // Nodo encontrado
            break;                                // Salir del bucle
        }
        else if(clave < arreglo[actual].clave){
            padre = actual;                       // Actualizar padre antes de moverse
            actual = arreglo[actual].izq;         // Buscar en izquierda
        }
        else{
            padre = actual;                       // Actualizar padre antes de moverse
            actual = arreglo[actual].der;         // Buscar en derecha
        }
    }
    
    // PASO 2: Verificar si se encontro
    if(!encontrado){
        return false;                             // Nodo no existe
    }
    
    // PASO 3: Imprimir informacion antes de eliminar y marcar en archivo
    string info = leerDelArchivo(arreglo[actual].id_info);
    cout << "Eliminando: " << info << endl;
    marcarBorradoEnArchivo(arreglo[actual].id_info);
    
    // PASO 4: Aplicar algoritmo de eliminacion segun casos
    
    // CASO 1: NODO HOJA (sin hijos)
    if(arreglo[actual].izq == -1 && arreglo[actual].der == -1){
        
        if(padre == -1){                          // Eliminar raiz sin hijos
            raiz = -1;                            // arbol queda vacio
        } 
        else{                                     // Eliminar hoja normal
            if(arreglo[padre].izq == actual){     // Es hijo izquierdo
                arreglo[padre].izq = -1;          // Desconectar de padre
            } 
            else{                                 // Es hijo derecho
                arreglo[padre].der = -1;          // Desconectar de padre
            }
        }
        
        arreglo[actual].activo = false;           // Marcar nodo como eliminado
    }
    
    // CASO 2: UN HIJO (izquierdo O derecho, pero no ambos)
    else if(arreglo[actual].izq == -1 || arreglo[actual].der == -1){
        
        // Determinar cual es el unico hijo
        int hijo;   
        if(arreglo[actual].izq != -1){
            hijo = arreglo[actual].izq;           // Tiene hijo izquierdo
        } 
        else{
            hijo = arreglo[actual].der;           // Tiene hijo derecho
        }
        
        // Conectar hijo directamente con abuelo
        if(padre == -1){                          // Eliminar raiz con un hijo
            raiz = hijo;                          // Hijo se convierte en nueva raiz
        } 
        else{                                     // Eliminar nodo interno
            if(arreglo[padre].izq == actual){     // Era hijo izquierdo
                arreglo[padre].izq = hijo;        // Conectar abuelo con nieto
            }
            else{                                 // Era hijo derecho
                arreglo[padre].der = hijo;        // Conectar abuelo con nieto
            }
        }
        
        arreglo[actual].activo = false;           // Marcar nodo como inactivo o "eliminado"
    }
    
    // CASO 3: DOS HIJOS (mas complejo - usar sucesor inorden)
    else{
        
        // Encontrar sucesor inorden: minimo del subarbol derecho
        int sucesorPadre = actual;                // Padre del sucesor
        int sucesor = arreglo[actual].der;        // Comenzar en subarbol derecho
        
        // Buscar el nodo mas a la izquierda del subarbol derecho
        while(arreglo[sucesor].izq != -1){
            sucesorPadre = sucesor;               // Actualizar padre del sucesor
            sucesor = arreglo[sucesor].izq;       // Moverse mas a la izquierda
        }
        
        // Reemplazar datos del nodo actual con datos del sucesor
        arreglo[actual].clave = arreglo[sucesor].clave;      // Copiar clave
        arreglo[actual].id_info = arreglo[sucesor].id_info;  // Copiar ID de informacion
        
        // Eliminar el sucesor (que sera nodo hoja o con un hijo derecho)
        if(sucesorPadre == actual){               // Sucesor es hijo directo
            arreglo[sucesorPadre].der = arreglo[sucesor].der;  // Conectar con hijo derecho del sucesor
        } 
        else{                                     // Sucesor esta mas profundo
            arreglo[sucesorPadre].izq = arreglo[sucesor].der;  // Conectar padre con hijo derecho del sucesor
        }
        
        arreglo[sucesor].activo = false;          // Marcar sucesor como eliminado
    }
    
    return true;                                  // Eliminacion exitosa
}

/**
 * FUNCIONES DE RECORRIDO
 * Todas implementadas de forma iterativa usando colas y pilas
 */

// Recorrido INORDEN iterativo: Izquierda -> Raiz -> Derecha
void ArbolBinarioOrdenado::inorden(){
    cout << "\n=== RECORRIDO INORDEN ===" << endl;
    queue<int> resultado = recorridoInorden();    // Obtener cola con recorrido
    
    // Imprimir todos los elementos de la cola
    while(!resultado.empty()){
        int indice = resultado.front();           // Obtener primer elemento
        resultado.pop();                          // Remover de cola
        
        // Imprimir clave e informacion asociada
        cout << "Clave: " << arreglo[indice].clave;
        cout << " -> " << leerDelArchivo(arreglo[indice].id_info) << endl;
    }
}

// Recorrido PREORDEN iterativo: Raiz -> Izquierda -> Derecha  
void ArbolBinarioOrdenado::preorden(){
    cout << "\n=== RECORRIDO PREORDEN ===" << endl;
    queue<int> resultado = recorridoPreorden();   // Obtener cola con recorrido
    
    // Imprimir todos los elementos de la cola
    while(!resultado.empty()){
        int indice = resultado.front();           // Obtener primer elemento
        resultado.pop();                          // Remover de cola
        
        // Imprimir clave e informacion asociada
        cout << "Clave: " << arreglo[indice].clave;
        cout << " -> " << leerDelArchivo(arreglo[indice].id_info) << endl;
    }
}

// Recorrido POSTORDEN iterativo: Izquierda -> Derecha -> Raiz
void ArbolBinarioOrdenado::posorden(){
    cout << "\n=== RECORRIDO POSTORDEN ===" << endl;
    queue<int> resultado = recorridoPostorden();  // Obtener cola con recorrido
    
    // Imprimir todos los elementos de la cola
    while(!resultado.empty()){
        int indice = resultado.front();           // Obtener primer elemento
        resultado.pop();                          // Remover de cola
        
        // Imprimir clave e informacion asociada
        cout << "Clave: " << arreglo[indice].clave;
        cout << " -> " << leerDelArchivo(arreglo[indice].id_info) << endl;
    }
}

// Recorrido POR NIVELES iterativo: Breadth-First Search
void ArbolBinarioOrdenado::porNiveles(){
    cout << "\n=== RECORRIDO POR NIVELES ===" << endl;
    queue<int> resultado = recorridoPorNiveles(); // Obtener cola con recorrido
    
    // Imprimir todos los elementos de la cola
    while(!resultado.empty()){
        int indice = resultado.front();           // Obtener primer elemento
        resultado.pop();                          // Remover de cola
        
        // Imprimir clave e informacion asociada
        cout << "Clave: " << arreglo[indice].clave;
        cout << " -> " << leerDelArchivo(arreglo[indice].id_info) << endl;
    }
}

// ===============================
// MeTODOS AUXILIARES PRIVADOS
// ===============================

/**
 * Genera ID unico para registros en archivo
 * Implementacion simple: usa timestamp o contador
 */
int ArbolBinarioOrdenado::obtenerIdUnico(){
    static int contador = 1000;                   // Contador estatico para IDs unicos
    return contador++;                            // Incrementar y retornar
}

/**
 * Guarda informacion en archivo de datos
 * Formato: ID|informacion en nueva linea
 */
void ArbolBinarioOrdenado::guardarEnArchivo(int id, string informacion){
    ofstream archivo(archivoDatos, ios::app);     // Abrir en modo append
    if(archivo.is_open()){
        archivo << id << "|" << informacion << endl;  // Formato: ID|datos
        archivo.close();
    }
}

/**
 * Lee informacion especifica del archivo usando ID
 * Busca linea que comience con el ID especificado
 */
string ArbolBinarioOrdenado::leerDelArchivo(int id){
    ifstream archivo(archivoDatos);               // Abrir archivo para lectura
    string linea;
    
    while(getline(archivo, linea)){               // Leer linea por linea
        if(linea.find(to_string(id) + "|") == 0){ // Verificar si linea comienza con ID|
            size_t pos = linea.find("|");         // Encontrar separador
            if(pos != string::npos){
                return linea.substr(pos + 1);     // Retornar parte despues de |
            }
        }
    }
    
    archivo.close();
    return "Informacion no encontrada";           // ID no existe en archivo
}

/**
 * Marca registro como eliminado en archivo
 * Prefija linea con "ELIMINADO:" para identificar registros borrados
 */
void ArbolBinarioOrdenado::marcarBorradoEnArchivo(int id){
    ifstream archivoLectura(archivoDatos);        // Archivo original
    ofstream archivoTemp("temp.txt");             // Archivo temporal
    string linea;
    
    // Copiar todas las lineas, modificando la que corresponde al ID
    while(getline(archivoLectura, linea)){
        if(linea.find(to_string(id) + "|") == 0){ // Linea del ID a eliminar
            archivoTemp << "ELIMINADO:" << linea << endl;  // Marcar como eliminado
        } 
        else{
            archivoTemp << linea << endl;          // Copiar linea sin cambios
        }
    }
    
    archivoLectura.close();
    archivoTemp.close();
    
    // Reemplazar archivo original con el modificado
    remove(archivoDatos.c_str());                 // Eliminar original
    rename("temp.txt", archivoDatos.c_str());     // Renombrar temporal
}

/**
 * Busca posicion donde insertar clave y retorna padre
 * Implementa busqueda BST guardando referencia al padre
 */
int ArbolBinarioOrdenado::buscarPosicion(int clave, int& padre){
    if(raiz == -1) return -1;                     // arbol vacio
    
    int actual = raiz;
    padre = -1;
    
    // Busqueda BST manteniendo referencia al padre
    while(actual != -1){
        if(clave == arreglo[actual].clave){
            return actual;                        // Clave encontrada
        }
        
        padre = actual;                           // Actualizar padre antes de moverse
        if(clave < arreglo[actual].clave){
            actual = arreglo[actual].izq;         // Buscar en izquierda
        } 
        else{
            actual = arreglo[actual].der;         // Buscar en derecha
        }
    }
    
    return -1;                                    // Clave no encontrada, padre queda configurado
}

/**
 * Encuentra nodo con valor minimo en subarbol
 * Usado para encontrar sucesor inorden en eliminacion
 */
int ArbolBinarioOrdenado::encontrarMinimo(int indice){
    while(arreglo[indice].izq != -1){             // Ir siempre a la izquierda
        indice = arreglo[indice].izq;             // El minimo esta mas a la izquierda
    }
    return indice;                                // Retornar indice del minimo
}

/**
 * IMPLEMENTACIoN DE RECORRIDOS ITERATIVOS
 * Todos retornan colas con los indices en el orden correspondiente
 */

// INORDEN iterativo usando pila
queue<int> ArbolBinarioOrdenado::recorridoInorden(){
    queue<int> resultado;                         // Cola resultado
    stack<int> pila;                              // Pila auxiliar
    int actual = raiz;                            // Comenzar desde raiz
    
    while(actual != -1 || !pila.empty()){         // Nodo activo, Aun elementos en la pila
        
        // Ir al extremo izquierdo apilando nodos
        while(actual != -1){
            pila.push(actual);                    // Apilar nodo actual
            actual = arreglo[actual].izq;         // Moverse a izquierda
        }
        
        // Procesar nodo en tope de pila
        actual = pila.top();                      // Obtener nodo del tope
        pila.pop();                               // Remover de pila
        
        if(arreglo[actual].activo){               // Solo procesar nodos activos
            resultado.push(actual);               // Agregar a resultado
        }
        
        // Moverse al subarbol derecho
        actual = arreglo[actual].der;             // Continuar con derecha
    }
    
    return resultado;                             // Retornar cola con recorrido
}

// PREORDEN iterativo usando pila
queue<int> ArbolBinarioOrdenado::recorridoPreorden(){
    queue<int> resultado;                         // Cola resultado
    if(raiz == -1) return resultado;              // arbol vacio
    
    stack<int> pila;                              // Pila auxiliar
    pila.push(raiz);                              // Comenzar con raiz
    
    while(!pila.empty()){
        int actual = pila.top();                  // Obtener nodo del tope
        pila.pop();                               // Remover de pila
        
        if(arreglo[actual].activo){               // Solo procesar nodos activos
            resultado.push(actual);               // Procesar nodo actual primero
        }
        
        // Apilar hijos (derecho primero para que izquierdo se procese antes)
        if(arreglo[actual].der != -1){
            pila.push(arreglo[actual].der);       // Apilar hijo derecho
        }
        if(arreglo[actual].izq != -1){
            pila.push(arreglo[actual].izq);       // Apilar hijo izquierdo
        }
    }
    
    return resultado;                             // Retornar cola con recorrido
}

// POSTORDEN iterativo usando dos pilas
queue<int> ArbolBinarioOrdenado::recorridoPostorden(){
    queue<int> resultado;                         // Cola resultado
    if(raiz == -1) return resultado;              // arbol vacio
    
    stack<int> pila1, pila2;                      // Dos pilas auxiliares
    pila1.push(raiz);                             // Comenzar con raiz en pila1
    
    // Primera fase: llenar pila2 con orden inverso a postorden
    while(!pila1.empty()){
        int actual = pila1.top();                 // Obtener nodo de pila1
        pila1.pop();                              // Remover de pila1
        pila2.push(actual);                       // Agregar a pila2
        
        // Apilar hijos en pila1 (izquierdo primero)
        if(arreglo[actual].izq != -1){
            pila1.push(arreglo[actual].izq);      // Apilar hijo izquierdo
        }
        if(arreglo[actual].der != -1){
            pila1.push(arreglo[actual].der);      // Apilar hijo derecho
        }
    }
    
    // Segunda fase: vaciar pila2 para obtener orden postorden
    while(!pila2.empty()){
        int actual = pila2.top();                 // Obtener nodo de pila2
        pila2.pop();                              // Remover de pila2
        
        if(arreglo[actual].activo){               // Solo procesar nodos activos
            resultado.push(actual);               // Agregar a resultado
        }
    }
    
    return resultado;                             // Retornar cola con recorrido
}

// POR NIVELES iterativo usando cola (BFS)
queue<int> ArbolBinarioOrdenado::recorridoPorNiveles(){
    queue<int> resultado;                         // Cola resultado
    if(raiz == -1) return resultado;              // arbol vacio
    
    queue<int> cola;                              // Cola auxiliar para BFS
    cola.push(raiz);                              // Comenzar con raiz
    
    while(!cola.empty()){
        int actual = cola.front();                // Obtener primer elemento
        cola.pop();                               // Remover de cola
        
        if(arreglo[actual].activo){               // Solo procesar nodos activos
            resultado.push(actual);               // Agregar a resultado
        }
        
        // Agregar hijos a la cola (izquierdo primero)
        if(arreglo[actual].izq != -1){
            cola.push(arreglo[actual].izq);       // Encolar hijo izquierdo
        }
        if(arreglo[actual].der != -1){
            cola.push(arreglo[actual].der);       // Encolar hijo derecho
        }
    }
    
    return resultado;                             // Retornar cola con recorrido
}

/**
 * FUNCIoN MODIFICAR
 * Permite cambiar informacion asociada sin alterar estructura del arbol
 */
bool ArbolBinarioOrdenado::modificar(int clave, string nuevaInformacion){
    
    // Buscar la clave en el arbol
    int actual = raiz;
    while(actual != -1 && arreglo[actual].activo){
        if(clave == arreglo[actual].clave){
            // Clave encontrada: actualizar informacion en archivo
            
            // Marcar registro anterior como eliminado
            marcarBorradoEnArchivo(arreglo[actual].id_info);
            
            // Crear nuevo registro con informacion actualizada
            int nuevoId = obtenerIdUnico();
            guardarEnArchivo(nuevoId, nuevaInformacion);
            
            // Actualizar ID en el nodo
            arreglo[actual].id_info = nuevoId;
            
            return true;                          // Modificacion exitosa
        }
        else if(clave < arreglo[actual].clave){
            actual = arreglo[actual].izq;         // Buscar en izquierda
        }
        else{
            actual = arreglo[actual].der;         // Buscar en derecha
        }
    }
    
    return false;                                 // Clave no encontrada
}

/**
 * GUARDAR aRBOL EN ARCHIVO BINARIO
 * Persiste todo el estado del arbol para recuperacion posterior
 */
void ArbolBinarioOrdenado::guardarArbol(){
    ofstream archivo(archivoArbol, ios::binary);  // Abrir archivo binario
    
    if(archivo.is_open()){
        // Guardar metadatos del arbol
        archivo.write((char*)&tamaño, sizeof(int));           // Tamaño del arreglo
        archivo.write((char*)&raiz, sizeof(int));             // indice de la raiz
        archivo.write((char*)&siguienteLibre, sizeof(int));   // Siguiente posicion libre
        
        // Guardar arreglo completo de nodos
        for(int i = 0; i <= tamaño; i++){
            archivo.write((char*)&arreglo[i], sizeof(Nodo));   // Escribir cada nodo
        }
        
        archivo.close();
    }
}

/**
 * CARGAR aRBOL DESDE ARCHIVO BINARIO  
 * Reconstruye el estado exacto del arbol desde persistencia
 */
void ArbolBinarioOrdenado::cargarArbol(){
    ifstream archivo(archivoArbol, ios::binary);  // Abrir archivo binario
    
    if(archivo.is_open()){
        int tamañoGuardado, raizGuardada, siguienteLibreGuardado;
        
        // Leer metadatos
        archivo.read((char*)&tamañoGuardado, sizeof(int));
        archivo.read((char*)&raizGuardada, sizeof(int));
        archivo.read((char*)&siguienteLibreGuardado, sizeof(int));
        
        // Verificar compatibilidad de tamaño
        if(tamañoGuardado == tamaño){
            // Restaurar metadatos
            raiz = raizGuardada;
            siguienteLibre = siguienteLibreGuardado;
            
            // Cargar arreglo completo
            for(int i = 0; i <= tamaño; i++){
                archivo.read((char*)&arreglo[i], sizeof(Nodo));  // Leer cada nodo
            }
        }
        
        archivo.close();
    }
    // Si archivo no existe, el arbol se mantiene vacio (inicializacion por defecto)
}

#endif //ARBOLBINORDENADO_H