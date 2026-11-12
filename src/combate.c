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
        strcpy(inimigo.nome, "Drone defeituoso");
        inimigo.poderAtaque = 10 + (2 * faseAtual);
        inimigo.blindagem = 3 + faseAtual;
        inimigo.xpLiberado = 10 * faseAtual;
    }
    else if(dado == 2){
        inimigo.cargaAtual = 40 * faseAtual;
        strcpy(inimigo.nome, "Guarda cibernético");
        inimigo.poderAtaque = 13 + (3 * faseAtual);
        inimigo.blindagem = 3 + (2 * faseAtual);
        inimigo.xpLiberado = 20 * faseAtual;
    }
    else{
        inimigo.cargaAtual = 45 * faseAtual;
        strcpy(inimigo.nome, "Sentinela de elite");
        inimigo.poderAtaque = 15 + (3.5 * faseAtual);
        inimigo.blindagem = 3 + (3 * faseAtual);
        inimigo.xpLiberado = 25 * faseAtual;
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
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                dado = jogarDado(20);
                printf("Seu dado caiu em %d!\n", dado);
                dano = (dado + jogador->poderAtaque) - inimigo.blindagem;
                if (dano < 1){
                    dano = 1;
                }
                printf("Você infringiu %d de dano %s!\n", dano, inimigo.nome);
                inimigo.cargaAtual -= dano;
                break;

            case 2:
                defesaEfetiva = jogador->blindagem * 1.20;
                printf("Você ativou o modo defesa!\n");
                break;

            case 3:
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
                        defesaEfetiva = (jogador->blindagem)*1.8;
                        printf("Sua blindagem aumentou em 80%%!\n");
                    }
                    else{
                        inimigo.cargaAtual -= (jogador->poderAtaque)*1.50;
                        printf("Seu dano aumentou em 50%%!\n");
                    }
                    saldoTurnosHabilidade = 5;
                    
                }
                else{
                    printf("Você não pode usar sua habilidade nos próximos %d turno\n", saldoTurnosHabilidade);
                }
                break;
                
                case 4:
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
            }
            
            if(inimigo.cargaAtual > 0 && !fugiu){
                printf("Turno do inimigo\n");
                dado = jogarDado(20);
                
                danoRecebido = (inimigo.poderAtaque + dado) - defesaEfetiva;
                if(danoRecebido < 1){
                    danoRecebido = 1;
                }
                printf("O %s deu %d de dano em você!\n", inimigo.nome, danoRecebido);
                jogador->cargaAtual -= danoRecebido;
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

    int opcao, dano, dado, danoRecebido, defesaEfetiva = jogador->blindagem, fugiu = 0, saldoTurnosHabilidade = 0;

    do{
        pausar();
        limpar_terminal();
        printf("\nSEU HP: %d/%d\n", jogador->cargaAtual, jogador->cargaMaxima);
        printf("HP DO INIMIGO: %d\n", chefao.cargaAtual);
        printf("1 - Atacar\n");
        printf("2 - Defender\n");
        printf("3 - Usar habilidade especial\n");
        printf("Escolha uma ação: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                dado = jogarDado(20);
                printf("Seu dado caiu em %d!\n", dado);
                dano = (dado + jogador->poderAtaque) - chefao.blindagem;
                if (dano < 1){
                    dano = 1;
                }
                printf("Você infringiu %d de dano %s!\n", dano, chefao.nome);
                chefao.cargaAtual -= dano;
                break;

            case 2:
                defesaEfetiva = jogador->blindagem * 1.20;
                printf("Você ativou o modo defesa!\n");
                break;

            case 3:
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
                        defesaEfetiva = (jogador->blindagem)*1.8;
                        printf("Sua blindagem aumentou em 80%%!\n");
                    }
                    else{
                        chefao.cargaAtual -= (jogador->poderAtaque)*1.50;
                        printf("Seu dano aumentou em 50%%!\n");
                    }
                    saldoTurnosHabilidade = 3;
                }
                else{
                    printf("Você não pode usar sua habilidade nos próximos %d turno\n", saldoTurnosHabilidade);
                }
                break;
            
            default:
                printf("Opção invalida! Selecione uma opção válida.\n");
        }

        if(chefao.cargaAtual > 0 && !fugiu){
            printf("Turno do inimigo\n");
            dado = jogarDado(20);

            danoRecebido = (chefao.poderAtaque + dado) - defesaEfetiva;
            if(danoRecebido < 1){
                danoRecebido = 1;
            }
            printf("O %s deu %d de dano em você!\n", chefao.nome, danoRecebido);
            jogador->cargaAtual -= danoRecebido;
        }
        saldoTurnosHabilidade--;

    } while(jogador->cargaAtual > 0 && chefao.cargaAtual > 0 && !fugiu);

    if(jogador->cargaAtual <= 0){
        printf("ALERTA!!! SUA BATERIA ESGOTOU. SEU ANDROID FOI DESTRUÍDO!\n");
    }
    else{
        printf("AMEAÇA ELIMINADA! Como recompensa você ganhou %dxp.\n", chefao.xpLiberado);
        jogador->xp += chefao.xpLiberado;
        verificarXpMax(jogador);
    }
}