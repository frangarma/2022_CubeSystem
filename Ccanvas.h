/*
 * Ccanvas.h
 *
 * Created: 22/08/2015 20:02:43
 *  Author: Fran
 */ 


#ifndef CCANVAS_H_
#define CCANVAS_H_

#include "definiciones.h"
#include <stdint.h>
#include "Clcd.h"
#include "Cclock.h"
#include <stddef.h>

class Csistema;



#define DATE_MAIN_CANVAS "%02d:%02d %c %02d/%02d"

class Ccanvas
{
    private:
        Clcd* lcd;
        Cclock clock;
        Cfecha horaActual;
        Csistema* sistema;
    public:
        Ccanvas();
        Ccanvas(Csistema*, Clcd*, const Cclock&, const Cfecha&);
        ~Ccanvas();
        void refresh(lcdmodes lcdmode);
        void showLcd(unsigned char page, unsigned char column, show_info message);
        void scroll_throug_menu(void);
        void enter_programming_mode(void);
        uint8_t DayOfWeek(int y, uint8_t m, uint8_t d);
        void infoDiasRiego (uint8_t* _dowRiego);
        void static reset(uint8_t &variable);
};   
#endif /* CCANVAS_H_ */