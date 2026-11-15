#include <bits/stdc++.h>
// Aguilar Tun Joan Enrique 3A Q1

using namespace std;

// CONSTANTES Y REPRESENTACIÓN DEL GRAFO DE DISTANCIAS

const int N = 10; // Cantidad total de Ciudades (Nodos) en el grafo

// Catálogo de nombres de las 10 ciudades asociadas a los identificadores 0 - 9
string ciudades[N] = {
    "Cancun",
    "Playa del Carmen",
    "Tulum",
    "Valladolid",
    "Tizimin",
    "Kanasin",
    "Merida",
    "Progreso",
    "Uman",
    "San Francisco De Campeche"
};

/* Matriz de adyacencia , los valores representan distancia en kilómetros.
   0 representa la distancia a la misma ciudad; INT_MAX (teoricamente infinto) indica ausencia de conexión directa
   entre ciudades (Nodos) . */
int grafo[N][N] =
{            //   0   //    1  //   2   //   3   //   4  //    5  //   6   //   7   //   8   //   9
    /* 0 */  {       0,      67, INT_MAX,    160 ,     169, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX },
    /* 1 */  {      67,       0,      63,     139, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX },
    /* 2 */  { INT_MAX,      63,       0,     103, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX },
    /* 3 */  {     160,     139,     103,       0,      53,     156, INT_MAX, INT_MAX, INT_MAX, INT_MAX },
    /* 4 */  {     169, INT_MAX, INT_MAX,      53,       0, INT_MAX,     165, INT_MAX, INT_MAX, INT_MAX },
    /* 5 */  { INT_MAX, INT_MAX, INT_MAX,     156, INT_MAX,       0,       8, INT_MAX, INT_MAX, INT_MAX },
    /* 6 */  { INT_MAX, INT_MAX, INT_MAX, INT_MAX,     165,       8,       0,      36,      18,     172 },
    /* 7 */  { INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX,      36,       0, INT_MAX, INT_MAX },
    /* 8 */  { INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX,      18, INT_MAX,       0,     153 },
    /* 9 */  { INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX,     172, INT_MAX,     153,       0 }
};

// FUNCIONES DE VISUALIZACIÓN DEL GRAFO

// Muestra el listado numerado (0-9) de las ciudades presentes en String ciudades[N]
void mostrarCiudades() {
    cout << "\n Lista de ciudades\n";
    for (int i = 0; i < N; i++)
        cout << "  " << i << " -> " << " " << ciudades[i] << endl;
}

// Recorre la matriz de adyacencia e imprime las conexiones directas y sus distancias en kilometros
void conexionesCiudades() {
    cout << "\n Conexiones Directas por ciudad\n";
    for (int i = 0; i < N; i++) { //Recorre la matriz ciudades[N]
        cout << " " << i << " ._" << ciudades[i] << endl;
        for (int j = 0; j < N; j++) { //Antes de pasar a la siguiente posicion, recorre grafo[N][N]
            // Filtra aristas válidas, descartando infinito INT_MAX y distancia 0.
            if (grafo[i][j] != INT_MAX && grafo[i][j] > 0) //Imprime unicamente las ciudades que tienen conexion directa.
                cout << "  Conexion Directa de " << ciudades[i] << " a " << ciudades[j] << " con distancia de " << grafo[i][j] << " km" << endl;
        }
    }
}

// ALGORITMOS DE RECORRIDO EN ANCHURA (BFS) Y PROFUNDIDAD (DFS)

// Recorrido en anchura (BFS) mediante una cola
void BFS(int inicio) {
    bool visitado[N] = {false}; // Arreglo de control para evitar visitar nodos repetidos
    queue<int> cola;            // Cola que gestiona el orden de visita por niveles

    cola.push(inicio);
    visitado[inicio] = true;
    cout << "\n Recorrido BFS\n";

    while (!cola.empty()) {
        int actual = cola.front();
        cola.pop();
        cout << " " << actual << " -> " << ciudades[actual] << endl;

        // Explora todos los vecinos adyacentes al nodo actual
        for (int i = 0; i < N; i++) {
            if (grafo[actual][i] != INT_MAX && !visitado[i]) {
                cola.push(i);
                visitado[i] = true;
            }
        }
    }
}

// Recorrido en profundidad (DFS) mediante una pila
void DFS(int inicio) {
    bool visitado[N] = {false}; // Arreglo de control de nodos ya visitados
    stack<int> pila;            // Pila para profundizar por cada rama antes de retroceder

    pila.push(inicio);
    visitado[inicio] = true;
    cout << "\n Recorrido DFS\n";

    while (!pila.empty()) {
        int actual = pila.top();
        pila.pop();
        cout << " " << actual << " -> " << ciudades[actual] << endl;

        // Apila los vecinos adyacentes no visitados
        for (int i = 0; i < N; i++) {
            if (grafo[actual][i] != INT_MAX && !visitado[i]) {
                pila.push(i);
                visitado[i] = true;
            }
        }
    }
}

// ALGORITMO DE RUTA MÁS CORTA (DIJKSTRA)

// Función auxiliar: obtiene el índice del nodo no visitado con menor distancia acumulada
int buscarMenor(int distancia[N], bool visitado[N]) {
    int menor = INT_MAX;
    int indice = -1;

    for (int i = 0; i < N; i++) {
        if (!visitado[i] && distancia[i] < menor) {
            menor = distancia[i];
            indice = i;
        }
    }
    return indice;
}

// Calcula la ruta de menor distancia en kilómetros entre origen y destino
void Dijkstra(int origen, int destino) {
    bool visitado[N] = {false}; // VISITADO // Marca ciudades cuya distancia mínima ya es definitiva
    int distancia[N];           // DISTANCIA // Almacena la distancia mínima acumulada desde el origen
    int ruta[N];                // RUTA // Arreglo de predecesores para reconstruir el recorrido

    // Inicializa distancias en infinito (INT_MAX) y predecesores sin asignar (-1)
    for (int i = 0; i < N; i++) {
        distancia[i] = INT_MAX;
        ruta[i] = -1;
    }
    distancia[origen] = 0;

    // Selección del nodo más cercano y relajación de aristas adyacentes
    for (int i = 0; i < N; i++) {
        int actual = buscarMenor(distancia, visitado);
        if (actual == -1) break;
        if (actual == destino) break;
        visitado[actual] = true;

        for (int j = 0; j < N; j++) {
            if (grafo[actual][j] != INT_MAX && !visitado[j]) {
                if (distancia[actual] + grafo[actual][j] < distancia[j]) {
                    distancia[j] = distancia[actual] + grafo[actual][j];
                    ruta[j] = actual;
                }
            }
        }
    }

    // Impresión de resultados
    cout << "\n Resultado Dijkstra\n";
    cout << " Origen: " << ciudades[origen] << endl;
    cout << " Destino: " << ciudades[destino] << endl;

    if (distancia[destino] == INT_MAX) {
        cout << " No existe una ruta entre las ciudades." << endl;
        return;
    }

    cout << " Distancia minima: " << distancia[destino] << " km" << endl;
    if (distancia[destino] == 0)
        cout << " " << "La ciudad de Origen es igual a la de Destino\n"; // en caso de que origen y destino sean el mismo.

    // Reconstrucción del camino óptimo desde destino hasta origen usando una pila
    stack<int> camino;
    int actual = destino;
    while (actual != -1) {
        camino.push(actual);
        actual = ruta[actual];
    }

    cout << " Ruta: ";
    while (!camino.empty()) {
        cout << ciudades[camino.top()];
        camino.pop();
        if (!camino.empty()) cout << " -> ";
    }
    cout << endl;
}

// Funcion principal y menu

int main() {
    int origen, destino;
    short Opcion; // Short para ahorrar memoria
    cout << " \n Bienvenido a Explorador de rutas de la Peninsula de Yucatan\n";

    for (int i = 0; i < INT_MAX; i++) { // Uso de INT_MAX para que se pueda hacer uso del menu en multiples ocasiones.
        cout << "\n Seleccione que desea consultar\n";
        cout << " Opcion 1. Mostrar las ciudades y sus conexiones\n ";
        cout << "Opcion 2. Recorrido en anchura (BFS)\n ";
        cout << "Opcion 3. Recorrido en profundidad (DFS)\n ";
        cout << "Opcion 4. Encontrar la ruta de menor distancia (Dijkstra)\n ";
        cout << "Opcion 5. Terminar y cerrar aplicacion\n "; //Opcion para terminar la aplicacion
        cout << " ** Valores validos 1-5 **\n";
        cout << "\n Mi opcion seleccionada es(1-5): ";
        cin >> Opcion;

        switch (Opcion) {
            case 1:
                cout << "\n\n 10 ciudades seleccionadas y sus conexiones directas, \n incluyendo las distancias en kilómetros.\n";
                mostrarCiudades(); //Imprime la lista de ciudades modeladas con su identificador
                conexionesCiudades(); //Imprime las ciudades y debajo las ciudades con conexion directa y su distancia.
                break;

            case 2:
                cout << "\n Has seleccionado recorrido en anchura.\n";
                mostrarCiudades();
                cout << "\nIndique una ciudad de origen (0-9): ";
                cin >> origen;

                if (origen < 0 || origen >= N) { //Filtro de valores validos
                    cout << "\n Seleccion invalida." << endl;
                    return 1;
                }
                BFS(origen); // Funcion de recorrido en anchura
                break;

            case 3:
                cout << "\n Has seleccionado recorrido en profundidad.\n";
                mostrarCiudades();
                cout << "\n Indique una ciudad de origen (0-9): ";
                cin >> origen;

                if (origen < 0 || origen >= N) { // Filtro de valores validos
                    cout << "\n Seleccion invalida." << endl;
                    return 1;
                }
                DFS(origen);// Funcion de recorrido en profundidad
                break;

            case 4:
                cout << "\n\n Has seleccionado ruta de menor distancia (Dijkstra).\n";
                mostrarCiudades();
                cout << "\n Indique Ciudad de origen (0-9): ";
                cin >> origen;
                cout << " Indique Ciudad de destino (0-9): ";
                cin >> destino;

                if (origen < 0 || origen >= N || destino < 0 || destino >= N) {
                    cout << "\n Seleccion invalida." << endl;
                    return 1;
                }
                Dijkstra(origen, destino); //Funcion de ruta de menor distancia
                break;

            case 5: // Terminar la aplicacion tras este case
                cout << "\n\n Cerro la Aplicacion ";
                return 0;
                break;
        }
    }

    return 0;
}
