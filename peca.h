#ifndef PECA_H
#define PECA_H

#include <iostream>
#include <string>

class Tabuleiro;

class Peca
{
public:
	void inicializa_posicao(int i1, int j1)
	{
		_i = i1;
		_j = j1;
		return;
	}
	void setNjogadas (){ nJogadas++; }
	int getNJogadas(void) { return nJogadas; }
	int get_linha_atual() { return _i; }
	int get_coluna_atual() { return _j; }
	void incremento_nJogadas() { nJogadas++; }

private:
	
	int nJogadas = 0;
	int _i;  
	int _j; //posicao atual em i e j
};


#endif