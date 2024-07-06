/*
 * config.h
 *
 * Created: 16/06/2024 14:28:08
 *  Author: Douglas Pasini
 */ 


#ifndef CONFIG_H_
#define CONFIG_H_

//Defini��o das sa�das que enviam sinais para as matrizes
#define CS (1<<PD2)
#define CLK (1<<PD1)
#define DATA (1<<PD0)

//Defini��o das entradas (bot�es)
#define B_RIGHT (PINB&(1<<7))
#define B_LEFT (PINB&(1<<6))
#define B_UP (PIND&(1<<3))
#define B_DOWN (PIND&(1<<4))
#define B_ACTION (PIND&(1<<5))
#define B_START (PIND&(1<<6))
#define B_EXIT (PIND&(1<<7))
#define B_PAUSE (PINB&(1<<0))

//Defini��o da frequencia do microcontrolador
#define F_CPU 1000000 

//Defini��o dos estados e jogos
#define N_GAMES 6 //N�o considera o teste como um jogo

#define TETRIS 0
#define PONG 1
#define SNAKE 2
#define BREAKOUT 3
#define MINESWEEPER 4
#define SPACEINVADERS 5
#define TEST 6

#define MENU 0
#define RUNNING 1
#define GAMEOVER 2
#define PAUSE 3

#define DO 19
#define RE 42
#define MI 66
#define FA 77
#define SOL 97
#define LA 113
#define SI 130

#endif /* CONFIG_H_ */