a.out: ManipuladorCadenas.o ManipuladorTokens.o TablaHash.o NodoTrie.o Arbol.o ConjuntoPalabras.o Consola.o main.o 
	g++ ManipuladorCadenas.o ManipuladorTokens.o TablaHash.o NodoTrie.o Arbol.o ConjuntoPalabras.o Consola.o main.o
ManipuladorCadenas.o: ManipuladorCadenas.cpp ManipuladorCadenas.hpp
	g++ -c ManipuladorCadenas.cpp
ManipuladorTokens.o: ManipuladorTokens.cpp ManipuladorTokens.hpp ManipuladorCadenas.hpp
	g++ -c ManipuladorTokens.cpp
TablaHash.o: TablaHash.cpp TablaHash.hpp ManipuladorCadenas.hpp
	g++ -c TablaHash.cpp
NodoTrie.o: NodoTrie.cpp NodoTrie.hpp
	g++ -c NodoTrie.cpp
Arbol.o: Arbol.cpp Arbol.hpp NodoTrie.hpp
	g++ -c Arbol.cpp
ConjuntoPalabras.o: ConjuntoPalabras.cpp ConjuntoPalabras.hpp TablaHash.hpp Arbol.hpp ManipuladorCadenas.hpp 
	g++ -c ConjuntoPalabras.cpp
Consola.o: Consola.cpp Consola.hpp ConjuntoPalabras.hpp ManipuladorTokens.hpp
	g++ -c Consola.cpp
main.o: main.cpp Consola.hpp
	g++ -c main.cpp