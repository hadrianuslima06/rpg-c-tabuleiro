#include <stdio.h>
#include <string.h>
#include "personagem.h"
#include "terminal.h"

void criarPersonagem(Personagem *p){
    int escolha = 0;

    printf("Identificador da unidade: ");
    scanf(" %49[^\n]", p->nome);
    limpar_terminal();

    printf("\n[DRA. Valeria]: \"Certo, %s. Liberei a fechadura manual. Antes de sair no\n", p->nome);
    printf(" corredor, da uma olhada na bancada de equipamentos ai do lado.\n");
    printf(" Os drones de patrulha ja estao hostis, entao escolhe o que\n");
    printf(" fizer mais sentido pra voce:\"\n\n");

    printf("Selecione a classe do seu Android de combate\n");
    printf("1 - Vanguarda   (Carga: 150 | Ataque: 10 | Blindagem: 15 | Proc.: 5)\n");
    printf("2 - Infiltrador (Carga: 100 | Ataque: 12 | Blindagem: 8  | Proc.: 18)\n");
    printf("3 - Artilheiro  (Carga: 90  | Ataque: 20 | Blindagem: 5  | Proc.: 10)\n");
    
    p->xp = 0;
    p->nivel = 1;
    p->missaoCumprida = 0;
    
    do{
        printf("Opcao: ");
        escolha = lerOpcaoSegura();
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
                printf("[DRA. Valeria]: \nBoa escolha! Com essa armadura voce vai conseguir\n");
                printf("segurar bem quando as coisas apertarem. Vai com cuidado.\n");
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
                printf("[DRA. Valeria]: \nQue escolha! Sua defesa não é tão boa mas com esse\n");
                printf("processador vai conseguir arrancar muita carga dos seus oponentes.\n");
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
                printf("[DRA. Valeria]: \nOtima ideia! Vai conseguir derrubar eles fácil,\n");
                printf("so toma cuidado com sua carga, ela pode ficar muito exposta.\n");
                break;
            default:
                printf("Opcao invalida! Você precisa selecionar um Android.\n");
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
    if (jogador->classe == VANGUARDA){
        strcpy(classe, "VANGUARDA");
    }
    else if(jogador->classe == INFILTRADOR){
        strcpy(classe, "INFILTRADOR");
    }
    else{
        strcpy(classe, "ARTILHEIRO");
    }
    printf("\n------- STATUS DO HERÓI -------\n");
    printf("CLASSE: %s\n", classe);
    printf("CARGA: %d/%d\n", jogador->cargaAtual, jogador->cargaMaxima);
    printf("ATAQUE: %d\n", jogador->poderAtaque);
    printf("BLINDAGEM: %d\n", jogador->blindagem);
    printf("ACESSORIO: %s\n", jogador->acessorio);
    printf("PROCESSAMENTO: %d\n", jogador->velocidadeProcessamento);
}

void verificarXpMax(Personagem *jogador){
    if(jogador->xp >= 40){
        jogador->xp -= 40;
        jogador->nivel++;
        printf("\n[SISTEMA ATUALIZADO]: Nivel %d alcancado!\n", jogador->nivel);
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

void aplicarBonusAleatorio(Personagem *jogador) {
    int sorteio = rand() % 4;

    printf("[OTIMIZACAO DE HARDWARE]: Dados de combate analisados!\n");
    switch (sorteio) {
        case 0:
            jogador->poderAtaque += 1;
            printf("Bonus aleatorio: +1 Poder de Ataque (Atual: %d)\n", jogador->poderAtaque);
            break;
        case 1:
            jogador->blindagem += 1;
            printf("Bonus aleatorio: +1 Blindagem (Atual: %d)\n", jogador->blindagem);
            break;
        case 2:
            jogador->velocidadeProcessamento += 1;
            printf("Bonus aleatorio: +1 Velocidade de Processamento (Atual: %d)\n", jogador->velocidadeProcessamento);
            break;
        default:
            jogador->cargaMaxima += 5;
            printf("Bonus aleatorio: +5 Carga Maxima de Bateria (Atual: %d)\n", jogador->cargaMaxima);
            break;
    }
}