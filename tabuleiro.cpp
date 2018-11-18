#include "tabuleiro.h"
#include <ctype.h>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

//incializando pecas no tabuleiro
Tabuleiro::Tabuleiro()
{
	for(int i = 0; i < 8; i++) {

		for(int j = 0; j < 8; j++) {

			_matriz[i][j] = "0";
		}
	}
	//colocando pecas brancas em suas posicoes
	_cavalos_brancos[0].inicializa_posicao(7,1);
	_cavalos_brancos[1].inicializa_posicao(7,6);
	_rei_branco.inicializa_posicao(7,4);
	_rainha_branca.inicializa_posicao(7,3);
	_bispos_brancos[0].inicializa_posicao(7,2);
	_bispos_brancos[1].inicializa_posicao(7,5);
	_torres_brancas[0].inicializa_posicao(7,0);
	_torres_brancas[1].inicializa_posicao(7,7);
	for(int i=0; i<8; i++)
	{
		_peoes_brancos[i].inicializa_posicao(6,i);
	}

	//colocando pecas pretas em suas posicoes
	_cavalos_pretos[0].inicializa_posicao(0,1);
	_cavalos_pretos[1].inicializa_posicao(0,6);
	_rei_preto.inicializa_posicao(0,4);
	_rainha_preta.inicializa_posicao(0,3);
	_bispos_pretos[0].inicializa_posicao(0,2);
	_bispos_pretos[1].inicializa_posicao(0,5);
	_torres_pretas[0].inicializa_posicao(0,0);
	_torres_pretas[1].inicializa_posicao(0,7);
	for(int i=0; i<8; i++)
	{
		_peoes_pretos[i].inicializa_posicao(1,i);
	}
	//colocando pecas no tabuleiro
	_matriz[0][0] = "T1P";
	_matriz[0][7] = "T2P"; // T = torre e B = branca
	_matriz[0][1] = "C1P";
	_matriz[0][6] = "C2P";
	_matriz[0][2] = "B1P";
	_matriz[0][5] = "B2P";
	_matriz[0][3] = "RP";
	_matriz[0][4] = "DP";
	for(int i=0; i<8; i++)
	{
		_matriz[1][i] = std::string("P") + char('1' + i) + "P";
	}

	_matriz[7][0] = "T1B";
	_matriz[7][7] = "T2B"; // T = torre e B = branca
	_matriz[7][1] = "C1B";
	_matriz[7][6] = "C2B";
	_matriz[7][2] = "B1B";
	_matriz[7][5] = "B2B";
	_matriz[7][3] = "RB";
	_matriz[7][4] = "DB";
	for(int i=0; i<8; i++)
	{
		_matriz[6][i] = std::string("P") + char('1' + i) + "B";
	}
}


bool Tabuleiro::jogada(const std::string& nome_peca, int pos_i_final, int pos_j_final, std::string jogada)
{
	if(pos_i_final > 7 || pos_j_final > 7 || pos_i_final < 0 || pos_j_final < 0) return false;
	if (roque(pos_i_final, pos_j_final,nome_peca[0])== true) {
		std::cout<<"Jogada por Roque \n";
		return true;
	}
	
	if(nome_peca == "0") return false;

	if( historico_jogadas.size() != 0 )
	{
		if( en_passant(nome_peca, pos_i_final, pos_j_final) == true )
		{
			std::cout << "Jogada por en-passant" << std::endl; 
			return true;
		} 
	}

	historico_jogadas.push_back(jogada); //armazenando a jogada realizada

	char tipo = nome_peca[0];
	char cor = nome_peca[nome_peca.size() - 1];
	int numero = nome_peca[1] - '1';

	if( cor == 'P')
	{
		switch(tipo)
		{

			case 'T':
				return _torres_pretas[numero].verifica_jogada(pos_i_final, pos_j_final, this);
			case 'C':
				return _cavalos_pretos[numero].verifica_jogada(pos_i_final, pos_j_final, this);
			case 'B':
				return _bispos_pretos[numero].verifica_jogada(pos_i_final, pos_j_final, this);
			case 'P':
				return _peoes_pretos[numero].verifica_jogada(pos_i_final, pos_j_final, this);
			case 'R':
				return _rei_preto.verifica_jogada(pos_i_final, pos_j_final, this);
			case 'D':
				return _rainha_preta.verifica_jogada(pos_i_final, pos_j_final, this);
			default: return -1; 
		}
	}

	else if( cor == 'B')
	{
		switch(tipo)
		{

			case 'T':
				return _torres_brancas[numero].verifica_jogada(pos_i_final, pos_j_final, this);
			case 'C':
				return _cavalos_brancos[numero].verifica_jogada(pos_i_final, pos_j_final, this);
			case 'B':
				return _bispos_brancos[numero].verifica_jogada(pos_i_final, pos_j_final, this);
			case 'P':
				return _peoes_brancos[numero].verifica_jogada(pos_i_final, pos_j_final, this);
			case 'R':
				return _rei_branco.verifica_jogada(pos_i_final, pos_j_final, this);
			case 'D':
				return _rainha_branca.verifica_jogada(pos_i_final, pos_j_final, this);
			default: return -1; 
		}
	}

	return false;
}

// ROQUE MAIOR E ROQUE MENOR
bool Tabuleiro :: roque(int pos_final_i, int pos_final_j, char ){
	if(_rei_branco.getNJogadas() == 0 && pos_final_i == 7 && pos_final_j == 6 && getMatriz(7, 5) == "0" && getMatriz(7, 6) == "0" && _rei_branco.getNJogadas() == 0 ){//roque menor pecas branca
		if((xeque( 7, 4))==true|| (xeque( 7, 6))== true)return false;
		if((xeque(0,4))==true|| (xeque(0,6))== true)return false;
		//std::cout<< "ROQUE MENOR BRANCAS";
		setMatriz(pos_final_i, pos_final_j, getMatriz(_rei_branco.get_linha_atual(), _rei_branco.get_coluna_atual()));
		setMatriz(_rei_branco.get_linha_atual(), _rei_branco.get_coluna_atual(), "0");
		_rei_branco.inicializa_posicao(pos_final_i, pos_final_j);
		_rei_branco.getNJogadas() ;
		//movimento torre
		setMatriz(7, 5, getMatriz(7, 7));
		setMatriz(7, 7, "0");
		_torres_brancas[1].inicializa_posicao(7, 5);
		_torres_brancas[1].setNjogadas();
		return true;
	}

	if(_rei_branco.getNJogadas() == 0 && pos_final_i == 7 && pos_final_j == 2 && getMatriz(7, 1) == "0" && getMatriz(7,2) == "0" && getMatriz(7, 3) == "0" && _torres_brancas[1].getNJogadas() == 0) {//roque maior branco
		if((xeque( 7, 4))==true|| (xeque( 7, 2))== true)return false;
		setMatriz(pos_final_i, pos_final_j,getMatriz(_rei_branco.get_linha_atual(), _rei_branco.get_coluna_atual()));
		setMatriz(_rei_branco.get_linha_atual(), _rei_branco.get_coluna_atual(), "0");
		_rei_branco.inicializa_posicao(7, 2);
		_rei_branco.getNJogadas() ;
		//movimento torre
		setMatriz(7, 3,getMatriz(7, 0));
		setMatriz(7, 0, "0");
		_torres_brancas[0].inicializa_posicao(7, 3);
		_torres_brancas[0].setNjogadas();
		return true;
	}


	if(_rei_preto.getNJogadas() == 0 && pos_final_i == 0 && pos_final_j == 6 && getMatriz(0, 5) == "0" && getMatriz(0, 6) == "0" && _torres_pretas[0].getNJogadas() == 0) {//roque menor pecas branca
		//std::cout<< "ROQUE MENOR pretas";
		if((xeque(0,4))==true|| (xeque(0,6))== true)return false;
		setMatriz(pos_final_i, pos_final_j, getMatriz(_rei_preto.get_linha_atual(), _rei_preto.get_coluna_atual()));
		setMatriz(_rei_preto.get_linha_atual(), _rei_preto.get_coluna_atual(), "0");
		_rei_preto.inicializa_posicao(pos_final_i, pos_final_j);
		_rei_preto.setNjogadas();
		//TORRE
		setMatriz(0, 5, getMatriz(0, 7));
		setMatriz(0, 7, "0");
		_torres_pretas[1].inicializa_posicao(0, 5);
		_torres_pretas[1].setNjogadas();
		return true;
	}


	if(_rei_preto.getNJogadas() == 0 && pos_final_i == 0 && pos_final_j == 2 && getMatriz(0, 1) == "0" && getMatriz(0,2) == "0" && getMatriz(0, 3) == "0" && _torres_pretas[1].getNJogadas() == 0) {//roque maior pecas bramcas
		//std::cout<< "ROQUE MaiOR PRETAS";
		if((xeque(0,4))==true|| (xeque(0,2))== true)return false;
		setMatriz(pos_final_i, pos_final_j, getMatriz(_rei_preto.get_linha_atual(), _rei_preto.get_coluna_atual()));
		setMatriz(_rei_preto.get_linha_atual(), _rei_preto.get_coluna_atual(), "0");
		_rei_preto.inicializa_posicao(pos_final_i, pos_final_j);
		_torres_pretas[1].getNJogadas() ;
		setMatriz(0, 3, getMatriz(0, 0));
		setMatriz(0, 0, "0");
		_torres_pretas[0].inicializa_posicao(0, 3);
		_torres_pretas[0].setNjogadas();
		return true;

	}
	return false;


}



bool Tabuleiro:: xeque(int n , int m){ //da pra verkfkcar na (0,2)(0,4)(0,6) os rksco para o rek
	int k = n;
	int l = m;

	if (m == 0 && n == 6){
		for (int j1 = 0; j1 < 8; j1++){
			if ((getMatriz(1, j1) == "C1P") || (getMatriz(1, j1) == "C2P")){
				if( (j1 == 2)|| (j1 == 4) ||(j1 == 6)){
					return true;
				}
			}
			if ((getMatriz(2, j1) == "C1P") || (getMatriz(2, j1) == "C2P")){
				if( (j1 == 3)|| (j1 == 5) ||(j1 == 7)){
					return true;
				}
			}
		}
	}
	if (m == 0 && n == 2){
		for (int j2 = 0; j2 < 8; j2++){
			if ((getMatriz(1, j2) == "C1P") || (getMatriz(1, j2) == "C2P")){
				if( (j2 == 4)|| (j2 == 2) ||(j2 == 0)||(j2 == 6)){
					return true;
				}
			}
			if ((getMatriz(2, j2) == "C1P") || (getMatriz(2, j2) == "C2P")){
				if( (j2 == 5)|| (j2 == 3) ||(j2== 1)){
					return true;
				}
			}
		}
	}
	return false;
}

