#ifndef CONFIG_H_
#define CONFIG_H_

//Definição das saídas que enviam sinais para as matrizes
#define CS (1<<PD2)
#define CLK (1<<PD1)
#define DATA (1<<PD0)

//Definição das entradas (botões)
#define B_RIGHT (PINB&(1<<7))
#define B_LEFT (PINB&(1<<6))
#define B_UP (PIND&(1<<3))
#define B_DOWN (PIND&(1<<4))
#define B_ACTION (PIND&(1<<5))
#define B_START (PIND&(1<<6))
#define B_EXIT (PIND&(1<<7))
#define B_PAUSE (PINB&(1<<0))

//Definição da frequencia do microcontrolador
#define F_CPU 1000000 

//Definição dos estados e jogos
#define N_GAMES 6 //Não considera o teste como um jogo

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

//Definição dos tempos para as frequências da saída de áudio
#define DO 19
#define DOs 31  
#define RE 43
#define REs 55
#define MI 66
#define FA 77
#define FAs 87
#define SOL 97
#define SOLs 106
#define LA 114
#define LAs 122
#define SI 129

#endif /* CONFIG_H_ */
