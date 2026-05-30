/*
 * @file Lector.h
 * @brief Definición de la clase Lector que actúa como el hilo Consumidor.
 */

#ifndef LECTOR_H
#define LECTOR_H

#include <thread>
#include "SistemaNoticias.h"

/**
 * @class Lector
 * @brief Representa a un consumidor que extrae y lee noticias del sistema.
 */
class Lector {
	private:
		SistemaNoticias& sistema;  ///< Referencia al sistema de noticias compartido.
		int id;                    ///< Identificador único del lector.
		int noticias_a_leer;       ///< Cantidad de noticias que este lector intentará consumir.
		std::thread hilo;          ///< Hilo de ejecución subyacente.

		/**
		 * @brief Función principal del hilo. 
		 * Extrae noticias de la cola compartida de forma segura.
		 */
		void consumir();
	public:

		/**
		 * 
		 * @brief Constructor del Lector.
		 * @param sistema Referencia al monitor del sistema de noticias.
		 * @param id Número identificador del hilo lector para la salida en consola.
	         * @param noticias_a_leer Número de noticias que desea extraer.
		 */
		Lector(SistemaNoticias& sistema, int id, int noticias_a_leer);
		
		/**
		 * @brief Inicia la ejecución del hilo interno llamando a consumir().
		 */
		void ejecutar();
		/*
		 * @brief Espera a que el hilo del lector termine su ejecución.
		 */
		void unir();
};
#endif
