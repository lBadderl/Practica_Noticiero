/* @file SistemaNoticias.h
 * @brief Definición de la clase SistemaNoticias para la gestión concurrente de mensajes.
 * Implementa una cola segura para hilos (Thread-Safe Queue) utilizando 
 * mutex y variables de condición para sincronizar la producción y el consumo.
 */

#ifndef SISTEMANOTICIAS_H
#define SISTEMANOTICIAS_H

#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>

 /** @brief Variable global atómica para el control seguro del ciclo de vida del programa.
  */
extern std::atomic<bool> sistema_activo;

/**
* @class SistemaNoticias
* @brief Monitor que encapsula una cola de noticias y asegura el acceso concurrente.
*/

class SistemaNoticias {
	private:
		size_t capacidad;                         ///< Capacidad máxima de la cola.
		std::queue<std::string> cola;             ///< Estructura de datos FIFO para almacenar las noticias.
		std::mutex mtx;                           ///< Mutex para proteger la sección crítica.
		std::condition_variable no_lleno;         ///< Variable de condición para bloquear al productor si la cola está llena.
		std::condition_variable no_vacio;         ///< Variable de condición para bloquear a los consumidores si la cola está vacía.
	public:
		/**
		 * @brief Constructor del Sistema de Noticias.
		 * @param capacidad Tamaño máximo de noticias que la cola puede almacenar simultáneamente.
		 */
		 explicit SistemaNoticias(size_t capacidad);
		/**
		 * @brief Inserta una nueva noticia en la cola.
		 * Bloquea el hilo llamador si la cola ha alcanzado su capacidad máxima, 
		 * hasta que un lector consuma una noticia o el sistema se desactive.
		 * @param noticia Cadena de texto con el contenido a publicar.
		 */
		 void publicar(const std::string& noticia);
		 /**
		 * @brief Extrae y lee la noticia más antigua de la cola.
		 * Bloquea el hilo llamador si la cola está vacía, hasta que un editor
		 * publique una nueva noticia o el sistema se desactive.
		 * @return std::string Contenido de la noticia leída. Retorna una cadena vacía si el sistema se apaga.
		 */
		 std::string leer();
		 /**
		 * @brief Despierta a todos los hilos bloqueados.
		 * Se utiliza principalmente durante el apagado del sistema.
		 * para evitar interbloqueos (deadlocks).
		 */
		 void despertar_hilos(); 
};
#endif
