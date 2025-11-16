# Proyecto: Árbol Binario Ordenado con Arreglo en C++

## Objetivo
Crear un programa en **C++** que utilice un **árbol binario ordenado representado con un arreglo**.

---

## Clase del Árbol

### Estructura del Nodo
Cada nodo debe incluir:
- `clave`: entero o string (según lo que se use como clave)  
- `id_info`: entero (identificador o índice de la información en el archivo)  
- `izq`: entero (índice del hijo izquierdo en el arreglo)  
- `der`: entero (índice del hijo derecho en el arreglo)

---

### Constructor
Recibe el **tamaño del arreglo** (con una posición extra para control).

---

### Funciones requeridas

#### `insertar()`
- Retorna **falso** si el arreglo está lleno.
- Si no está lleno:
  - Inserta el nuevo nodo en la posición correspondiente.
  - Guarda la información asociada en un archivo.
  - Asigna un **ID** a la información (por ejemplo, el número de línea o un identificador único).

#### `buscar()`
- Busca la **clave** en el árbol (usando el arreglo).
- Si la encuentra:
  - Usa el `id_info` para leer la información desde el archivo.
  - Retorna la información asociada.

#### `modificar()`
- Usa `buscar()` para localizar la clave.
- Permite **modificar la información** en el archivo asociada a esa clave.

#### `eliminar()`
- Busca el nodo por clave.
- Elimina según el caso:
  - Nodo hoja.
  - Nodo con un hijo.
  - Nodo con dos hijos.
- Ajusta los punteros (`izq`, `der`) según corresponda.
- Imprime la información eliminada.
- Marca la información como **borrada** en el archivo.

#### Recorridos (iterativos)
Cada recorrido debe retornar una **cola** con los resultados:
- **Inorden**
- **Preorden**
- **Posorden**
- **Por niveles**

Usar estructuras iterativas (pilas y colas de la STL).

---

## Archivo de Información

### Estructura
Puede ser un archivo de texto o binario que almacene los datos de los estudiantes.

### Consideraciones
- Cada registro debe tener un **ID único**.
- En caso de eliminar un registro, se marca como **borrado** (sin eliminar físicamente del archivo).
- Alternativamente, se puede mantener un archivo de control de IDs reutilizables.

---

## Consideraciones sobre el Arreglo

- El arreglo tiene **tamaño fijo** definido por el constructor.
- La **posición 0** se usa para **control**:
  - Puede guardar el índice de la **raíz**.
  - Puede guardar el **siguiente índice libre**.

---

## Persistencia del Árbol

- Al **cerrar** el programa:
  - Guardar el **arreglo completo** (con los nodos) en un **archivo binario**.
- Al **iniciar**:
  - Cargar el arreglo desde ese archivo (si existe).

---

## Programa Principal

El programa debe:

1. **Insertar** claves e información hasta que el usuario decida parar.  
2. **Imprimir** los 4 recorridos (inorden, preorden, posorden, por niveles).  
3. Dar opción de **eliminar** o **buscar** una clave.  
4. Después de eliminar, **volver a imprimir** los recorridos.  
5. Al cerrar, **guardar** el arreglo y poder **reconstruirlo** al reiniciar.  

---

## Resumen de Componentes

| Componente | Descripción |
|-------------|--------------|
| **Estructura del nodo** | Contiene clave, ID de información y punteros a hijos |
| **Archivo de información** | Guarda los datos asociados a cada clave |
| **Funciones principales** | insertar, buscar, modificar, eliminar |
| **Recorridos** | Inorden, preorden, posorden, por niveles |
| **Persistencia** | Guarda y recupera el árbol desde un archivo binario |
| **Menú principal** | Permite interacción con el usuario |

---