/* 
* CeepromAVR.cpp
*
* Created: 26/07/2021 17:43:53
* Author: fgm97
*/


#include "CeepromAVR.h"
#include "Csistema.h"
#include <stdlib.h>


// default constructor
CeepromAVR::CeepromAVR()
{
} //CeepromAVR

CeepromAVR::CeepromAVR(Csistema* _sistema)
{
    if(_sistema != NULL)
        sistema = _sistema;
} //CeepromAVR

// default destructor
CeepromAVR::~CeepromAVR()
{
} //~CeepromAVR

void CeepromAVR::writeZonaRiego(CzonaRiego* zonaRiego)
{
	if (zonaRiego != NULL)
    {
        uint8_t* ptr_ee_addr_Reference = 0;
        uint8_t* ptr_ee_addr_programmed;
        uint8_t* ptr_ee_addr_diasRiego;
        uint8_t* ptr_ee_addr_HoraRiego;
        uint8_t* ptr_ee_addr_Duracion;

        uint8_t numZonaRiego = zonaRiego->getNumZona();
        const uint8_t numDatosToWriteinEeprom = 12;
        const uint8_t offesetMapEepromZRx = (numZonaRiego-1) * numDatosToWriteinEeprom;

        ptr_ee_addr_programmed = ptr_ee_addr_Reference + offesetMapEepromZRx ;
        ptr_ee_addr_diasRiego = ptr_ee_addr_Reference + 1 + offesetMapEepromZRx;
        ptr_ee_addr_HoraRiego = ptr_ee_addr_Reference + 10 + offesetMapEepromZRx;
        ptr_ee_addr_Duracion = ptr_ee_addr_Reference + 11 + offesetMapEepromZRx;
        uint8_t state= zonaRiego->getcurrentStateZonaRiego(); 
        uint8_t* diasRiego = zonaRiego->getDiasRiego();
        uint8_t horaRiego = zonaRiego->gethoraRiego();
        uint8_t duracion = zonaRiego->getDuracionRiego();
	    eeprom_write_byte(ptr_ee_addr_programmed, state);
        //eeprom_write_block(sistema->getDroppingZone_01()->getDiasRiego(), ptr_ee_addr_diasRiego, 8);
        eeprom_write_block(zonaRiego->getDiasRiego(), ptr_ee_addr_diasRiego, 8);
        eeprom_write_byte(ptr_ee_addr_HoraRiego, horaRiego);
        eeprom_write_byte(ptr_ee_addr_Duracion, duracion);   
        
    }
}

CzonaRiego* CeepromAVR::readZonaRiego(uint8_t numZonaRiego)
{
    CzonaRiego* zonaRiego = NULL;
    const uint8_t numDatosToWriteinEeprom = 12;
    uint8_t* ptr_ee_addr_Reference = 0;
    uint8_t* ptr_ee_addr_programmed;
    uint8_t* ptr_ee_addr_diasRiego;
    uint8_t* ptr_ee_addr_HoraRiego;
    uint8_t* ptr_ee_addr_Duracion;

    zonaRiego = (CzonaRiego*) malloc(sizeof(CzonaRiego));

    const uint8_t offesetMapEepromZRx = (numZonaRiego-1) * numDatosToWriteinEeprom;

    ptr_ee_addr_programmed = ptr_ee_addr_Reference + offesetMapEepromZRx;
    ptr_ee_addr_diasRiego = ptr_ee_addr_Reference + 1 + offesetMapEepromZRx;
    ptr_ee_addr_HoraRiego = ptr_ee_addr_Reference + 10 + offesetMapEepromZRx;
    ptr_ee_addr_Duracion = ptr_ee_addr_Reference + 11 + offesetMapEepromZRx;

    uint8_t status = eeprom_read_byte(ptr_ee_addr_programmed);
    eeprom_read_block(sistema->getDroppingZone_01()->getDiasRiego(), ptr_ee_addr_diasRiego, 8);
    //eeprom_read_block(zonaRiego->getDiasRiego(), ptr_ee_addr_diasRiego, 8);

    uint8_t horaRiego = eeprom_read_byte(ptr_ee_addr_HoraRiego);
    uint8_t duracion = eeprom_read_byte(ptr_ee_addr_Duracion);

    zonaRiego->setStatusZonaRiego( (CzonaRiego::statesZonasRiego) status);
    zonaRiego->sethoraRiego(horaRiego);
    zonaRiego->setminutosRegando(duracion);

    return zonaRiego;
}