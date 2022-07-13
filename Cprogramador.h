/* 
* Cprogramador.h
*
* Created: 20/10/2018 11:36:50
* Author: Fran
*/


#ifndef __CPROGRAMADOR_H__
#define __CPROGRAMADOR_H__


#include <stdbool.h>
#include <stdio.h>
#include "Csensorlluvia.h"
#include "CzonaRiego.h"
#include "definiciones.h"


typedef struct  t_Zona
{
	uint8_t activate;
	uint8_t offset_activated;	
	CzonaRiego riego();
	
} Zona;



typedef struct t_lista_zonas
{
	Zona zona[num_zonas]; 	
} lista_zonas;


class Cprogramador {
	//variables
	private:
	
		uint8_t num_zonasRiego;
		uint8_t offset_activated;
		uint8_t sensorLluvia_activated;
		lista_zonas listadoZonas; // listadoZonas.zona[x].riego.
		Csensorlluvia sensorlluvia;
		typedef struct st_Estado_Programador {
			bool ready;
			
			
		} Estado_programador;
		
		
	

	//functions
	public:
		//default constructor & ~
		Cprogramador();
		~Cprogramador();
		Cprogramador (uint8_t _num_zonasRiego, uint8_t _offset_activated, uint8_t _sensorLluvia_activated); 

}; //Cprogramador

#endif //__CPROGRAMADOR_H__
