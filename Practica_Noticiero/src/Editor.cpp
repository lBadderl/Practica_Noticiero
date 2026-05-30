#include "Editor.h"
#include <iostream>
#include <string>
#include <mutex>

using namespace std;
extern mutex mtx_consola;

Editor::Editor(SistemaNoticias& sistema, int total_noticias) 
	    : sistema{sistema}, total_noticias{total_noticias} {}

void Editor::producir() {
	for (int i = 1; i <= total_noticias && sistema_activo; ++i) {
	        string noticia = "Extra! Noticia #" + to_string(i);
		sistema.publicar(noticia);
		{
			lock_guard<mutex> lock(mtx_consola);
			cout << "[Editor] Publicó: " << noticia << endl;
		}
	}
}

void Editor::ejecutar() {
	hilo = thread(&Editor::producir, this);
}

void Editor::unir() {
	if (hilo.joinable()) {
		hilo.join();
	}
}

