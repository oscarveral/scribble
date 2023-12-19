/**
 * Fichero de implementación de la clase Árbol.
 */
#include "Arbol.hpp"
Arbol::Arbol (void)
{
    /* Reservamos memoria para un nuevo nodo que comenzará un árbol vacío. */
    raiz = new NodoTrie;   
    /* Establecemos el número de palabras a 0. */
    nPalabras = 0;
}
Arbol::~Arbol (void)
{
    /* Liberamos toda la memoria del árbol al liberar la memoria del nodo raiz. */
    delete raiz;
}
void Arbol::inserta (std::string palabra)
{
    /* Nodo auxiliar para recorrer el árbol. */
    NodoTrie * pos = raiz;
    /* Recorremos toda la palabra caracter a caracter. */
    for (char c : palabra)
    {
        /* Si el nodo actual no tiene un hijo para el caracter actual lo insertamos. */
        if (pos->consulta(c) == nullptr)
        {
            pos->inserta(c);
        }
        /* Avanzamos al nodo del caracter actual. */
        pos = pos->consulta(c);
    }
    /* Vemos si hay marca de fin de palabra, si la hay no hacemos nada. */
    if (pos->hayMarca())
    {
        return;
    }
    /* Marcamos y sumamos 1 al contador de palabras. */
    pos->ponMarca();
    nPalabras += 1;   
}
bool Arbol::consulta (std::string palabra)
{
    /* Nodo auxiliar que usaremos para recorrer el árbol. */
    NodoTrie * pos = raiz;
    /* Recorremos toda la palabra caracter a caracter. */
    for (char c : palabra)
    {
        /* Si consultar un caracter devuelve un puntero nulo (no existe) se devuelve false. */
        if (pos->consulta(c) == nullptr) return false;
        /* Avanzamos al siguiente nodo. */
        pos = pos->consulta(c);
    }
    /* Llegamos al nodo de la última letra y devolvemos el valor de su marca. */
    return pos->hayMarca();
}
void Arbol::elimina (std::string palabra)
{
    /* Nodo auxiliar que usaremos para recorrer el arbol. */
    NodoTrie * pos = raiz;
    /* Nodo auxiliar que usaremos para posicionarnos en el nodo padre a partir del cual eliminaremos la palabra (o lo que quede de ella). 
       Inicializado al nodo raiz por defecto, ya que toda palabra surge a partir del nodo raiz. Todas las primera letras son hijas del nodo raiz.
       Este nodo nunca podrá ser el nodo de la última letra, como máximo será el de la antepenúltima. */
    NodoTrie * nodoPadreBorrar = raiz;
    /* Caracter que usaremos para identificar la entrada de nodoPadreBorrar a partir de la que eliminar. Inicializado al primer caracter de la palabra. */
    char caracter = palabra[0];
    /* Recorremos toda la palabra para identificár a partir de donde podemos eliminar. */
    for (unsigned int i = 0; i < palabra.length(); i++)
    {
        /* Recuperamos el nodo correspondiente al caracter actual sobre el nodo de posición. */
        NodoTrie * nodoCaracterHijo = pos->consulta(palabra[i]);
        /* Si para el caracter actual no existe entrada en el nodo de posición volvemos ya que no está la palabra. */
        if (nodoCaracterHijo == nullptr) return;
        /* Hay que diferenciar si nos encontramos ante el último caracter o no. Caso de no último caracter de la palabra. */
        if (i < (palabra.length() - 1))
        {
            /* Si nos encontramos en el nodo del caracter que es fin de palabra no podemos eliminarlo, por tanto hay que actualizar el nodoPadreBorrar a este nodo.
               Si no hay marca de eliminación comprobamos el número de hijos. Si el número de hijos es mayor de 1 no podemos eliminar el nodo. Actualizamos. 
               Si solo tiene 1 hijo puede ser o no caracter de la palabra, da igual ya que si lo es en la siguiente iteración lo analizará y si no la palabra no estará y no haremos nada. */
            if (nodoCaracterHijo->hayMarca() || nodoCaracterHijo->numeroHijos() > 1)
            {
                /* Establecemos que el nodo a partir del cual borrar es el del caracter actual. */
                nodoPadreBorrar = nodoCaracterHijo;
                /* Establecemos que el caracter a partir del cual borrar es el siguiente al actual. */
                caracter = palabra[i+1];
            }
            /* Establecemos que la nueva posición será el nodo hijo. */
            pos = nodoCaracterHijo;
        }
        /* Caso de que nos encontremos en el último caracter de la palabra. */
        else
        {
            /* Si el nodo del último carcater tiene hijos no podemos eliminarlo, en ese caso marcamos nodoPadreBorrar como nulo */
            if(nodoCaracterHijo->numeroHijos() > 0) 
            {
                /* Como no podemos liberar nodos establecemos el nodo a partir del cual liberaremos a puntero nulo. */
                nodoPadreBorrar = nullptr;
            }
            /* Si encontramos marca de fin de palabra la quitamos y restamos 1 al contador de palabras. */
            if (nodoCaracterHijo->hayMarca())
            {
                nodoCaracterHijo->quitarMarca();
                nPalabras -= 1;
            }
        }   
    }
    /* Eliminamos todo el subarbol correspondiente al hijo identificado con caracter en el nodoPadreBorrar. Si nodoPadreBorar es nulo no se hace nada.*/
    if (nodoPadreBorrar != nullptr)
    {
        nodoPadreBorrar->elimina(caracter);
    }
}
void Arbol::vacia (void)
{
    /* Para vaciar el arbol liberamos toda la memoria al liberar de memoria la raíz. */
    delete raiz;
    /* Reservamos memoria para un nuevo árbol reservando memoria para un nuevo nodo que será la nueva raiz. */
    raiz = new NodoTrie;
    /* Establecemos el contador de palabras a 0. */
    nPalabras = 0;
}
int Arbol::numeroPalabras (void)
{
    /* Devolvemos la cantidad actual de palabras. */
    return nPalabras;
}
std::string Arbol::comandoAdicionalCompletarPalabras (std::string palabra)
{
    /* Declaramos un nodo trie que usaremos para recorrer el árbol. */
    NodoTrie * pos = raiz;
    /* Recorremos toda la palabra hasta llegar al final de esta si es posible. */
    for (char c : palabra)
    {
        /* Recuperamos el nodo del siguiente caracter, avanzando en el árbol. */
        pos = pos->consulta(c);
        /* Si pos es puntero nulo no existe nodo de dicho caracter y por tanto devolvemos una cadena vacía. */
        if (pos == nullptr) return CADENA_VACIA;
    }
    /* Al final pos tiene el puntero al nodo del último caracter. */
    /* Si el nodo del último caracter está marcado como fin de palabra no hay que completar nada y devolvemos una cadena vacía. */
    if (pos->hayMarca()) return CADENA_VACIA;
    /* Cadena que almacena los caracteres con los que se completará la palabra. */
    std::string letrasCompletado = "";
    /* Mientras no lleguemos a un nodo con una marca de fin de palabra y el número de hijos sea 1, iteramos sobre los hijos. */
    while (pos->numeroHijos() == 1 && !pos->hayMarca())
    {
        /* Recupero el único par caracter - NodoTrie de la lista de hijos. */
        std::pair<char, NodoTrie *> tuplaUnicoHijo = pos->listaHijos().back();
        /* Añado el caracter a la lista de letras de completado y avanzo al siguiente nodo. */
        letrasCompletado += tuplaUnicoHijo.first;
        pos = tuplaUnicoHijo.second;
    }
    /* Devolvemos la cadena de letras con las que completamos la palabra. */
    return letrasCompletado;
}