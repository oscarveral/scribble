/**
 * Libreria de la clase que extiende la funcionalidad de ManipuladorCadenas para el manejo e identificación de tokens en una cadena de texto que permitan identificar comandos.
 */

#ifndef __MANIPULADOR_TOKENS_HPP
#define __MANIPULADOR_TOKENS_HPP
#include <string>
#include <iostream>
/* Como extendemos el manipulador de cadenas necesitamos su libreria. */
#include "ManipuladorCadenas.hpp"
/* Declaración del enumerado y constante para la clasificación de tokens del manipulador. */
/* Enumerado de los tipos de tokens disponibles. */
enum tipoToken {PALABRA, SIMBOLO, COMANDO, FINCOMANDO, FINENTRADA};
/* Array de cadenas de caracteres que se corresponden con los diferentes tokens de nuestro enumerado. ej: para PALABRA el array contiene "PALABRA". */
extern const std::string TIPOS_TOKEN[5];
/* Declaración de constantes de identificación de tokens COMANDO y FINCOMANDO. */
/* Cadena que representa el caracter de inicio de token comando. */
extern const std::string STRING_INICIO_COMANDO;
/* Cadena que representa el caracter de fin de de token comando. */
extern const std::string STRING_FIN_COMANDO;
/* Caracter de identificación del token FINCOMANDO. */
extern const char CHAR_IDENTIFICADOR_FIN_COMANDO;
/* Clase manipulador de tokens que extiende el manipulador de cadenas. */
class ManipuladorTokens : public ManipuladorCadenas
{
    public:
        /* Métodos. */
        /* Función que escribe n seguido del tipo de token seguido de la cadena de texto que es dicho token. */
        void escribirToken (int n, int token, std::string cadena);
        /* Función que recorre la entrada identificando tokens en la cadena de texto de la entrada. Mientras pueda identificar tokens pone el valor de dicho token en el argumento tipo. El argumento cadena se queda con el texto del token identificado.*/
        void obtenerToken (tipoToken &tipo, std::string &cadena);
};
#endif /* __MANIPULADOR_TOKENS_HPP */