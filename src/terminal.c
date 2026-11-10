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