/**
 * Código fuente del TDA TablaHash.
 */
#include "TablaHash.hpp"
#include <iostream>
const int TablaHash::INIT_SIZE = 5381;
const int TablaHash::INIT_VALUE_DJB2 = 5381;
const int TablaHash::BASE_DJB2 = 33;
const std::string TablaHash::MARCA_POS_LIBRE = "";
const std::string TablaHash::MARCA_POS_ELIMINADA = "\t";
const double TablaHash::MAX_OCUPACION = 0.5;
unsigned int TablaHash::hashDJB2A (std::string palabra)
{
    /* Declaramos un entero que almacenará el resultado, y lo inicializamos a INIT_VALUE_DJB2. */
    unsigned int result = INIT_VALUE_DJB2;
    /* Recorremos todos los caracteres de la cadena dada para calcular el hash. */
    for (int i = 0; i < palabra.length(); i++)
    {
        /* Aplicamos una multiplicación por la BASE_DJB2. */
        result = result * BASE_DJB2;
        /* Usamos el caracter actual para combinarlo con nuestro resultado. (XOR) */
        result = result ^ palabra[i];
    }
    /* Devolvemos el valor resultante. */
    return result;
}
unsigned int TablaHash::hashDJB2Mod (std::string palabra)
{
    /* Declaramos un entero que almacenará el resultado, y lo inicializamos a INIT_VALUE_DJB2. */
    unsigned int result = INIT_VALUE_DJB2;
    /* Recorremos todos los caracteres de la cadena dada para calcular el hash. */
    for (int i = 0; i < palabra.length(); i++)
    {
        /* Aplicamos una multiplicación por la BASE_DJB2. */
        result = result * BASE_DJB2;
        /* Usamos el caracter actual para combinarlo con nuestro resultado. Tratamos el caracter como un entero sin signo. */
        result = result + (unsigned) palabra[i];
    }
    /* Aseguramos que nuestro hash sea coprimo con el tamaño actual de la tabla, así sabremos que recorremos la tabla entera.. */
    result = result + sizeTablaHash + 1; 
    result == 0 ? result = 1 : result;
    /* Devolvemos el valor resultante. */
    return result;
}
unsigned int TablaHash::hash (unsigned int iteration, std::string palabra)
{
    /*Declaramos un entero sin signo resultado. */
    unsigned int result;
    /* Si la iteración dada es la 0 asignamos el valor devuelto por hashDJB2A si no aplicamos la formula hashDJB2A + iteration * hashDJB2Mod. */
    result = iteration == 0 ? hashDJB2A(palabra) : (hashDJB2A(palabra) + hashDJB2Mod(palabra)*iteration);
    /* Aplicamos la operación módulo para obtener el índice correspondiente según el tamaño de la tabla hash. */
    result = result % sizeTablaHash;
    /* Devolvemos el resultado. */
    return result;
}
void TablaHash::reestructurar (void)
{
    /* Declaro un nuevo array para almacenar la tabla actual y guardo el tamaño anterior. */
    std::string * vT = T;
    int sizeViejo = sizeTablaHash;
    /* A T le asigno un nuevo array con memoria para almacenar el doble de elementos del anterior. */
    sizeTablaHash *= 2;
    T = new std::string[sizeTablaHash];
    /* Inicializo el nuevo array. */
    for (unsigned int i = 0; i < sizeTablaHash; i++) T[i] = MARCA_POS_LIBRE;
    /* Reestablezco el contador de palabras para que al insertar en el nuevo array no me reestructure todo el rato. */
    nPalabras = 0;
    /* Recorro el array viejo para reasignar los elementos no libres y no eliminados. */
    for (unsigned int j = 0; j < sizeViejo; j++)
    {
        if (vT[j] != MARCA_POS_LIBRE && vT[j] != MARCA_POS_ELIMINADA) inserta(vT[j]);
    }
    /* Libero la memoria del array viejo. */
    delete [] vT;
}
TablaHash::TablaHash (void)
{
    /* Inicializamos el contador a 0. */
    nPalabras = 0;
    /* Inicializamos el tamaño de la tabla al tamño inicial y guardamos el valor del tamaño inicial. */
    sizeTablaHash = INIT_SIZE;
    sizeInicial = INIT_SIZE;
    /* Reservamos memoria para una tabla del tamaño sizeTablaHash. */
    T = new std::string[sizeTablaHash];
    /* Inicializamos todos los valores de la tabla a MARCA_POS_LIBRE. */
    for (unsigned int i = 0; i < sizeTablaHash; i++)
    {
        T[i] = MARCA_POS_LIBRE;
    }
}
TablaHash::TablaHash (unsigned int size)
{
    /* Inicializamos el contador a 0. */
    nPalabras = 0;
    /* Inicializamos el tamaño de la tabla al tamño inicial dado. */
    sizeTablaHash = size;
    sizeInicial = size;
    /* Reservamos memoria para una tabla del tamaño sizeTablaHash. */
    T = new std::string[sizeTablaHash];
    /* Inicializamos todos los valores de la tabla a MARCA_POS_LIBRE. */
    for (unsigned int i = 0; i < sizeTablaHash; i++)
    {
        T[i] = MARCA_POS_LIBRE;
    }
}
void TablaHash::inserta (std::string palabra)
{
    /* Si encontramos la palabra no haceos nada. */
    if (consulta(palabra) == true) return;
    /* Si no la encontramos buscamos la posición donde insertarla, */
    /* Declaro un entero sin signo para las iteraciones y otro para almacenar el índice de la iteración actual. */
    unsigned int iteration = 0;
    unsigned int index = hash(iteration, palabra);
    /* Calcularemos índices hasta encontrar una posición libre, o eliminada. */
    while (T[index] != MARCA_POS_LIBRE && T[index] != MARCA_POS_ELIMINADA)
    {        
        iteration += 1;
        index = hash(iteration, palabra);
    }
    /* Insertamos la palabra en la posición encontrada. */
    T[index] = palabra;
    nPalabras += 1;
    /* Si superamos cierta ocupación reestructuramos la tabla. */
    double ocupacionActual = (double) nPalabras / sizeTablaHash;
    if (ocupacionActual > MAX_OCUPACION) reestructurar();
}
void TablaHash::elimina (std::string palabra)
{
    /* Declaro un entero sin signo para las iteraciones y otro para almacenar el índice de la iteración actual. */
    unsigned int iteration = 0;
    unsigned int index = hash(iteration, palabra);
    /* Calcularemos índices hasta encontrar una posición libre o nuestra palabra, ignorando posibles posiciones eliminadas. */
    while (T[index] != MARCA_POS_LIBRE && T[index] != palabra)
    {        
        iteration += 1;
        index = hash(iteration, palabra);
    }
    /* Si la posición estaba libre es porque no estaba la palabra y por tanto no hacemos nada. */
    if (T[index] == MARCA_POS_LIBRE) return;
    /* Si la posición estaba ocupada, es porque encontramos nuestra palabra y la queremos eliminar. Sustituimos su entrada por la marca de eliminación y decrementamos el contador de palabras.*/
    T[index] = MARCA_POS_ELIMINADA;
    nPalabras -= 1;
}
bool TablaHash::consulta (std::string palabra)
{
   /* Declaro un entero sin signo para las iteraciones y otro para almacenar el índice de la iteración actual. */
    unsigned int iteration = 0;
    unsigned int index = hash(iteration, palabra);
    /* Calcularemos índices hasta encontrar una posición libre o nuestra palabra, ignorando posibles posiciones eliminadas. */
    while (T[index] != MARCA_POS_LIBRE && T[index] != palabra)
    {        
        iteration += 1;
        index = hash(iteration, palabra);
    }
    /* Si estamos ante una posición libre es porque no estaba nuestra palabra. */
    if (T[index] == MARCA_POS_LIBRE) return false;
    /* Devolvemos verdadero por defecto. */
    return true;
}
void TablaHash::vacia (void)
{
    /* Reiniciamos el contador a 0. */
    nPalabras = 0;
    /* Reiniciamos el tamaño de la tabla al inicial. */
    sizeTablaHash = sizeInicial;
    /* Liberamos la memoria de la tabla para deshacernos de todos los datos.*/
    delete [] T;
    /* Volvemos a reservar memoria para una tabla del tamaño inicial. */
    T = new std::string[sizeTablaHash];
    /* Inicializamos todos los valores de la tabla a MARCA_POS_LIBRE. */
    for (unsigned int i = 0; i < sizeTablaHash; i++)
    {
        T[i] = MARCA_POS_LIBRE;
    }
}
int TablaHash::numeroPalabras (void)
{
    /* Devolvemos la cantidad de palabras. */
    return nPalabras;
}
std::vector<std::string> TablaHash::comandoAdicionalProcesarComodines (std::string patron)
{
    std::vector<std::string> lista;
    /* Recorremos todo el diccionario en busca de coincidencias con nuestro patron dado como argumento. */
    for (std::string * i = T; i < T + sizeTablaHash ; i++)
    {
        /* Si la palabra actual es expansión del patrón dado la insertamos en la lista de palabras. */
        if (str.esExpansionPatron(patron, *i)) lista.push_back(*i);
    }
    /* Ordenamos la lista de coincidentes para poder imprimir. */
    std::sort(lista.begin(), lista.end());
    return lista;
}
TablaHash::~TablaHash (void)
{
    /* Liberamos la memoria de la tabla. */
    delete [] T;
}