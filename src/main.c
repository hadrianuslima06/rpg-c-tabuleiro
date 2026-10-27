#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define TAMANHO_TABULEIRO 20

typedef enum {
    VANGUARDA = 1,
    INFILTRADOR,
    ARTILHEIRO
} ClasseRobo;

typedef enum {
    CASA_VAZIA,
    CASA_COMBATE,
    CASA_RECARGA,
    CASA_VIRUS,
    CASA_MISSAO
} Tipocasa;

typedef struct {
    char nome[50];
    int cargaAtual;
    int cargaMaxima;
    int poderAtaque;
    int blindagem;
    int velocidadeProcessamento;
    int xp;
    ClasseRobo classe;
} Personagem;

typedef struct{
    char nome[50];
    int cargaAtual;
    int poderAtaque;
    int blindagem;
    int xpLiberado;
} Monstro;

void criarPesonagem(Personagem *p);
void inicializarTabuleiro(Tipocasa tabuleiro[], int tamanho);
int jogarDado(int lados);
void exibirTabuleiro(int tamanho, int posicaoHeroi, Tipocasa tabuleiro[]);

int main(){
    srand(time(NULL));
    Personagem heroi;
    criarPesonagem(&heroi);

    Tipocasa mapa[TAMANHO_TABULEIRO];
    inicializarTabuleiro(mapa, TAMANHO_TABULEIRO);

    int posicaoAtual = 0;
    int missaoCumprida = 0;
    int opcao = 0;

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
                    break;
                
                case 2:
                    printf("\n------- STATUS DO HERÓI -------\n");
                    printf("CLASSE: %d\n", heroi.classe);
                    printf("CARGA: %d\n", heroi.cargaAtual);
                    printf("ATAQUE: %d\n", heroi.poderAtaque);
                    printf("BLINDAGEM: %d\n", heroi.blindagem);
                    break;
                default:
                    printf("Opção inválida!\n");
                    break;
    
            }
        } while(opcao > 2 || opcao < 1);

    }
    

    return 0;
}


void criarPesonagem(Personagem *p){
    int escolha = 0;

    printf("------ SISTEMA DE INICIALIZAÇÃO ------\n");
    printf("Informe um nome para sua Unidade: ");
    scanf("%s", p->nome);

    printf("Selecione a classe do seu Android de combate\n");
    printf("1 - Vanguarda (Foco em Blindagem)\n");
    printf("2 - Infiltrador (Foco em Processamento e Agilidade)\n");
    printf("3 - Artilheiro (Foco em Poder de Fogo)\n");
    
    p->xp = 0;
    
    do{
        printf("Opcao: ");
        scanf("%d", &escolha);
        switch(escolha) {
            case VANGUARDA:
                p->classe = VANGUARDA;
                p->cargaMaxima = 150;
                p->cargaAtual = 150;
                p->poderAtaque = 10;
                p->blindagem = 15;
                p->velocidadeProcessamento = 5;
                break;
            case INFILTRADOR:
                p->classe = INFILTRADOR;
                p->cargaMaxima = 100;
                p->cargaAtual = 100;
                p->poderAtaque = 12;
                p->blindagem = 8;
                p->velocidadeProcessamento = 18;
                break;
            case ARTILHEIRO:
                p->classe = ARTILHEIRO;
                p->cargaMaxima = 90;
                p->cargaAtual = 90;
                p->poderAtaque = 20;
                p->blindagem = 5;
                p->velocidadeProcessamento = 10;
                break;
            default:
                printf("Opcao invalida! Você precisa selecionar um Herói.\n");
                break;
        }
    } while (escolha > 3 || escolha < 1);
}

void inicializarTabuleiro(Tipocasa tabuleiro[], int tamanho){
    for (int i = 0; i < tamanho; i++){
        tabuleiro[i] = CASA_VAZIA;
    }

    tabuleiro[3] = CASA_COMBATE;
    tabuleiro[5] = CASA_RECARGA;
    tabuleiro[8] = CASA_COMBATE;
    tabuleiro[11] = CASA_VIRUS;
    tabuleiro[15] = CASA_COMBATE;
    tabuleiro[17] = CASA_RECARGA;
    tabuleiro[tamanho-1] = CASA_MISSAO;
}

int jogarDado(int lados){
    return (rand() % lados) + 1;
}

void exibirTabuleiro(int tamanho, int posicaoHeroi, Tipocasa tabuleiro[]){
    for(int i = 0; i < tamanho; i++){
        if (i == posicaoHeroi){
            printf("[ P ] ");
        }
        else{
            switch (tabuleiro[i]){
                case CASA_VAZIA:
                    printf("[  ]" );
                    break;
                case CASA_COMBATE:
                    printf("[ ! ]" );
                    break;
                case CASA_RECARGA:
                    printf("[ + ]" );
                    break;
                case CASA_VIRUS:
                    printf("[ * ]" );
                    break;
                case CASA_MISSAO:
                    printf("[ M ]" );
                    break;
            }
        }
    }
    printf("\n-----------------------------------\n");
}