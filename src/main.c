#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define TAMANHO_TABULEIRO 20

typedef enum {
    VANGUARDA = 1,
    INFILTRADOR,
    ARTILHEIRO
} ClasseRobo;

typedef enum{
    PROTECAO_DANO,
    ROUBO_CARGA,
    MAIOR_DANO
} Tipohabilidade;

typedef enum {
    CASA_VAZIA,
    CASA_COMBATE,
    CASA_RECARGA,
    CASA_VIRUS,
    CASA_MISSAO
} Tipocasa;

typedef struct {
    char nome[50];
    int cargaAtual;
    int cargaMaxima;
    int poderAtaque;
    int blindagem;
    int velocidadeProcessamento;
    int xp;
    ClasseRobo classe;
    Tipohabilidade habilidade; 
} Personagem;

typedef struct{
    char nome[50];
    int cargaAtual;
    int poderAtaque;
    int blindagem;
    int xpLiberado;
} Monstro;

void criarPesonagem(Personagem *p);
void inicializarTabuleiro(Tipocasa tabuleiro[], int tamanho);
int jogarDado(int lados);
void exibirTabuleiro(int tamanho, int posicaoHeroi, Tipocasa tabuleiro[]);
void executarEvento(Personagem *jogador, int tipoCasa, int faseAtual);
void verificarCargaMax(Personagem *j);
void iniciarCombate(Personagem *jogador, int faseAtual);

int main(){
    srand(time(NULL));
    Personagem heroi;
    criarPesonagem(&heroi);

    Tipocasa mapa[TAMANHO_TABULEIRO];
    inicializarTabuleiro(mapa, TAMANHO_TABULEIRO);

    int faseAtual = 1;
    int ultimaFase = 3;

    while (faseAtual <= ultimaFase){
        int posicaoAtual = 0;
        int missaoCumprida = 0;
        int opcao = 0;

        printf("-------- FASE %d --------\n", faseAtual);
        while (!missaoCumprida && heroi.cargaAtual > 0){
            exibirTabuleiro(TAMANHO_TABULEIRO, posicaoAtual, mapa);
            int dado;
    
            printf("Bateria: %d/%d | Posicao: %d\n", heroi.cargaAtual, heroi.cargaMaxima, posicaoAtual);
            printf("1 - Rolar Dado de Movimento\n");
            printf("2 - Ver Status do Androide\n");
            
            do {
                printf("Opcao: ");
                scanf("%d", &opcao);
                switch (opcao){
                    case 1:
                        dado = jogarDado(6);
                        printf("O dado parou no número %d!\n", dado);
                        posicaoAtual += dado;
        
                        if(posicaoAtual >= TAMANHO_TABULEIRO){
                            posicaoAtual = TAMANHO_TABULEIRO - 1;
                        }
        
                        if(mapa[posicaoAtual] == CASA_MISSAO){
                            printf("ATENÇÃO: Você chegou ao núcleo do setor\n");
                            missaoCumprida = 1;
                        }
                        else{
                            executarEvento(&heroi,mapa[posicaoAtual]);
                        }
                        break;
                    
                    case 2:
                        printf("\n------- STATUS DO HERÓI -------\n");
                        printf("CLASSE: %d\n", heroi.classe);
                        printf("CARGA: %d\n", heroi.cargaAtual);
                        printf("ATAQUE: %d\n", heroi.poderAtaque);
                        printf("BLINDAGEM: %d\n", heroi.blindagem);
                        break;
                    default:
                        printf("Opção inválida!\n");
                        break;
        
                }
            } while(opcao > 2 || opcao < 1);
        }

        faseAtual++;
        if (faseAtual <= ultimaFase){
            printf("Avançando para a fase %d...\n", faseAtual);
        }


    }
    
    return 0;
}


void criarPesonagem(Personagem *p){
    int escolha = 0;

    printf("------ SISTEMA DE INICIALIZAÇÃO ------\n");
    printf("Informe um nome para sua Unidade: ");
    scanf("%s", p->nome);

    printf("Selecione a classe do seu Android de combate\n");
    printf("1 - Vanguarda (Foco em Blindagem)\n");
    printf("2 - Infiltrador (Foco em Processamento e Agilidade)\n");
    printf("3 - Artilheiro (Foco em Poder de Fogo)\n");
    
    p->xp = 0;
    
    do{
        printf("Opcao: ");
        scanf("%d", &escolha);
        switch(escolha) {
            case VANGUARDA:
                p->classe = VANGUARDA;
                p->cargaMaxima = 150;
                p->cargaAtual = 150;
                p->poderAtaque = 10;
                p->blindagem = 15;
                p->velocidadeProcessamento = 5;
                p->habilidade = PROTECAO_DANO;
                break;
            case INFILTRADOR:
                p->classe = INFILTRADOR;
                p->cargaMaxima = 100;
                p->cargaAtual = 100;
                p->poderAtaque = 12;
                p->blindagem = 8;
                p->velocidadeProcessamento = 18;
                p->habilidade = ROUBO_CARGA;
                break;
            case ARTILHEIRO:
                p->classe = ARTILHEIRO;
                p->cargaMaxima = 90;
                p->cargaAtual = 90;
                p->poderAtaque = 20;
                p->blindagem = 5;
                p->velocidadeProcessamento = 10;
                p->habilidade = MAIOR_DANO;
                break;
            default:
                printf("Opcao invalida! Você precisa selecionar um Herói.\n");
                break;
        }
    } while (escolha > 3 || escolha < 1);
}

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

int jogarDado(int lados){
    return (rand() % lados) + 1;
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
            printf("Acesso ao núcleo concedido. Preparando reinicializacao...\n");
            break;
    }
}

void iniciarCombate(Personagem *jogador, int faseAtual){
    Monstro inimigo;
    if ((rand() % 2) == 1){
        inimigo.cargaAtual = 30 * faseAtual;
        strcpy(inimigo.nome, "Drone defeituoso");
        inimigo.poderAtaque = 10 + (2 * faseAtual);
        inimigo.blindagem = 3 + faseAtual;
        inimigo.xpLiberado = 10 * faseAtual;
    }
    else{
        inimigo.cargaAtual = 40 * faseAtual;
        strcpy(inimigo.nome, "Guarda cibernético");
        inimigo.poderAtaque = 13 + (3 * faseAtual);
        inimigo.blindagem = 3 + (2 * faseAtual);
        inimigo.xpLiberado = 20 * faseAtual;
    }
    printf("INIMIGO: %s", inimigo.nome);

    int opcao, dado, dano, danoRecebido, defesaEfetiva = jogador->blindagem, fugiu = 0;

    do{
        printf("SEU HP: %d/%d\n", jogador->cargaAtual, jogador->cargaMaxima);
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
            jogador->cargaAtual -= danoRecebido;
        }

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
    }
    
}

void verificarCargaMax(Personagem *j){
    if (j->cargaAtual > j->cargaMaxima){
        j->cargaAtual = j->cargaMaxima;
    }
}