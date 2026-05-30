/* @file main.cpp
 * @brief Sistema Publicador-Suscriptor.
 *  * * Este archivo inicializa el monitor, crea y ejecuta los hilos del editor 
 *   * y los lectores, y gestiona la captura de señales del sistema operativo.
 *    */

#include <iostream>
#include <vector>
#include <csignal>
#include <atomic>
#include <mutex>
#include "SistemaNoticias.h"
#include "Editor.h"
#include "Lector.h"

 using namespace std;

atomic<bool> sistema_activo{true};     ///< Bandera atómica para el control de bucles en hilos.
SistemaNoticias* ptr_sistema = nullptr; ///< Puntero global utilizado por el manejador de señales.
mutex mtx_consola;                      ///< Mutex global para evitar condiciones de carrera en la salida estándar.
///
////**
/// * @brief Manejador de interrupciones del sistema.
///  * * Función que se ejecuta de manera asíncrona cuando el sistema operativo
///   * envía la señal SIGINT (presionar Ctrl+C). Cambia la bandera atómica para
///    * iniciar un apagado ordenado.
///     * * @param signum Número de la señal capturada.
///      */

void manejador_senial(int signum) {
	cout << "\n[Sistema] Señal " << signum << " recibida (Ctrl+C). Apagando de forma segura...\n";
	sistema_activo = false;
	if (ptr_sistema) {
		ptr_sistema->despertar_hilos(); 
	}
}
/**
* @brief Punto de entrada del programa.
* @return int Código de salida del programa (0 para éxito).
*/

int main() {
	signal(SIGINT, manejador_senial);
	cout << "[Sistema] Iniciando. Presiona Ctrl+C para interrumpir.\n\n";
	SistemaNoticias sistema{5}; 
	ptr_sistema = &sistema; 
	Editor editor{sistema, 15}; 
	vector<Lector*> lectores;
	for (int i = 1; i <= 3; ++i) {
		lectores.push_back(new Lector(sistema, i, 5)); 
	}
	editor.ejecutar();
	for (auto l : lectores) l->ejecutar();
	editor.unir();
	for (auto l : lectores) {
		l->unir();
		delete l; 
	}
	cout << "\n[Sistema] Ejecución finalizada correctamente.\n";
	return 0;
}
