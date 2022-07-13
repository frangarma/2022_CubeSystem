/*
 * CzonaRiego.h
 *
 * Created: 11/03/2018 17:15:45
 *  Author: Fran
 */ 


#ifndef CPERIODORIEGO_H_
#define CPERIODORIEGO_H_

#include "Cswitchable.h"
#include "Cdadodia.h"
#include "CdadoHora.h"
#include "CdadoDuracion.h"
#include "Cprogram.h"
#include <stdint.h>
#include "Cclock.h"
#include "Ci2c.h"
#include "definiciones.h"
//#include "VariablesGlobales.h"


typedef enum {notDroppingNow, firstStageBeforeEntryJustDroppingJustNow, firstStageBeforeAbortingJustDroppingJustNow, inAbortingJustDroppingJustNow, inProgrammingJustDroppingJustNow, JustDroppingNow } statesJustdroppingNow;
typedef enum {shortcut, inRange, infinite} resistanceZoneCubeCategory;
typedef enum {eventInit, unionConditionDeleting, unionInRange, unionInfinite, unionConditionJustDroppingNow, 
			  unionPreconditionAbort_EntryJustDroppingNow, unionInderteminate, unionPreconditionMenuMode, unionConditionmenuMode,
			  unionConditionPlusmenuMode, unionConditionMinusmenuMode} unionResistanceZoneDices;
//typedef vector <Cfecha> listCfecha;


class Csistema;

class CzonaRiego : public Cswitchable 
{
	public:
		typedef enum {standby, calculateProgram, inProgramming, programmed, inDeleting} statesZonasRiego;
	
	private:
		uint8_t num_zona;
		uint8_t diasRiego[nelementdoWRiego];
		uint8_t horaRiego;		
		uint8_t duracionRiego;
		uint8_t minutoInicioRiego;
		uint8_t offset_minutosRiego;
		uint8_t offset_factor;
		uint8_t riegoProgramado;
		bool is_justDroppingNow;
		uint8_t ajustadoDroppingJustNow;
		uint8_t nowRunning;
		uint8_t horaRiegoDroppingJustNow;
		uint8_t minutoInicioRiegoJustoDroppingNow;
		uint8_t duracionDroppingJustNow;
  		CdadoDia dadoDia;
  		CdadoHora dadoHora;
  		CdadoDuracion dadoDuracion;
		Cprogram programa;
		Cclock clock;
		Cfecha horaActual, programStartDate, programEndDate;
		Ci2c *i2c;
		statesZonasRiego  currentStateZonaRiego;
		statesZonasRiego lastStateZonaRiego;
		bool is_newStateZoneRiego;
		statesJustdroppingNow stateDroppingNow;
		bool newStateDroppingNow;
		unionResistanceZoneDices eventCurrentUnionStateDices, eventLastUnionStateDices;
		Csistema* sistema;
		//Defined in Csistema::typedef enum {standBy, progMode, menuMode} systemStatus;
		uint8_t statusSystem;
		resistanceZoneCubeCategory resistanceZoneCubeDia;
		resistanceZoneCubeCategory resistanceZoneCubeHora;
		resistanceZoneCubeCategory resistanceZoneCubeDuracion;
		unionResistanceZoneDices resultUnionResistanceZoneDices; 

	public:
		//default constructor
		CzonaRiego();
		~CzonaRiego();
		//Constructor
		CzonaRiego(Csistema* _sistema, const Cclock& _clock, const Cfecha& _horaActual, Ci2c* i2c,  const uint8_t _num_zona, const uint8_t _nOutputpin, char _port);//Initialize the three attributes to 0 and choose the outputpin
		
		/**
		 * 
		 */
		void doThings(Cfecha);// Offset para que la segunda zona tome el valor del dado desplazado estos minutos
		
		/**
		 * Method: readDices()
		 * Brief: Read dices in current moment
		 * @param: void
		 * @return: void
		 */
		void readDices();

		/**
		 * Method: refreshDicesValues.
		 * Brief: This method aims to refresh all cubes values, these are properties of the class
		 * @param: uint8_t* _dias
		 * @param:uint8_t _hora
		 * @param: uint8_t duracion
		 * @return: void
		 */
		void refreshDicesValues (uint8_t* _dias, uint8_t _hora, uint8_t duracion);

		/** 
		* Method:  is_programmed()
		* Brief: This method return if it programmed, if all of them are is the true condition other case is the opposite.
		* @param null
		* @return bool binary
		*/
		uint8_t is_programmed ();
		void setoffset_factor (uint8_t _offset_factor);
		//void setdiasRiego(uint8_t _diasRiego[7]);
		void setdiasRiego(uint8_t* _diasRiego);
		void sethoraRiego (uint8_t _horaRiego);
		void setminutoRiego(uint8_t _minutosRiego);
		void setminutosRegando(uint8_t _minutosRegando);
		void setStatusZonaRiego(statesZonasRiego);
		uint8_t* getDiasRiego();
		uint8_t getoffsetTime();
		uint8_t getoffsetTimeJustDroppingNow();
		uint8_t is_currentDiaProgrammed(uint8_t i);
		uint8_t gethoraRiego();
		uint8_t getminutoInicioRiego();
		uint8_t getDuracionRiego();	
		uint8_t getriegoProgramado();	
		uint8_t getNumZona();

		
		/*
			This method return the value of the attribute is_justDroppingNow
			@param null
			@return bool binary attribute is_justDroppingNow
		*/
		bool is_justDroppingNowRunning();
		uint8_t getminutoRiegoDroppingJustNow();
		uint8_t getDuracionDroppingJustNow();
		void setStateJustDroppingNow(statesJustdroppingNow);
		void ajustarDroppingJustNow (uint8_t, uint8_t);
		void setNowRunning(bool);
		bool isNowRunning();
		void setAjustadoDroppingJustNow(uint8_t value);
		void ResetDroppingJustNow();


		/** 
		* Brief: This method refresh the state of ZonaRiego
		* @param void
		* @return void
		*/

		/** Method: updateStateMachine()
		* Brief: This method refresh the state of ZonaRiego and by the way the state of the system
		* @param void
		* @return void
		*/
		void updateStateMachine();

		/** Method: refreshSistemaMenuModeState()
		* Brief: This method specifically refresh the menuMode of the Sistema, only if numZona is equal to 1
		* @param void
		* @return void
		*/
		void refreshSistemaMenuModeState();

		/** 
		* Method: updateOutputs()
		* Brief: This method aims to act over relays, once updateStatateMAchine() is called
		* @param void
		* @return void
		*/
		void updateOutputs();

		/** 
		* Brief: This method return the union resistace zone of all dices.
		* @param uint16_t adcRawData: This the adc value get of each dice position.
		* @return unionResistanceZoneDices: This is a enum type that define the union resistances dices: unionConditionDeleting, unionPreconditionJustDroppingNow, unionInRange, unionInfinite
		*/
		unionResistanceZoneDices CalculateUnionResistanceZoneDices(uint16_t adcRawDataDia, uint16_t adcRawDataHora, uint16_t adcRawDataDuracion);

		/** 
		* Brief: This method return the resultUnionResistanceZoneDices attribute.
		* @param void
		* @return resultUnionResistanceZoneDices attribute: This is a enum type that define the union resistances dices: unionConditionDeleting, unionPreconditionJustDroppingNow, unionInRange, unionInfinite
		*/
		unionResistanceZoneDices getResultUnionResistanceZoneDices(void);

		/** 
		* Brief: This method return the resistace zone of a dice.
		* @param uint16_t adcRawData: This the adc value get of the dice position
		* @return resistanceZoneDiceCategory: This is a enum type that define three resistances zones: shortcut, inRange, infinite
		*/
		resistanceZoneCubeCategory getCubeResistanceCategory(uint16_t adcRawData);

		statesZonasRiego getcurrentStateZonaRiego();

		void updateDuracionJustDroppingNow();

		void setJustDroppingNowRunning(bool value);

		/**
		 * brief: This method aims to get the date of next program, whos goal is fill programStartDate, programEndDate
		 * and compare it with current time and take decitions.
		 * @param lista fechas
		 * @return void
		 */
		 void calculateProgramDate(Cfecha*);
	

};
/*extern periodoRiego cicloRiego;*/

#endif /* CPERIODORIEGO_H_ */