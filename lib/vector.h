/*
 * vector.h
 *
 * Created: 12/06/2024 18:14:18
 *  Author: Douglas Pasini
 */ 


#ifndef VECTOR_H_
#define VECTOR_H_

#include <avr/io.h>

//Rotaciona o vetor para ficar melhor apresentado na matriz
void rotacionaVetor(unsigned int *vet, unsigned int *rotVet);

//As seguintes funções tem como objetivo manipular os vetores durante os jogos
void unirVetores(unsigned int *vet1, unsigned int *vet2, unsigned int *vet_res);
void atribuirVetores(unsigned int *vet_res, unsigned int *vet);
void limparVetores(unsigned int *vet_res, int slots);
void ligaLED(unsigned int *vet, int x, int y);
void desligaLED(unsigned int *vet, int x, int y);
char verificarLED(unsigned int *vet, int x, int y);
char vetorVazio(unsigned int *vet);


#endif /* VECTOR_H_ */
