/*
 * light_player.c
 *
 * Created: 2023-04-30 13:53:37
 *  Author: Branden
 */ 

#include "light_player.h"

#define POS_LED_COUNT 7
#define HALF_POS_LED_COUNT 3
#define RAINBOW_LED_COUNT 12

static const ws2812drv_led_t BUTTON_0 = {.r = MAX_BRIGHTNESS, .g = 0, .b = 0};
static const ws2812drv_led_t BUTTON_1 = {.r = 0, .g = MAX_BRIGHTNESS, .b = 0};
static const ws2812drv_led_t BUTTON_2 = {.r = 0, .g = 0, .b = MAX_BRIGHTNESS};
static const ws2812drv_led_t BUTTON_3 = {.r = MAX_BRIGHTNESS / 2, .g = MAX_BRIGHTNESS / 2, .b = 0};
static const ws2812drv_led_t LED_OFF = {.r = 0, .g = 0, .b = 0};
static const ws2812drv_led_t LED_MAX_ON =
{
	.r = MAX_BRIGHTNESS / 4,
	.g = MAX_BRIGHTNESS / 4,
	.b = MAX_BRIGHTNESS / 4
};

static uint8_t offset = 0;
static int8_t bump = -1;

static const ws2812drv_led_t pos_leds[POS_LED_COUNT] = {
	{.r = 0, .g = 0, .b = 0},
	{
		.r = MAX_BRIGHTNESS / 32,
		.g = MAX_BRIGHTNESS / 32,
		.b = MAX_BRIGHTNESS / 32,
	},
	{
		.r = MAX_BRIGHTNESS / 16,
		.g = MAX_BRIGHTNESS / 16,
		.b = MAX_BRIGHTNESS / 16,
	},
	{
		.r = MAX_BRIGHTNESS / 4,
		.g = MAX_BRIGHTNESS / 4,
		.b = MAX_BRIGHTNESS / 4,
	},
	{
		.r = MAX_BRIGHTNESS / 16,
		.g = MAX_BRIGHTNESS / 16,
		.b = MAX_BRIGHTNESS / 16,
	},
	{
		.r = MAX_BRIGHTNESS / 32,
		.g = MAX_BRIGHTNESS / 32,
		.b = MAX_BRIGHTNESS / 32,
	},
	{.r = 0, .g = 0, .b = 0}						
};



static const ws2812drv_led_t rainbow_leds[RAINBOW_LED_COUNT] = {
	{
		.r = MAX_BRIGHTNESS,
		.g = 0,
		.b = 0,
	},
	{
		.r = MAX_BRIGHTNESS / 4,
		.g = MAX_BRIGHTNESS / 16,
		.b = 0,
	},
	{
		.r = MAX_BRIGHTNESS / 4,
		.g = MAX_BRIGHTNESS / 4,
		.b = 0,
	},
	{
		.r = MAX_BRIGHTNESS / 16,
		.g = MAX_BRIGHTNESS / 4,
		.b = 0,
	},
	{
		.r = 0,
		.g = MAX_BRIGHTNESS,
		.b = 0,
	},
	{
		.r = 0,
		.g = MAX_BRIGHTNESS / 4,
		.b = MAX_BRIGHTNESS / 16,
	},
	{
		.r = 0,
		.g = MAX_BRIGHTNESS / 4,
		.b = MAX_BRIGHTNESS / 4,
	},
	{
		.r = 0,
		.g = MAX_BRIGHTNESS / 16,
		.b = MAX_BRIGHTNESS / 4,
	},
	{
		.r = 0,
		.g = 0,
		.b = MAX_BRIGHTNESS,
	},
	{
		.r = MAX_BRIGHTNESS / 16,
		.g = 0,
		.b = MAX_BRIGHTNESS / 4,
	},
	{
		.r = MAX_BRIGHTNESS / 4,
		.g = 0,
		.b = MAX_BRIGHTNESS / 4,
	},
	{
		.r = MAX_BRIGHTNESS / 4,
		.g = 0,
		.b = MAX_BRIGHTNESS / 16,
	}
};

void overlay_note_button_leds(ws2812drv_led_t * leds, uint8_t buttons)
{
	if (buttons & 0x01)
	{
		leds[GRUMBO_LED_COUNT] = BUTTON_0;
		leds[GRUMBO_LED_COUNT + 1] = BUTTON_0;
	}
	else
	{
		leds[GRUMBO_LED_COUNT] = LED_OFF;
		leds[GRUMBO_LED_COUNT + 1] = LED_OFF;
	}
	
	if (buttons & 0x02)
	{
		leds[GRUMBO_LED_COUNT + 2] = BUTTON_1;
		leds[GRUMBO_LED_COUNT + 3] = BUTTON_1;
	}
	else
	{
		leds[GRUMBO_LED_COUNT + 2] = LED_OFF;
		leds[GRUMBO_LED_COUNT + 3] = LED_OFF;
	}
	
	if (buttons & 0x04)
	{
		leds[GRUMBO_LED_COUNT + 4] = BUTTON_2;
		leds[GRUMBO_LED_COUNT + 5] = BUTTON_2;
	}
	else
	{
		leds[GRUMBO_LED_COUNT + 4] = LED_OFF;
		leds[GRUMBO_LED_COUNT + 5] = LED_OFF;
	}
	
	if (buttons & 0x08)
	{
		leds[GRUMBO_LED_COUNT + 6] = BUTTON_3;
		leds[GRUMBO_LED_COUNT + 7] = BUTTON_3;
	}
	else
	{
		leds[GRUMBO_LED_COUNT + 6] = LED_OFF;
		leds[GRUMBO_LED_COUNT + 7] = LED_OFF;
	}
}
	
void overlay_dingle_pos(ws2812drv_led_t * leds, uint16_t dingle_pos)
{
	uint8_t led_i;
	
	for (uint8_t i = 0; i < 16; i++)
	{
		if (!(dingle_pos & (0x01 << i)))
		{
			//if i is 0, since we are using unsigned ints, we have to manually calc the starting index
			//in the LED array
			//This only works out because HALF_POS_LED_COUNT = 3, our multiple for i 
			//(or the number of grumbo leds / the number of hall effect sensors)
			//This algorithm only works as expected for one-at-a-time activated sensors
			if (i == 0)
			{
				led_i = GRUMBO_LED_COUNT - HALF_POS_LED_COUNT;
			}
			else
			{
				led_i = (i * 3) - HALF_POS_LED_COUNT;
			}
			
			for (uint8_t j = 0; j < POS_LED_COUNT; j++)
			{				
				leds[led_i % GRUMBO_LED_COUNT] = pos_leds[j];
				led_i++;
			}
		}
		
	}
}

void play_lights_standby(ws2812drv_led_t * leds)
{
	for (uint8_t i = 0; i < LED_COUNT; i++)
	{
		leds[i].r = 0;
		leds[i].g = 0;
		leds[i].b = 0;
			
		switch((i + offset)%3)
		{
			case 0:
			leds[i].r = MAX_BRIGHTNESS;
			break;
			case 1:
			leds[i].g = MAX_BRIGHTNESS;
			break;
			case 2:
			leds[i].b = MAX_BRIGHTNESS;
			break;
		}
	}
	offset++;
}

void play_lights_free_play(ws2812drv_led_t * leds, uint16_t dingle_pos, uint8_t buttons)
{
	for (uint8_t i = 0; i < GRUMBO_LED_COUNT; i++)
	{
		leds[(i + offset) % GRUMBO_LED_COUNT] = rainbow_leds[i % RAINBOW_LED_COUNT];
		
		if (offset == GRUMBO_LED_COUNT)
		{
			offset = 0;
		}
	}
	offset++;
		
	overlay_note_button_leds(leds, buttons);
	overlay_dingle_pos(leds, dingle_pos);
}



void play_lights_nyan(ws2812drv_led_t * leds)
{
	uint8_t i = 0;
	uint8_t j = 0;
	uint8_t half = GRUMBO_LED_COUNT / 2;
	uint8_t margin = ((half - RAINBOW_LED_COUNT) / 2);
	
	
	if (!(offset % 2))
	{
		
		if (bump > 0)
		{
			bump = -1;
		}
		else
		{
			bump = 1;
		}
	}
	
	for (i = 0; i < half; i++)
	{
		if (i < margin || i >= half - margin)
		{
			
			leds[i + bump] = (ws2812drv_led_t)LED_OFF;
			leds[i + half - bump] = (ws2812drv_led_t)LED_OFF;
		}
		else
		{
			

			
			leds[i + bump] = 	
			(ws2812drv_led_t){
				.r = MAX_BRIGHTNESS / 4,
				.g = 0,
				.b = MAX_BRIGHTNESS / 4,
			};
			
			leds[i+half  - bump] = rainbow_leds[j++ % RAINBOW_LED_COUNT];
		}
				
	}
	
	leds[margin + bump] = (ws2812drv_led_t)LED_MAX_ON;
	leds[(half - margin - 1) + bump] = (ws2812drv_led_t)LED_MAX_ON;
	
	
	
	for (i = GRUMBO_LED_COUNT; i < LED_COUNT; i++)
	{

		if (offset % 23)
		{
			leds[i] = (ws2812drv_led_t){ .r=0, .g=0, .b = MAX_BRIGHTNESS};
		}
		else
		{
			leds[i] = (ws2812drv_led_t)LED_MAX_ON;
		}
	}
	
	offset++;

}

void play_lights_portal(ws2812drv_led_t * leds)
{
	uint8_t i = 0;
	uint8_t half = GRUMBO_LED_COUNT / 2;
	
	if (offset <= 16)
	{
		bump += 4;
	}
	else
	{
		bump -= 4;
	}
	
	if (offset == 32)
	{
		offset = 0;
	}
	
	for (i = 0; i < half; i++)
	{
		leds[i] = (ws2812drv_led_t){
			.r = 0,
			.g = ((i * 2) + bump) / 8,
			.b = ((MAX_BRIGHTNESS - (i * 2)) + bump) / 4
		};
		
	}
	
	for (i = 0; i < half; i++)
	{
		leds[i + half] = (ws2812drv_led_t){
			.r = ((MAX_BRIGHTNESS - (i * 2)) + bump) / 4,
			.g = ((MAX_BRIGHTNESS - (i * 2)) + bump) / 4,
			.b = ((GRUMBO_LED_COUNT - (i * 2)) + bump)/16
		};
			
	}
	
	offset++;
}