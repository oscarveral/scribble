/**
 * Clase Árbol que representa un conjunto de palabras utilizando nodoTrie.
 */
#ifndef __ARBOL_HPP
#define __ARBOL_HPP
#include <string>
/* Usamos nuestros nodos Trie. */
#include "NodoTrie.hpp"
/* Clase Árbol. */
    class Arbol
    {
        private:
            /* Nodo raiz del árbol. */
            NodoTrie * raiz;
            /* Contador de las palabras que contiene el árbol. */
            int nPalabras;
            /* Constante con el valor a devolver en el procesado de completado si no tiene éxito. */
            const std::string CADENA_VACIA = "";
        public:
            /* Constructor. */
            Arbol(void);
            /* Destructor. */
            ~Arbol(void);
            /* Métodos. */
            /* Método de inserción de la palabra dada en el árbol. */
            void inserta (std::string palabra);
            /* Método de consulta si existe la palabra dada en el árbol. */
            bool consulta (std::string palabra);
            /* Método que elimina una palabra del diccionario del árbol. */
            void elimina (std::string palabra);
            /* Método que vacía un árbol completamente. */
            void vacia (void);
            /* Método que devuelve la cantidad de palabras en el árbol. */
            int numeroPalabras (void);
            /* Método que implementa el comando adicional de completado de palabras, que devuelve una cadena con los caracteres que faltan para completar una palabra si es posible. (309) */
            std::string comandoAdicionalCompletarPalabras (std::string palabra);
    };
#endif /* __ARBOL_HPP */