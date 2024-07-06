/*
 * matrix.h
 *
 * Created: 16/06/2024 14:20:17
 *  Author: Douglas Pasini
 */ 


#ifndef MATRIX_H_
#define MATRIX_H_

#include <avr/io.h>
#include "vector.h"
#include "config.h"
#include <util/delay.h>

//Manda informações serialmente para as matrizes
void mandaComando(unsigned char addrs, unsigned int data);

//Inicializa o display
void inicializa();

//Envia o vetor com imagem completa
void mandaImagem(unsigned int *vet);





#endif /* MATRIX_H_ */