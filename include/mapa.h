#ifndef MAPA_H
#define MAPA_H

#include "estruturas.h"
#include "personagem.h"

void inicializarTabuleiro(Tipocasa tabuleiro[], int tamanho);
void exibirTabuleiro(int tamanho, int posicaoHeroi, Tipocasa tabuleiro[]);
void executarEvento(Personagem *jogador, Tipocasa tipoCasa, int faseAtual);
void exibirHistoriaFase(int fase);
void exibirMensagemFinal(Personagem jogador);
void moverJogador(Personagem *jogador, int *posicaoAtual, Tipocasa tabuleiro[], int tamanho, int faseAtual);
void jogarFase(Personagem *jogador, Tipocasa tabuleiro[], int tamanho, int faseAtual);

#endif