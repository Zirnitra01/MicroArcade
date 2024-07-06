/*
 * move.c
 *
 * Created: 06/06/2024 14:00:55
 *  Author: Douglas Pasini
 */ 


#include "move.h"

//As seguintes funções são responsáveis por movimentar os vetores nas direções indicadas
void up(unsigned int *vet){
	vet[9]--;
	for(int i=0; i<8; i++){
		vet[i] = vet[i]<<1;
	}
}
void down(unsigned int *vet){
	vet[9]++;
	for(int i=0; i<8; i++){
		vet[i] = vet[i]>>1;
	}
}
void right(unsigned int *vet){
	vet[8]++;
	unsigned int temp;
	temp = vet[7];
	for(int i=7; i>0; i--){vet[i] = vet[i-1];}
	vet[0] = temp;
}
void left(unsigned int *vet){
	vet[8]--;
	unsigned int temp;
	temp = vet[0];
	for(int i=0; i<7; i++){vet[i] = vet[i+1];}
	vet[7] = temp;
}

//Responsável pela movimentação das peças rotacionadas do tetris
void deslAuto(unsigned int *vet, unsigned int *vetRef, int x, int y){
	if(x>vet[8]){
		for(int i=vet[8]; i<x; i++){
			if(colisaoDireitaWall(vet) == 0 && colisaoDireitaRef(vet,vetRef) == 0){right(vet);}
		}
	}
	if(x<vet[8]){
		for(int i=vet[8]; i>x ;i--){
			if(colisaoEsquerdaWall(vet) == 0 && colisaoEsquerdaRef(vet,vetRef) == 0){left(vet);}
		}
	}
	if(y>vet[9]){
		for(int i=vet[9]; i<y; i++){
			if(colisaoInferiorWall(vet) == 0 && colisaoInferiorRef(vet,vetRef) == 0){down(vet);}
		}
	}
	if(y<vet[9]){
		for(int i=vet[9]; i>y; i--){
			if(colisaoSuperiorWall(vet) == 0 && colisaoSuperiorRef(vet,vetRef) == 0){up(vet);}
		}
	}
}

//Responsável pela movimentação da bola nos jogos pong e breakout
void ballMov(char pX, char pY, char dirX, char dirY,unsigned int *vet){
	if(dirX==1){
		for(int i=0;i<pX;i++){right(vet);}
	}
	if(dirX==0){
		for(int i=0;i<pX;i++){left(vet);}
	}
	if(dirY==1){
		for(int i=0;i<pY;i++){down(vet);}
	}
	if(dirY==0){
		for(int i=0;i<pY;i++){up(vet);}
	}
}

//Move os segmentos da cobra no snake
void moveSnake(unsigned int *vet, int nSeg, int dir, int sent, unsigned char anterior[][2]){
	//vet -> vetor em que a cobrinha se move
	//nSeg -> número de segmentos da cobrinha
	//dir -> 0 para X e 1 para Y
	//sent -> 1 para baixo ou direita e -1 para cima ou esquerda
	//anterior -> vetor de posições anteriores dos segmentos
	for(int i=0; i<nSeg; i++){
		desligaLED(vet,anterior[i][0],anterior[i][1]);
	}
	for (int i=nSeg; i>0; i--){
		anterior[i][0] = anterior[i-1][0];
		anterior[i][1] = anterior[i-1][1];
	}
	anterior[0][dir]+=sent;
	for(int i=0; i<nSeg; i++){
		ligaLED(vet,anterior[i][0],anterior[i][1]);
	}
}
