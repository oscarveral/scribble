/**
 * Implementación de la consola/intérprete de comandos. 
 */
#include "Consola.hpp"
void Consola::meter (std::string palabra)
{
    /* Simplemente se llama a la rutina de insertar una palabra en el ConjuntoPalabras de la consola. */
    diccionarioLocal.inserta(palabra);
}
void Consola::borrar (std::string palabra)
{
    /*Llamamos a la ruitna de eliminado de palabras del ConjuntoPalabras local. */
    diccionarioLocal.elimina(palabra);
}
void Consola::comprobar (std::string palabra)
{
    /* Llamamos al procedimiento de consulta del ConjuntoPalabras para ver si está la palabra dada. */
    if (!diccionarioLocal.consulta(palabra)) std::cout << "[error]";
}
void Consola::ejecutarConsola ()
{
    /* tipoToken que representa el tipo de token leido. */
    tipoToken token;
    /* Cadena de caracteres que procesará el intérprete. */
    std::string cadena;
    /* Llamada inicial para identificar el primer token. */
    manipuladorLocal.obtenerToken(token, cadena);
    /* Lectura hasta final de input de los tokens introducidos en el interprete. */
    while (token != FINENTRADA)
    {
        /* Si el token leido es un comando. */
        if (token == COMANDO) procesarComando (cadena);
        /* Si en otro caso el token leido es cualquier otro excepto fin de comando imprimimos la cadena actual. */
        else if (token != FINCOMANDO) std::cout << cadena;
        /* Obtención del siguiente token. */
        manipuladorLocal.obtenerToken(token, cadena);
    }
}
void Consola::procesarComando(std::string comando)
{
    /* Declaración del stream de input segun la cadena. */
    std::istringstream inputStream (comando);
    /* Declaración de las cadenas de comando y parámetros (para los comandos unitarios). */
    std::string cmd, argumento;
    /* Extraigo el comando de la cadena dada. */
    inputStream >> cmd;
    /* Análisis de casos de comando. */
    if (cmd == "texto") procesarTexto();
    else if (cmd == "diccionario") procesarDiccionario();
    else if (cmd == "insertar") procesarInsertar();
    else if (cmd == "eliminar") procesarEliminar();
    /* Si no entras a ninguno de los comandos anteriores estamos ante un comando unario que tiene argumento, por tanto hay que procesarlo. */
    else
    {
        /* Lectura de argumentos. */
        inputStream >> argumento;
        /* Buscamos el comando */
        if (cmd == "comodines") procesarComodines(argumento);
        if (cmd == "completar") procesarCompletar(argumento);
    }
}
void Consola::procesarTexto()
{   
    /* Declaro un nuevo tipo token para identificar tokens en nuestra cadena de texto. */
    tipoToken token;
    /* Cadena de texto que usaremos para "recorrer" el texo de nuestro comando texto. */
    std::string cadenaTexto;
    /* Primera llamada para identificar el primer token dentro del texto. */
    manipuladorLocal.obtenerToken(token, cadenaTexto);
    /* Recorrido del texto del comando hasta encontrar el fin del comando de texto o el fin de la entrada. */
    while (token != FINENTRADA && token != FINCOMANDO)
    {
        /* Si se identifica un comando se llama al procedimiento de la consola que lo identificará para procesarolo. */
        if (token == COMANDO)
        {
            procesarComando(cadenaTexto);
        }
        /* Si el token identificado es una palabra se escribe y llamamos a comprobar palabra. */
        else if (token == PALABRA)
        {
            /* Impresión de la palabra directamente. */
            std::cout << cadenaTexto;
            comprobar(cadenaTexto);
        }
        /* Si el token identificado es un símbolo se escribe exactamente igual. */
        else
        {
            std::cout << cadenaTexto;
        }
        /* Llamada para obtener el siguiente token. */
        manipuladorLocal.obtenerToken(token, cadenaTexto);
    }
}
void Consola::procesarDiccionario()
{
    /* Vaciamos el diccionario. */
    diccionarioLocal.vacia();
    /* Declaro un nuevo tipo token para identificar tokens en nuestra cadena de texto. */
    tipoToken token;
    /* Cadena de texto que usaremos para "recorrer" el texo de nuestro comando texto. */
    std::string cadenaTexto;
    /* Primera llamada para identificar tokens. */
    manipuladorLocal.obtenerToken(token, cadenaTexto);
    /* Recorrido del texto del comando hasta encontrar el fin del comando de diccionario. . */
    while (token != FINENTRADA && token != FINCOMANDO)
    {
        /* Si el token identificado es una palabra se llama a meter(palabra). Si el token identificado es un símbolo o comando no se hace nada. */
        if (token == PALABRA)
        {
            meter(cadenaTexto);
        }
        /* Llamada para obtener el siguiente token. */
        manipuladorLocal.obtenerToken(token, cadenaTexto);
    }
    /* Impresión del total de palabras del diccionario. */
    std::cout << "[" << diccionarioLocal.numeroPalabras() << " palabras]";
}
void Consola::procesarInsertar()
{
    /* Declaro un nuevo tipo token para identificar tokens en nuestra cadena de texto. */
    tipoToken token;
    /* Cadena de texto que usaremos para "recorrer" el texo de nuestro comando texto. */
    std::string cadenaTexto;
    /* Primera llamada para identificar tokens. */
    manipuladorLocal.obtenerToken(token, cadenaTexto);
    /* Recorrido del texto del comando hasta encontrar el fin del comando de insertar.*/
    while (token != FINENTRADA && token != FINCOMANDO)
    {
        /* Si el token identificado es una palabra se llama a meter(palabra). Si el token identificado es un símbolo o comando no se hace nada. */
        if (token == PALABRA)
        {
            meter(cadenaTexto);
        }
        /* Llamada para obtener el siguiente token. */
        manipuladorLocal.obtenerToken(token, cadenaTexto);
    }
    /* Impresión del total de palabras del diccionario. */
    std::cout << "[" << diccionarioLocal.numeroPalabras() << " palabras]";
}
void Consola::procesarEliminar()
{
    /* Declaro un nuevo tipo token para identificar tokens en nuestra cadena de texto. */
    tipoToken token;
    /* Cadena de texto que usaremos para "recorrer" el texo de nuestro comando texto. */
    std::string cadenaTexto;
    /* Primera llamada para identificar tokens. */
    manipuladorLocal.obtenerToken(token, cadenaTexto);
    /* Recorrido del texto del comando hasta encontrar el fin del comando de diccionario. . */
    while (token != FINENTRADA && token != FINCOMANDO)
    {
        /* Si el token identificado es una palabra se llama a borrar(palabra). Si el token identificado es un símbolo o comando no se hace nada. */
        if (token == PALABRA)
        {
            borrar(cadenaTexto);
        }
        /* Llamada para obtener el siguiente token. */
        manipuladorLocal.obtenerToken(token, cadenaTexto);
    }
    /* Impresión del total de palabras del diccionario. */
    std::cout << "[" << diccionarioLocal.numeroPalabras() << " palabras]";
}
void Consola::procesarComodines(std::string argumento)
{
    /* Impresión del comienzo del output. */
    std::cout << argumento << "[comod: ";
    /* Creamos una lista en la que almacenaremos las palabras que coinciden con el patrón. */
    std::vector<std::string> listaCoincidentes = diccionarioLocal.procesarPatron(argumento);
    /* Imprimimos la lista de coincidentes. */
    for (unsigned i = 0; i < listaCoincidentes.size(); i++)
    {
        std::cout << listaCoincidentes[i];
        if (i+1 != listaCoincidentes.size()) std::cout << " ";
    }
    /* Impresión del final del comando. */
    std::cout << "]";
}
void Consola::procesarCompletar (std::string argumento)
{
    /* Impresión estandar del principio de la salida. */
    std::cout << argumento << "[comp: ";
    /* Cadena que recoge las letras con las que se completa la palabra. */
    std::string letrasCompletado = diccionarioLocal.procesarCompletado(argumento);
    /* Imprimimos dichas letras y acabamos la salida. */
    std::cout << letrasCompletado << "]";
}