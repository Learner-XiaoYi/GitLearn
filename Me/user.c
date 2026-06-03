#include "user.h"

void led_disp(uint16_t ueled)
{
	GPIOC -> ODR = ~(ueled << 8);
	
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIO_PIN_RESET);
}

void led_show(void)
{
	uint16_t text = 0x00;
	
	led_disp(text);
}

int count;
int feng;
char text[20];
void lcd_text(void)
{
	sprintf(text,"        LCD        ");
	LCD_DisplayStringLine(Line0,(uint8_t *)text);
	
	sprintf(text," count:%d            ",count);
	LCD_DisplayStringLine(Line1,(uint8_t *)text);
	
	sprintf(text," fre:%d            ",fre);
	LCD_DisplayStringLine(Line2,(uint8_t *)text);
	
	sprintf(text," adc1 R38:%1.2f              ",adc1);
	LCD_DisplayStringLine(Line3,(uint8_t *)text);
	
	sprintf(text," adc2:R37 %1.2f              ",adc2);
	LCD_DisplayStringLine(Line4,(uint8_t *)text);
	
	sprintf(text," feng:%d            ",feng);
	LCD_DisplayStringLine(Line5,(uint8_t *)text);
}

void lcd_show(void)
{
	sprintf(text,"        LCD        ");
	LCD_DisplayStringLine(Line0,(uint8_t *)text);
	
	sprintf(text," count:%d            ",count);
	LCD_DisplayStringLine(Line1,(uint8_t *)text);
}

uint8_t key_read(void)
{
	uint8_t text = 0;
	
	if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0) == RESET){text = 1;}
	if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1) == RESET){text = 2;}
	if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_2) == RESET){text = 3;}
	if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0) == RESET){text = 4;}
	
	return text;
}

typedef enum
{
	KEY_init,
	KEY_watt_down,
	KEY_down,
	KEY_long_down_D,
	KEY_long_down
}KEY_STATE;

KEY_STATE key_state = KEY_init;
uint16_t key_tick;
void key_show(void)
{
	uint8_t id = key_read();
	
	uint32_t key_tick_last;
	if(id == 0)
	{
		if(uwTick - key_tick_last >= 20)
		{
			key_state = KEY_watt_down;
			key_tick = 0;
		}
	}
	key_tick_last = uwTick;
	
	switch (key_state)
	{
		case KEY_watt_down:
		{
			if(id != 0)
			{
			
				key_state = KEY_down;
				key_tick = 0;
			}
			else{key_state = KEY_watt_down;key_tick = 0;}
			break;
		}
		
		case KEY_down:
		{
			if(key_tick >= 2)
			{
				if(id != 0)
				{
					if(id == 1){count ++;}
					if(id == 2){count --;}
					if(id == 3){printf("3");}
					if(id == 4){printf("4");}
					
					key_state = KEY_long_down_D;
					key_tick = 0;
				}
				else{key_state = KEY_watt_down;key_tick = 0;}
			}
			break;
		}
		
		case KEY_long_down_D:
		{
			if(key_tick >= 30)
			{
				if(id != 0)
				{
					if(id == 1){count ++;}
					if(id == 2){count --;}
					if(id == 3){printf("3");}
					if(id == 4){printf("4");}
					
					key_state = KEY_long_down;
					key_tick = 0;
				}
				else{key_state = KEY_watt_down;key_tick = 0;}
			}
			break;
		}
		
		case KEY_long_down:
		{
			if(key_tick >= 10)
			{
				if(id != 0)
				{
					if(id == 1){count ++;}
					if(id == 2){count --;}
					if(id == 3){printf("3");}
					if(id == 4){printf("4");}
					
					key_tick = 0;
				}
				else{key_state = KEY_watt_down;key_tick = 0;}
			}
			break;
		}
		
	}
	
	
}
