/*
 * File:  estruturas.h
 * Author:  Miguel Barbosa
 * Description: Ficheiro *.h que contém as estruturas usadas no Projeto 2.
*/


#ifndef _ESTRUTURAS_H_
#define _ESTRUTURAS_H_

/* Estrutura para as carreiras. */

typedef struct node_carreira {
    char* nome;
    int id_carreira, id_LigacaoOrigem, id_LigacaoDestino;
    char* par_origem, *par_destino;
    int contador_par;
    double custoTotal, duracaoTotal;
    struct node_carreira *prev, *next;
} Carreira;

/* Estrutura que contém o início e o fim da lista de carreiras. */

typedef struct {
    int _total_Carreiras;
    struct node_carreira *inicio, *fim;
} lista_Carreiras;


/* Estrutura para as carreiras da lista de carreiras de uma paragem. */

typedef struct node_carreirasParagem {
    Carreira* carreira;
    struct node_carreirasParagem *next, *prev;
} CarreirasParagem;


/* Estrutura que contém o início e o fim da lista de carreiras de uma paragem. */

typedef struct {
    struct node_carreirasParagem *inicio, *fim;
} lista_carreirasParagem;


/* Estrutura para as paragens. */

typedef struct node_paragem {
    char* nome;
    double latitude;
    double longitude; 
    lista_carreirasParagem* carreiras;
    int numCarreiras;
    struct node_paragem *prev, *next;
} Paragem;

/* Estrutura que contém o início e o fim da lista de paragens. */

typedef struct {
    struct node_paragem *inicio, *fim;
} lista_Paragens;


/* Estrutura para as ligações. */

typedef struct node_ligacao {
    int id_carreira, id_ligacao;
    Paragem* par_origem;
    Paragem* par_destino;
    double custo;
    double duracao;
    struct node_ligacao *prev, *next;
} Ligacao;

/* Estrutura que contém o início e o fim da lista de ligações. */

typedef struct {
    struct node_ligacao *inicio, *fim;
} lista_Ligacoes;



#endif