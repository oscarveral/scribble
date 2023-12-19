/**
 * Libreria de la clase consola. Sería el intérprete de comandos como tal, al que llamaremos desde la rutina main.
 */
#ifndef __CONSOLA_HPP
#define __CONSOLA_HPP
#include <sstream>
#include <vector>
/* Inclusión del TDA ConjuntoPalabras para el manejo de diccionarios. */
#include "ConjuntoPalabras.hpp"
/* Inclusión del ManipuladorTokens para el manejo de cadenas e identificación de comandos. */
#include "ManipuladorTokens.hpp"
class Consola
{
    private:
        /* Declaración del diccionario de palabras local a la consola. */
        ConjuntoPalabras diccionarioLocal;
        /* Declaración del objeto que usaremos para la manipulación de tokens localmente. */
        ManipuladorTokens manipuladorLocal;
        /* Procedimientos de gestión directa al diccionario local. */
        /* Introduce una palabra en el diccionario local. */
        void meter (std::string palabra);
        /* Elimina una palabra del diccionario local. */
        void borrar (std::string palabra);
        /* Comprueba si la palabra dada está en el diccionario local. Si no está escribe un mensaje de error  */
        void comprobar (std::string palabra);
    public:
        /* Procedimientos auxiliares de la consola. */
        /* Procedimiento que pone en marcha la consola de comandos, comenzando la identificación de comandos. */
        void ejecutarConsola (void);
        /* Dado un comando analiza de cual se trata y lo procesa en caso de existir entre los comandos disponibles. */
        void procesarComando (std::string comando);
        /* Comandos complejos de la consola. */
        /* Hasta llegar al fin del comando procesa todo el texto que contiene, intreprentado, si los hay, los comandos que estén contenidos en el texto. */
        void procesarTexto ();
        /* Vacia el diccionario local y lee las palabras a introducir a continuación hasta llegar al fin del comando. */
        void procesarDiccionario ();
        /* Inserta las palabras dadas a continuación en el diccionario hasta llegar al fin del comando. */
        void procesarInsertar();
        /* Elimina las palabras a continuación hasta llegar al fin del comando del diccionario local a la consola. */
        void procesarEliminar();
        /* Comandos unarios de la consola. */
        /* Comando que procesa palabras con comodines, buscándolas en el diccionario local todas las posibilidades. Usa el diccionario de tablas de dispersión. (209) */
        void procesarComodines (std::string argumento);
        /* Comando que completa la palabra dada del diccionario si es posible. Usa el diccionario de árbol trie.(309) */
        void procesarCompletar (std::string argumento);
};
#endif /* _CONSOLA_HPP */