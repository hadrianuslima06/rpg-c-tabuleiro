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
    tabuleiro[8] = CASA_COMBATE;
    tabuleiro[11] = CASA_VIRUS;
    tabuleiro[15] = CASA_COMBATE;
    tabuleiro[17] = CASA_RECARGA;
    tabuleiro[tamanho-1] = CASA_MISSAO;
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
        case CASA_MISSAO:
            iniciarCombateChefe(jogador, faseAtual);
            printf("Acesso ao núcleo concedido. Preparando reinicializacao...\n");
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
            printf("Voce e a ultima unidade operacional no setor.\n");
            break;

        case 2:
            printf("                      FASE 2\n");
            printf("        SETOR DE MANUTENCAO E PROCESSAMENTO\n");
            printf("------------------------------------------------------\n");
            printf("Missao: Atravessar a area industrial sem esgotar a bateria.\n");
            printf("As luzes de emergencia piscam no subsolo da base.\n");
            printf("O ar esta denso com o cheiro de circuitos queimados.\n");
            printf("Os guardas ciberneticos pesados bloqueiam o caminho.\n");
            break;

        case 3:
            printf("                      FASE 3\n");
            printf("                O NUCLEO DO SISTEMA\n");
            printf("------------------------------------------------------\n");
            printf("Missao: Alcancar o mainframe e expurgar a ameaca.\n");
            printf("Voce chegou ao coracao da instalacao. A energia pulsa\n");
            printf("de forma instavel e os sistemas estao em colapso.\n");
            printf("Apenas as maquinas de elite protegem este local.\n");
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