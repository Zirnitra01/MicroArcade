/*
 * matrix.c
 *
 * Created: 16/06/2024 14:20:05
 *  Author: Douglas Pasini
 */ 

#include "matrix.h"

//Manda informações serialmente para as matrizes
void mandaComando(unsigned char addrs, unsigned int data){
	unsigned int tmp = (data>>8)&0xFF;
	PORTD&=~(CS); //CS=0
	for(int i=0; i<2; i++){
		tmp = tmp|(addrs<<8);
		for(int c=0; c<16; c++){
			if((tmp&0x8000) != 0){PORTD|=(DATA);} //DATA=1
			else{PORTD&=~(DATA);} //DATA=0
			PORTD|=(CLK); //CLK=1
			PORTD&=~(CLK); //CLK=0
			tmp = tmp<<1;
		}
		tmp = data&0xFF;
	}	
	PORTD|=(CS); //CS=1
}

//Inicializa o display
void inicializa(){
	DDRD|=(CS)|(CLK)|(DATA);
	PORTD|=(CS); 
	PORTD&=~(CLK);
	_delay_ms(100);
	mandaComando(0x09,0x0000); //decode none
	mandaComando(0x0A,0x0909); //int. 2
	mandaComando(0x0B,0x0707); //Scan all
	mandaComando(0x0C,0xFFFF); //enable
	mandaComando(0x0F,0x0000); //test off
}

void mandaImagem(unsigned int *vet){
	//Manda os comandos para a matriz no circuito na prática
	/*
	unsigned int rotVet[8] = {0};	
	rotacionaVetor(vet,rotVet);	
		
	for(int i=0; i<8; i++){
		mandaComando(i+1,rotVet[i]);
	}
	*/
	
	//Manda os comandos para a matriz na simulação
	for(int i=0; i<8; i++){
		mandaComando(i+1,vet[7-i]);	
	}	
}
