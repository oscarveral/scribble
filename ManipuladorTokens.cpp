/**
 * Implementación de la clase del manipulador de tokens. Extiende la clase del maniulador de caracteres. 
 */

#include "ManipuladorTokens.hpp"
const std::string TIPOS_TOKEN[5] = {"PALABRA", "SIMBOLO", "COMANDO", "FINCOM", "FINENTRADA"};
const std::string STRING_INICIO_COMANDO = "<";
const std::string STRING_FIN_COMANDO = ">";
const char CHAR_IDENTIFICADOR_FIN_COMANDO = '/';
void ManipuladorTokens::escribirToken (int n, int token, std::string cadena)
{
    std::cout << n << ". " << TIPOS_TOKEN[token] << ": [" << cadena << "]";
    /* Si el token fue una palabra imprimimos además el tipo de palabra que es. */
    if (token == PALABRA)
    {
        std::cout << " " << TIPOS_PALABRAS[tipoCadena(cadena)];
    }
    std::cout << std::endl;
}
void ManipuladorTokens::obtenerToken (tipoToken &tipo, std::string &cadena)
{
    /* Si nos encontramos al final de la cadena devolvemos un token de FINENTRADA. */
    if (std::cin.eof())
    {
        /* Establecemos además el tipo de token a FINENTRADA. */
        tipo = FINENTRADA;
    }
    /* En otro caso. */
    else
    {
        /* Declaramos un string y le asignamos el caracter actual de la entrada. */
        std::string caracter;
        caracter = obtenerCaracter();
        /* Si es un caracter alfabético nos encontramos ante un token PALABRA. */
        if (esAlpha(caracter)) {
            tipo = PALABRA;
            /* Asignamos a la cadena nuestro caracter. */
            cadena = caracter;
            /* Mientras encontremos más caracteres alfabéticos o no lleguemos al final de la entrada añadimos a la cadena los caracteres encontrados. */
            while (esAlpha(caracter = obtenerCaracter()) && !std::cin.eof()) cadena += caracter;
            /* Si no estamos al final de la cadena el caracter encontrado no es alfabético y hay que devolverlo a la entrada. */
            if (!std::cin.eof()) devolverCaracter(caracter);
        }
        /* Si el texto comienza con "<" estamos ante un token de comando. */
        else if (caracter == STRING_INICIO_COMANDO)
        {
            /* Creamos una cadena vacía en la que almacenar el texto del token. */
            cadena = "";
            /* Mientras el caracter obtenido no sea ">" o no lleguemos al final continuamos añadiendo a la cadena los caracteres obtenidos. */
            while ((caracter = obtenerCaracter()) != STRING_FIN_COMANDO && !std::cin.eof())
            {
                cadena += caracter;
            }
            /* Si el primer caracter de la cadena es '/' es un token FINCOMANDO, en otro caso será COMANDO. */
            if (cadena[0] == CHAR_IDENTIFICADOR_FIN_COMANDO) tipo = FINCOMANDO;
            else tipo = COMANDO;
        }
        /* Cualquier otra entrada será un token símbolo. */
        else
        {
            tipo = SIMBOLO;
            /* Asignamos a cadena el caracter leído. */
            cadena = caracter;
            /* Mientras nuestro caracter no sea alfabético, ni "<" de inicio de comando ni el final de la entrada añadimos a la cadena dicho caracter leído. */
            while (!esAlpha(caracter = obtenerCaracter()) && caracter != STRING_INICIO_COMANDO && !std::cin.eof())
            {
                cadena += caracter;
            }
            /* Si no nos encontrabamos al final de la cadena tenemos que devolver el caracter que rompió el bucle. */
            if (!std::cin.eof()) devolverCaracter(caracter);
        }
    }
}