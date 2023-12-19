/**
 * Fichero de cabecera del TDA ConjuntoPalabras.
 */
#ifndef __CONJUNTO_PALABRAS_HPP
#define __CONJUNTO_PALABRAS_HPP
#include <string>
#include <vector>
#include "TablaHash.hpp"
#include "Arbol.hpp"
#include "ManipuladorCadenas.hpp"
/* Clase ConjjuntoPalabras que almacena un diccionario de palabras. */
class ConjuntoPalabras
{
    private:
        /* Tabla hash que almacena las palabras del conjunto. */
        TablaHash th;
        /* Árbol Trie que almacena las palabras del conjunto. */
        Arbol ab;
        /* Manipulador de cadenas necesario para la operación de consulta del conjunto. */
        ManipuladorCadenas str;
    public:
        /* Constructor. */
        ConjuntoPalabras(void);
        /* Métodos. */
        /* Vacía completamente una lista de palabras. */
        void vacia (void);
        /* Inserta una palabra en el diccionario en orden alfabético, comprobando que no esté repetida. Se incrementa el contador de palabras. */
        void inserta (std::string palabra);
        /* ELimina una palabra de la lista. Si estaba se decrementa el contador de palabras. */
        void elimina (std::string palabra);
        /* Consulta si la palabra dada se encontraba en la lista de palabras. Si la palabra es del tipo MAYUS o FRASE hay que buscar su variante MINUS también.*/
        bool consulta (std::string palabra);
        /* Consulta exacta de una palabra en el diccionario. */
        bool consultaExacta (std::string palabra);
        /* Devuelve la cantidad actual de palabras en el conjunto. */
        int numeroPalabras (void);
        /* Comandos adicionales. */
        /* Comando de procesado de comodines con Tablas de Hash. (209) */
        std::vector<std::string> procesarPatron (std::string patron);
        /* Comando de procesado de completado de palabras con Árboles Trie. (309) */
        std::string procesarCompletado (std::string comienzoPalabra);
};
#endif /* __CONJUNTO_PALABRAS_HPP */