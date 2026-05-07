/*
 * flappy.h
 *
 *  Created on: May 3, 2026
 *      Author: Zelowi
 */

#ifndef INC_FLAPPY_H_
#define INC_FLAPPY_H_
#include <stdint.h>
#include"stm32f407xx.h"

#define PIPE_COUNT 4


typedef struct{
	uint8_t x;
	uint8_t y;
}Bird_t;

typedef struct{
	uint8_t x;
	uint8_t gap;
}Pipe_t;



void DrawBird(Bird_t* bird,uint8_t buffer[1025]);
void DrawPipe(Pipe_t pipes[PIPE_COUNT],uint8_t buffer[1025]);
void BirdFall();
void BirdJump();



uint8_t ReadButton();

int HandleInput(uint8_t buttonState);

uint8_t Collision(Bird_t* bird,Pipe_t pipes[PIPE_COUNT]);


void MovePipes(Pipe_t pipes[PIPE_COUNT],uint8_t buffer[1025]);

void MoveBird(Bird_t* bird,uint8_t buffer[1025],int direction);


extern Pipe_t pipes[PIPE_COUNT];
void Pipes_Init(Pipe_t pipes[PIPE_COUNT]);

#endif /* INC_FLAPPY_H_ */
