/*
 * CzonaRiego.cpp
 *
 * Created: 11/03/2018 17:15:30
 *  Author: Fran
 */ 

#include "CzonaRiego.h"
#include "VariablesGlobales.h"
#include <string.h>

#ifdef DEBUGGER_MODE_R
	#include "BSP.h"
	#include <stdio.h>	
#endif

using namespace std;

//default constuctor/~

CzonaRiego::CzonaRiego() 
{

}

CzonaRiego::~CzonaRiego() {
	
}


CzonaRiego :: CzonaRiego (Csistema* _sistema, const Cclock& _clock, const Cfecha& _horaActual, Ci2c* _i2c, const uint8_t _num_zona, const uint8_t _nOutputpin, char _port) : Cswitchable (_nOutputpin, _port) 
{
	sistema = NULL;
	if (_sistema != NULL)
	{
		sistema = _sistema;		
	}
	lastStateZonaRiego = standby;
	stateDroppingNow = notDroppingNow;
	//It is neccesary to put a true this booleans() in order to reboot initial conditions when read the eeprom
	is_newStateZoneRiego = true;
	newStateDroppingNow = true;
	clock = _clock;
	horaActual = _horaActual;
	num_zona=_num_zona;
	riegoProgramado=0;
	//for (uint8_t i=0; i<nelementdoWRiego; i++) { diasRiego[i]=0;}	
	memset(diasRiego, 0, nelementdoWRiego);
	duracionRiego= 0;
	setminutoRiego(0);// Currently dices get times oclock.
	offset_minutosRiego=0;	
	//dadoDia = CdadoDia(1);
   	//dadoHora = CdadoHora(2);
   	//dadoDuracion= CdadoDuracion(3);
	ajustadoDroppingJustNow=0;
	is_justDroppingNow = false;
	nowRunning = false;
	duracionDroppingJustNow = 0;
	minutoInicioRiegoJustoDroppingNow = 0;
	i2c = _i2c;		

	currentStateZonaRiego = standby;
	eventCurrentUnionStateDices = eventInit;
	eventLastUnionStateDices = eventInit;
	unionResistanceZoneDices resultUnionResistanceZoneDices = unionInderteminate; 

}

uint8_t CzonaRiego::getNumZona()
{
	return num_zona;
}

void CzonaRiego::setoffset_factor (uint8_t _offset_factor){
	offset_factor=_offset_factor;
	
}

void CzonaRiego:: setdiasRiego(uint8_t* _diasRiego)
{
	for (uint8_t i=0; i<nelementdoWRiego; i++) 
	{ 
		diasRiego[i]=_diasRiego[i];
	}	
}

void CzonaRiego::sethoraRiego (uint8_t _horaRiego)
{
	horaRiego=_horaRiego;
}

void CzonaRiego:: setminutoRiego(uint8_t _minutoRiego)
{
	minutoInicioRiego=_minutoRiego;
}

void CzonaRiego:: setminutosRegando(uint8_t _minutosRegando)
{
	duracionRiego=_minutosRegando;	
}

void CzonaRiego::setStatusZonaRiego(statesZonasRiego _state)
{
		currentStateZonaRiego = _state;
		lastStateZonaRiego = _state;
}

uint8_t CzonaRiego :: getoffsetTime()
{
	return (offset_factor * duracionRiego);
}

uint8_t CzonaRiego::getoffsetTimeJustDroppingNow()
{
	return (offset_factor * duracionDroppingJustNow);
}


uint8_t CzonaRiego::is_currentDiaProgrammed(uint8_t i)
{
	if (diasRiego[i-1])	{return 1;}
	else return 0;	
}

uint8_t CzonaRiego::gethoraRiego()
{
	return horaRiego;
}

uint8_t CzonaRiego::getminutoInicioRiego()
{
	return minutoInicioRiego;
}

uint8_t CzonaRiego::getminutoRiegoDroppingJustNow()
{
	return minutoInicioRiegoJustoDroppingNow;
}

uint8_t CzonaRiego:: getDuracionRiego()
{
	return duracionRiego;
}

void CzonaRiego::updateDuracionJustDroppingNow()
{
	duracionDroppingJustNow = dadoDuracion.valor();
}


uint8_t CzonaRiego:: getDuracionDroppingJustNow()
{
	return duracionDroppingJustNow;
}

uint8_t CzonaRiego::getriegoProgramado()
{
	return riegoProgramado;
}

void CzonaRiego :: refreshDicesValues (uint8_t* _dias, uint8_t _hora, uint8_t _duracion) 
{
	setdiasRiego(_dias);
	sethoraRiego(_hora);
	setminutosRegando(_duracion);	
}

void CzonaRiego :: ajustarDroppingJustNow (uint8_t _hora, uint8_t _minutoRiegoDroppingJustNow)
{	
	horaRiegoDroppingJustNow=_hora;
	minutoInicioRiegoJustoDroppingNow=_minutoRiegoDroppingJustNow;
	setAjustadoDroppingJustNow(1);
}

uint8_t CzonaRiego :: is_programmed ()
{
	if (currentStateZonaRiego == programmed)
		return 1;
	else 
		return 0;
}


bool CzonaRiego:: is_justDroppingNowRunning() {
	
	return is_justDroppingNow;
}

void CzonaRiego::setJustDroppingNowRunning(bool value)
{
	is_justDroppingNow = value;
}

void CzonaRiego:: setStateJustDroppingNow(statesJustdroppingNow _stateDroppingNow)
{
	stateDroppingNow = _stateDroppingNow;
}

void CzonaRiego:: setNowRunning(bool value) {
	nowRunning= value;
}



void CzonaRiego:: ResetDroppingJustNow(){
	setNowRunning(false);
	setStateJustDroppingNow(notDroppingNow);
	off();
}




bool CzonaRiego:: isNowRunning() 
{
	return nowRunning;
}


void CzonaRiego::doThings(Cfecha currentDate) 
{	
	horaActual = currentDate;
	readDices();
	updateStateMachine();
	updateOutputs();
	refreshSistemaMenuModeState();	
}

void CzonaRiego::readDices()
{
	uint16_t adcRawDataDia = dadoDia.read();
	uint16_t adcRawDataHora = dadoHora.read();
	uint16_t adcRawDataDuracion = dadoDuracion.read();
	eventLastUnionStateDices = eventCurrentUnionStateDices;
	eventCurrentUnionStateDices = CalculateUnionResistanceZoneDices(adcRawDataDia, adcRawDataHora, adcRawDataDuracion);
}

void CzonaRiego::updateStateMachine()
{
	//Implement updateStateMachine, good way
	//https://www.luisllamas.es/maquina-de-estados-finitos-arduino/
	//updateStateMachine()

	switch(currentStateZonaRiego)
	{
		case standby:
			refreshDicesValues(dadoDia.valor(diasRiego), dadoHora.valor(), dadoDuracion.valor() );			
			if (eventCurrentUnionStateDices == unionInRange)
			{
				currentStateZonaRiego = inProgramming;
			}
			break;

		case calculateProgram:			
			break;
			
		case inProgramming:
			currentStateZonaRiego = programmed;
			sistema->getAvrEeprom()->writeZonaRiego(this);
			sistema->setStatus(Csistema::progMode);
			break;

		case programmed:
		 	if (eventCurrentUnionStateDices == unionConditionDeleting)
			{
				currentStateZonaRiego = inDeleting;
			}
			break;

		case inDeleting:
		 		currentStateZonaRiego = standby;
				refreshDicesValues(dadoDia.valor(diasRiego), dadoHora.valor(), dadoDuracion.valor() );		
				sistema->getAvrEeprom()->writeZonaRiego(this);
				sistema->setStatus(Csistema::standBy);
				setNowRunning(false);
				if (! is_justDroppingNowRunning())
				{
					off();
				}
			break;

		default:
			break;

	}//End switch(currentStateZonaRiego)

	switch (stateDroppingNow)
	{
		case notDroppingNow:
			if  ( (eventCurrentUnionStateDices == unionPreconditionAbort_EntryJustDroppingNow) && (!isNowRunning()) )
			{
				setStateJustDroppingNow(firstStageBeforeEntryJustDroppingJustNow);
			}
			break;

		case firstStageBeforeEntryJustDroppingJustNow:
			if	(eventCurrentUnionStateDices == unionConditionJustDroppingNow)
			{
				updateDuracionJustDroppingNow();
				programStartDate = programStartDate.addToDateXMinutes(horaActual, getoffsetTimeJustDroppingNow());
				programEndDate = programEndDate.addToDateXMinutes(horaActual, ( getDuracionDroppingJustNow() + getoffsetTimeJustDroppingNow()) );
				setStateJustDroppingNow(JustDroppingNow);
			}
			break;

		case JustDroppingNow:
			if(horaActual <= programEndDate)
			{
					on();
					setJustDroppingNowRunning(true);
			}
			
			else 
			{
				off();
				if (is_justDroppingNowRunning())
				{
					setStateJustDroppingNow(notDroppingNow);
					setJustDroppingNowRunning(false);
				}

			}
			if(eventCurrentUnionStateDices == unionInfinite)
			{
				stateDroppingNow = firstStageBeforeAbortingJustDroppingJustNow;
			}
			break;
		
		case firstStageBeforeAbortingJustDroppingJustNow:
			if(horaActual <= programEndDate)
			{
				on();
				setJustDroppingNowRunning(true);
			}
			else 
			{
				off();
				if (is_justDroppingNowRunning())
				{
					setStateJustDroppingNow(notDroppingNow);
					setJustDroppingNowRunning(false);
				}
			}			
			if (eventCurrentUnionStateDices == unionPreconditionAbort_EntryJustDroppingNow)
			{
				stateDroppingNow = inAbortingJustDroppingJustNow;
			}
			break;

		case inAbortingJustDroppingJustNow:
			
			off();
			setStateJustDroppingNow(notDroppingNow);
			setJustDroppingNowRunning(false);

			break;

		default:
			break;
	}//End switch(stateDroppingNow)
	NULL;
	
}//End updateStateMachine()


void CzonaRiego::refreshSistemaMenuModeState()
{
	if(num_zona ==1)
	{
		//statusSystem = sistema->getStatus();
		if((((eventCurrentUnionStateDices == unionPreconditionMenuMode) &&eventLastUnionStateDices == unionInfinite)| (sistema->getStatus() == Csistema::menuMode)) && resistanceZoneCubeDuracion ==shortcut ) //| (eventCurrentUnionStateDices == unionConditionmenuMode) && 
		{
			if(sistema->getStatus() != Csistema::menuMode)
			{
				sistema->setStatus(Csistema::menuMode);
				//statusSystem = Csistema::menuMode;
				new_entry_mode_prog = 1;
			}
			switch(sistema->getStatus())
			{
				case (Csistema::standBy):
					;
				break;
				case (Csistema::progMode):
					;
				break;
				case (Csistema::menuMode):
					;
				break;
			}
		}
		else if ((resistanceZoneCubeDuracion == infinite) && (sistema->getStatus() == Csistema::menuMode))
		{
			//Go out from menuMode, restart variables and systemStatuslast
			sistema->setStatus(sistema->getLastStatus());
			time_out_menu_inactivity = 0;
			menu_cursor_position = position_cursor_sethour;		
			toogle = 1;	
		}		
	}

}

void CzonaRiego::updateOutputs()
{
	switch(currentStateZonaRiego)
	{
		case programmed:

			if ( !is_justDroppingNowRunning() )
			{
				if ( this->is_currentDiaProgrammed(horaActual.getDoW() ))
				{
					//if durancionRiego is as big as there is a change of day ¡¡¡ It won't work!!!
					uint8_t tempminutosInicioRiego = getminutoInicioRiego() + getoffsetTime();
					uint8_t tempminutosFinRiego = tempminutosInicioRiego;
					uint8_t temphoraFinRiego = this->gethoraRiego();
					uint8_t tempModuloHoras =0;
					if(this->getDuracionRiego() > 60 )
						tempModuloHoras = this->getDuracionRiego() / 60;

					temphoraFinRiego += tempModuloHoras;
					if( (tempminutosInicioRiego + this->getDuracionRiego()) <= 60)
					{
						tempminutosFinRiego += this->getDuracionRiego();
					}
					else
						tempminutosFinRiego +=  this->getDuracionRiego() % 60;
					//if ( this->gethoraRiego() == horaActual.getHour() ) 
					if ( ( (temphoraFinRiego - horaActual.getHour() >= 0) && (temphoraFinRiego - horaActual.getHour() <= tempModuloHoras) ) )
					{
						//if  ( (horaActual.getMinute() >= (getminutoInicioRiego() + getoffsetTime()) ) &&  (horaActual.getMinute() < ((getminutoInicioRiego() + getoffsetTime() + getDuracionRiego())) ) ) 
						if  ( (horaActual.getMinute() >= (getminutoInicioRiego() + getoffsetTime()) ) &&  (horaActual.getMinute() < tempminutosFinRiego) ) 

						{
							on();
							setNowRunning(true);
						}
						else 
						{
							off();// go out due to minutes
							setNowRunning(false);
						}
					}
					else
					{
						off();// go out due to hour
						setNowRunning(false);
					} 

				}
				else
				{
					off();// go out due to the day	
					setNowRunning(false);
				}
			}
			
			if( (getNumZona() ==2) && !is_justDroppingNowRunning() )
			{
				if ( sistema->getDroppingZone_01()->is_currentDiaProgrammed(horaActual.getDoW() ))
				{
					if (   this->gethoraRiego() == horaActual.getHour() ) 
					{
						if  ( (horaActual.getMinute() >= (getminutoInicioRiego() + getoffsetTime()) ) &&  (horaActual.getMinute() < ((getminutoInicioRiego() + getoffsetTime() + getDuracionRiego())) ) ) 
						{
							on();
							setNowRunning(true);
						}
						else 
						{
							off();// go out due to minutes
							setNowRunning(false);
						}
					}
					else
					{
						off();// go out due to hour
						setNowRunning(false);
					} 

				}
				else
				{
					off();// go out due to the day	
					setNowRunning(false);
				}
				
			}
	}//end switch(currentStateZonaRiego)
}


unionResistanceZoneDices CzonaRiego::CalculateUnionResistanceZoneDices(uint16_t adcRawDataDia, uint16_t adcRawDataHora, uint16_t adcRawDataDuracion)
{
	resistanceZoneCubeDia = getCubeResistanceCategory(adcRawDataDia);
	resistanceZoneCubeHora = getCubeResistanceCategory(adcRawDataHora);
	resistanceZoneCubeDuracion = getCubeResistanceCategory(adcRawDataDuracion);
	
	if ( (resistanceZoneCubeDia == infinite) && (resistanceZoneCubeHora == infinite) && (resistanceZoneCubeDuracion == infinite ) )
		resultUnionResistanceZoneDices = unionInfinite;
		
	else if ( (resistanceZoneCubeDia == inRange) && (resistanceZoneCubeHora == inRange) && (resistanceZoneCubeDuracion == inRange) )
		resultUnionResistanceZoneDices = unionInRange;
	
	else if ( (resistanceZoneCubeDia == shortcut) && (resistanceZoneCubeHora == infinite) && (resistanceZoneCubeDuracion == infinite ))
		resultUnionResistanceZoneDices = unionConditionDeleting;

	else if ( (resistanceZoneCubeDia == infinite) && (resistanceZoneCubeHora == shortcut) && (resistanceZoneCubeDuracion == inRange) )
		resultUnionResistanceZoneDices = unionConditionJustDroppingNow;
	
	else if ( (resistanceZoneCubeDia == infinite) && (resistanceZoneCubeHora == shortcut) && (resistanceZoneCubeDuracion == infinite) )
		resultUnionResistanceZoneDices = unionPreconditionAbort_EntryJustDroppingNow;

	else if ( (resistanceZoneCubeDia == infinite) && (resistanceZoneCubeHora == infinite) && (resistanceZoneCubeDuracion == shortcut) )
		resultUnionResistanceZoneDices = unionPreconditionMenuMode;
	
	else if ( (resistanceZoneCubeDia == shortcut) && (resistanceZoneCubeHora == infinite) && (resistanceZoneCubeDuracion == shortcut) )
		resultUnionResistanceZoneDices = unionConditionPlusmenuMode;
	
	else if ( (resistanceZoneCubeDia == infinite) && (resistanceZoneCubeHora == shortcut) && (resistanceZoneCubeDuracion == shortcut) )
		resultUnionResistanceZoneDices = unionConditionMinusmenuMode;

	else	
		resultUnionResistanceZoneDices = unionInderteminate;		

	#ifdef DEBUGGER_MODE_R
		sprintf(serialprintdebugger, "CalculateUnionResistanceZoneDices: %d,", resultUnionResistanceZoneDices);
		UsartTransmitData(serialprintdebugger);
	#endif
	
	return resultUnionResistanceZoneDices;
	
}

unionResistanceZoneDices CzonaRiego::getResultUnionResistanceZoneDices()
{
	return resultUnionResistanceZoneDices;
}

resistanceZoneCubeCategory CzonaRiego::getCubeResistanceCategory(uint16_t adcRawData)
{
	uint16_t  r;
	uint8_t i=0; // j=0, encontrado=0;
	resistanceZoneCubeCategory resistanceDice;
 	if (adcRawData==1023)
	{ r = infiniteResistor; } // avoid 0 division
 	else { r= ( referenceResistor / ((1023.0/adcRawData)-1) ); } // r is the resistor value in ohm
	#ifdef DEBUGGER_MODE_R
		sprintf(serialprintdebugger, "%d,", r);
		UsartTransmitData(serialprintdebugger);
	#endif
	if 		( r < shortcutResistor) { i=0; }
	else if ((r >= (arrayValoresResistor[0]-toleranceenohmLecturasResistor)) && ( r <= (arrayValoresResistor[0]+toleranceenohmLecturasResistor))) { i=1; }
	else if ((r >= (arrayValoresResistor[1]-toleranceenohmLecturasResistor)) && ( r <= (arrayValoresResistor[1]+toleranceenohmLecturasResistor))) { i=2; }	
	else if ((r >= (arrayValoresResistor[2]-toleranceenohmLecturasResistor)) && ( r <= (arrayValoresResistor[2]+toleranceenohmLecturasResistor))) {	i=3; }
	else if ((r >= (arrayValoresResistor[3]-toleranceenohmLecturasResistor)) && ( r <= (arrayValoresResistor[3]+toleranceenohmLecturasResistor))) {	i=4; }
	else if ((r >= (arrayValoresResistor[4]-toleranceenohmLecturasResistor)) && ( r <= (arrayValoresResistor[4]+toleranceenohmLecturasResistor))) {	i=5; } // caso 1 y 15 lo paso a corto
	else if ((r >= (arrayValoresResistor[5]-toleranceenohmLecturasResistor)) && ( r <= (arrayValoresResistor[5]+toleranceenohmLecturasResistor))) {	i=6; }
	else if ( r >= infiniteResistor) { i=7; }

	else i=10;// Caso para el default
		
	#ifdef DEBUGGER_MODE
		sprintf(serialprintdebugger, "case_h=%d,", i);
		UsartTransmitData(serialprintdebugger);
	#endif
	
 	switch (i) 
	 {
		case 0:
			resistanceDice = shortcut;
			break;		
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			resistanceDice = inRange;
			break;
		case 7:
			resistanceDice = infinite;
			break;	
	}// end switch
	return resistanceDice;
}

uint8_t* CzonaRiego::getDiasRiego(void)
{
	return diasRiego;
}

CzonaRiego::statesZonasRiego CzonaRiego::getcurrentStateZonaRiego(void)
{
	return currentStateZonaRiego;
}	


void CzonaRiego::calculateProgramDate(Cfecha* listDates)
{
	//Through listDates and dadoDia it is neccesary to get start and endprogram

}
