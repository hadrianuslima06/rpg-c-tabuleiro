#include <stdlib.h>
#include <stdio.h>
#include "terminal.h"

void limpar_terminal(){
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
void pausar() {
    printf("Clique em ENTER para continuar.\n");
    limparBuffer();
}

int lerOpcaoSegura() {
    int opcao;
    int status = scanf("%d", &opcao);
    limparBuffer();

    if (status != 1) {
        return -1;
    }
    return opcao;
}

void exibirPrologo(){
    limpar_terminal();
    printf("==================================================================\n");
    printf(" [BIOS] REINICIALIZACAO DE EMERGENCIA CONCLUIDA...\n");
    printf(" [SISTEMA] Integridade do casco: 100%% | Rede neural: ISOLADA\n");
    printf(" [ALERTA!!!] Conexao com o Mainframe do Setor Alfa: PERDIDA\n");
    printf("==================================================================\n\n");
    printf("*chiado de radio*\n\n");
    printf("[DRA. Valeria]: \"Ei... tem alguem ai? O painel acusou pico de energia na\n");
    printf(" baia de isolamento. Se voce estiver me ouvindo, responde.\"\n\n");
    printf("[DRA. Valeria]: \"Sou a Valeria, da equipe de sistemas. Deu tudo errado por\n");
    printf(" aqui, um virus derrubou o mainframe e assumiu o controle das\n");
    printf(" maquinas do Setor Alfa. Esta tudo trancado e o reator ja comecou\n");
    printf(" a superaquecer.\"\n\n");
    printf("[DRA. Valeria]: \"Como voce estava desligado da rede principal, e a unica\n");
    printf(" unidade que nao foi infectada. Preciso liberar a porta da sua\n");
    printf(" sala, mas o sistema pede um identificador. Qual e o seu nome?\"\n");
    printf("------------------------------------------------------------------\n");
}
