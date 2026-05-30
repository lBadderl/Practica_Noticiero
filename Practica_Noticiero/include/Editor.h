/*
 * @file Editor.h
 * @brief Definición de la clase Editor que actúa como el hilo Productor.
 *  */

#ifndef EDITOR_H
#define EDITOR_H

#include <thread>
#include "SistemaNoticias.h"

 /**
  * @class Editor
  * @brief Representa a un productor que genera noticias y las inyecta en el sistema.
  */
class Editor {
	 private:
		SistemaNoticias& sistema;  ///< Referencia al sistema de noticias compartido.
		int total_noticias;        ///< Cantidad total de noticias que este editor publicará.
		std::thread hilo;          ///< Hilo de ejecución subyacente.
		
		/** 
		 * @brief Función principal del hilo.
		 * Genera noticias secuenciales y llama al método publicar del sistema.
		 */
		 void producir();
	 public:
		 /**
		  * @brief Constructor del Editor.
		  * @param sistema Referencia al monitor del sistema de noticias.
		  * @param total_noticias Número de noticias a generar.
		  */
		  Editor(SistemaNoticias& sistema, int total_noticias);
		 /** 
		  * @brief Inicia la ejecución del hilo interno llamando a producir().
		  */
	  	  void ejecutar();
		 /**
		  * @brief Espera a que el hilo del editor termine su ejecución.
		  */
		  void unir();
};
#endif
