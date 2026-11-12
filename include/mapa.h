#ifndef MAPA_H
#define MAPA_H

#include "estruturas.h"
#include "personagem.h"

void inicializarTabuleiro(Tipocasa tabuleiro[], int tamanho);
void exibirTabuleiro(int tamanho, int posicaoHeroi, Tipocasa tabuleiro[]);
void executarEvento(Personagem *jogador, int tipoCasa, int faseAtual);
void exibirHistoriaFase(int fase);
void exibirMensagemFinal(Personagem jogador);

#endif