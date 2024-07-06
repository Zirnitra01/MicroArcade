/*
 * vector.c
 *
 * Created: 12/06/2024 18:14:03
 *  Author: Douglas Pasini
 */ 

#include "vector.h"

//Rotaciona o vetor para ficar melhor apresentado na matriz do circuito ná prática
void rotacionaVetor(unsigned int *vet, unsigned int *rotVet){
	unsigned char tempVet[16] = {0};
	for(int i=0; i<16; i++){
		for(int j=0; j<8; j++){
			if(vet[j]&(1<<i)){tempVet[i]|=(1<<j);}
		}
	}
	for(int i=0; i<8; i++){rotVet[i] = (tempVet[i+8]<<8)|tempVet[i];}
}

//As seguintes funções tem como objetivo manipular os vetores durante os jogos
void unirVetores(unsigned int *vet1, unsigned int *vet2, unsigned int *vet_res){
	for(int i=0; i<8; i++){vet_res[i] = vet1[i]|vet2[i];}
}

void atribuirVetores(unsigned int *vet_res, unsigned int *vet){
	for(int i=0; i<10; i++){vet_res[i] = vet[i];}
}

void limparVetores(unsigned int *vet_res, int slots){
	for(int i=0; i<slots; i++){vet_res[i] = 0;}
}

void ligaLED(unsigned int *vet, int x, int y){
	vet[x-1]|=(1<<(16-y));
}

void desligaLED(unsigned int *vet, int x, int y){
	vet[x-1]&=~(1<<(16-y));
}

char verificarLED(unsigned int *vet, int x, int y){
	if((vet[x-1]&(1<<(16-y))) != 0){return 1;}
	else{return 0;}
}

char vetorVazio(unsigned int *vet) {
	for(int i=0; i<8; i++){
		if(vet[i] != 0){return 1;}
	}
	return 0;
}
