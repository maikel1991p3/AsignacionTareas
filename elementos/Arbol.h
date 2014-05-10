/*
 * Arbol.h
 *
 *  Created on: 06/05/2014
 *      Author: maikel
 */

#ifndef ARBOL_H_
#define ARBOL_H_

#include "Nodo.h"

class Arbol {
public:
	Arbol () : _raiz(NULL) {}
	Arbol(int* solInicial, unsigned int tam); // Raíz se crea con una solución inicial
	virtual ~Arbol();

	void mostrar ();
	void insertarNodo (int id, Nodo* nodo);
	Nodo* buscarNodo (int id);

	// Manejadores de atributos
	Nodo* getRaiz();
	void setRaiz(Nodo* raiz);
	const vector<Nodo*>& getRefNodos();

private:
	Nodo* _raiz;
	vector<Nodo*> _refNodos;	// Para visualizar el árbol (recorrido preorden)
};

#endif /* ARBOL_H_ */
