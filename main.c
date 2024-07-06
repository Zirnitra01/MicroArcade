//Inclusão das bibliotecas utilizadas
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "Lib/collider.h"
#include "Lib/move.h"
#include "Lib/vector.h"
#include "Lib/config.h"
#include "Lib/matrix.h"
#include <util/delay.h>

//Definição dos vetores que são usados nos jogos
//As duas ultimas casas dos vetores com [10] são as posições x(horizontal) e y(vertical) em relação a matriz
unsigned int playerPong[2][10] = {{0,0,0x4,0x4,0x4,0,0,0,0,0},{0,0x4,0x4,0x4,0x4,0x4,0,0,0,0}};
unsigned int enemyPong[10] = {0,0,0,0,0x1000,0x1000,0x1000,0,6,0};
	
unsigned int playerBreakout[2][10] = {{0,0,0x1,0x1,0x1,0,0,0,4,16},{0,0x1,0x1,0x1,0x1,0x1,0,0,0,0}};
	
unsigned int ball[10] = {0,0,0,0,0x80,0,0,0,5,9};
	
unsigned int snakeStartVet[10] = {0,0,0,0,0x80,0,0,0,5,9};
unsigned int snakeHead[10] = {0};
unsigned int snakeVet[10] = {0};	
unsigned char posAnterior[128][2] = {0};

unsigned int mapPong[8] = {0x2002,0x2002,0x2002,0x2002,0x2002,0x2002,0x2002,0x2002};
unsigned int mapBreakout[8] = {0x7F80,0x7F80,0x7F80,0x7F80,0x7F80,0x7F80,0x7F80,0x7F80};

//Este vetor armazena as imagens apresentadas no menu dos jogos.
unsigned int menuImg[8][8] = {
	{0x801B,0xF,0xF,0x40E,0xC02,0x401,0xF,0x7},
	{0x6002,0xE006,0x2106,0x2006,0x3002,0x3003,0x3003,0x2003},
	{0,0x3C00,0xA400,0x24C8,0x2480,0x480,0x780,0},
	{0x3FC0,0x3FE0,0x3FE1,0xBFC1,0x3F81,0x3F08,0x3FC0,0x3FE0},
	{0x6E14,0x48D1,0x5A8B,0x5AE8,0xC22A,0x7EBA,0x4003,0x5FF5}};

//Peças para o Tetris
unsigned int fig[7][4][10] = {
	{{0,0,0x4000,0xC000,0x4000,0,0,0,4,2},{0,0,0,0xE000,0x4000,0,0,0,4,2},{0,0,0x4000,0x6000,0x4000,0,0,0,4,2},{0,0,0x4000,0xE000,0,0,0,0,4,2}},//"T"
	{{0,0,0x4000,0x4000,0xC000,0,0,0,4,2},{0,0,0,0xE000,0x2000,0,0,0,4,2},{0,0,0x6000,0x4000,0x4000,0,0,0,4,2},{0,0,0x8000,0xE000,0,0,0,0,4,2}},//"L"
	{{0,0,0xC000,0x4000,0x4000,0,0,0,4,2},{0,0,0,0xE000,0x8000,0,0,0,4,2},{0,0,0x4000,0x4000,0x6000,0,0,0,4,2},{0,0,0x2000,0xE000,0,0,0,0,4,2}},//"J"
	{{0,0,0x8000,0xC000,0x4000,0,0,0,4,2},{0,0,0,0x6000,0xC000,0,0,0,4,2},{0,0,0x4000,0x6000,0x2000,0,0,0,4,2},{0,0,0x6000,0xC000,0,0,0,0,4,2}},//"Z"
	{{0,0,0x4000,0xC000,0x8000,0,0,0,4,2},{0,0,0,0xC000,0x6000,0,0,0,4,2},{0,0,0x2000,0x6000,0x4000,0,0,0,4,2},{0,0,0xC000,0x6000,0,0,0,0,4,2}},//"S"
	{{0,0,0x2000,0x2000,0x2000,0x2000,0,0,4,3},{0,0,0,0x7800,0,0,0,0,4,3},{0,0x2000,0x2000,0x2000,0x2000,0,0,0,4,3},{0,0,0,0xF000,0,0,0,0,4,3}},//"I"
	{{0,0,0,0xC000,0xC000,0,0,0,4,2},{0,0,0,0xC000,0xC000,0,0,0,4,2},{0,0,0,0xC000,0xC000,0,0,0,4,2},{0,0,0,0xC000,0xC000,0,0,0,4,2}}};//"O"

unsigned int res[8] = {0};
unsigned int pec[10];
unsigned int imp[8] = {0};
unsigned int endGame[8] = {0};

//Ordem das peças para o tetris
unsigned int lista[30] = {3,2,1,6,4,0,3,2,5,1,0,6,4,3,5,2,0,1,4,6,3,5,2,0,4,1,6,3,5,2};//Talvez eu remova a lista caso eu use os valores aleatórios

//Definição das variáveis que são usados nos jogos
//Algumas delas são reaproveitadas em outros jogos para economizar memória 

//O aux1 atribui alguns valores no início dos jogos
char aux1 = 0;
char aux2 = 1;

int gameMode = 0;
int gameState = GAMEOVER;

int dirX = 1;
int dirY = 1;
int posX = 1;
int posY = 1;

int contRot = 0;
int segment = 0;
int moveTimer = 0;
int tickSpeed = 0;
int tick = 0;
int maxTick = 100;

int contReg = 0;
int maxContReg = 0;

int numList = 0;
int maxMoveTime = 0;
char move = 0;

char scorePlayer = 1;
char scoreEnemy = 1;
int pointTimer = 0;

//Responsável por apagar as linhas completas do tetris
void apagarLinha(unsigned int *vet){
	//*vet -> recebe o vetor das peças que já cairam
	unsigned int vet_temp[8];	
	unsigned int temp = vet[0]&vet[1]&vet[2]&vet[3]&vet[4]&vet[5]&vet[6]&vet[7];
	unsigned int cont = 0;			
	if(temp != 0){
		for(int i=0; i<16; i++){							
			if((temp&(1<<i)) !=0 ){cont = i;break;}
		}			
		for(int i=0; i<8; i++){vet[i]^=(1<<cont);} //Apaga a linha completa
		atribuirVetores(vet_temp,vet);	
		if(temp != 0){
			temp = (temp<<1);
			unsigned int temp_down = ((temp-1)&(~temp));
			unsigned int temp_up = ~temp_down;
			for(int i=0; i<8; i++){vet[i]&=temp_up;}
			for(int i=0; i<8; i++){vet_temp[i]&=temp_down;}
			down(vet);			
			unirVetores(vet, vet_temp,vet);
		}		
	}
}

void gerarComida(unsigned int *vetComida, int maxX, int maxY) {
	// Gera coordenadas aleatórias para a comida
	do{
		posX = (rand()%(maxX+1));
		posY = (rand()%(maxY+1));
	}while(verificarLED(snakeVet,posX,posY)==1);
	// Liga o LED nas coordenadas geradas
	ligaLED(vetComida,posX,posY);
}

//Faz uma animação quando inicia ou perde os jogos
void gameOver(){
	limparVetores(endGame,8);
	for(int i=0; i<16; i++){
		_delay_ms(50);
		for(int j=0; j<8; j++){
			endGame[j]|=(1<<i);
		}
		mandaImagem(endGame);
	}
	//Limpa os vetores para poderem ser usados novamente.
	limparVetores(endGame,8);
	limparVetores(res,8);
	limparVetores(imp,8);
	limparVetores(pec,10);
	limparVetores(snakeVet,10);
	limparVetores(snakeHead,10);
	for(int i=0; i<2; i++){
		for(int j=0; j<128; j++){
			posAnterior[j][i] = 0;
		}
	}
	gameState = MENU;	
	aux1 = 0;
}

//As proximas funções se tratam dos jogos em si
void tetris(){
	if(aux1 == 0){ 
		aux1 = 1;
		atribuirVetores(pec,fig[lista[numList]][contRot]);
		for(int i=0; i<5 && colisaoSuperiorWall(pec)==0; i++){up(pec);}
		posX = 0;
		posY = 0;
		maxTick = 150;
		maxMoveTime = 900;
		maxContReg = 1000;
	}
	
	//Inprime os vetores na matriz
	unirVetores(res,pec,imp);
	mandaImagem(imp);
	limparVetores(imp,8);
	
	//Acelera a peça que está em queda
	if(B_DOWN == 0){maxMoveTime = 200;}
	else{maxMoveTime = 900;}
	
	//Após um certo tempo, salva as peças que cairam 
	if(contReg >= maxContReg){
		contReg = 0;
		numList++;
		if(numList == 15 && maxTick > 125){maxTick-=2;}
		if(numList >= 29){numList = 0;}
		unirVetores(pec,res,res);
		atribuirVetores(pec,fig[lista[numList]][contRot]);
		for(int i=0; i<4; i++){
			if(colisaoSuperiorWall(pec) == 0){up(pec);} //Move as peças geradas para o topo
		}
	}
	
	//Verifica e apaga as linhas completas
	apagarLinha(res);
	
	//Faz a movimentação lateral das peças em queda
	if(B_LEFT == 0 && colisaoEsquerdaWall(pec) == 0 && colisaoEsquerdaRef(pec,res) == 0){
		left(pec);
	}	
	if(B_RIGHT == 0 && colisaoDireitaWall(pec) == 0 && colisaoDireitaRef(pec,res) == 0){
		right(pec);
	}
	
	//Salva a posição do centro das peças 
	posX=pec[8];
	posY=pec[9];	
	
	//Rotaciona as peças em queda
	if(B_ACTION == 0){
		contRot++;
		if(contRot > 3){contRot = 0;}
		atribuirVetores(pec,fig[lista[numList]][contRot]);
		deslAuto(pec,res,posX,posY);
	}
	
	//Verifica se o jogador perdeu
	if(colisaoSuperiorWall(res) == 1){
		gameState = GAMEOVER;
	}
}

void pong(){
	if(aux1 == 0){
		aux1 = 1;
		posX = 1;
		posY = 1;
		dirY = 0;
		dirX = 1;
		aux2 = 1;
		atribuirVetores(res,mapPong);
		atribuirVetores(pec,ball);
		maxTick = 130;
		maxMoveTime = 155;
	}
	
	limparVetores(imp,8);
	unirVetores(pec,res,imp);
	unirVetores(imp,enemyPong,imp);
	unirVetores(imp,playerPong[0],imp);
	unirVetores(imp,pec,imp);
	mandaImagem(imp);
	
	if(aux2 == 0){
		ballMov(posX,posY,dirX,dirY,pec);
	}
	
	if(colisaoEsquerdaWall(pec) == 1 || colisaoDireitaWall(pec) == 1){
		dirX^=1;
	}
	if(colisaoInferiorRef(pec,playerPong[0]) != 0 || colisaoSuperiorRef(pec,enemyPong) != 0){
		dirY^=1;
		if(maxTick>110){maxTick--;}		
	}
	
	if(scorePlayer >= 9 || scoreEnemy >= 9){
		gameState = GAMEOVER;
		scorePlayer = 0;
		scoreEnemy = 0;
	}
	
	if(colisaoInferiorRef(pec,mapPong) == 1){
		atribuirVetores(pec,ball);
		ligaLED(res,scoreEnemy,2);
		scoreEnemy++;
		aux2 = 1;
		maxTick = 120;
	}
	
	if(colisaoSuperiorRef(pec,mapPong) == 1){
		atribuirVetores(pec,ball);
		ligaLED(res,9-scorePlayer,16);
		scorePlayer++;
		aux2 = 1;
		maxTick = 120;		
	}
	
	if(B_RIGHT == 0 && colisaoDireitaWall(playerPong[0]) == 0){
		right(playerPong[0]);
		right(playerPong[1]);
	}
	if(B_LEFT == 0 && colisaoEsquerdaWall(playerPong[0]) == 0){
		left(playerPong[0]);
		left(playerPong[1]);
	}
	
	if(pec[8]>enemyPong[8] && colisaoDireitaWall(enemyPong) == 0 && move == 1){
		move = 0;
		right(enemyPong);
	}
	if(pec[8]<enemyPong[8] && colisaoEsquerdaWall(enemyPong) == 0 && move == 1){
		move = 0;
		left(enemyPong);
	}
}

void snake(){
	if(aux1 == 0){
		aux1 = 1;
		segment = 4;
		dirX = 2;
		dirY = 0;		 
		maxMoveTime = 50;
		atribuirVetores(snakeVet,snakeStartVet);
		atribuirVetores(snakeHead,snakeStartVet);
		posAnterior[0][0] = snakeVet[8];
		posAnterior[0][1] = snakeVet[9];
		maxTick = 200;		
	}	
	
	limparVetores(imp,8);
	unirVetores(snakeVet,pec,imp);	
	mandaImagem(imp);	
	
	if(B_RIGHT == 0 && B_UP != 0 && B_DOWN != 0 && dirY != 2){
		dirX = 1;
		dirY = 2;
	}
	if(B_LEFT == 0 && B_UP != 0 && B_DOWN != 0 && dirY != 2){
		dirX = 0;
		dirY = 2;
	}
	if(B_RIGHT != 0 && B_LEFT != 0 && B_UP == 0 && dirX != 2){
		dirX = 2;
		dirY = 1;
	}
	if(B_RIGHT != 0 && B_LEFT != 0 && B_DOWN == 0 && dirX != 2){
		dirX = 2;
		dirY = 0;
	}	

	//Verifica se o jogador pegou a comida
	if(snakeHead[8] == posX && snakeHead[9] == posY){
		segment++;
		desligaLED(pec,posX,posY);
	}
	
	//Essse if é para verificar se o jogador perdeu
	if(snakeHead[8] > 8 || snakeHead[8] < 1 || snakeHead[9] > 16 || snakeHead[9] < 1 || (colisaoEsquerdaRef(snakeHead,snakeVet) == 1 && dirX == 0) || (colisaoDireitaRef(snakeHead,snakeVet) == 1 && dirX == 1) || (colisaoSuperiorRef(snakeHead,snakeVet) == 1 && dirY == 1) || (colisaoInferiorRef(snakeHead,snakeVet) == 1 && dirY == 0)){
		gameState = GAMEOVER;
	}
	//Testar a posição do snakeHead para não dar problema	
	if(dirY == 0){moveSnake(snakeVet,segment,1,1,posAnterior);down(snakeHead);}//down
	if(dirY == 1){moveSnake(snakeVet,segment,1,-1,posAnterior);up(snakeHead);}//up
	if(dirX == 0){moveSnake(snakeVet,segment,0,-1,posAnterior);left(snakeHead);}//left
	if(dirX == 1){moveSnake(snakeVet,segment,0,1,posAnterior);right(snakeHead);}//right
		
	//Verifica se é necessario gerar a proxima comida
	if(vetorVazio(pec) == 0){gerarComida(pec,8,16);}	
	
	//Verifica se o jogador ganhou
	if(segment == 128){}
}

void breakout(){
	if(aux1 == 0){
		aux1 = 1;
		posX = 1;
		posY = 1;
		dirY = 0;
		dirX = 0;
		atribuirVetores(pec,ball);
		for(int i=0; i<3; i++){down(pec);}
		for(int j=0; j<8; j++){res[j] = 0x7F00;}
		maxTick = 130;
	}
	
	limparVetores(imp,8);
	unirVetores(pec,res,imp);
	unirVetores(imp,playerBreakout[0],imp);
	unirVetores(imp,pec,imp);
	mandaImagem(imp);
	
	if(colisaoSuperiorRef(pec,res) != 0){
		desligaLED(res, pec[8], pec[9]-1);
		dirY^=1;
	}
	if(colisaoDireitaSuperiorRef(pec,res) != 0 && dirY == 0 && dirX == 1){
		desligaLED(res, pec[8]+1, pec[9]-1);
		dirX^=1;
		dirY^=1;
	}
	if(colisaoEsquerdaSuperiorRef(pec,res) != 0 && dirY == 0 && dirX == 0){
		desligaLED(res, pec[8]-1, pec[9]-1);
		dirX^=1;
		dirY^=1;
	}
	if(colisaoEsquerdaRef(pec,res) !=0 && dirX == 0){
		desligaLED(res, pec[8]-1, pec[9]);		
		dirX^=1;
	}
	if(colisaoDireitaRef(pec,res) !=0 && dirX == 1){
		desligaLED(res, pec[8]+1, pec[9]);
		dirX^=1;
	}
	
	//Ainda falta adicionar as colisões nas outras direções e fazer o jogador perder quando a bolinha tocar a parte inferior	
		
	ballMov(posX,posY,dirX,dirY,pec);
	
	if(colisaoEsquerdaWall(pec) == 1 || colisaoDireitaWall(pec) == 1){
		dirX^=1;
	}
	if(colisaoInferiorRef(pec,playerBreakout[0]) !=0 || colisaoSuperiorWall(pec) != 0){
		dirY^=1;
	}
	if(colisaoInferiorWall(pec) != 0){
		dirY^=1;
	}
		
	
	if(B_RIGHT == 0 && colisaoDireitaWall(playerBreakout[0]) == 0){
		right(playerBreakout[0]);
		right(playerBreakout[1]);
	}
	if(B_LEFT == 0 && colisaoEsquerdaWall(playerBreakout[0]) == 0){
		left(playerBreakout[0]);
		left(playerBreakout[1]);
	}	
}

//Preciso trocar a imagem dele no menu
void minesWeeper(){
	if(aux1 == 0){
		contRot = 1;
		aux1 = 1;
		atribuirVetores(pec,ball);
		for(int i=0; i<50; i++){gerarComida(res,8,15);}
		for(int i=1; i<9; i++){desligaLED(res,i,1);}
		for(int j=0; j<8; j++){endGame[j] = 0x7FFF;}
		maxMoveTime = 300; //Para piscar a posição do cursor
		maxTick = 150;
	}
	limparVetores(imp,8);
	atribuirVetores(imp,endGame);
	mandaImagem(imp);

	if(B_UP == 0 && pec[9] > 2){
		if(aux2 == 1){ligaLED(endGame,pec[8],pec[9]);}
		if(aux2 == 0){desligaLED(endGame,pec[8],pec[9]);}
		up(pec);
		aux2 = verificarLED(endGame,pec[8],pec[9]);
	}
	if(B_DOWN == 0 && pec[9] < 16){
		if(aux2 == 1){ligaLED(endGame,pec[8],pec[9]);}
		if(aux2 == 0){desligaLED(endGame,pec[8],pec[9]);}
		down(pec);
		aux2 = verificarLED(endGame,pec[8],pec[9]);
	}
	if(B_RIGHT == 0 && pec[8] < 8){
		if(aux2 == 1){ligaLED(endGame,pec[8],pec[9]);}
		if(aux2 == 0){desligaLED(endGame,pec[8],pec[9]);}
		right(pec);
		aux2 = verificarLED(endGame,pec[8],pec[9]);
	}
	if(B_LEFT == 0 && pec[8] > 1){
		if(aux2 == 1){ligaLED(endGame,pec[8],pec[9]);}
		if(aux2 == 0){desligaLED(endGame,pec[8],pec[9]);}
		left(pec);
		aux2 = verificarLED(endGame,pec[8],pec[9]);
	}
	
	if(colisaoSuperiorRef(pec,res) == 1){contRot++;}
	if(colisaoInferiorRef(pec,res) == 1){contRot++;}
	if(colisaoDireitaRef(pec,res) == 1){contRot++;}
	if(colisaoEsquerdaRef(pec,res) == 1){contRot++;}
	
	if(colisaoDireitaSuperiorRef(pec,res) == 1){contRot++;}
	if(colisaoDireitaInferiorRef(pec,res) ==1 ){contRot++;}
	if(colisaoEsquerdaSuperiorRef(pec,res) == 1){contRot++;}
	if(colisaoEsquerdaInferiorRef(pec,res) == 1){contRot++;}
	
	for(int i=1; i<9; i++){
		desligaLED(endGame,i,1);
	}
	for(int i=1; i<contRot; i++){
		ligaLED(endGame,i,1);
	}
	
	if(move == 1){ligaLED(endGame,pec[8],pec[9]);}
	if(move == 0){desligaLED(endGame,pec[8],pec[9]);}
	
	if(B_ACTION == 0 && verificarLED(res,pec[8],pec[9]) == 0){
		desligaLED(endGame,pec[8],pec[9]);
		aux2 = 0;
	}
	if(B_ACTION == 0 && verificarLED(res,pec[8],pec[9]) == 1){
		gameState = GAMEOVER;
	}
	//Só falta verificar se o jogador ganhou (fazer um & entre o res e o endGame)
		
	contRot = 1;
}

//Os proximos são apenas testes

//Move os segmentos dos projéteis no spaceInvaders
void moveBullet(unsigned int *vet, int nSeg, unsigned char anterior[][2]){
	//vet -> vetor em que a cobrinha se move
	//nSeg -> número de segmentos da cobrinha
	//anterior -> vetor de posições anteriores dos segmentos
	for(int i=0; i<nSeg; i++){
		desligaLED(vet,anterior[i][0],anterior[i][1]);
	}
	for (int i=nSeg; i>0; i--){
		anterior[i][0] = anterior[i-1][0];
		anterior[i][1] = anterior[i-1][1];
	}
	anterior[0][1]--;
	for(int i=0; i<nSeg; i++){
		ligaLED(vet,anterior[i][0],anterior[i][1]);
	}
}
void spaceInvaders(){
	if (aux1 == 0){
		aux1 = 1;
		posX = 0;
		posY = 0;
		maxTick = 120;
		maxMoveTime = 110;
		atribuirVetores(pec,playerBreakout[0]);
		desligaLED(pec,4,16);
		ligaLED(pec,4,15);
		contRot = 0;
	}
	
	limparVetores(imp,8);	
	unirVetores(snakeVet,pec,imp);
	mandaImagem(imp);
		
	if(B_LEFT== 0 && colisaoEsquerdaWall(pec) == 0){
		left(pec);
	}
	if(B_RIGHT== 0 && colisaoDireitaWall(pec) == 0){
		right(pec);
	}
	
	if(B_ACTION == 0){
		posAnterior[0][0] = pec[8];		
		posAnterior[0][1] = 15;		
		move = 1;
	}
	
	if(move == 1){
		moveBullet(snakeVet,1,posAnterior);		
	}	
}

//Por enquanto eu uso essa parte para testes
unsigned int stairs[2][8]={{0,0,0x2,0x2,0xA,0xA,0x2A,0x2A},{0,0x2,0x2,0xA,0xA,0x2A,0x2A,0x2A}};

//Tentei criar uma gravidade
void test(){
	if (aux1 == 0){
		aux1 = 1;
		posX = 0;
		posY = 0;
		maxTick = 120;
		maxMoveTime = 110;
		atribuirVetores(pec,ball);
		atribuirVetores(res,stairs[0]);
	}
	unirVetores(res,pec,imp);
	mandaImagem(imp);
	limparVetores(imp,8);
	
	if(B_LEFT == 0 && colisaoEsquerdaWall(pec) == 0){
		left(pec);
	}
	
	if(B_RIGHT == 0 && colisaoDireitaWall(pec) == 0){
		right(pec);
	}
	
	if(B_UP == 0 && (colisaoInferiorRef(pec,stairs[1]) != 0 || colisaoInferiorWall(pec) != 0)){
		up(pec);
		up(pec);
	}
	if(B_DOWN == 0 && colisaoInferiorWall(pec) == 0 && colisaoInferiorRef(pec,stairs[1]) != 0){
		down(pec);
	}	
}

//Uma tela inicial utilizada para escolher entre os jogos
void menu(){
	if(B_LEFT == 0){
		gameMode--;
		aux1 = 0;
	}
	if(B_RIGHT == 0){
		gameMode++;
		aux1 = 0;
	}
		
	if(gameMode > N_GAMES){gameMode = 0;}
	if(gameMode < 0){gameMode = N_GAMES;}
		
	if(aux1 == 0){
		mandaImagem(menuImg[gameMode]);	
		aux1 = 1;
	}
	
	if(B_START == 0){
		gameState = RUNNING;
		aux1 = 0;
	}
}

//Utilizado para organizar os jogos
void running(){
	if(gameMode == TETRIS){tetris();}
	if(gameMode == PONG){pong();}
	if(gameMode == SNAKE){snake();}
	if(gameMode == BREAKOUT){breakout();}
	if(gameMode == MINESWEEPER){minesWeeper();}
	if(gameMode == SPACEINVADERS){spaceInvaders();}
	if(gameMode == TEST){test();}	
	
	if(B_PAUSE == 0){
		gameState = PAUSE;
	}
}

//Para o jogo e permite o jogador voltar ao menu
void pause(){
	if(B_START == 0){
		gameState = RUNNING;
	}	
	if(B_EXIT == 0){
		gameState = GAMEOVER;
	}
}

//Incrementa variáveis de contagem em 1 milisegundo (0,001s)
ISR(TIMER0_OVF_vect){	
	TCNT0+=131;
	if(gameState == RUNNING && gameMode == TETRIS){
		moveTimer++;
		if(moveTimer>=maxMoveTime){
			moveTimer=0;
			if(colisaoInferiorWall(pec)==0 && colisaoInferiorRef(pec,res) == 0){contReg = 0; down(pec);}
		}
		if(colisaoInferiorRef(pec,res) != 0 || colisaoInferiorWall(pec) != 0){
			contReg++;
		}
	}
	if(gameState == RUNNING && gameMode == PONG){
		moveTimer++;
		if(moveTimer >= maxMoveTime){
			moveTimer = 0;
			move = 1;
		}
		if(aux2 == 1){
			pointTimer++;
			if(pointTimer >= 700){
				pointTimer = 0;
				aux2 = 0;
			}
		}
	}
	if(gameState == RUNNING && gameMode == SNAKE){}
	if(gameState == RUNNING  && gameMode == MINESWEEPER){
		moveTimer++;
		if(moveTimer >= maxMoveTime){
			moveTimer = 0;
			move^=1;
		}
	}
	if(gameState == RUNNING && gameMode == SPACEINVADERS){}
	if(gameState == RUNNING && gameMode == TEST){
		moveTimer++;
		if(moveTimer >= maxMoveTime){
			moveTimer = 0;
			if(colisaoInferiorRef(pec,res) == 0 && colisaoInferiorWall(pec) == 0){down(pec);}
		}
	}
	//Tentei fazer atela piscar quando o jogo estivesse pausado 
	/*if(gameState == PAUSE){
		moveTimer++;
		if(moveTimer >= maxMoveTime){
			moveTimer = 0;
			move^=1;
		}
	}*/
	//O tick limita a velocidade dos jogos
	if(tick == 0){tickSpeed++;}
	if(tickSpeed >= maxTick){
		tick = 1;
		tickSpeed = 0;
	}	
}

//Função principal onde são feitas as configurações e onde está o loop do jogo
int main(void){
	//Inicializa a matriz
	inicializa();
	
	//Configuração das entradas (botões) em pull-up
	PORTD|=(1<<3)|(1<<4)|(1<<5)|(1<<6)|(1<<7);
	PORTB|=(1<<0)|(1<<6)|(1<<7);
	
	//Configuração do temporizador/contador e da interrupção
	TCCR0B|=0b00000010;
	TCNT0+=131;
	TIMSK0|=1;
	sei();
	
	while(1){
		if(tick == 1){	
			if(gameState == MENU){menu();}
			if(gameState == RUNNING){running();}
			if(gameState == GAMEOVER){gameOver();}
			if(gameState == PAUSE){pause();}			
			tick=0;
		}
	}
}


//Estava usando para tentar colocar música no jogo
/*
int notaTemp=0;
int nota = 0;
int musica1[2][7] = {{20,42,66,77,97,113,130},{1000,2000,3000,4000,5000,6000,7000}};//o tempo tem que ser contado no outro temporizador

ISR(TIMER0_OVF_vect){
	TCNT0+=131;
	if(notaTemp!=0){notaTemp--;}
	if(notaTemp == 0){
		notaTemp=musica1[1][nota];
		nota++;
		if(nota>=7){nota=0;}
	}
	
}

ISR(TIMER2_OVF_vect){
	TCNT2+=musica1[0][nota];
	PORTB^=(1<<1);
}


int main(void){
	int x, int y
	//Configuração da saída de audio
	DDRB|=(1<<1);
	PORTB|=(1<<6)|(1<<7);
	TCCR2B|=0b00000010;
	TIMSK2|=1;
	//Configuração do temporizador de 1ms
	TCCR0B|=0b00000010;
	TCNT0+=131;
	TIMSK0|=1;
	sei();
	
	while(1){
		
	}
}*/
