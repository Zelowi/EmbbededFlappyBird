/*
 * flappy.c
 *
 *  Created on: May 3, 2026
 *      Author: Zelowi
 */
#include "ssd1306.h"
#include <stdlib.h>
#include "flappy.h"
#include "stm32f407xx_gpio.h"
#include"stm32f407xx.h"





void DrawBird(Bird_t* bird,uint8_t buffer[1025]){
	for (int i = 0; i < 3;i++){
		for(int j = 0;j < 3;j++){
			SSD1306_DrawPixel(bird->x + j,bird->y + i,buffer);
		}
	}
}



void DrawPipe(Pipe_t pipes[PIPE_COUNT],uint8_t buffer[1025]){
	for(int k = 0; k < PIPE_COUNT; k++){
	for (int i = 0; i < pipes[k].gap;i++){
			for(int j = 0;j < 3;j++){
				SSD1306_DrawPixel(pipes[k].x + j,i,buffer);
			}
		}
	for (int i = pipes[k].gap + 20 ;i < 64;i++){
				for(int j = 0;j < 3;j++){
					SSD1306_DrawPixel(pipes[k].x + j,i,buffer);
				}
			}
	}
}
void Pipes_Init(Pipe_t pipes[PIPE_COUNT]){
	//srand(TIM2->CNT);

	for(int i = 0; i < PIPE_COUNT; i++)
	{
	    pipes[i].x = 40 + i * 25;
	    pipes[i].gap = rand() % 35 + 10;
	}
}


void MovePipes(Pipe_t pipes[PIPE_COUNT],uint8_t buffer[1025]){
	for (int i = 0;i < PIPE_COUNT;i++){
		pipes[i].x -= 1;
		if(pipes[i].x < 10){
			pipes[i].x = 110;
			pipes[i].gap = rand() % 35 + 10;
		}
	}
	DrawPipe(pipes,buffer);
}


void MoveBird(Bird_t* bird,uint8_t buffer[1025],int direction){
	/*if(direction >= 0){
	bird->y -= 1;
	}
	else{
		bird->y += 1;
		direction += 1;
	}*/
	bird->y += direction - 1;
	DrawBird((Bird_t*)bird,buffer);
}

uint8_t ReadButton()
{
    static uint8_t prev = 0;

    uint8_t state = GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NUMBER_0);

    uint8_t result = 0;

    if(state && !prev)
    {
        result = 1;
    }

    prev = state;

    return result;
}

int HandleInput(uint8_t buttonState){
	if(buttonState == 0){
		return 0;
	}
	else{
		return 8;
	}
}


uint8_t Collision(Bird_t* bird, Pipe_t pipes[PIPE_COUNT])
{
    for(int i = 0; i < PIPE_COUNT; i++)
    {
        uint8_t bird_left   = bird->x;
        uint8_t bird_right  = bird->x + 2;
        uint8_t bird_top    = bird->y;
        uint8_t bird_bottom = bird->y + 2;

        uint8_t pipe_left  = pipes[i].x;
        uint8_t pipe_right = pipes[i].x + 2;

        uint8_t gap_top    = pipes[i].gap;
        uint8_t gap_bottom = pipes[i].gap + 20;

        if(bird_right >= pipe_left && bird_left <= pipe_right)
        {
            if(bird_top < gap_top || bird_bottom > gap_bottom)
            {
                return 0; // collision
            }
        }
    }

    return 1; // no collision
}
