/**
 * Fichero de implementación del NodoTrie.
 */
#include "NodoTrie.hpp"
NodoTrie::NodoTrie (void)
{
    /* Por defecto un nodo no es fin de palabra. */
    esFinPalabra = false;
    /* Por defecto el mapa está vacío y por tanto no hay que inicializar sus elementos. */
}
NodoTrie::~NodoTrie (void)
{
    /* Cuando liberamos la memoria de un NodoTrie hay que liberar tambien la de todos los hijos, de forma recursiva. */
    for (auto it = mapaHijos.begin(); it != mapaHijos.end(); it++)
    {
        /* Eliminamos el nodo, que es la segunda componente del mapa. */
        delete it->second;
    }
    /* El resto de cosas como el booleano y el mapa con sus entradas se eliminan solas al declararse de forma estática. */
}
NodoTrie * NodoTrie::consulta (char caracter)
{
    /* Obtenemos la entrada del mapa que codifica caracter. */ 
    auto tupla = mapaHijos.find(caracter);
    /* Si dicha entrada equivale al fin del mapa no existe (véase std::unordered_map::find los valores que devuelve) y por tanto devolvemos un puntero nulo. */
    if (tupla == mapaHijos.end()) return nullptr;
    /* En otro caso devolvemos el puntero a NodoTrie almacenado en dicha tupla. */
    return tupla -> second;
}
void NodoTrie::inserta (char caracter)
{
    /* En otro caso creamos un nuevo nodo y lo insertaremos con clave caracter. */
    NodoTrie * nuevoNodo = new NodoTrie;
    /* Véase std::unordered_map::insert. Si se intenta insertar un elemento cuya clave ya está presente no se insertará ya que las claves deben ser únicas. */
    mapaHijos.insert({caracter,nuevoNodo});
}
void NodoTrie::elimina (char caracter)
{
    /* Obtenemos la tupla que corresponde al caracter. */
    auto tupla = mapaHijos.find(caracter);
    /* Si no existe dicha tupla en el mapa no hacemos nada. */
    if (tupla == mapaHijos.end()) return;
    /* En otro caso llamamos al destructor para destruir el nodo hijo en dicha tupla (destrucción recursiva). */
    delete tupla->second;
    /* Eliminamos la entrada correspondiente al caracter dado del mapa del nodo. */
    mapaHijos.erase(tupla);
}
void NodoTrie::ponMarca (void)
{
    esFinPalabra = true;
}
void NodoTrie::quitarMarca (void)
{
    esFinPalabra = false;
}
bool NodoTrie::hayMarca (void)
{
    return esFinPalabra;
}
int NodoTrie::numeroHijos (void)
{
    return mapaHijos.size();
}
std::vector<std::pair<char, NodoTrie*>> NodoTrie::listaHijos (void)
{
    /* Vector que vamos a devolver. */
    std::vector<std::pair<char, NodoTrie*>> lista;
    for (auto hijo : mapaHijos)
    {
        lista.push_back(hijo);
    }
    /* Devolvemos la lista de hijos. */
    return lista;
}