/**
 * Código fuente del TDA ConjuntoPalabras.
 */ 
#include "ConjuntoPalabras.hpp"
ConjuntoPalabras::ConjuntoPalabras (void) {}
void ConjuntoPalabras::vacia (void)
{
    /* Llamada al vaciado de la tabla hash. */
    th.vacia();
    /* Llamada al vaciado del árbol trie. */
    ab.vacia();
}
void ConjuntoPalabras::inserta (std::string palabra)
{
    /* Llamada a la inserción en la tabla hash. */
    th.inserta(palabra);  
    /* Llamada a la inserción en el árbol trie. */
    ab.inserta(palabra);
}
void ConjuntoPalabras::elimina (std::string palabra)
{
    /* Llamada a la eliminación en la tabla hash. */
    th.elimina(palabra);
    /* Llamada al eliminado en el árbol trie. */
    ab.elimina(palabra);
}
bool ConjuntoPalabras::consulta (std::string palabra)
{
    /* Obtenemos el tipo de la palabra que tenemos. */
    tipoPalabras tipoP = str.tipoCadena(palabra);
    /* Si estabamos ante una palabra MAYUS o FRASE buscamos esa palabra o su versión en minusculas. */
    if (tipoP == MAYUS || tipoP == FRASE)
    {
        /* Obtenemos la versión en minusculas de la palabra. */
        std::string pMinus = str.minuscula(palabra);
        /* Buscamos la palabra y su versión en minusculas. */
        return th.consulta(palabra) || th.consulta(pMinus);
    }
    /* Para el resto buscamos unicamente la palabra. */
    return th.consulta(palabra);
}
bool ConjuntoPalabras::consultaExacta (std::string palabra)
{
    return th.consulta(palabra);
}
int ConjuntoPalabras::numeroPalabras (void)
{
    /* Llamada al recuento del número de palabras de la tabla de hash. */
    return th.numeroPalabras();
}
std::vector<std::string> ConjuntoPalabras::procesarPatron (std::string patron)
{
    /* Llamada al procesado de comodines en la tabla de hash local. */
    return th.comandoAdicionalProcesarComodines(patron);
}
std::string ConjuntoPalabras::procesarCompletado (std::string comienzoPalabra)
{
    /* Llamada el comando adicional de completado en el árbol local. */
    return ab.comandoAdicionalCompletarPalabras(comienzoPalabra);
}