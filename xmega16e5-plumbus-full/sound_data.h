/*
 * sound_data.h
 *
 * Created: 2023-05-04 21:22:50
 *  Author: Branden
 */ 


#ifndef SOUND_DATA_H_
#define SOUND_DATA_H_

#include <avr/pgmspace.h>

const uint8_t nyanIntroTreble[] PROGMEM = {0x12,0x11,0xf,0x0,0xa,0x11,0x12,0x11,0xf,0xa,0x6,0x5,0x6,0xb,0xa,0x0,0xf,0x0,0x12,0x11,0xf,0x0,0x4a,0x8,0xb,0xa,0x8,0x5,0x6,0x5,0x8};
const uint8_t nyanIntroExtTreble[] PROGMEM = {0x0,0x0,0x0,0x0};

const uint8_t nyanMainTreble[] PROGMEM = {0x4f,0x4d,0x15,0x52,0x14,0x13,0x14,0x56,0x56,0x54,0x53,0x13,0x14,0x16,0x14,0x12,0xf,0xd,0x12,0xf,0x14,0x12,0x16,0x14,0x16,0x52,0x4f,0xd,0x12,0xf,0x14,0x12,0x16,0x15,0x12,0x13,0x14,0x16,0x14,0x53,0x16,0x14,0x12,0xf,0x14,0x13,0x14,0x16,0x54,0x56,0x54,0x4f,0x4d,0x15,0x52,0x14,0x13,0x14,0x56,0x56,0x54,0x53,0x13,0x14,0x16,0x14,0x12,0xf,0xd,0x12,0xf,0x14,0x12,0x16,0x14,0x16,0x52,0x4f,0xd,0x12,0xf,0x14,0x12,0x16,0x15,0x12,0x13,0x14,0x16,0x14,0x53,0x16,0x14,0x12,0xf,0x14,0x13,0x14,0x16,0x54,0x56,0x56,0x56,0x1b,0x19,0x56,0x1b,0x19,0x16,0x14,0x12,0x16,0x11,0x12,0x11,0xf,0x56,0x56,0x1b,0x19,0x16,0x1b,0x11,0x12,0x14,0x16,0x1d,0x1e,0x1d,0x1b,0x56,0x1b,0x19,0x56,0x1b,0x19,0x16,0x16,0x14,0x12,0x16,0x1b,0x19,0x1b,0x56,0x16,0x17,0x16,0x1b,0x19,0x16,0x11,0x12,0x11,0xf,0x56,0x57,0x56,0x1b,0x19,0x56,0x1b,0x19,0x16,0x14,0x12,0x16,0x11,0x12,0x11,0xf,0x56,0x56,0x1b,0x19,0x16,0x1b,0x11,0x12,0x14,0x16,0x1d,0x1e,0x1d,0x1b,0x56,0x1b,0x19,0x56,0x1b,0x19,0x16,0x16,0x14,0x12,0x16,0x1b,0x19,0x1b,0x56,0x16,0x17,0x16,0x1b,0x19,0x16,0x11,0x12,0x11,0xf,0x56,0x54};
const uint8_t nyanMainExtTreble[] PROGMEM = {0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0};

const uint8_t nyanMainBass[] PROGMEM = {0x75,0x69,0x73,0x67,0x76,0x6a,0x71,0x65,0x78,0x6c,0x73,0x67,0x3a,0x2e,0x7a,0x78,0x76};
const uint8_t nyanMainExtBass[] PROGMEM = {0x0,0x0,0x0};

const uint16_t nyanBPMPeriod = 13787;
	
//Left out of PROGMEM for ease of use and because it is used my 5 modes	
const uint16_t noteClocks[] = {1204,1276,1352,1432,1516,1608,1704,1804,1912,2024,2144,2272,2408,2552,2704,2864,3032,3216,3404,3608,3824,4048,4292,4544,4816,5104,5404,5728,6068,6428,6812,7216,7644,8100,8580,9092,9632,10204,10812,11456,12136,12856,13620,14432,15288,16200,17160,18180,19264,20408,21620,22908,24268,25712,27240,28860,30576,32392,34324,36364,38528,40816,43244,45820};
const uint16_t exp_decay_vals[] = {4095, 4000, 3800, 3500, 3100, 2600, 2000, 1300, 500, 400, 300, 200, 100};

#endif /* SOUND_DATA_H_ */