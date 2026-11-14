#include <stdlib.h>
#include <stdio.h>

void limpar_terminal(){
    system("clear");
}
void pausar(){
    printf("Clique em ENTER para continuar.\n");

    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    getchar();
}

int lerOpcaoSegura() {
    int opcao;
    // Se o usuário digitar uma letra, scanf retorna 0 (diferente de 1)
    if (scanf("%d", &opcao) != 1) {
        int c;
        // O aspirador de pó em ação limpando o lixo do buffer:
        while ((c = getchar()) != '\n' && c != EOF); 
        
        return -1; // Retorna -1 para forçar o código a cair no 'default' dos menus
    }
    return opcao; // Se digitou número certinho, devolve o número
}

void exibirPrologo(){
    limpar_terminal();
    printf("==================================================================\n");
    printf(" [BIOS] REINICIALIZACAO DE EMERGENCIA CONCLUIDA...\n");
    printf(" [SISTEMA] Integridade do casco: 100%% | Rede neural: ISOLADA\n");
    printf(" [ALERTA!!!] Conexao com o Mainframe do Setor Alfa: PERDIDA\n");
    printf("==================================================================\n\n");
    printf("*chiado de radio*\n\n");
    printf("[DRA. Helena]: \"Ei... tem alguem ai? O painel acusou pico de energia na\n");
    printf(" baia de isolamento. Se voce estiver me ouvindo, responde.\"\n\n");
    printf("[DRA. Helena]: \"Sou a Helena, da equipe de sistemas. Deu tudo errado por\n");
    printf(" aqui — um virus derrubou o mainframe e assumiu o controle das\n");
    printf(" maquinas do Setor Alfa. Esta tudo trancado e o reator ja comecou\n");
    printf(" a superaquecer.\"\n\n");
    printf("[DRA. Helena]: \"Como voce estava desligado da rede principal, e a unica\n");
    printf(" unidade que nao foi infectada. Preciso liberar a porta da sua\n");
    printf(" sala, mas o sistema pede um identificador. Qual e o seu nome?\"\n");
    printf("------------------------------------------------------------------\n");
}
