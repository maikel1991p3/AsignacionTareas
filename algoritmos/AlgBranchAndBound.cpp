/*
 * AlgBranchAndBound.cpp
 *
 *  Created on: 08/05/2014
 *      Author: maikel
 */

#include "AlgBranchAndBound.h"

AlgBranchAndBound::AlgBranchAndBound() {
	_cota = -1;
	// Cargamos la instancia a ejecutar desde fichero.
	leerInstancias();

	// Creamos el árbol de soluciones (Con la solución inicial).
	int* _solIni = new int[_dim];
	_solucionIni = new int [_dim];
	for (int i = 0; i < _dim; ++i) {
		_solIni[i] = -1;
		_solucionIni[i] = -1;
	}

	// Inicializamos el árbol con su solución inicial (vacía)
	_arbolSolucion = new Arbol(_solIni, _dim);
	delete[] _solIni;

	crearSolucionInicialGRASP();

	_arbolSolucion->mostrar();

	ejecutarAlgoritmo();
}

AlgBranchAndBound::~AlgBranchAndBound() {
	if (_tablaAsignaciones != NULL)
		for (int i = 0; i < _dim; ++i)
			delete[] _tablaAsignaciones[i];
	_cota = -1;
	_dim = -1;
	if (_arbolSolucion != NULL)
		delete _arbolSolucion;

	if (_solucionIni != NULL)
		delete [] _solucionIni;
}

void AlgBranchAndBound::leerInstancias() {
	char* nombreFich = new char[50];
	cout << " Introduzca nombre de fichero a cargar: ";
	cin >> nombreFich;

	fstream fich_in;

	fich_in.open(nombreFich, fstream::in);
	if (fich_in.is_open()) {

		fich_in >> _dim; // Leemos el número de máquinas / tareas (coinciden en número)

		// Reservamos memoria para las instancias de entrada (costes máquinas/tareas)
		_tablaAsignaciones = new int*[_dim];
		for (int i = 0; i < _dim; ++i)
			_tablaAsignaciones[i] = new int[_dim];

		// Leemos los costes máquinas / tareas desde el fichero de entrada
		int fila = 0, columna = 0;
		while (!fich_in.eof()) {
			fich_in >> _tablaAsignaciones[fila][columna];
			++columna;
			if (columna == _dim) {
				columna = 0;
				++fila;
			}
		}

		// Mostramos la tabla de asignaciones almacenada.
		cout << endl << " + Tabla de costes Máquinas / Tareas " << endl;
		for (int i = 0; i < _dim; ++i) {
			for (int j = 0; j < _dim; ++j)
				cout << "\t" << _tablaAsignaciones[i][j];
			cout << endl;
		}

	} else {
		cerr << " ERROR: hubo un error al intentar leer el fichero de entrada! " << endl;
	}
}

void AlgBranchAndBound::crearSolucionInicialGRASP() {
	const int TAMLRC = 2;
	int* maquinasLibres = new int [_dim];
	int** listaRestCandidatos = new int*[_dim];

	for (int i = 0; i < _dim; ++i)
		listaRestCandidatos[i] = new int [TAMLRC];

	for (int i = 0; i < _dim; ++i)
		maquinasLibres[i] = i;

	srand(time (NULL));
	int min = 9999, k = 0, aleatorio = 0;
	for (int i = 0; i < _dim; ++i) { // Para toda tarea ...
		min = 9999;
		k = 0;
		for (int j = 0; j < _dim; ++j) { // Para toda máquina ...

			if (maquinasLibres[j] != -1 && _tablaAsignaciones[j][i] < min) {
				min = _tablaAsignaciones[j][i];
				listaRestCandidatos[i][k] = j; // Almacenamos las n mejores máquinas para la tarea 'i'

				k++;
				if (k > TAMLRC)
					k = 0;
			}
		}

		aleatorio = rand () % TAMLRC; // elegimos un candidato de la LRC al azar
		if (listaRestCandidatos[i][aleatorio] < _dim) // Comprobamos que entró el candidato en la lista GRASP
			_solucionIni[i] = listaRestCandidatos[i][aleatorio];
		else
			_solucionIni[i] = listaRestCandidatos[i][0];
		maquinasLibres[_solucionIni[i]] = -1;
	}

	cout << endl << " Solución inicial GRASP: " << endl;
	for (int i = 0; i < _dim; ++i) {
		cout << "\t" << _solucionIni[i];
	}
	_cota = calcularCota(_solucionIni);
	_arbolSolucion->getRaiz()->setValorObjetivo(_cota);
	cout << endl << " Cota = " <<  _cota << endl;
}

int AlgBranchAndBound::calcularCota (int* sol) {
	int cota = 0;
	for (int i = 0; i < _dim; ++i) {
		cota += _tablaAsignaciones[sol[i]][i];
	}
	return cota;
}

void AlgBranchAndBound::ejecutarAlgoritmo() {
	Nodo* actual = _arbolSolucion -> getRaiz ();
	/*
	cout << actual;

	do {
		expandir (actual);
		seleccionar (actual);



	} while (true);
*/
	expandir(actual);
}

void AlgBranchAndBound::expandir (Nodo* nodo) {

}

void AlgBranchAndBound::seleccionar (Nodo* nodo) {

}
