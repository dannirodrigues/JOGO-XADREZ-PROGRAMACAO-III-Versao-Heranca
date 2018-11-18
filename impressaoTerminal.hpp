#ifndef IMPRESSAO_TERMINAL
#define IMPRESSAO_TERMINAL

#include <iostream>
#include <string.h>
#include "tabuleiro.h"

void impressao(Tabuleiro, bool);

void impressao(Tabuleiro t, bool printar_caracteres_especiais)
{
	if(!printar_caracteres_especiais)
	{
		std::cout << "   a  b  c  d  e  f  g  h  " << std::endl;
		std::cout << "---------------------------" << std::endl;
	}
	for(int i = 0 ; i < 8 ; i++) {

		if(printar_caracteres_especiais == false) std::cout << 8-i << "|";

		for(int j = 0; j < 8 ; j++) {
			
			if(printar_caracteres_especiais)
			{				
				std::cout.width(3);
				std::cout << t.getMatriz(i, j) << ' ';
				continue;
			}

			std::string nome_peca = t.getMatriz(i, j);
			char tipo = nome_peca[0];
			char cor = nome_peca[nome_peca.size() - 1];				

			//std::cout.width(4);
			if( cor == 'P')
			{
				switch(tipo)
				{

					case 'T':				
						std::cout << " \u265C" << ' ';
						break;
					case 'C':				
						std::cout << " \u265E" << ' ';
						break;
					case 'B':				
						std::cout << " \u265D" << ' ';
						break;					
					case 'P':				
						std::cout << " \u265F" << ' ';
						break;				
					case 'D':				
						std::cout << " \u265A" << ' ';
						break;					
					case 'R':				
						std::cout << " \u265B" << ' ';
						break;
					default: break;
				}			
			}

			else if( cor == 'B')
			{
				switch(tipo)
				{

					case 'T':				
						std::cout << " \u2656" << ' ';
						break;
					case 'C':				
						std::cout << " \u2658" << ' ';
						break;
					case 'B':				
						std::cout << " \u2657" << ' ';
						break;					
					case 'P':				
						std::cout << " \u2659" << ' ';
						break;					
					case 'D':				
						std::cout << " \u2654" << ' ';
						break;					
					case 'R':				
						std::cout << " \u2655" << ' ';
						break;	
					default: break;							
				}			
			}
			else std::cout << " - ";	
		}
		
		if(printar_caracteres_especiais == false) std::cout << "|" << 8-i << std::endl;
		else std::cout << std::endl;
	}
	if(printar_caracteres_especiais == false)
	{
		std::cout << "---------------------------" << std::endl;
		std::cout << "   a  b  c  d  e  f  g  h  " << std::endl;		
	}
}

#endif