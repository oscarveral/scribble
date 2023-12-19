/**
 * Libreria de la calse especializada en la manipulación de cadenas de caracteres UTF-8.
 */
#ifndef __MANIPULADOR_CADENAS_HPP
#define __MANIPULADOR_CADENAS_HPP
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
/* Declaración de constantes de cadenas de caracteres para el tratamiento de caracteres especiales UTF-8. */
/* Cadena de caracteres con los caracteres especiales en mayúsculas. */
extern const std::string SPECIAL_CHAR_MAYUS;
/* Cadena de caracteres con todos los caracteres especiales. */
extern const std::string SPECIAL_CHAR_ALL;
/* Cadena de caracteres con los caracteres especiales en minúsculas. */
extern const std::string SPECIAL_CHAR_MINUS;
/* Declaración de constantes de caracteres usados en el tratamiento de caracteres especiales UTF-8. */
/* Caracter representante del byte con el que empiezan todos los caracteres especiales. */
extern const char SPECIAL_CHAR_IDENTIFIER;
/* Constante que representa el factor de conversión a sumar al segundo byte de los caracteres especiales para convertirlos de mayúscula a minúscula. */
extern const char SPECIAL_CHAR_MAYUS_TO_MINUS_CONVERSION_FACTOR;
/* Declaración de enumerado y constante para la clasificación de cadenas de caracteres de los tipos del manipulador. */
/* Enumerado de los tipos de palabras posibles. */
enum tipoPalabras {MINUS, MAYUS, FRASE, PROPIO};
/* Array de cadenas de caracteres que representan a cada uno de los posibles tipoPalabras. ej. para MINUS en el array hay alamcenado "MINUS". */
extern const std::string TIPOS_PALABRAS[4];
/* Delcaración de constantes para el tratamiento de comodines. */
/* Constante que define el caracter que identifica el comodín de cualquier letra. */
extern const char COMODIN_TOTAL;
/* Constante que define el caracter que identifica el comodín de cualquier consonante. */
extern const char COMODIN_CONSONANTE;
/* Constante que define el caracter que identifica el comodín de cualquier vocal. */
extern const char COMODIN_VOCAL;
/* Constante que define todos los caracteres del COMODIN_TOTAL en orden alfabético. */
extern const std::string LISTA_LETRAS;
/* Constante que define todos los caracteres del COMODIN_CONSONANTE en orden alfabético. */
extern const std::string LISTA_CONSONANTES;
/* Constante que define todos los caracteres del COMODIN_VOCAL en orden alfabético. */
extern const std::string LISTA_VOCALES; 
class ManipuladorCadenas
{
    public:
        /* Métodos. */
        /*Extensión de la función de librería isalpha teniendo en cuenta el tratamiento de carácteres especiales. input es una cadena de caracteres que debe contener un caracter normal o especial unicamente. */
        bool esAlpha(std::string input);
        /* Función que dada una cadena la devuelve en minúsculas teniendo en cuenta los caracteres especiales.*/
        std::string minuscula (std::string input);
        /* Función que dada una cadena de texto nos dice que tipo de palabra de nuestro enumerado es dicha cadena. */
        tipoPalabras tipoCadena (std::string input);
        /* Función que obtiene un caracter de la entrada, incluyendo los especiales. */
        std::string obtenerCaracter();
        /* Función que devuelve un caracter a la entrada, incluyendo los especiales. La cadena dada devolverá a la entrada el primer caracter especial o los dos primeros carácteres de la cadena dada.*/
        void devolverCaracter(std::string input);
        /* Funcón que compara un patrón y una palabra y devuelve verdadero si la palabra se ajusta al patrón dado según los comodines que tenga este. */
        bool esExpansionPatron (std::string patron, std::string palabra);
};
#endif /* __MANIPULADOR_CADENAS_HPP */