/*
 * Arbol.cpp
 *
 *  Created on: 06/05/2014
 *      Author: maikel
 */

#include "Arbol.h"

Arbol::Arbol(int* solIni, unsigned int tam) {
	Nodo* raizTemp = new Nodo (0, solIni, tam);

	bool* maquinasLibres = new bool[tam];
	for (unsigned int i = 0; i < tam; ++i) // Inicialmente: todas las máquinas libres xD
		maquinasLibres[i] = true;
	raizTemp->setMaquinasLibres(maquinasLibres);

	setRaiz(raizTemp);
	_refNodos.push_back(getRaiz());
}

Arbol::~Arbol() {
	if (!_refNodos.empty()) {
		for (unsigned int i = 0; i < _refNodos.size(); ++i)
			delete _refNodos[i];
	}
}

void Arbol::mostrar () {
	cout << endl << " - Árbol de soluciones: " << endl;
	if (!_refNodos.empty()) {
		for (unsigned int i = 0; i < _refNodos.size(); ++i) {
			cout << _refNodos[i] << endl;
		}
	}
}

void Arbol::insertarNodo (int id, Nodo* nodo) {
	Nodo* padre = buscarNodo(id);
	if (padre != NULL) {
		padre->getHijos().push_back(nodo);
		nodo->setRefPadre(padre);
	}
	_refNodos.push_back(nodo);
}

Nodo* Arbol::buscarNodo (int id) {
	for (unsigned int i = 0; i < _refNodos.size(); ++i) {
		if (_refNodos[i]->getId() == id)
			return _refNodos[i];
	}
	return NULL;
}

// Manejadores de atributos
Nodo* Arbol::getRaiz() {
	return _raiz;
}

void Arbol::setRaiz(Nodo* raiz) {
	_raiz = raiz;
}

const vector<Nodo*>& Arbol::getRefNodos() {
	return _refNodos;
}
