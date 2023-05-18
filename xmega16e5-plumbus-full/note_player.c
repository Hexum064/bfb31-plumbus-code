/*
 * note_player.c
 *
 * Created: 2023-04-30 13:52:46
 *  Author: Branden
 */ 

#include <avr/io.h>
#include "note_player.h"
#include "sound_data.h"

uint8_t decay_table_len = sizeof(expDecayVals);
uint8_t playing = 0;


void note_timer_C5_init()
{
	TCC5.CTRLB = TC_BYTEM_NORMAL_gc | TC_CIRCEN_DISABLE_gc | TC_WGMODE_FRQ_gc;
	TCC5.CTRLE = TC_CCAMODE_COMP_gc;
	TCC5.CTRLA = TC_CLKSEL_DIV8_gc;
}

void sys_timer_D5_init()
{
	TCD5.CTRLB = TC_BYTEM_NORMAL_gc | TC_CIRCEN_DISABLE_gc | TC_WGMODE_NORMAL_gc;
	TCD5.CTRLE = 0;
	TCD5.INTCTRLB = TC_OVFINTLVL_HI_gc;
	TCD5.CTRLA = TC_CLKSEL_DIV1024_gc;
	TCD5.PER = 312; //100Hz
}

void note_decay_init()
{
	////////////////////////////////////////// Timer and Event config ?
	EVSYS.CH1MUX =
	EVSYS_CHMUX_TCC4_OVF_gc;        // Event ch1 = tcc4 overflow
	TCC4.PER = 1200;
	TCC4.CTRLA = TC_CLKSEL_DIV1024_gc;
	
	////////////////////////////////////////// DAC config
	DACA.CTRLB =
	DAC_CHSEL_SINGLE_gc |          // DAC ch0 is active
	DAC_CH0TRIG_bm;			// DAC ch0 auto triggered by an event (CH1)
	DACA.CTRLC =
	DAC_REFSEL_AVCC_gc;             // Use AVCC (3.3v), right adj
	DACA.EVCTRL =
	DAC_EVSEL_1_gc;                 // Event Ch1 triggers the DAC conversion
	DACA.CTRLA = DAC_CH0EN_bm | DAC_ENABLE_bm;  // enable DACA channel 0
	
	EDMA.CH0.CTRLA = EDMA_CH_RESET_bm;
	EDMA.CH0.ADDRCTRL =
	EDMA_CH_RELOAD_TRANSACTION_gc |   // Reload after transaction
	EDMA_CH_DIR_INC_gc;		  // increment source address
	EDMA.CH0.TRIGSRC =
	EDMA_CH_TRIGSRC_DACA_CH0_gc;	  // DACA Ch0 is trigger source
	
	EDMA.CH0.CTRLB =
	EDMA_CH_TRNIF_bm |               //  Clear flag
	EDMA_CH_TRNINTLVL_HI_gc;          // For XMegaE5, this ISR is necessary to re-enable channel after transaction
	
	EDMA.CTRL = EDMA_ENABLE_bm; 	          // Enable, single buffer, round robin
}

void run_note_decay()
{
	
	EDMA.CH0.TRFCNT = decay_table_len;                  // data array has len values
	EDMA.CH0.ADDR = (uint16_t)expDecayVals;           // this is the source SRAM address
	EDMA.CH0.CTRLA =
	EDMA_CH_ENABLE_bm |               //   enable EDMA Ch0
	EDMA_CH_SINGLE_bm |               //   one burst per trigger
	EDMA_CH_BURSTLEN_bm;              //   2 bytes per burst
}

void note_play(uint8_t note_index)
{
	playing = 1;
	TCC5.CCA = noteClocks[STARTING_NOTE_INDEX + note_index];
	run_note_decay();
	TCC5.CTRLA = TC_CLKSEL_DIV8_gc;// TC_CLKSEL_DIV1024_gc;
}

void reset_play()
{
	playing = 0;
	EDMA.CH0.CTRLB |= EDMA_CH_TRNIF_bm;   // clear INT flag    // EDMA.INTFLAGS = EDMA_CH0TRNFIF_bm;    // alternate flag location also works
	TCC5.CNT = 0;
	TCC5.CTRLA = 0;// TC_CLKSEL_DIV1024_gc;
}

void note_player_init()
{
	note_timer_C5_init();
	sys_timer_D5_init();
	note_decay_init();
}

void note_interrupt_handler()
{
	reset_play();
}

uint8_t note_player_playing()
{
	return playing;
}