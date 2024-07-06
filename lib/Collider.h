/*
 * Collider.h
 *
 * Created: 06/06/2024 13:11:10
 *  Author: Douglas Pasini
 */ 


#ifndef COLLIDER_H_
#define COLLIDER_H_

#include <avr/io.h>

//As funções de colisão Wall detectam quando há alguma colisão entre o objeto e o limite da matriz
char colisaoInferiorWall(unsigned int *vet);
char colisaoSuperiorWall(unsigned int *vet);
char colisaoDireitaWall(unsigned int *vet);
char colisaoEsquerdaWall(unsigned int *vet);

//As funções de colisão Ref detectam quando há alguma colisão entre os dois objetos
char colisaoInferiorRef(unsigned int *vet, unsigned int *vet_ref);
char colisaoSuperiorRef(unsigned int *vet, unsigned int *vet_ref);
char colisaoDireitaRef(unsigned int *vet, unsigned int *vet_ref);
char colisaoEsquerdaRef(unsigned int *vet, unsigned int *vet_ref);
char colisaoDireitaSuperiorRef(unsigned int *vet, unsigned int *vet_ref);
char colisaoEsquerdaSuperiorRef(unsigned int *vet, unsigned int *vet_ref);
char colisaoDireitaInferiorRef(unsigned int *vet, unsigned int *vet_ref);
char colisaoEsquerdaInferiorRef(unsigned int *vet, unsigned int *vet_ref);


#endif /* COLLIDER_H_ */
