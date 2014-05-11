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

	srand(time (NULL));
	crearSolucionInicialGRASP();

	ejecutarAlgoritmo();


	_arbolSolucion->mostrar();
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
	int* listaRestCandidatos = NULL;
	int dentroLista = 0;

	for (int i = 0; i < _dim; ++i)
		maquinasLibres[i] = i;

	int aleatorio = 0, peorMaquina = 0;
	for (int i = 0; i < _dim; ++i) { // Para toda tarea ...
		dentroLista = 0;
		listaRestCandidatos = new int [TAMLRC];
		for (int j = 0; j < _dim; ++j) { // Para toda máquina ...

			if (maquinasLibres[j] != -1) {

				if (dentroLista < TAMLRC) { // Mientras la lista no esté llena ... entran las máquinas
					listaRestCandidatos[dentroLista] = j; // Almacenamos las n mejores máquinas para la tarea 'i'
					++dentroLista;

					if (contar(maquinasLibres) == 1) { // Controlamos la útima iteración (solo queda 1 máquina)
						for (int l = 0; l < TAMLRC; ++l)
							listaRestCandidatos[l] = j;
						++dentroLista;
					}

				} else {
					// Buscar peor máquina j para tarea i
					peorMaquina = buscarPeorLista(listaRestCandidatos, TAMLRC, i);
					if (_tablaAsignaciones[j][i] < _tablaAsignaciones[listaRestCandidatos[peorMaquina]][i]) {
						listaRestCandidatos[peorMaquina] = j;

					}
				}
			}
		}

		aleatorio = rand () % TAMLRC; // elegimos un candidato de la LRC al azar
		_solucionIni[i] = listaRestCandidatos[aleatorio];
		maquinasLibres[_solucionIni[i]] = -1;

		delete [] listaRestCandidatos;
	}

	cout << endl << " Solución inicial GRASP: " << endl;
	for (int i = 0; i < _dim; ++i) {
		cout << "\t" << i << "-> " <<_solucionIni[i];
	}
	_cota = calcularCota(_solucionIni);
	_arbolSolucion->getRaiz()->setValorObjetivo(_cota);
	cout << endl << " Cota = " <<  _cota << endl;

	delete [] maquinasLibres;
}

int AlgBranchAndBound::buscarPeorLista (int* lista, int tamLista, int tarea) {
	int max = -999, pos = -1;
	for (unsigned int i = 0; i < tamLista; ++i) { // FIXME
		if (_tablaAsignaciones[lista[i]][tarea] > max) {
			max = _tablaAsignaciones[lista[i]][tarea];
			pos = i;
		}
	}
	return pos;
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
	actual = seleccionar(actual);
	expandir (actual);
	//actual->calcularValor(_tablaAsignaciones);
}

void AlgBranchAndBound::expandir (Nodo* nodo) {

	int tareasOcupadas = nodo -> contarOcupadas ();
	int maquinasLibres = nodo -> getTamSol() - tareasOcupadas;
	bool* libres = new bool [nodo -> getTamSol()];
	for (int i = 0; i < nodo -> getTamSol(); ++i)
		libres[i] = nodo -> getMaquinasLibres()[i];

	Nodo* temp = NULL;
	while (maquinasLibres > 0) {
		temp = new Nodo (_arbolSolucion->getRefNodos().size(), nodo -> getSolucion(), nodo -> getTamSol());
		temp -> setRefPadre(nodo);
		temp -> setMaquinasLibres(nodo -> getMaquinasLibres());

		int pos = 0;
		for (int i = 0; i < nodo -> getTamSol(); ++i) {
			if (libres[i] == true) {
				pos = i;
				break;
			}
		}
		temp->getSolucion()[tareasOcupadas] = pos;
		temp->getMaquinasLibres()[pos] = false;

		temp -> calcularValor(_tablaAsignaciones);

		nodo -> getHijos().push_back(temp);
		_arbolSolucion->insertarNodo(_arbolSolucion->getRefNodos().size(), temp);

		libres[pos] = false;
		maquinasLibres--;
	}

}

Nodo* AlgBranchAndBound::seleccionar (Nodo* nodo) {
	unsigned int nhijos = nodo -> getHijos().size();
	int min = 9999, pos = 0, valorObjetivo = 0;
	for (unsigned int i = 0; i < nhijos; ++i) {
		valorObjetivo = nodo->getHijos()[i]->getValorObjetivo();
		if (valorObjetivo < min) {
			min = valorObjetivo;
			pos = i;
		}
	}
	return nodo->getHijos()[pos];
}

int AlgBranchAndBound::contar (int* maquinasLibres) {
	int libres = 0;
	for (int i = 0; i < _arbolSolucion->getRaiz()->getTamSol(); ++i){
		if (maquinasLibres[i] != -1)
			++libres;
	}
	return libres;
}
