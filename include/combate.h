#ifndef COMBATE_H
#define COMBATE_H

#include "estruturas.h"

int jogarDado(int lados);
void iniciarCombate(Personagem *jogador, int faseAtual);
void iniciarCombateChefe(Personagem *jogador, int faseAtual);
void infringirDano(Monstro *m, int *dano);
void receberDano(Personagem *jogador, int *dano);

#endif