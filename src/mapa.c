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

void executarEvento(Personagem *jogador, Tipocasa tipoCasa, int faseAtual){
    int dado;
    switch(tipoCasa){
        case CASA_VAZIA:
            dado = jogarDado(3);
            if (dado == 1){
                printf("Corredor silencioso. Apenas o zumbido das luzes de emergencia.\n");
            }
            else if (dado == 2){
                printf("Voce ouve passos no setor vizinho, mas ninguem aparece.\n");
            }
            else{
                printf("[DRA. Valeria]: \"Sinal limpo nesse trecho. Pode continuar avancando.\"\n");
            }
            break;
        case CASA_RECARGA:
            jogador->cargaAtual += 20;
            verificarCargaMax(jogador);
            
            printf("[Acoplamento concluido. +20 de carga.]\n");
            printf("[DRA. Valeria]: \"Boa, achou um ponto de recarga ativo.\"\n");
            printf("CARGA ATUAL: %d/%d\n", jogador->cargaAtual, jogador->cargaMaxima);
            break;
        case CASA_VIRUS:
            jogador->cargaAtual -= 15;
            printf("[ALERTA]: Pulso de interferencia do virus atingiu seus circuitos! -15 de carga.\n");
            printf("[DRA. Valeria]: \"Sua telemetria caiu aqui no meu monitor! Toma cuidado onde pisa.\"\n");
            printf("CARGA ATUAL: %d/%d\n", jogador->cargaAtual, jogador->cargaMaxima);
            break;
        case CASA_COMBATE:
            printf("[DRA. Valeria]: \"Tem maquina corrompida na sua frente. Prepara pra combater!\"\n");
            iniciarCombate(jogador, faseAtual);
            break;
        case CASA_CHEFAO:
            iniciarCombateChefe(jogador, faseAtual);
            if (!verificarCargaMin(jogador)){
                printf("[DRA. Valeria]: \"Ameaca neutralizada! A trava do setor acabou de abrir.\"\n");
                jogador->missaoCumprida = 2;
            }
            break;
        case CASA_RECOMPENSA:
            printf("[Voce abriu um armario de manutencao selado!]\n");
            dado = jogarDado(3);
            if (dado == 1){
                jogador->cargaMaxima += 10;
                jogador->cargaAtual = jogador->cargaMaxima;
                printf("Item encontrado: Celula de alta densidade (+10 Bateria Max e carga recarregada).\n");
                printf("[DRA. Valeria]: \"Essa celula vai dar um folego bom pra sua bateria.\"\n");
            }
            else if (dado == 2){
                jogador->poderAtaque += 10;
                printf("Item encontrado: Amplificador de disparo (+10 Poder de Ataque).\n");
                printf("[DRA. Valeria]: \"Modulo ofensivo acoplado. Seus disparos vao bater bem mais forte agora.\"\n");
            }
            else{
                jogador->blindagem += 15;
                printf("Item encontrado: Placas de reforco composto (+15 em Blindagem).\n");
                printf("[DRA. Valeria]: \"Otimo, esse revestimento extra vai segurar bastante impacto sofrido.\"\n");
            }
            break;
        case CASA_OBJETIVO:
            if (faseAtual == 2){
                if(jogador->missaoCumprida == 0){
                    printf("[Credencial de nivel 2 encontrada.]\n");
                    printf("[DRA. Valeria]: \"Boa! Voce achou o CARTAO DE ACESSO de um dos supervisores.\n");
                    printf(" Agora a comporta no fim do setor vai abrir.\"\n");
                    jogador->missaoCumprida = 1;
                }
                else{
                    printf("[DRA. Valeria]: \"Voce ja coletou o CARTAO DE ACESSO.\n");
                    printf(" Nao precisa parar ai novamente. Va ate o final do corredor.\"\n");
                }
            }
            else if(faseAtual == 3){
                if (jogador->missaoCumprida == 0){
                    printf("[Transferindo patch de limpeza... 100%%.]\n");
                    printf("[DRA. Valeria]: \"CODIGO DE SOBRESCRITA carregado na sua memoria! Quando\n");
                    printf(" voce derrubar o virus, o codigo apaga ele da rede na hora.\"\n");
                    jogador->missaoCumprida = 1;
                } 
                else {
                    printf("[DRA. Valeria]: \"O codigo ja esta na sua memoria. Vai direto pro nucleo!\"\n");
                }
            }
            break;
    }
}

void exibirHistoriaFase(int fase){
    limpar_terminal();
    printf("======================================================\n");
    switch(fase){
        case 1:
            printf("FASE 1 - PERIMETRO EXTERNO\n");
            printf("------------------------------------------------------------------\n");
            printf("A comporta externa abre lentamente. La fora, a chuva fina bate nas\n");
            printf("estruturas metalicas do patio enquanto as sirenes giram no escuro.\n\n");
            printf("[DRA. Valeria]: \"Certo, voce saiu. O patio esta cheio de drones de\n");
            printf(" patrulha e sentinelas que o virus reescreveu pra atacar qualquer\n");
            printf(" coisa que se mova.\"\n\n");
            printf("[DRA. Valeria]: \"O elevador de carga fica no fim desse corredor. Como e\n");
            printf(" area externa, a trava dele e mecanica, portanto nao precisa de cartao.\n");
            printf(" So chega la e derruba o Guardiao do Perimetro.\"\n");
            break;

        case 2:
            printf("FASE 2 - SETOR DE MANUTENCAO E PROCESSAMENTO\n");
            printf("------------------------------------------------------------------\n");
            printf("O elevador para no subsolo industrial. O ar aqui embaixo e quente,\n");
            printf("pesado com cheiro de oleo queimado e faiscas de cabos partidos.\n\n");
            printf("[DRA. Valeria]: \"Voce entrou na parte de manutencao. O virus assumiu os\n");
            printf(" soldadores e operarios pesados daqui, entao o impacto vai ser\n");
            printf(" bem maior que la em cima.\"\n\n");
            printf("[DRA. Valeria]: \"Outra coisa, a porta pro nucleo esta trancada por senha.\n");
            printf(" Para nos terminais [ ? ] pelo caminho pra puxar o CARTAO DE\n");
            printf(" ACESSO antes de encarar o Amalgama Cibernetico no final.\"\n");
            break;

        case 3:
           printf("FASE 3 - O NUCLEO DO SISTEMA\n");
            printf("------------------------------------------------------------------\n");
            printf("Voce chegou a camara do reator. Os servidores centrais vibram com\n");
            printf("uma luz roxa instavel e o proprio ar parece carregado de estatica.\n\n");
            printf("[DRA. Valeria]: \"E aqui. O Virus Primordial esta alojado direto no\n");
            printf(" mainframe. Se voce so destruir o corpo fisico dele, ele faz backup\n");
            printf(" na rede em segundos.\"\n\n");
            printf("[DRA. Valeria]: \"Eu mandei um patch pra rede local. Baixa o CODIGO DE\n");
            printf(" SOBRESCRITA nos terminais [ ? ] antes de atacar, senao nao vai\n");
            printf(" adiantar nada.\"\n");
            break;
    }
    printf("======================================================\n");
}

void exibirMensagemFinal(Personagem jogador){
    if (!verificarCargaMin(&jogador)){
        printf("\n==================================================================\n");
        printf("        [MISSAO CUMPRIDA] - CONTROLE DO SISTEMA RESTAURADO\n");
        printf("==================================================================\n");
        printf("Com o nucleo fisico destruido, o Codigo de Sobrescrita varre os\n");
        printf("servidores centrais. O Virus Primordial e apagado sem deixar backup.\n\n");
        printf("*chiado de radio*\n\n");
        printf("[DRA. Valeria]: \"Conseguimos! O painel aqui na torre acabou de ficar verde.\n");
        printf(" A temperatura do reator geotermico ja esta caindo e os drones\n");
        printf(" voltaram pro modo de espera.\"\n\n");
        printf("[DRA. Valeria]: \"Voce salvou o Setor Alfa e todo mundo la fora em\n");
        printf(" Neo-Veridia. Pode descansar agora, %s. Bom trabalho.\"\n", jogador.nome);
        printf("------------------------------------------------------------------\n");
    }
    else{
        printf("\n==================================================================\n");
        printf("                  [FALHA] - BATERIA ESGOTADA\n");
        printf("==================================================================\n");
        printf("Seus sensores falham ate a tela escurecer por completo.\n");
        printf("Sem carga, sua unidade desliga no piso frio do Setor Alfa.\n\n");
        printf("[DRA. Valeria]: \"%s? Ei, %s, responde! Perdi o seu sinal no monitor...\n", jogador.nome, jogador.nome);
        printf(" Nao, nao agora... o reator passou do ponto critico...\"\n\n");
        printf("Conexao perdida. Sobrecarga do nucleo.\n");
        printf("                            GAME OVER\n");
        printf("==================================================================\n\n");
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
            printf("\n[PORTA TRANCADA]: Acesso negado. Credencial obrigatoria ausente.\n");
            printf("[DEFESA AUTOMATICA]: Protocolo de repulsao ativado!\n");
            printf("[DRA. Valeria]: \"Ei, volta! A trava de seguranca jogou voce pro comeco do\n");
            printf(" corredor. Voce precisa parar na casa [ ? ] antes de ir pra porta!\"\n");
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