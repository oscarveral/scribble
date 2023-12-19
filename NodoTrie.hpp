/**
 *  Clase Nodo Trie que representa un nodo de un árbol trie.
 */
#ifndef __NODO_TRIE_HPP
#define __NODO_TRIE_HPP
/** 
 * Nos aventajamos de la estructura de datos unordered_map para almacenar los punteros a los hijos acelerando búsquedas y reduciendo memoria usada.
 * Además nos permite trabajar con diccionarios de letras de tamaño arbitrario.
 */ 
#include <unordered_map>
#include <vector>
class NodoTrie
{
    private:
        /* Booleano que inidica si la llegada a este nodo marca el fin de una palabra formada por el recorrido de los nodos anteriores. */
        bool esFinPalabra;
        /**
         * Mapa hash que almacena los punteros a los nodos hijos, igual de eficiente en tiempo que un array pero más eficiente en espacio. 
         * Como claves usaremos los caracteres de la palabra.
        */
        std::unordered_map<char, NodoTrie*> mapaHijos;
    public:
        /* Constructor. */
        NodoTrie(void);
        /* Destructor. (Esta pensado para su aplicación a la raiz del arbol, si se elimina un nodo hijo con delete, en el mapa del padre todavía existirá el puntero a este aunque ya no esté en memoria) */
        ~NodoTrie(void);
        /* Métodos. */
        /* Método que consulta si para el caracter dado hay un nodoTrie hijo en el mapa del nodoTrie actual. */
        NodoTrie * consulta (char caracter);
        /* Método que inserta un nuevo nodoTrie en el mapa del nodo actual para el caracter dado. */
        void inserta (char caracter);
        /* Método que simplifica la eliminación de nodos hijos de un nodo padre. Elimina un nodo hijo del mapa de nodos (y por tanto recursivamente todos los subhijos...) y borra su entrada del mapa. */
        void elimina (char caracter);
        /* Métodos de marcado. Consideramos que cuando una palabra acabe se marcará el nodo de su último caracter.*/
        /* Pone a true la marca de fin de palabra del nodoTrie. */
        void ponMarca (void);
        /* Pone a false la marca de fin de palabra del nodoTrie. */
        void quitarMarca (void);
        /* Devuelve el valor de la marca de fin de palabra del nodoTrie. */
        bool hayMarca (void);
        /* Método auxiliar que devuelve el número de hijos del nodo. */
        int numeroHijos (void);
        /* Método auxiliar que devuelve la lista completa de hijos del nodo en tuplas con los caracteres que los identifican. */
        std::vector<std::pair<char, NodoTrie *>> listaHijos (void);
};
#endif /* __NODO_TRIE_HPP */