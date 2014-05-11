/*
 * Nodo.h
 *
 *  Created on: 06/05/2014
 *      Author: maikel
 */

#ifndef NODO_H_
#define NODO_H_

#include <iostream>
using namespace std;

#include <vector>

class Nodo {
public:
	Nodo(int id, int* sol, unsigned int tam); // Necesario: id + solución + tamaño de la solución
	virtual ~Nodo();

	friend ostream& operator<< (ostream& os, Nodo*);

	// Funciones de utilidad
	void calcularValor (int** tablaCostes);
	int contarOcupadas ();
	bool esHoja ();

	// Manejadores de atributos
	int getId();
	void setId(int id);
	Nodo* getRefPadre();
	void setRefPadre(Nodo* refPadre);
	int* getSolucion();
	void setSolucion(int* solucion);
	int getTamSol();
	void setTamSol(int tamSol);
	int getValorObjetivo();
	void setValorObjetivo(int valorObjetivo);
	vector<Nodo*>& getHijos();
	void setHijos(vector<Nodo*>& hijos);
	bool* getMaquinasLibres();
	void setMaquinasLibres(bool* maquinasLibres);
	bool isPodado();
	void setPodado(bool podado);

private:
	int _id;				// Identoficador único para cada nodo.
	int* _solucion;			// Vector que representa una solución codificada.
	bool* _maquinasLibres;	// Lleva la cuenta de las máquinas por asignar a tareas.
	int _tamSol; 			// Tamaño de la solución (nº de máquinas / tareas)
	int _valorObjetivo;		// Valor objetivo de la solución del nodo.1
	Nodo* _refPadre;		// Referencia al nodo padre (para recorrido del árbol).
	vector<Nodo*> _hijos;	// Vector de hijos (soluciones vecinas).
	bool _podado;			// Indica si el nodo en cuestión ha sido podado
};

#endif /* NODO_H_ */
