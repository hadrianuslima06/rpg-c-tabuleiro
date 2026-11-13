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