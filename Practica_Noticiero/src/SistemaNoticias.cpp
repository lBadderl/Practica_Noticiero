#include "SistemaNoticias.h"

using namespace std;

SistemaNoticias::SistemaNoticias(size_t capacidad) : capacidad{capacidad} {}

void SistemaNoticias::publicar(const string& noticia) {
	unique_lock<mutex> lock(mtx);
	no_lleno.wait(lock, [this] { return cola.size() < capacidad || !sistema_activo; });
		    
	if (!sistema_activo) return; 
		        
	cola.push(noticia);
	no_vacio.notify_one(); 
}

string SistemaNoticias::leer() {
	unique_lock<mutex> lock(mtx);
	no_vacio.wait(lock, [this] { return !cola.empty() || !sistema_activo; });
		    
	if (!sistema_activo && cola.empty()) return ""; 
		        
	string noticia = cola.front();
	cola.pop();
	no_lleno.notify_one(); 
	return noticia;
}

void SistemaNoticias::despertar_hilos() {
	no_vacio.notify_all();
	no_lleno.notify_all();
}

