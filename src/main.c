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
    Personagem heroi;
    criarPersonagem(&heroi);

    Tipocasa mapa[TAMANHO_TABULEIRO];
    inicializarTabuleiro(mapa, TAMANHO_TABULEIRO);

    int faseAtual = 1;
    int ultimaFase = 3;

    while (faseAtual <= ultimaFase){
        int posicaoAtual = 0;
        int opcao = 0;
        heroi.missaoCumprida = 0;

        if (!verificarCargaMin(&heroi)){
            exibirHistoriaFase(faseAtual);
            pausar();
        }
        else{
            break;
        }
        while (heroi.missaoCumprida != 2 && !verificarCargaMin(&heroi)){
            exibirTabuleiro(TAMANHO_TABULEIRO, posicaoAtual, mapa);
            int dado;

            printf("Bateria: %d/%d | Posicao: %d\n", heroi.cargaAtual, heroi.cargaMaxima, posicaoAtual);
            printf("1 - Rolar Dado de Movimento\n");
            printf("2 - Ver Status do Androide\n");
            
            do {
                printf("Opcao: ");
                opcao = lerOpcaoSegura();
                switch (opcao){
                    case 1:
                        dado = jogarDado(6);
                        printf("O dado parou no número %d!\n", dado);
                        posicaoAtual += dado;
        
                        if(posicaoAtual >= TAMANHO_TABULEIRO){
                            posicaoAtual = TAMANHO_TABULEIRO - 1;
                        }
        
                        if(mapa[posicaoAtual] == CASA_CHEFAO){
                            if (faseAtual >= 2 && heroi.missaoCumprida == 0) {
                                printf("\nACESSO NEGADO! Faltam credenciais!\n");
                                printf("Você precisa encontrar o item na casa [ ? ] antes do chefe.\n");
                                printf("Teletransportando para o início do setor...\n");
                                posicaoAtual = 0;
                            } 
                            else {
                                executarEvento(&heroi, mapa[posicaoAtual], faseAtual);
                            }

                        }
                        else{
                            executarEvento(&heroi,mapa[posicaoAtual], faseAtual);
                        }
                        break;
                    
                    case 2:
                        exibirStatusHeroi(&heroi);
                        break;
                    default:
                        printf("Opção inválida!\n");
                        break;
        
                }
            } while(opcao > 2 || opcao < 1);
        }

        faseAtual++;
        if (faseAtual <= ultimaFase && !verificarCargaMin(&heroi)){
            printf("Avançando para a fase %d...\n", faseAtual);
        }
        pausar();


    }
    limpar_terminal();
    exibirMensagemFinal(heroi);
    
    return 0;
}