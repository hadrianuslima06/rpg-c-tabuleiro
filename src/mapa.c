#include <stdio.h>
#include "mapa.h"
#include "combate.h"
#include "terminal.h"

void inicializarTabuleiro(Tipocasa tabuleiro[], int tamanho){
    for (int i = 0; i < tamanho; i++){
        tabuleiro[i] = CASA_VAZIA;
    }

    tabuleiro[3] = CASA_COMBATE;
    tabuleiro[5] = CASA_RECARGA;
    tabuleiro[7] = CASA_OBJETIVO;
    tabuleiro[8] = CASA_COMBATE;
    tabuleiro[10] = CASA_RECOMPENSA;
    tabuleiro[11] = CASA_VIRUS;
    tabuleiro[13] = CASA_RECOMPENSA;
    tabuleiro[14] = CASA_OBJETIVO;
    tabuleiro[15] = CASA_COMBATE;
    tabuleiro[17] = CASA_RECARGA;
    tabuleiro[18] = CASA_RECOMPENSA;
    tabuleiro[tamanho-1] = CASA_CHEFAO;
}

void exibirTabuleiro(int tamanho, int posicaoHeroi, Tipocasa tabuleiro[]){
    for(int i = 0; i < tamanho; i++){
        if (i == posicaoHeroi){
            printf("[ P ] ");
        }
        else{
            switch (tabuleiro[i]){
                case CASA_VAZIA:
                    printf("[  ]");
                    break;
                case CASA_COMBATE:
                    printf("[ ! ]");
                    break;
                case CASA_RECARGA:
                    printf("[ + ]");
                    break;
                case CASA_VIRUS:
                    printf("[ * ]");
                    break;
                case CASA_CHEFAO:
                    printf("[ M ]");
                    break;
                case CASA_RECOMPENSA:
                    printf("[ $ ]");
                    break;
                case CASA_OBJETIVO:
                    printf("[ ? ]");
                    break;
            }
        }
    }
    printf("\n-----------------------------------\n");
}

void executarEvento(Personagem *jogador, int tipoCasa, int faseAtual){
    switch(tipoCasa){
        case CASA_VAZIA:
            printf("Tudo tranquilo, por enquanto! Nenhum sinal de corrupção no sistema!\n");
            break;
        case CASA_RECARGA:
            jogador->cargaAtual += 20;
            verificarCargaMax(jogador);
            
            printf("Ponto de Recarga! Você recebeu 20 pontos de bateria.\n");
            printf("CARGA ATUAL: %d/%d\n", jogador->cargaAtual, jogador->cargaMaxima);
            break;
        case CASA_VIRUS:
            printf("ALERTA: Armadilha cibernética!\n");
            jogador->cargaAtual -= 15;
            printf("Você perdeu 15 pontos de bateria!\n");
            printf("CARGA ATUAL: %d/%d\n", jogador->cargaAtual, jogador->cargaMaxima);
            break;
        case CASA_COMBATE:
            printf("SISTEMA COMPROMETIDO!!!!\n");
            iniciarCombate(jogador, faseAtual);
            // aqui estara a batalha contra os inimigos
            break;
        case CASA_CHEFAO:
            iniciarCombateChefe(jogador, faseAtual);
            printf("Acesso ao núcleo concedido. Preparando reinicializacao...\n");
            if (!verificarCargaMin(jogador)){
                jogador->missaoCumprida = 2;
            }
            break;
        case CASA_RECOMPENSA:
            printf("VOCÊ ENCONTROU UM BAU!\n");
            int dado = jogarDado(3);
            if (dado == 1){
                jogador->cargaMaxima += 10;
                jogador->cargaAtual = jogador->cargaMaxima;
                printf("Voce ganhou 10 pontos de bateria!\n");
            }
            else if (dado == 2){
                jogador->poderAtaque += 10;
                printf("Voce ganhou 10 pontos de ataque!\n");
            }
            else{
                jogador->blindagem += 15;
                printf("Voce ganhou 15 pontos de blindagem!\n");
            }
            break;
        case CASA_OBJETIVO:
            if (faseAtual == 2){
                printf("Você encontrou o CARTÃO DE ACESSO!\n");
                jogador->missaoCumprida = 1;
            }
            else if(faseAtual == 3){
                printf("Você baixou o CÓDIGO DE SOBRESCRITA!\n");
                jogador->missaoCumprida = 1;
            }
            break;
    }
}

void exibirHistoriaFase(int fase){
    limpar_terminal();
    printf("======================================================\n");
    switch(fase){
        case 1:
            printf("                      FASE 1\n");
            printf("           INVASAO DO PERIMETRO EXTERNO\n");
            printf("------------------------------------------------------\n");
            printf("Missao: Sobreviver as defesas iniciais e avancar.\n");
            printf("O sistema de seguranca foi corrompido por um virus\n");
            printf("desconhecido. Os drones de patrulha estao hostis.\n");
            break;

        case 2:
            printf("                      FASE 2\n");
            printf("        SETOR DE MANUTENCAO E PROCESSAMENTO\n");
            printf("------------------------------------------------------\n");
            printf("Missao: Vasculhe as casas [ ? ] para encontrar o\n");
            printf("CARTAO DE ACESSO, e derrote o Amalgama Cibernetico.\n");
            printf("As luzes de emergencia piscam no subsolo da base.\n");
            break;

        case 3:
            printf("                      FASE 3\n");
            printf("                O NUCLEO DO SISTEMA\n");
            printf("------------------------------------------------------\n");
            printf("Missao: Vasculhe as casas [ ? ] para baixar o\n");
            printf("CODIGO DE SOBRESCRITA, e elimine o Virus Primordial.\n");
            printf("Voce chegou ao coracao da instalacao. A energia pulsa\n");
            break;
    }
    printf("======================================================\n");
}

void exibirMensagemFinal(Personagem jogador){
    if (!verificarCargaMin(&jogador)){
        printf("\n======================================================\n");
        printf(" [ MISSÃO CUMPRIDA ] - CONTROLE DO SISTEMA RESTAURADO\n");
        printf("------------------------------------------------------\n");
        printf("Parabéns, Unidade %s!\n", jogador.nome);
        printf("O Vírus Primordial foi completamente expurgado.\n");
        printf("As luzes de emergência apagam-se enquanto o mainframe\n");
        printf("reinicia os protocolos de segurança padrão.\n");
        printf("O Setor Alfa está a salvo graças a você.\n\n");
        printf("                   VITÓRIA TOTAL!\n");
        printf("======================================================\n\n");
    }
    else{
        printf("\n======================================================\n");
        printf("      [ FALHA CATASTRÓFICA ] - BATERIA ESGOTADA\n");
        printf("------------------------------------------------------\n");
        printf("A sua visão ótica escurece à medida que a energia cai a 0%%.\n");
        printf("Os seus circuitos param de responder. O Vírus Primordial\n");
        printf("acaba de consumir os últimos vestígios do mainframe.\n");
        printf("O Setor Alfa foi perdido para sempre...\n\n");
        printf("                     GAME OVER\n");
        printf("======================================================\n\n");
    }
}

void moverJogador(Personagem *jogador, int *posicaoAtual, Tipocasa tabuleiro[], int tamanho, int faseAtual){
    int dado = jogarDado(6);
    printf("O dado parou no número %d!\n", dado);
    *posicaoAtual += dado;

    if(*posicaoAtual >= tamanho){
        *posicaoAtual = tamanho - 1;
    }

    if(tabuleiro[*posicaoAtual] == CASA_CHEFAO){
        if (faseAtual >= 2 && jogador->missaoCumprida == 0) {
            printf("\nACESSO NEGADO! Faltam credenciais!\n");
            printf("Você precisa encontrar o item na casa [ ? ] antes do chefe.\n");
            printf("Teletransportando para o início do setor...\n");
            *posicaoAtual = 0;
        } 
        else {
            executarEvento(jogador, tabuleiro[*posicaoAtual], faseAtual);
        }

    }
    else{
        executarEvento(jogador,tabuleiro[*posicaoAtual], faseAtual);
    }
}

void jogarFase(Personagem *jogador, Tipocasa tabuleiro[], int tamanho, int faseAtual){
    int posicaoAtual = 0;
    int opcao = 0;
    jogador->missaoCumprida = 0;

    while (jogador->missaoCumprida != 2 && !verificarCargaMin(jogador)){
        exibirTabuleiro(tamanho, posicaoAtual, tabuleiro);

        printf("Bateria: %d/%d | Posicao: %d\n", jogador->cargaAtual, jogador->cargaMaxima, posicaoAtual);
        printf("1 - Rolar Dado de Movimento\n");
        printf("2 - Ver Status do Androide\n");
        
        do {
            printf("Opcao: ");
            opcao = lerOpcaoSegura();
            switch (opcao){
                case 1:
                    moverJogador(jogador, &posicaoAtual, tabuleiro, tamanho, faseAtual);
                    break;
                case 2:
                    exibirStatusHeroi(jogador);
                    break;
                default:
                    printf("Opção inválida!\n");
                    break;
    
            }
        } while(opcao > 2 || opcao < 1);
    }
}