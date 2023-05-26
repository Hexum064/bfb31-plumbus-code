/*
 * rand_seed.c
 *
 * Created: 2023-05-24 23:47:51
 *  Author: Branden
 */ 

#include <stdlib.h>
#include <avr/io.h>

unsigned int get_seed()
{
	ADCA.CTRLB|=ADC_CURRLIMIT1_bm|ADC_CONMODE_bm; //medium current consumption, maximum sampling speed 150ksps, resolution 12-bit right adjusted, signed mode
	
	ADCA.REFCTRL|=ADC_REFSEL0_bm; //INTVCC2 i.e. Vcc/1.6 is selected as reference voltage
	
	ADCA.EVCTRL=0x00;               //no event channel input is selected
	
	ADCA.PRESCALER|=ADC_PRESCALER2_bm; //prescaler 64 is selected and peripheral clock is 8MHz
	
	ADCA.INTFLAGS=ADC_CH0IF_bm; //clear interrupt flag by writing one to it
	
	ADCA.CH0.CTRL|=ADC_CH_INPUTMODE0_bm; //signed mode, single ended positive input selected
	
	ADCA.CH0.MUXCTRL|=ADC_CH_MUXPOS1_bm; //select PIN1 as input for ADC
	
	ADCA.CTRLA=ADC_ENABLE_bm | ADC_START_bm; //enable ADC and start
	
	while(!(ADCA.INTFLAGS & ADC_CH0IF_bm));
	
	ADCA.INTFLAGS=ADC_CH0IF_bm;  //clear flag immediately after conversion
	
	unsigned int result = ADCA.CH0.RES;
	
	ADCA.CTRLA = 0;
	return result;
}