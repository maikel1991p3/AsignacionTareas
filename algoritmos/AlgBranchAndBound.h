/*
 * AlgBranchAndBound.h
 *
 *  Created on: 08/05/2014
 *      Author: maikel
 */

#ifndef ALGBRANCHANDBOUND_H_
#define ALGBRANCHANDBOUND_H_

#include "../elementos/Arbol.h"
#include <fstream>
#include <cstdlib>

class AlgBranchAndBound {
public:
	AlgBranchAndBound(); 	// Número de máquinas = nº tareas
	virtual ~AlgBranchAndBound();

	// Inicialización
	void leerInstancias ();
	void crearSolucionInicialGRASP ();
	int buscarPeorLista (int* lista, int tamLista, int tarea);
	int calcularCota (int* sol);

	// Algoritmo Ramificación y Poda
	void ejecutarAlgoritmo ();
	void expandir (Nodo*);
	Nodo* seleccionar (Nodo*);
	int contar (int*);

private:
	int _cota;					// Cota esencial para la poda en el árbol de soluciones
	Arbol* _arbolSolucion;		// Aŕbol para la ejecución del método
	int _dim;					// Número de máquinas = nº tareas
	int** _tablaAsignaciones;	// Corespondencia de costes Máquinas-Tareas (filas, columnas)
	int* _solucionIni;
};

#endif /* ALGBRANCHANDBOUND_H_ */
