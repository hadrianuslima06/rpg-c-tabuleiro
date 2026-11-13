#include <stdio.h>
#include <string.h>
#include "personagem.h"

void criarPersonagem(Personagem *p){
    int escolha = 0;

    printf("------ SISTEMA DE INICIALIZAÇÃO ------\n");
    printf("Informe um nome para sua Unidade: ");
    scanf("%s", p->nome);

    printf("Selecione a classe do seu Android de combate\n");
    printf("1 - Vanguarda (Foco em Blindagem)\n");
    printf("2 - Infiltrador (Foco em Processamento e Agilidade)\n");
    printf("3 - Artilheiro (Foco em Poder de Fogo)\n");
    
    p->xp = 0;
    p->missaoCumprida = 0;
    
    do{
        printf("Opcao: ");
        scanf("%d", &escolha);
        switch(escolha) {
            case VANGUARDA:
                p->classe = VANGUARDA;
                strcpy(p->acessorio, "Armadura de Titânio");
                p->cargaMaxima = 150;
                p->cargaAtual = 150;
                p->poderAtaque = 10;
                p->blindagem = 15;
                p->velocidadeProcessamento = 5;
                p->habilidade = PROTECAO_DANO;
                break;
            case INFILTRADOR:
                p->classe = INFILTRADOR;
                strcpy(p->acessorio, "Processador 100GHz");
                p->cargaMaxima = 100;
                p->cargaAtual = 100;
                p->poderAtaque = 12;
                p->blindagem = 8;
                p->velocidadeProcessamento = 18;
                p->habilidade = ROUBO_CARGA;
                break;
            case ARTILHEIRO:
                p->classe = ARTILHEIRO;
                strcpy(p->acessorio, "Arma de plasma");
                p->cargaMaxima = 90;
                p->cargaAtual = 90;
                p->poderAtaque = 20;
                p->blindagem = 5;
                p->velocidadeProcessamento = 10;
                p->habilidade = MAIOR_DANO;
                break;
            default:
                printf("Opcao invalida! Você precisa selecionar um Herói.\n");
                break;
        }
    } while (escolha != 1 && escolha != 2 && escolha != 3);
}

void verificarCargaMax(Personagem *j){
    if (j->cargaAtual > j->cargaMaxima){
        j->cargaAtual = j->cargaMaxima;
    }
}

void exibirStatusHeroi(Personagem *jogador){
    char classe[50];
    if (jogador->classe == 1){
        strcpy(classe, "VANGUARDA");
    }
    else if(jogador->classe == 2){
        strcpy(classe, "INFILTRADOR");
    }
    else{
        strcpy(classe, "ARTILHEIRO");
    }
    printf("\n------- STATUS DO HERÓI -------\n");
    printf("CLASSE: %s\n", classe);
    printf("CARGA: %d\n", jogador->cargaAtual);
    printf("ATAQUE: %d\n", jogador->poderAtaque);
    printf("BLINDAGEM: %d\n", jogador->blindagem);
}

void verificarXpMax(Personagem *jogador){
    if(jogador->xp >= 40){
        jogador->xp -= 40;
        switch(jogador->classe){
            case VANGUARDA:
                jogador->cargaMaxima += 20;
                jogador->blindagem += 3;
                jogador->poderAtaque += 1;
                printf("Melhorias: +20 Bateria Max, +3 Blindagem, +1 Ataque\n");
                break;
            
            case INFILTRADOR:
                jogador->cargaMaxima += 10;
                jogador->velocidadeProcessamento += 4;
                jogador->poderAtaque += 2;
                printf("Melhorias: +10 Bateria Max, +4 Processamento, +2 Ataque\n");
                break;

            case ARTILHEIRO:
                jogador->cargaMaxima += 5;
                jogador->poderAtaque += 5;
                jogador->blindagem += 1;
                printf("Melhorias: +5 Bateria Max, +5 Ataque, +1 Blindagem\n");
                break;
        }
        verificarXpMax(jogador);
        jogador->cargaAtual = jogador->cargaMaxima;
        

    }
}

int verificarCargaMin(Personagem *jogador){
    if (jogador->cargaAtual <= 0){
        return 1;
    }
    else{
        return 0;
    }
}