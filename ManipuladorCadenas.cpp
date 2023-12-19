/**
 * Implementación de la clase de la libreria para la manipulación de cadenas de caracteres UTF-8.
 */
#include "ManipuladorCadenas.hpp"
const std::string SPECIAL_CHAR_MAYUS = "ÑÁÉÍÓÚÜ";
const std::string SPECIAL_CHAR_ALL = "ÑñÁáÉéÍíÓóÚúÜü";
const std::string SPECIAL_CHAR_MINUS = "ñáéíóúü";
const char SPECIAL_CHAR_IDENTIFIER = 0xC3;
const char SPECIAL_CHAR_MAYUS_TO_MINUS_CONVERSION_FACTOR = 0x20;
const std::string TIPOS_PALABRAS[4] = {"MINUS", "MAYUS", "FRASE", "PROPIO"};
const char COMODIN_TOTAL = '*';
const char COMODIN_CONSONANTE = '+';
const char COMODIN_VOCAL = '_';
const std::string LISTA_LETRAS = "aáAÁbBcCdDeéEÉfFgGhHiíIÍjJkKlLmMnNñÑoóOÓpPqQrRsStTuúüUÚÜvVwWxXyYzZ";
const std::string LISTA_CONSONANTES = "bBcCdDfFgGhHjJkKlLmMnNñÑpPqQrRsStTvVwWxXyYzZ";
const std::string LISTA_VOCALES = "aáAÁeéEÉiíIÍoóOÓuúüUÚÜ";
bool ManipuladorCadenas::esAlpha (std::string input)
{
    /* Combinamos una llamada a la función isAlpha con el tratamiento de especiales, identificando si encontramos nuestro caracter especial o llegamos a npos sin encontrarla */
    return (isalpha(input[0]) || ((input[0]) == SPECIAL_CHAR_IDENTIFIER && SPECIAL_CHAR_ALL.find(input[1]) != std::string::npos));
}
std::string ManipuladorCadenas::minuscula(std::string input)
{
    /* Recorrido de toda la cadena dada. */
    for (unsigned i = 0; i < input.length(); i++)
    {
        /* Se aplica la conversión a minusculas para los caracteres ASCII. */
        input[i] = tolower(input[i]);
        /* Tratamos el caso de los especiales buscando su identificador y en caso de encontrarlo buscando el siguiente caracter en el array de carcateres especiales. */
        if ((input[i] == SPECIAL_CHAR_IDENTIFIER) && SPECIAL_CHAR_MAYUS.find(input[++i]) != std::string::npos)
        {
            /* Se aplica la conversión a minusculas de caracteres especiales. */
            input[i] |= SPECIAL_CHAR_MAYUS_TO_MINUS_CONVERSION_FACTOR;
        }
    }
    /* Devolvemos la nueva cadena. */
    return input;   
}
tipoPalabras ManipuladorCadenas::tipoCadena(std::string input)
{
    /* Entero que registra la posición actual en la cadena. */
    unsigned pos= 0;
    /* Booleano que se pondrá a false una vez hayamos pasado la primera letra de la cadena. */
    bool primera= true;
    /* Tipo de palabra de la primera letra. */
    tipoPalabras tipoPrimera;
    /* Enteros que almacenan el número de minúsculas y mayúsculas. */
    int numMayus= 0, numMinus= 0;
    /* Recorrido de la cadena de caracteres usando pos. */
    while (pos<input.length() && numMayus*numMinus==0) {
        /* Tratamiento de que el caracter en la posición actual sea el identificador de especiales. En este caso incrementamos el contador de posición */
        if (input[pos]==SPECIAL_CHAR_IDENTIFIER) pos++;
        /* Tratamiento de que el caracter actual sea mayúscula, incluidos los especiales. */
        if ((input[pos]>='A' && input[pos]<='Z') || SPECIAL_CHAR_MAYUS.find(input[pos])!=std::string::npos)
        {
            /* Si estamos en la primera letra establecemos su tipo a MAYUS. */
            if (primera) tipoPrimera= MAYUS;
            /* En otro caso incrementamos el número de mayusculas. */
            else numMayus++;
        }
        /* Tratamiento de que el caracter sea cualquier otro. */
        else
        {
            /* Incrementamos el número de minúsculas. */
            numMinus++;
            /* Si era la primera letra ponemos su tipo a MINUS. */
            if (primera)
                tipoPrimera= MINUS;
        }
        /* Después de la primera iteración ponemos primera a false. */
        primera= false;
        pos++;
    }
    /* Analisis de casos para devolver el tipo de cadena. */
    if (numMayus && numMinus)
        return PROPIO;
    else if (tipoPrimera==MAYUS && numMinus)
        return FRASE;
    else if (numMinus)
        return MINUS;
    else
        return MAYUS;
}
std::string ManipuladorCadenas::obtenerCaracter()
{
    /* Si nos encontramos al final de la entrada devolvemos una cadena vacía. */
    if (std::cin.eof())
    {
        return "";
    }
    /* En otro caso creamos una cadena a la que le introducimos el caracter actual de la entrada. */
    else
    {
        std::string res;
        res += std::cin.get();
        /* Si el caracter actual fue el identificador de los especiales UTF-8 añadimos a la cadena el siguiente caracter para completarlo. */
        if (res[0] == SPECIAL_CHAR_IDENTIFIER) res += std::cin.get();
        /* Devolvemos la cadena con el caracter obtenido. */
        return res;
    }
}
void ManipuladorCadenas::devolverCaracter(std::string input)
{
    /* Si la cadena dada tiene una longitud mayor que uno el caracter que se devuele, es UTF-8 y por tanto es necesario devolver 2 bytes. */
    if (input.length() > 1) std::cin.putback(input[1]);
    /* NOTA. Por la implementación de cin.putback(...) se devuelven en orden inverso a su obtención. */
    std::cin.putback(input[0]);
}
bool ManipuladorCadenas::esExpansionPatron(std::string patron, std::string palabra)
{
    /* Natural que guardará la posición actual de la palabra. */
    unsigned int posPalabra = 0;   
    /* Recorremos caracter a caracter el patrón comparandolo con los caracteres de la palabra. */
    for (unsigned int i = 0; i < patron.length(); i++)
    {
        /* Tratamos los casos de comodines. */
        if (patron[i] == COMODIN_VOCAL)
        {
            /* Tratamos caracteres especiales. */
            if (palabra[posPalabra] == SPECIAL_CHAR_IDENTIFIER)
            {
                if(LISTA_VOCALES.find(palabra[++posPalabra]) == std::string::npos) return false;
            }
            /* Si no encontramos el caracter de la posición i en la lista de vocales volvemos. */
            else if (LISTA_VOCALES.find(palabra[posPalabra]) == std::string::npos) return false;
        }
        else if (patron[i] == COMODIN_CONSONANTE)
        {
            /* Tratamos los caracteres especiales. */
            if (palabra[posPalabra] == SPECIAL_CHAR_IDENTIFIER)
            {
                if (LISTA_CONSONANTES.find(palabra[++posPalabra]) == std::string::npos) return false;
            }
            /* Si no encontramos el caracter de la posición en la lista de consonantes volvemos. */
            else if (LISTA_CONSONANTES.find(palabra[posPalabra]) == std::string::npos) return false;
        }
        else if (patron[i] == COMODIN_TOTAL)
        {
            /* Tratamos caracteres especiales. */
            if (palabra[posPalabra] == SPECIAL_CHAR_IDENTIFIER)
            {
                if(LISTA_LETRAS.find(palabra[++posPalabra]) == std::string::npos) return false;
            }
            /* Si no encontramos el caracter de la posición i en la lista de letras volvemos. */
            else if (LISTA_LETRAS.find(palabra[posPalabra]) == std::string::npos) return false;
        }
        /* Tratamos el caso de caracter normal. */
        else
        {   
            /* Si en la misma posición hay dos caracteres (bytes) diferentes volvemos. */
            if (patron[i] != palabra[posPalabra]) return false;
        }
        posPalabra += 1;
    }
    if (palabra.length() > posPalabra) return false;
    /* Se devuelve true por defecto. */
    return true;
}