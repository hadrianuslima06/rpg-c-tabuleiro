#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define TAMANHO_TABULEIRO 20
#include "estruturas.h"
#include "personagem.h"
#include "mapa.h"
#include "combate.h"

void criarPersonagem(Personagem *p);
void inicializarTabuleiro(Tipocasa tabuleiro[], int tamanho);
int jogarDado(int lados);
void exibirTabuleiro(int tamanho, int posicaoHeroi, Tipocasa tabuleiro[]);
void executarEvento(Personagem *jogador, int tipoCasa, int faseAtual);
void verificarCargaMax(Personagem *j);
void iniciarCombate(Personagem *jogador, int faseAtual);
void exibirStatusHeroi(Personagem *jogador);
void verificarXpMax(Personagem *jogador);
void exibirHistoriaFase(int fase);

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
        int missaoCumprida = 0;
        int opcao = 0;

        exibirHistoriaFase(faseAtual);
        while (!missaoCumprida && heroi.cargaAtual > 0){
            exibirTabuleiro(TAMANHO_TABULEIRO, posicaoAtual, mapa);
            int dado;
    
            printf("Bateria: %d/%d | Posicao: %d\n", heroi.cargaAtual, heroi.cargaMaxima, posicaoAtual);
            printf("1 - Rolar Dado de Movimento\n");
            printf("2 - Ver Status do Androide\n");
            
            do {
                printf("Opcao: ");
                scanf("%d", &opcao);
                switch (opcao){
                    case 1:
                        dado = jogarDado(6);
                        printf("O dado parou no número %d!\n", dado);
                        posicaoAtual += dado;
        
                        if(posicaoAtual >= TAMANHO_TABULEIRO){
                            posicaoAtual = TAMANHO_TABULEIRO - 1;
                        }
        
                        if(mapa[posicaoAtual] == CASA_MISSAO){
                            printf("ATENÇÃO: Você chegou ao núcleo do setor\n");
                            missaoCumprida = 1;
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
        if (faseAtual <= ultimaFase){
            printf("Avançando para a fase %d...\n", faseAtual);
        }


    }
    
    return 0;
}