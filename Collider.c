/*
 * Collider.c
 *
 * Created: 06/06/2024 13:11:01
 *  Author: Douglas Pasini
 */ 

#include "collider.h"

//As fun��es de colis�o Wall detectam quando h� alguma colis�o entre o objeto e o limite da matriz
char colisaoInferiorWall(unsigned int *vet){
	char colisao = 0;
	for(int i=0; i<8; i++){
		if((vet[i]&0x0001) != 0){
			colisao = 1;
		}
	}
	return colisao;
}
char colisaoSuperiorWall(unsigned int *vet){
	char colisao = 0;
	for(int i=0; i<8; i++){
		if((vet[i]&0x8000) != 0){
			colisao = 1;
		}
	}
	return colisao;
}
char colisaoDireitaWall(unsigned int *vet){
	char colisao = 0;
	for(int i=0; i<7; i++){
		if(vet[7] != 0){
			colisao = 1;
		}
	}
	return colisao;
}
char colisaoEsquerdaWall(unsigned int *vet){
	char colisao = 0;
	for(int i=0; i<7; i++){
		if(vet[0] != 0){
			colisao = 1;
		}
	}
	return colisao;
}

//As fun��es de colis�o Ref detectam quando h� alguma colis�o entre os dois objetos
char colisaoInferiorRef(unsigned int *vet, unsigned int *vet_ref){
	char colisao = 0;
	for(int i=0; i<8; i++){
		if(((vet[i]>>1)&vet_ref[i]) != 0){
			colisao = 1;
		}
	}
	return colisao;
}
char colisaoSuperiorRef(unsigned int *vet, unsigned int *vet_ref){
	char colisao = 0;
	for(int i=0; i<8; i++){
		if(((vet[i]<<1)&vet_ref[i]) != 0){
			colisao = 1;
		}
	}
	return colisao;
}
char colisaoDireitaRef(unsigned int *vet, unsigned int *vet_ref){
	char colisao = 0;
	for(int i=0; i<7; i++){
		if((vet[i]&vet_ref[i+1]) != 0){
			colisao = 1;
		}
	}
	return colisao;
}
char colisaoEsquerdaRef(unsigned int *vet, unsigned int *vet_ref){
	char colisao = 0;
	for(int i=0; i<7; i++){
		if((vet[i+1]&vet_ref[i]) != 0){
			colisao = 1;
		}
	}
	return colisao;
}
char colisaoDireitaSuperiorRef(unsigned int *vet, unsigned int *vet_ref){
	char colisao = 0;
	for(int i=0; i<7; i++){
		if(((vet[i]<<1)&vet_ref[i+1]) != 0){
			colisao = 1;
		}
	}
	return colisao;
}
char colisaoEsquerdaSuperiorRef(unsigned int *vet, unsigned int *vet_ref){
	char colisao = 0;
	for(int i=0; i<7; i++){
		if(((vet[i+1]<<1)&vet_ref[i]) != 0){
			colisao = 1;
		}
	}
	return colisao;
}
char colisaoDireitaInferiorRef(unsigned int *vet, unsigned int *vet_ref){
	char colisao = 0;
	for(int i=0; i<7; i++){
		if(((vet[i]>>1)&vet_ref[i+1]) != 0){
			colisao = 1;
		}
	}
	return colisao;
}
char colisaoEsquerdaInferiorRef(unsigned int *vet, unsigned int *vet_ref){
	char colisao = 0;
	for(int i=0; i<7; i++){
		if(((vet[i+1]>>1)&vet_ref[i]) != 0){
			colisao = 1;
		}
	}
	return colisao;
}