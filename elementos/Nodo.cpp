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
	if (getMaquinasLibres() != NULL) {
		delete [] getMaquinasLibres();
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
	// Calculamos valor de la solución hasta ese momento
	int tareasOcupadas = 0, cota = 0;
	bool* maqLibresTemp = new bool[getTamSol()];
	int* solFutura = new int[getTamSol()];
	for (int i = 0; i < getTamSol(); ++i) {
		if (getSolucion()[i] != -1) {
			cota += tablaCostes[getSolucion()[i]][i];
		}
		solFutura[i] = getSolucion()[i];
		maqLibresTemp[i] = getMaquinasLibres()[i];
	}
	// Miramos cuantas tareas quedan sin máquina por asignar
	tareasOcupadas =  contarOcupadas();

	// Cogemos la mejor máquina para cada tarea en cada caso (aumentando la cota)
	int min = 9999, mejorMaq = 0;
	for (int i = tareasOcupadas; i < getTamSol(); ++i) {
		min = 9999; mejorMaq = 0;
		for (int j = 0; j < getTamSol(); ++j) {
			if (maqLibresTemp[j] == true) {
				if (tablaCostes[j][i] < min) {
					min = tablaCostes[j][i];
					mejorMaq = j;
				}
			}
		}
		solFutura[i] = mejorMaq;
		cota += tablaCostes[solFutura[i]][i];
		maqLibresTemp[mejorMaq] = false;
	}

	cout << endl << endl << " SOL FUT: "<< endl;
	for (int i = 0; i < getTamSol(); ++i)
		cout << "  " << solFutura[i];
	cout << endl;
	setValorObjetivo(cota);
	delete [] solFutura;
	cout << "ID = " << getId() << "     COTA = " << cota << endl;
}

int Nodo::contarOcupadas () {
	int ocupadas = 0;
	for (int i = 0; i < getTamSol(); ++i){
		if (getMaquinasLibres()[i] == false)
			++ocupadas;
	}
	return ocupadas;
}

bool Nodo::esHoja () {
	return (getHijos().size() == 0) ? true : false;
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
	if (_maquinasLibres == NULL)
		_maquinasLibres = new bool [getTamSol()];
	for (int i = 0; i < getTamSol(); ++i)
		_maquinasLibres[i] = maquinasLibres[i];
}

bool Nodo::isPodado() {
	return _podado;
}

void Nodo::setPodado(bool podado) {
	_podado = podado;
}
