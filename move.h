/*
 * move.h
 *
 * Created: 06/06/2024 14:01:08
 *  Author: Douglas Pasini
 */ 

#ifndef MOVE_H_
#define MOVE_H_

#include <avr/io.h>
#include "collider.h"
#include "vector.h"

//As seguintes funções são responsáveis por movimentar os vetores nas direções indicadas
void up(unsigned int *vet);
void down(unsigned int *vet);
void right(unsigned int *vet);
void left(unsigned int *vet);

//Responsável pela movimentação das peças rotacionadas do tetris
void deslAuto(unsigned int *vet, unsigned int *vetRef, int x, int y);

//Responsável pela movimentação da bola nos jogos pong e breakout
void ballMov(char pX, char pY, char dirX, char dirY,unsigned int *vet);

//Move os segmentos da cobra no snake
void moveSnake(unsigned int *vet, int nSeg, int dir, int sent, unsigned char anterior[][2]);

#endif /* MOVE_H_ */