#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define TAMANHO_TABULEIRO 20
#include "estruturas.h"
#include "personagem.h"
#include "mapa.h"
#include "combate.h"
#include "terminal.h"

int main(){
    srand(time(NULL));
    exibirPrologo();
    Personagem heroi;
    criarPersonagem(&heroi);

    Tipocasa mapa[TAMANHO_TABULEIRO];
    inicializarTabuleiro(mapa, TAMANHO_TABULEIRO);

    int faseAtual = 1;
    int ultimaFase = 3;

    while (faseAtual <= ultimaFase && !verificarCargaMin(&heroi)){
        exibirHistoriaFase(faseAtual);
        pausar();

        jogarFase(&heroi, mapa, TAMANHO_TABULEIRO, faseAtual);
        faseAtual++;
        if (faseAtual <= ultimaFase && !verificarCargaMin(&heroi)){
            printf("Avançando pra a fase %d!\n", faseAtual);
            pausar();
        }
    }
    
    limpar_terminal();
    exibirMensagemFinal(heroi);
    
    return 0;
}