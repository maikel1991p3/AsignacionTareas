/*
 * Nodo.cpp
 *
 *  Created on: 06/05/2014
 *      Author: maikel
 */

#include "Nodo.h"

Nodo::Nodo(int id, int* sol, unsigned int tam) {
	setId(id);
	setTamSol(tam);
	_solucion = new int[tam];
	for (unsigned int i = 0; i < tam; ++i) {
		_solucion[i] = sol[i];
	}
	setRefPadre(NULL);
	setValorObjetivo(-1);
}

Nodo::~Nodo() {
	if (getSolucion() != NULL)
		delete[] getSolucion();
	if (getRefPadre() != NULL)
		delete getRefPadre();
	if (!getHijos().empty()) {
		for (unsigned int i = 0; i < getHijos().size(); ++i) {
			delete getHijos()[i];
		}
	}
	setId(-1);
	setValorObjetivo(-1);
}

ostream& operator<< (ostream& os, Nodo* nodo) {
	os << "Nodo: " << nodo->getId() << endl;
	if (nodo ->getRefPadre() != NULL)
		os << " - Padre: id = " << nodo ->getRefPadre()->getId() << endl;
	else
		os << " - Padre: No tiene -> es Raíz! " << endl;
	os << " - N. hijos: " << nodo ->getHijos().size() << endl;
	os << " + Solución:  [";
	for (int j = 0; j < nodo ->getTamSol(); ++j) {
		os << " " << nodo ->getSolucion()[j];
	}
	os << " ] valor = " << nodo ->getValorObjetivo();

	cout << endl << " Máquinas libres: " << endl;
	for (int i = 0; i < nodo->getTamSol(); ++i)
		cout << " " << nodo->getMaquinasLibres()[i];

	return os;
}

void Nodo::calcularValor(int** tablaCostes) {


}

int Nodo::contarOcupadas () {
	int ocupadas = 0;
	for (int i = 0; i < getTamSol(); ++i){
		if (getSolucion()[i] != -1)
			++ocupadas;
	}
	return ocupadas;
}

// Manejadores de atributos
int Nodo::getId() {
	return _id;
}

void Nodo::setId(int id) {
	_id = id;
}

Nodo* Nodo::getRefPadre() {
	return _refPadre;
}

void Nodo::setRefPadre(Nodo* refPadre) {
	_refPadre = refPadre;
}

int* Nodo::getSolucion() {
	return _solucion;
}

void Nodo::setSolucion(int* solucion) {
	_solucion = solucion;
}

int Nodo::getTamSol() {
	return _tamSol;
}

void Nodo::setTamSol(int tamSol) {
	_tamSol = tamSol;
}

int Nodo::getValorObjetivo() {
	return _valorObjetivo;
}

void Nodo::setValorObjetivo(int valorObjetivo) {
	_valorObjetivo = valorObjetivo;
}

vector<Nodo*>& Nodo::getHijos() {
	return _hijos;
}

void Nodo::setHijos(vector<Nodo*>& hijos) {
	_hijos = hijos;
}

bool* Nodo::getMaquinasLibres() {
	return _maquinasLibres;
}

void Nodo::setMaquinasLibres(bool* maquinasLibres) {
	_maquinasLibres = maquinasLibres;
}
