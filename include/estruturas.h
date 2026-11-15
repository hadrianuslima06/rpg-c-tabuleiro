#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

// enumeração de classe de android
typedef enum {
    VANGUARDA = 1,
    INFILTRADOR,
    ARTILHEIRO
} ClasseRobo;

// enumeração dos tipos de habilidades
typedef enum{
    PROTECAO_DANO,
    ROUBO_CARGA,
    MAIOR_DANO
} Tipohabilidade;

// enumeração dos tipos de casa do tabuleiro, para melhorar a leitura do switch case
typedef enum {
    CASA_VAZIA,
    CASA_COMBATE,
    CASA_RECARGA,
    CASA_VIRUS,
    CASA_CHEFAO,
    CASA_RECOMPENSA,
    CASA_OBJETIVO
} Tipocasa;

// enumeração das ações de combate
typedef enum{
    ATACAR = 1,
    DEFENDER,
    HABILIDADE_ESPECIAL,
    FUGIR
} Tipoacao;

// aqui esta a estrutura personagem
typedef struct {
    char nome[50];
    char acessorio[50];
    int cargaAtual;
    int cargaMaxima;
    int poderAtaque;
    int blindagem;
    int velocidadeProcessamento;
    int xp;
    int nivel;
    int missaoCumprida;
    ClasseRobo classe;
    Tipohabilidade habilidade; 
} Personagem;

// essa é a estrutura dos monstros e dos vilões
typedef struct{
    char nome[50];
    int cargaAtual;
    int poderAtaque;
    int blindagem;
    int xpLiberado;
} Monstro;

#endif