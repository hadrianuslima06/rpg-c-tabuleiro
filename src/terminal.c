#include <stdlib.h>
#include <stdio.h>
#include "terminal.h"

// essa função foi implementada para usar ao decorrer do jogo
// para deixar visualmente mais agradável
// funciona tanto em Linux, MacOS e Windows
void limpar_terminal(){
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

// Essa função de o objetivo caracteres pendentes do buffer
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    // o getchar retira o proximo caracter da fila e atribui na variavel c (int porque essa 
    // função retorna numeros interiro de 0 a 255), depois ele verifica se esse C é diferente
    // de \n(enter) e se é diferente de EOF (fim do arquivo)
    // esse laço de repete ate uma das condições de para for satisfeita
}

// Fiz essa função para dar certas pausas no jogo, principalmente  em dialgos e interações
void pausar() {
    printf("Clique em ENTER para continuar.\n");
    limparBuffer();
    // utiliza a função anterior ate que o jogador clique em ENTER
}

// fiz essa função para verificar se o usuario não digitou uma letra ao inves de um numero
int lerOpcaoSegura() {
    int opcao;
    int status = scanf("%d", &opcao);
    // como a função scanf retorna a quantidade de itens que foram lidos, atribui isso na
    // variavel status
    limparBuffer();

    // aqui verifiquei se o status é diferente de 1, se for, significa que o usuario informou
    // um dado invalido, retornado -1 pra essa função
    // esse -1 retornado vai fazer com que a opção caia no default do switch case
    if (status != 1) {
        return -1;
    }
    return opcao;
}

// apenas para introduzir o jogo
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