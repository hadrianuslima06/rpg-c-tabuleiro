#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

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
    char acessorio[50];
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



#endif