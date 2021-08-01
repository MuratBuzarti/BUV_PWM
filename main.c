/*
 * File:   main.c
 * Author: buzar
 *
 * Created on 23 ???? 2021 ?., 10:17
 */

#define _XTAL_FREQ 8000000
#include "pic10f322.h"
#include "functions.h"
//#include "config.h"
#include "xc.h"

#define LowPower RA3
#define MidPower RA1
#define HighPower RA0


// Период ШИМ, Задание скважности, Текущее значение счётчика периода
unsigned char PWM_period=25, PWM_high=9, PWM_counter=0;

// Счётчик времени в количествах прерываний для измерения времени
unsigned int time_counter=0;

// Счётчик отсутствия команд
unsigned int NoCommandCounter=0;

void main()
{
    init();
    GIE = 1; // Разрешение глобльных прерываний
    
    while(1)
    {
        
        
        PWM_high=3;
        __delay_ms(3000);
        PWM_high=8;
        __delay_ms(3000);
        PWM_high=12;
        __delay_ms(3000);
        PWM_high=25;
        __delay_ms(3000);
        
        
        /*
        if (LowPower == 0) {
            PWM_high = 12;
            NoCommandCounter = 0;
        }

        if (MidPower == 0) {
            PWM_high = 8;
            NoCommandCounter = 0;
        }

        if (HighPower == 0) {
            PWM_high = 3;
            NoCommandCounter = 0;
        }

        
        if ((LowPower==1)&&(MidPower==1)&&(HighPower==1))
        {
            NoCommandCounter++;
            if (NoCommandCounter>=10000)
            {
                PWM_high = PWM_period;
                NoCommandCounter=10000;
            }
        }
        */
        
    }
    
}

// Обработчик прерывания
// Название tmr2Int придумывается самостоятельно
void __interrupt() tmr2Int()
{
    PWM_counter++;
    
    if(PWM_counter>=PWM_period)
    {
        RA2=1;
        PWM_counter=0;
    }
    
    if(PWM_counter>=PWM_high)
    {
        RA2=0;
    }
    
    TMR2IF=0;   // сброс флага прерывания
    return;
}