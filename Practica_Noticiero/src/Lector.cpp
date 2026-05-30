#include "Lector.h"
#include <iostream>
#include <mutex>

using namespace std;
extern mutex mtx_consola;

Lector::Lector(SistemaNoticias& sistema, int id, int noticias_a_leer) : sistema{sistema}, id{id}, noticias_a_leer{noticias_a_leer} {}

void Lector::consumir() {
	for (int i = 0; i < noticias_a_leer && sistema_activo; ++i) {
		string noticia = sistema.leer();
		if (!noticia.empty()) {
			lock_guard<mutex> lock(mtx_consola);
			cout << "[Lector " << id << "] Leyendo: " << noticia << endl;
									}
	}
}

void Lector::ejecutar() {
	hilo = thread([this]() { this->consumir(); });
}

void Lector::unir() {
	if (hilo.joinable()) {
		hilo.join();
	}
}

