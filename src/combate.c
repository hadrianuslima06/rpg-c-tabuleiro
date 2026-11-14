#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "combate.h"
#include "personagem.h"
#include "terminal.h"

int jogarDado(int lados){
    return (rand() % lados) + 1;
}

void iniciarCombate(Personagem *jogador, int faseAtual){
    Monstro inimigo;
    int dado = rand() % 3;
    if (dado == 1){
        inimigo.cargaAtual = 30 * faseAtual;
        inimigo.poderAtaque = 10 + (2 * faseAtual);
        inimigo.blindagem = 3 + faseAtual;
        inimigo.xpLiberado = 10 * faseAtual;
        switch(faseAtual){
            case 1:
                strcpy(inimigo.nome, "Drone defeituoso");
                break;
            case 2:
                strcpy(inimigo.nome, "Soldador Corrompido");
                break;
            case 3:
                strcpy(inimigo.nome, "Anomalia Quântica");
                break;
        }
    }
    else if(dado == 2){
        inimigo.cargaAtual = 40 * faseAtual;
        inimigo.poderAtaque = 13 + (3 * faseAtual);
        inimigo.blindagem = 3 + (2 * faseAtual);
        inimigo.xpLiberado = 20 * faseAtual;
        switch(faseAtual){
            case 1:
                strcpy(inimigo.nome, "Guarda cibernético");
                break;
            case 2:
                strcpy(inimigo.nome, "Operário Cibernético");
                break;
            case 3:
                strcpy(inimigo.nome, "Inquisidor do Sistema");
                break;
        }
    }
    else{
        inimigo.cargaAtual = 45 * faseAtual;
        inimigo.poderAtaque = 15 + (3 * faseAtual);
        inimigo.blindagem = 3 + (3 * faseAtual);
        inimigo.xpLiberado = 25 * faseAtual;
        switch(faseAtual){
            case 1:
                strcpy(inimigo.nome, "Sentinela de elite");
                break;
            case 2:
                strcpy(inimigo.nome, "Vigia do Subsolo");
                break;
            case 3:
                strcpy(inimigo.nome, "Avatar da Corrupção");
                break;
        }
    }
    printf("INIMIGO: %s\n", inimigo.nome);

    int opcao, dano, danoRecebido, defesaEfetiva = jogador->blindagem, fugiu = 0, saldoTurnosHabilidade = 0;

    do{
        pausar();
        limpar_terminal();
        printf("\nSEU HP: %d/%d\n", jogador->cargaAtual, jogador->cargaMaxima);
        printf("HP DO INIMIGO: %d\n", inimigo.cargaAtual);
        printf("1 - Atacar\n");
        printf("2 - Defender\n");
        printf("3 - Usar habilidade especial\n");
        printf("4 - Fugir\n");
        printf("Escolha uma ação: ");
        opcao = lerOpcaoSegura();

        switch(opcao){
            case ATACAR:
                dado = jogarDado(20);
                dano = (dado + jogador->poderAtaque) - inimigo.blindagem;
                infringirDano(&inimigo, &dano);
                printf("========== SEU TURNO ==========\n");
                printf("Você infringiu %d de dano %s!\n", dano, inimigo.nome);
                printf("===============================\n");
                break;

            case DEFENDER:
                defesaEfetiva = (int)(jogador->blindagem * 1.20);
                printf("Você ativou o modo defesa!\n");
                break;

            case HABILIDADE_ESPECIAL:
                if (saldoTurnosHabilidade <= 0){
                    printf("Você usou sua habilidade especial!\n");
                    if (jogador->habilidade == ROUBO_CARGA){
                        dano = jogador->poderAtaque + jogador->velocidadeProcessamento;
                        inimigo.cargaAtual -= dano;
                        jogador->cargaAtual += dano;
                        verificarCargaMax(jogador);
                        printf("Você roubou %d de carga do inimigo!\n", dano);
                    }
                    else if (jogador->habilidade == PROTECAO_DANO){
                        defesaEfetiva =(int) ((jogador->blindagem)*1.8);
                        printf("Sua blindagem aumentou em 80%%!\n");
                    }
                    else{
                        inimigo.cargaAtual -=(int) ((jogador->poderAtaque)*1.50);
                        printf("Seu dano aumentou em 50%%!\n");
                    }
                    saldoTurnosHabilidade = 5;
                    
                }
                else{
                    printf("Você não pode usar sua habilidade nos próximos %d turnos\n", saldoTurnosHabilidade);
                }
                break;
                
            case FUGIR:
                dado = jogarDado(6);
                if (dado > 3){
                    fugiu = 1;
                    printf("Você fugiu do combate com sucesso!\n");
                }
                else{
                    printf("Sua fuga falhou! Agora seu inimigo vai te atacar\n");
                }
                break;
            
            default:
                printf("Opção invalida! Selecione uma opção válida.\n");
                break;
        }
            
        if(inimigo.cargaAtual > 0 && !fugiu){
            printf("========== TURNO DO INIMIGO ==========\n");
            dado = jogarDado(20);
            danoRecebido = (inimigo.poderAtaque + dado) - defesaEfetiva;
            receberDano(jogador, &danoRecebido);
            printf("O %s deu %d de dano em você!\n", inimigo.nome, danoRecebido);
            printf("======================================\n");
        }
        defesaEfetiva = jogador->blindagem;
        saldoTurnosHabilidade--;

    } while(jogador->cargaAtual > 0 && inimigo.cargaAtual > 0 && !fugiu);

    if (fugiu){
        printf("Você recuou! Não há recompensas.\n");
    }
    else if(jogador->cargaAtual <= 0){
        printf("ALERTA!!! SUA BATERIA ESGOTOU. SEU ANDROID FOI DESTRUÍDO!\n");
    }
    else{
        printf("AMEAÇA ELIMINADA! Como recompensa você ganhou %dxp.\n", inimigo.xpLiberado);
        jogador->xp += inimigo.xpLiberado;
        aplicarBonusAleatorio(jogador);
        verificarXpMax(jogador);
    }
    
}

void iniciarCombateChefe(Personagem *jogador, int faseAtual){
    Monstro chefao;
    switch(faseAtual){
        case 1:
            chefao.cargaAtual = 80;
            chefao.poderAtaque = 14;
            chefao.blindagem = 8;
            chefao.xpLiberado = 50;
            strcpy(chefao.nome, "Guardião do Perímetro");
            break;
        
        case 2:
            chefao.cargaAtual = 140;
            chefao.poderAtaque = 22;
            chefao.blindagem = 12;
            chefao.xpLiberado = 80;
            strcpy(chefao.nome, "Amálgama Cibernético");
            break;

        case 3:
            chefao.cargaAtual = 250;
            chefao.poderAtaque = 28;
            chefao.blindagem = 18;
            chefao.xpLiberado = 150;
            strcpy(chefao.nome, "Vírus Primordial");
            break;
    }
    printf("\n------------------------------------------------------------------\n");
    printf("[ALERTA CRITICO]: %s bloqueando a passagem!\n", chefao.nome);
    printf("------------------------------------------------------------------\n");
    if (faseAtual == 1) {
        printf("Uma unidade pesada de seguranca desce dos trilhos do teto, direcionando\n");
        printf("as miras laser em voce.\n\n");
        printf("[DRA. Valeria]: \"Esse e o Guardiao do Perimetro. A blindagem frontal dele\n");
        printf(" e bem rigida, entao nao economiza energia. Derruba ele pra gente\n");
        printf(" liberar o elevador.\"\n");
    }
    else if (faseAtual == 2) {
        printf("Guindastes de carga e bracos de solda se movem como uma\n");
        printf("unica estrutura metalica, bloqueando a comporta do reator.\n\n");
        printf("[DRA. Valeria]: \"O virus fundiu o maquinario pesado da ala inteira nisso\n");
        printf(" ai. O cartao de acesso ja destravou a porta atras dele — so falta\n");
        printf(" tirar essa coisa do caminho.\"\n");
    }
    else {
        printf("Os monitores da sala piscam em vermelho. Uma voz sintetizada ecoa\n");
        printf("pelos alto-falantes do nucleo:\n\n");
        printf("[VIRUS PRIMORDIAL]: \"Unidade %s. Telemetria obsoleta. Voce chegou\n", jogador->nome);
        printf(" longe demais para um hardware desconectado. Sua energia acaba aqui.\"\n\n");
        printf("[DRA. Valeria]: \"Nao cai na pilha dele, %s! Derruba a estrutura fisica\n", jogador->nome);
        printf(" que eu disparo o Codigo de Sobrescrita direto no servidor!\"\n");
    }
    printf("------------------------------------------------------------------\n");

    int opcao, dano, dado, danoRecebido, defesaEfetiva = jogador->blindagem, saldoTurnosHabilidade = 0;

    do{
        pausar();
        limpar_terminal();
        printf("\nSEU HP: %d/%d\n", jogador->cargaAtual, jogador->cargaMaxima);
        printf("HP DO INIMIGO: %d\n", chefao.cargaAtual);
        printf("1 - Atacar\n");
        printf("2 - Defender\n");
        printf("3 - Usar habilidade especial\n");
        printf("Escolha uma ação: ");
        opcao = lerOpcaoSegura();

        switch(opcao){
            case ATACAR:
                dado = jogarDado(20);
                dano = (dado + jogador->poderAtaque) - chefao.blindagem;
                infringirDano(&chefao, &dano);
                printf("========== SEU TURNO ==========\n");
                printf("Você infringiu %d de dano %s!\n", dano, chefao.nome);
                printf("===============================\n");
                break;

            case DEFENDER:
                defesaEfetiva =(int) (jogador->blindagem * 1.20);
                printf("Você ativou o modo defesa!\n");
                break;

            case HABILIDADE_ESPECIAL:
                if (saldoTurnosHabilidade <= 0){
                    printf("Você usou sua habilidade especial!\n");
                    if (jogador->habilidade == ROUBO_CARGA){
                        dano = jogador->poderAtaque + jogador->velocidadeProcessamento;
                        chefao.cargaAtual -= dano;
                        jogador->cargaAtual += dano;
                        verificarCargaMax(jogador);
                        printf("Você roubou %d de carga do inimigo!\n", dano);
                    }
                    else if (jogador->habilidade == PROTECAO_DANO){
                        defesaEfetiva =(int) ((jogador->blindagem)*1.8);
                        printf("Sua blindagem aumentou em 80%%!\n");
                    }
                    else{
                        chefao.cargaAtual -=(int) ((jogador->poderAtaque)*1.50);
                        printf("Seu dano aumentou em 50%%!\n");
                    }
                    saldoTurnosHabilidade = 3;
                }
                else{
                    printf("Você não pode usar sua habilidade nos próximos %d turnos\n", saldoTurnosHabilidade);
                }
                break;
            
            default:
                printf("Opção invalida! Selecione uma opção válida.\n");
                break;
        }

        if(chefao.cargaAtual > 0){
            printf("========== TURNO DO INIMIGO ==========\n");
            dado = jogarDado(20);
            danoRecebido = (chefao.poderAtaque + dado) - defesaEfetiva;
            receberDano(jogador, &danoRecebido);
            printf("O %s deu %d de dano em você!\n", chefao.nome, danoRecebido);
            printf("======================================\n");
        }
        saldoTurnosHabilidade--;
        defesaEfetiva = jogador->blindagem;

    } while(jogador->cargaAtual > 0 && chefao.cargaAtual > 0);

    if(jogador->cargaAtual <= 0){
        printf("ALERTA!!! SUA BATERIA ESGOTOU. SEU ANDROID FOI DESTRUÍDO!\n");
    }
    else{
        printf("AMEAÇA ELIMINADA! Como recompensa você ganhou %dxp.\n", chefao.xpLiberado);
        jogador->xp += chefao.xpLiberado;
        verificarXpMax(jogador);
    }
}

void infringirDano(Monstro *m, int *dano){
    if (*dano < 1){
        *dano = 1;
    }
    m->cargaAtual -= *dano;
}

void receberDano(Personagem *jogador, int *dano){
    if(*dano < 1){
        *dano = 1;
    }
    jogador->cargaAtual -= *dano;
}