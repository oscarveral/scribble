/**
 *  Fichero de cabecera del TDA TablaHash. Implementación con dispersión cerrada y hashing doble.
 *  Para la elimnación de elementos se marcarán aquellos elementos eliminados para tenerlos en cuenta en inserción pero no en búsqueda. En la redimensión los elementos eliminados no se tienen en cuenta.
 */
#ifndef __TABLA_HASH_HPP
#define __TABLA_HASH_HPP
#include <string>
#include <vector>
#include "ManipuladorCadenas.hpp"
/* Clase que representa la tabla Hash. */
class TablaHash
{
    private:
        /* Constantes de clase. */
        /* Constante que define el tamaño inicial por defecto de las tablas hash recien creadas o vaciadas. */
        static const int INIT_SIZE;
        /* Constantes que definen el valor inicial y la base de calculo para hashDJB2. */
        static const int INIT_VALUE_DJB2;
        static const int BASE_DJB2;
        /* Constante con la que se inicializarán todas las posiciones de la tabla en su construcción (Cadena Vacía). Equivale a señalar que una posición está libre. */
        static const std::string MARCA_POS_LIBRE;
        /* Constante que marca una posición como eliminada para poder tratarla adecuadamente en la inserción y búsqueda. */
        static const std::string MARCA_POS_ELIMINADA;
        /* Constante que define la ocupación máxima de una tabla antes de ser reestructurada. */
        static const double MAX_OCUPACION;
        /* Variables de objeto. */
        /* Contador de palabras alamacenadas en la tabla. */
        int nPalabras;
        /* Contador que almacena el tamaño actual de la tabla. */
        int sizeTablaHash;
        /* Entero que almacena el taamaño inicial al que se inicializó la tabla por primera vez. */
        int sizeInicial;
        /* Puntero a la tabla de hash. */
        std::string * T;
        /* Manipulador de cadenas local usado para porcesar los comodines en el comando adicional. */
        ManipuladorCadenas str;
        /* Métodos privados. */
        /* Función de hash principal. Función de hash iterativa que implementa el algoritmo djb2a visto en teoría. */
        unsigned int hashDJB2A (std::string palabra);
        /* Función de hash secundaria. Usada si ocurren colisiones. Implementa el algoritmo djb2 mencionado en teoria con una pequeña modificación para que nunca devuelva 0. */
        unsigned int hashDJB2Mod (std::string palabra);
        /* Función que usando las dos funciones hash calcula el hash normalizado al tamaño de la tabla (modulo sizeTablaHash) correspondiente a la palabra e iteración dada. Aplica (hashDJB2A * hashDJB2Mod*iteration) MOD sizeTablaHash. */
        unsigned int hash (unsigned int iteration, std::string palabra);
        /* Función utilizada para reestructurar la tabla si se llena por encima de un límite. Se duplicará el tamaño de la tabla actual, lo que da un crecimiento exponencial. */
        void reestructurar (void);
    public:
        /* Constructores. */
        TablaHash(void);
        TablaHash(unsigned int size);
        /* Métodos. */
        /* Método de inserción de una palabra en la tabla. Si ya estaba en ella no insertamos nada. Si superamos cierta ocupación redimensionamos nuestra tabla. */
        void inserta (std::string palabra);
        /* Método de eliminación de una palabra de la tabla. Se marca dicha entrada como eliminada si se encontró la palabra. */
        void elimina (std::string palabra);
        /* Método de consulta de palabras. Se consulta si la palabra dada se encuentra exactamente en la tabla, devolviendo verdadero si es asi o falso en caso contrario. */
        bool consulta (std::string palabra);
        /* Método que vacía completamente una tablaHash. */
        void vacia (void);
        /* Método que devuelve la cantidad de palabras almacenadas en la tabla. */
        int numeroPalabras (void);
        /* Método que implementa el comando adicional de comodines, devuelve un vector ordenado con la lista de palabras que de la tabla que coinciden con el patrón. Ejercicio 209. */
        std::vector<std::string> comandoAdicionalProcesarComodines (std::string patron);
        /* Destructor. */
        ~TablaHash(void);
    };
#endif