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

volatile ws2812drv_led_t leds[LED_COUNT];

#define BUTTON_0 0
#define BUTTON_1 1
#define BUTTON_2 2
#define BUTTON_3 3
#define LED_OFF 4
#define LED_MAX_ON 5

// static const ws2812drv_led_t BUTTON_0 = {.r = MAX_BRIGHTNESS, .g = 0, .b = 0};
// static const ws2812drv_led_t BUTTON_1 = {.r = 0, .g = MAX_BRIGHTNESS, .b = 0};
// static const ws2812drv_led_t BUTTON_2 = {.r = 0, .g = 0, .b = MAX_BRIGHTNESS};
// static const ws2812drv_led_t BUTTON_3 = {.r = MAX_BRIGHTNESS / 2, .g = MAX_BRIGHTNESS / 2, .b = 0};
// static const ws2812drv_led_t LED_OFF = {.r = 0, .g = 0, .b = 0};
// static const ws2812drv_led_t LED_MAX_ON =
// {
// 	.r = MAX_BRIGHTNESS / 4,
// 	.g = MAX_BRIGHTNESS / 4,
// 	.b = MAX_BRIGHTNESS / 4
// };

static uint8_t offset = 0;
static int8_t bump = -1;

const ws2812drv_led_t game_colors[] = {
	(ws2812drv_led_t){.r = MAX_BRIGHTNESS, .g = 0, .b = 0},
	(ws2812drv_led_t){.r = 0, .g = MAX_BRIGHTNESS, .b = 0},
	(ws2812drv_led_t){.r = 0, .g = 0, .b = MAX_BRIGHTNESS},
	(ws2812drv_led_t){.r = MAX_BRIGHTNESS / 2, .g = MAX_BRIGHTNESS / 2, .b = 0},
	(ws2812drv_led_t){.r = 0, .g = 0, .b = 0},
	(ws2812drv_led_t){
			.r = MAX_BRIGHTNESS / 4,
			.g = MAX_BRIGHTNESS / 4,
			.b = MAX_BRIGHTNESS / 4
		}
};

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

void play_lights_overlay_note_button_leds(uint8_t buttons)
{
	if (buttons & 0x01)
	{
		leds[GRUMBO_LED_COUNT] = game_colors[BUTTON_0];
		leds[GRUMBO_LED_COUNT + 1] = game_colors[BUTTON_0];
	}
	else
	{
		leds[GRUMBO_LED_COUNT] = game_colors[LED_OFF];
		leds[GRUMBO_LED_COUNT + 1] = game_colors[LED_OFF];
	}
	
	if (buttons & 0x02)
	{
		leds[GRUMBO_LED_COUNT + 2] = game_colors[BUTTON_1];
		leds[GRUMBO_LED_COUNT + 3] = game_colors[BUTTON_1];
	}
	else
	{
		leds[GRUMBO_LED_COUNT + 2] = game_colors[LED_OFF];
		leds[GRUMBO_LED_COUNT + 3] = game_colors[LED_OFF];
	}
	
	if (buttons & 0x04)
	{
		leds[GRUMBO_LED_COUNT + 4] = game_colors[BUTTON_2];
		leds[GRUMBO_LED_COUNT + 5] = game_colors[BUTTON_2];
	}
	else
	{
		leds[GRUMBO_LED_COUNT + 4] = game_colors[LED_OFF];
		leds[GRUMBO_LED_COUNT + 5] = game_colors[LED_OFF];
	}
	
	if (buttons & 0x08)
	{
		leds[GRUMBO_LED_COUNT + 6] = game_colors[BUTTON_3];
		leds[GRUMBO_LED_COUNT + 7] = game_colors[BUTTON_3];
	}
	else
	{
		leds[GRUMBO_LED_COUNT + 6] = game_colors[LED_OFF];
		leds[GRUMBO_LED_COUNT + 7] = game_colors[LED_OFF];
	}
}
	
void overlay_dingle_pos(uint16_t dingle_pos)
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

uint8_t red = MAX_BRIGHTNESS/16;
uint8_t green = MAX_BRIGHTNESS/16;
uint8_t blue = MAX_BRIGHTNESS/16;

void play_lights_standby()
{
	ws2812drv_led_t color = {.r = red, .g = green, .b = blue};
	blue++;
	if (blue >= MAX_BRIGHTNESS / 4)
	{
		blue = MAX_BRIGHTNESS/16;
		red++;
		if (red >= MAX_BRIGHTNESS / 4)
		{
			red = MAX_BRIGHTNESS/16;
			green++;
			if (green >= MAX_BRIGHTNESS / 4)
			{
				green = MAX_BRIGHTNESS/16;
				
			}
			
		}
	}
	
	
	
	for (uint8_t i = 0; i < LED_COUNT; i++)
	{
		leds[i] = color;
	}

	ws2812drv_start_transfer(leds, LED_COUNT);
}

void play_lights_free_play(uint16_t dingle_pos, uint8_t buttons)
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
		
	play_lights_overlay_note_button_leds(buttons);
	overlay_dingle_pos(dingle_pos);
	ws2812drv_start_transfer(leds, LED_COUNT);
}



void play_lights_nyan()
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
			
			leds[i + bump] = (ws2812drv_led_t)game_colors[LED_OFF];
			leds[i + half - bump] = (ws2812drv_led_t)game_colors[LED_OFF];
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
	
	leds[margin + bump] = (ws2812drv_led_t)game_colors[LED_MAX_ON];
	leds[(half - margin - 1) + bump] = (ws2812drv_led_t)game_colors[LED_MAX_ON];
	
	
	
	for (i = GRUMBO_LED_COUNT; i < LED_COUNT; i++)
	{

		if (offset % 23)
		{
			leds[i] = (ws2812drv_led_t){ .r=0, .g=0, .b = MAX_BRIGHTNESS};
		}
		else
		{
			leds[i] = (ws2812drv_led_t)game_colors[LED_MAX_ON];
		}
	}
	
	offset++;
	ws2812drv_start_transfer(leds, LED_COUNT);
}

void play_lights_portal()
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
			.r = ((MAX_BRIGHTNESS - (i * 2)) + bump) / 2,
			.g = ((MAX_BRIGHTNESS - (i * 2)) + bump) / 4,
			.b = (half-i)/16
		};
			
	}
	
	offset++;
	ws2812drv_start_transfer(leds, LED_COUNT);
}

void play_lights_game(uint16_t dingle_pos, uint8_t buttons)
{
	uint8_t i = 0;
	uint8_t quarter = GRUMBO_LED_COUNT / 4;
	uint8_t divisor = 32;
	uint8_t b_i;
	for (; i < GRUMBO_LED_COUNT; i++)
	{
		b_i = i/quarter;
		leds[i] = (ws2812drv_led_t){game_colors[b_i].r / divisor, game_colors[b_i].g / divisor, game_colors[b_i].b / divisor};
	}	
	
	overlay_dingle_pos(dingle_pos);	
	play_lights_overlay_note_button_leds(buttons);
	ws2812drv_start_transfer(leds, LED_COUNT);
}

void play_lights_game_over()
{
	uint8_t i = 0;
	ws2812drv_led_t color;
	
	if (!(offset++ % 4))
	{
		color = (ws2812drv_led_t){.r=MAX_BRIGHTNESS, .g=0, .b=0};
	}
	else
	{
		color = (ws2812drv_led_t)game_colors[LED_OFF];
	}
	
	for (i = 0; i < LED_COUNT; i++)
	{
		leds[i] = color;
	}
	ws2812drv_start_transfer(leds, LED_COUNT);
}

void play_lights_won_easy_game()
{
	
	uint8_t i = 0;
	uint8_t quarter = GRUMBO_LED_COUNT / 4;
	uint8_t b_i;
	for (; i < GRUMBO_LED_COUNT; i++)
	{
		b_i = i/quarter;
		b_i += offset;
		b_i %= 4;
			
		leds[i] = game_colors[b_i];
	}
	
	offset++;
	
	leds[GRUMBO_LED_COUNT] = game_colors[BUTTON_0];
	leds[GRUMBO_LED_COUNT + 1] = game_colors[BUTTON_0];

	leds[GRUMBO_LED_COUNT + 2] = game_colors[BUTTON_1];
	leds[GRUMBO_LED_COUNT + 3] = game_colors[BUTTON_1];

	leds[GRUMBO_LED_COUNT + 4] = game_colors[BUTTON_2];
	leds[GRUMBO_LED_COUNT + 5] = game_colors[BUTTON_2];

	leds[GRUMBO_LED_COUNT + 6] = game_colors[BUTTON_3];
	leds[GRUMBO_LED_COUNT + 7] = game_colors[BUTTON_3];


	ws2812drv_start_transfer(leds, LED_COUNT);
}

void play_lights_easter_egg(uint16_t dingle_pos, uint8_t buttons)
{
		uint8_t i = 0;
		uint8_t half = GRUMBO_LED_COUNT / 2;		
		
		for (;i<LED_COUNT; i++)
		{
			leds[i] = (ws2812drv_led_t){.r = MAX_BRIGHTNESS / 2, .g = MAX_BRIGHTNESS / 4, .b = 0};			
		}
		
		if (!(offset % GRUMBO_LED_COUNT))
		{
			leds[0] = game_colors[LED_MAX_ON];
		}
		else if (!(offset % half))
		{
			//bottom center
			leds[half] = game_colors[LED_MAX_ON];
		}		
		else
		{
			leds[half - (offset % half)] = game_colors[LED_MAX_ON];
			leds[half + (offset % half)] = game_colors[LED_MAX_ON];
		}
		
		offset++;
		
		overlay_dingle_pos(dingle_pos);
		play_lights_overlay_note_button_leds(buttons);
		ws2812drv_start_transfer(leds, LED_COUNT);
}

void play_lights_easter_egg_intro()
{
	uint8_t i = 0;
	
	for (;i<GRUMBO_LED_COUNT; i++)
	{
		leds[i] = (ws2812drv_led_t){.r = 0, .g = MAX_BRIGHTNESS, .b = 0};
		
	}

	for (;i < LED_COUNT; i++)
	{
		if (i%2)
		{
			leds[i] = (ws2812drv_led_t){.r = MAX_BRIGHTNESS, .g = 0, .b = MAX_BRIGHTNESS};
		}
		else
		{
			leds[i] = (ws2812drv_led_t){.r = MAX_BRIGHTNESS, .g = MAX_BRIGHTNESS, .b = MAX_BRIGHTNESS};
		}
	}

	offset += 3;

	leds[offset % GRUMBO_LED_COUNT] =(ws2812drv_led_t){.r = MAX_BRIGHTNESS, .g = MAX_BRIGHTNESS, .b = 0};
	leds[(offset + 1) % GRUMBO_LED_COUNT] =(ws2812drv_led_t){.r = MAX_BRIGHTNESS, .g = MAX_BRIGHTNESS, .b = 0};
	leds[(offset + 2) % GRUMBO_LED_COUNT] =(ws2812drv_led_t){.r = MAX_BRIGHTNESS, .g = MAX_BRIGHTNESS, .b = 0};	
		
	ws2812drv_start_transfer(leds, LED_COUNT);
}