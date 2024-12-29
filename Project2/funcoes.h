/*
 * File:  funcoes.h
 * Author:  Miguel Barbosa
 * Description: Ficheiro *.h que contém os protótipos das funções auxiliares do 
            Projeto 2, bem como a sua descrição.
*/


#ifndef _FUNCOES_H_
#define _FUNCOES_H_

#include "estruturas.h"


/* Função que levanta o erro de quando o limite de memória é excedido e termina
    o programa. */

void erroMemoria();


/* Função que cria a lista com a head e a tail da lista total das carreiras; dá
    return da lista de carreiras. */

lista_Carreiras* cria_lista_carreiras();


/* Função que cria a lista com a head e a tail da lista total das paragens; dá
    return da lista de paragens. */

lista_Paragens* cria_lista_paragens();


/* Função que cria a lista com a head e a tail da lista total das ligações; dá
    return da lista de ligações. */

lista_Ligacoes* cria_lista_ligacoes();



            /* ||FUNÇÕES DE LEITURA E VERIFICAÇÃO DE INPUT|| */


/* Devolve 1 se o caracter c é um espaço ou um TAB; caso contrário, devolve 0. */

int caracter_branco(char c);


/* Lê espaços. Devolve 0 se chegou ao final de linha ou 1 caso contrário. */

int leEspacos();


/* Lê um nome para a string que recebe como parâmetro. */

void leNome(char s[]);


/* Lê todo o texto até ao final de linha. */

void leAteFinalLinha(char s[]);


/* Devolve 1 se o input para o inverso estiver escrito conforme as restrições
    do enunciado; caso contrário, devolve 0. */

int carreira_inverso_test(char s[]);



                /* ||FUNÇÕES DE LIBERTAR MEMÓRIA|| */


/* Liberta toda a memória associada a uma ligação. */

void libertaLigacao(Ligacao* lig);


/* Liberta toda a memória a associada a uma carreira */

void libertaCarreira(Carreira* carreira);


/* Liberta toda a memória associada a uma paragem*/

void libertaParagem(Paragem* paragem);


/* Liberta toda a memória associada ao programa. */

void liberta_memoria(lista_Carreiras* _carreiras,
                        lista_Ligacoes* _ligacoes,
                        lista_Paragens* _paragens);


    /* ||FUNÇÕES DE ATUALIZAÇÃO DE NODES DAS LISTAS PRINCIPAIS|| */


/* Atualiza os nodes da lista de carreiras quando se remove uma carreira. */

void atualizaCarreiras(Carreira* carreira, lista_Carreiras* _carreiras);


/* Atualiza os nodes da lista de paragens quando se remove uma paragem. */

void atualizaParagens(Paragem* paragem, lista_Paragens* _paragens);


/* Atualiza os nodes da lista de ligações quando se remove uma ligação. */

void atualizaLigacoes(Ligacao* ligacao, lista_Ligacoes* _ligacoes);


                /* ||FUNÇÕES AUXILIARES AO PROJETO|| */

/* Função que dá printf de todas as carreiras, por ordem de criação, da forma
    descrita no enunciado do projeto. */

void apresentaCarreiras(lista_Carreiras* _carreiras);


/* Função que verifica se a carreira já existe na lista de carreiras; se não
    existir, devolve NAOEXISTENTE; caso contrário, devolve o pointer para o node
    da carreira correspondente. */

Carreira* carreiraNaoExistente(char carreira[], lista_Carreiras* _carreiras);


/* Função que coloca o node recém-criado da carreira na lista de carreiras;
    se a lista de carreiras for vazia, coloca no início; caso contrário, coloca
    no fim e atualiza a tail da lista de carreiras sempre que coloca uma nova. */

void colocaCarreira(lista_Carreiras* _carreiras, Carreira* node);


/* Função que cria uma nova carreira, inicializando todos os parâmetros
    necessários para que esta funcione ao longo do projeto. */

void criaCarreira(char s[], lista_Carreiras* _carreiras);


/* Função que da printf das paragens de uma carreira, pela ordem que estas se
    encontram na carreira; enquanto o id da ligação atual não for igual
    ao id da ligação de destino na carreira, a função não acaba e vai dando printf
    da paragem de origem da ligação, incrementando o índice sempre que encontra uma
    ligação válida para o id da ligação atual; quando encontrar o id da ligação
    de destino, dá printf da paragem de origem e de destino da ligação, terminando
    assim o ciclo. */

void mostraParagens_carreira(Carreira* carreira, lista_Ligacoes* _ligacoes);


/* Função que dá printf das paragens de uma carreira, pela ordem inversa que estas
    se encontram na carreira; enquanto o id da ligação atual não for igual ao id
    da ligação de origem da carreira, a função não acaba e vai dando printf
    da paragem de destino da ligação, incrementando o índice sempre que encontra
    uma ligação válida para o id da ligação atual; quando encontrar o id da ligação
    de destino, dá printf da paragem de destino e de origem da ligação, terminando
    assim o ciclo. */

void mostraParagens_carreira_Inverso(Carreira* carreira, 
                                        lista_Ligacoes* _ligacoes);


/* Função que dá printf de todas as paragens, por ordem de criação, da forma
    descrita no enunciado do projeto. */

void apresentaParagens(lista_Paragens* _paragens);


/* Função que verifica se a paragem já existe na lista de paragens; se não
    existir, devolve NAOEXISTENTE; caso contrário, devolve o pointer para o node
    da paragem correspondente. */

Paragem* encontraParagem(char s[], lista_Paragens* _paragens);


/* Função que coloca o node recém-criado da paragem na lista de paragens;
    se a lista de paragens for vazia, coloca no início; caso contrário, coloca
    no fim e atualiza a tail da lista de paragens sempre que coloca uma nova. */

void colocaParagem(lista_Paragens* _paragens, Paragem* node);


/* Função que cria uma nova paragem, inicializando todos os parâmetros
    necessários para que esta funcione ao longo do projeto. */

void criaParagem(char s[], double latitude, double longitude, 
                    lista_Paragens* _paragens);


/* Função que coloca o node recém-criado da ligação na lista de ligações;
    se a lista de ligações for vazia, coloca no início; caso contrário, coloca
    no fim e atualiza a tail da lista de ligações sempre que coloca uma nova. */

void colocaLigacao(lista_Ligacoes* _ligacoes, Ligacao* ligacao);


/* Função que cria uma nova ligação, inicializando todos os parâmetros
    necessários para que esta funcione ao longo do projeto. */

Ligacao* criaLigacao(Carreira* nodeCarreira, Paragem* parOrigem, 
                    Paragem* parDestino, double custo, double duracao,
                    int id_Ligacao);


/* Função de INPUT específica para o comando l, lendo os parâmetros nomeCarreira,
    nodeOrigem e nomeDestino, que correspondem ao nome da Carreira, nome da
    Paragem de Origem da ligação e o nome da Paragem de Destino da ligação,
    respetivamente. */

void leNomesComando(char nomeCarreira[], char nomeOrigem[], char nomeDestino[]);


/* Função que coloca o node recém-criado que contém o pointer para um node de
    uma carreira que passa numa paragem específica na lista de carreiras que
    se encontra dentro de cada paragem; apenas coloca o pointer da carreira na 
    paragem específica; se a lista das carreiras da paragem for vazia,
    coloca no início; caso contrário, coloca no fim e atualiza a tail da lista
    sempre que coloca uma nova. */

void colocaCarreira_na_Paragem(CarreirasParagem* nova_carreira,
                            lista_carreirasParagem* carreirasParagem);


/* Função que adiciona o pointer da carreira ao node da carreira da lista de
    carreiras da paragem. */

void adicionaCarreiraParagem(Paragem* nodeParagem, Carreira* nodeCarreira);


/* Função que verifica se a carreira já existe na lista de carreiras da paragem
    específica; se não existir, devolve NAOENCONTRADO; caso contrário, devolve 
    ENCONTRADO. */

int encontraParagemCarreira(Paragem* paragem, Carreira* carreira);


/* Caso se queira adicionar uma ligação à carreira e esta não tenha paragens,
    esta função é chamada; atualiza os parâmetros da carreira conforme os
    parâmetros da ligação (custo, duração, paragem origem, paragem destino,
    id_LigaçãoOrigem, id_LigaçãoDestino, contador de paragens); devolve a ligação. */

Ligacao* adicionaPrimeiraLigacao(Carreira* nodeCarreira, Paragem* nodeParOrigem,
                        Paragem* nodeParDestino, double custo, double duracao);


/* Caso se queira adicionar uma ligação ao fim da carreira, esta função é
    chamada; atualiza os parâmetros da carreira conforme os parâmetros da ligação
    (custo, duração, paragem destino, id_LigaçãoDestino, contador de paragens);
    devolve a ligação. */

Ligacao* adicionaLigacaoFim(Carreira* nodeCarreira, Paragem* nodeParOrigem, 
                        Paragem* nodeParDestino, double custo, double duracao);


/* Caso se queira adicionar uma ligação ao início da carreira, esta função é
    chamada; atualiza os parâmetros da carreira conforme os parâmetros da ligação
    (custo, duração, paragem origem, id_LigaçãoOrigem, contador de paragens);
    devolve a ligação. */

Ligacao* adicionaLigacaoInicio(Carreira* nodeCarreira, Paragem* nodeParOrigem,
                        Paragem* nodeParDestino, double custo, double duracao);


/* Função que verifica se a carreira não tem ligações, se é para adicionar a
    ligação no início da carreira, ou no fim; caso não seja uma ligação válida,
    é levantado um erro. */

void adicionaLigacao(Carreira* nodeCarreira, Paragem* nodeParOrigem,
                        Paragem* nodeParDestino, double custo, double duracao,
                        lista_Ligacoes* _ligacoes);


/* Função que ordena as carreiras pela ordem do código ASCII; o algoritmo
    de ordenação usado é o bubble sort. */

void organiza_carreiras(CarreirasParagem* carreiras[], int tamanho);


/* Função que apresenta as carreiras que passam numa paragem, por ordem alfabética,
    da forma descrita no enunciado do projeto. */

void apresenta_intersecoes(Paragem* paragem, CarreirasParagem* vetorCarreiras[]);


/* Função que liberta toda a memória usada no comando i. */

void libertaIntersecoesAux(lista_carreirasParagem* lista, CarreirasParagem* *vetor);


/* Adiciona o pointer da carreira para um novo node auxiliar para apresentar
    as interseções. */

void adicionaNodeAux(CarreirasParagem* nodeCar, lista_carreirasParagem* aux);


/* Cria vetor auxiliar usado no comando i, que contém o pointer para uma carreira,
    que passe em uma ou mais paragens. */

void cria_vetor_intersecoes(Paragem* paragem, int tamanho);


/* Atualiza os nodes da lista de carreiras de uma paragem específica quando se 
    remove uma carreira que passe nessa paragem. */

void atualizaCarreirasParagem(Paragem* paragem, CarreirasParagem* carreira);


/* Função que verifica se a carreira que se quer remover se encontra na lista
    de carreiras de uma paragem; se sim, atualiza-se os nodes da lista e remove-se
    a carreira da lista (a carreira não é removida da memória, apenas o node
    que continha o pointer para a mesma). */

void removeCarreiraParagem(Paragem* paragem, int idCarreira);


/* Função que remove as ligações da carreira que se quer remover. */

void removeCarreiraLigacoes(int idCarreira, lista_Ligacoes* _ligacoes);


/* Função que atualiza os valores de uma carreira quando se remove uma paragem
    do programa e se tem que atualizar todas as ligações da carreira. */

void atualizaValoresCarreira(double duracao, double custo, int par_contador,
    Carreira* carreira, int id_LigacaoDestino_Novo, char* par_destino);


/* Função que dá reset à carreira, caso esta fique sem paragens e sem ligações
    associadas. */

void resetCarreira(Carreira* carreira);


/* Função que remove todas as ligações que tenham a paragem que se quer remover;
    enquanto não se encontrar uma ligação que não contenha a paragem de remoção
    como paragem de origem, a ligação é libertada e os parâmetros da carreira
    são atualizados:
    - caso se chegue ao fim da carreira, se a paragem de destino
        da última ligação for diferente da paragem que se quer remover, a paragem
        deixa de estar associada à carreira, devolvendo FINAL;
    - no caso de se encontrar uma ligação válida, isto é, cuja paragem de origem
     não seja a paragem que se quer remover, esta é devolvida. */

Ligacao* procuraParagemInicio(Paragem* paragem, Carreira* carreira, 
                                            lista_Ligacoes* _ligacoes);


/* Aumenta o custo e duração adicionando o custo e duração da ligação. */

void extendeLigacao(double *duracao, double *custo, Ligacao* lig);


/* Iguala o custo e duração a zeros. */

void resetDuracaoCusto(double *duracao, double *custo);


/* Atualiza uma ligação consoante a paragem de origem, custo duração e id. */

void mudaLigacao(Ligacao* lig, Paragem* par, double* custo, double* duracao, int id);


/* Função que procura ligações válidas quando se tenta remover uma paragem do programa;
    esta função só é chamada se a procuraParagemInicio devolver uma ligação
    válida; enquanto não se chegar ao final da carreira:
    - caso a paragem de destino de uma ligação seja igual à paragem que se está a tentar
        remover, extende-se a ligação usando a extendeLigacao e liberta-se a ligação;
    - caso se encontre uma ligação válida, é chamada a mudaLigacao para atualizar
        os seus parâmetros e fica guardada a paragem de destino da ligação, que vai
        servir de paragem de origem na próxima ligação válida que se encontre;

    Quando se chegar ao final da carreira:
    - se nenhuma ligação tiver sido alterada e todas tiverem sido libertadas,
        dá-se reset à carreira;
    - caso contrário, atualizam-se os valores da carreira consoante as alterações
        feitas nas ligações. */

void procuraParagemMeio(Paragem* paragem, Carreira* carreira, 
                                lista_Ligacoes* _ligacoes, Ligacao* ligacao);


/* Percorre todas as carreiras da lista de carreiras da paragem e removem-se as
    ligações que contenham a paragem. */

void removeParagemCarreiras(Paragem* paragem, lista_Ligacoes* _ligacoes);



                /* ||FUNÇÕES PRINCIPAIS DOS COMANDOS|| */


/* Função principal do comando c, que pode ter 3 variações de input:
    - <c> que apresenta todas as carreiras, por ordem de criação;
    - <c> <nome-de-carreira>, que, ou cria uma nova carreira, caso esta não exista,
        ou mostra as paragens da mesma;
    - <c> <nome-de-carreira> <inverso>, que mostra as paragens de uma carreira
        de forma inversa, se <inverso> estiver bem escrito; caso contrário,
        levanta um erro. */

void c_Command(lista_Carreiras* _carreiras, lista_Ligacoes* _ligacoes);


/* Função principal do comando p, que pode ter 3 variações de input:
    - <p>, que apresenta todas as paragens, por ordem de criação;
    - <p> <nome-de-paragem>, que, ou mostra a latitude e longitude de uma paragem,
        ou levanta um erro, caso a paragem ainda não exista no programa;
    - <p> <nome-de-paragem> <latitude> <longitude> que cria uma paragem, se 
        esta ainda não existir; caso contrário levanta um erro. */

void p_Command(lista_Paragens* _paragens);


/* Função principal do comando l, que adiciona uma ligação ao programa; os erros
    levantados podem ser:
    - caso a carreira não exista;
    - caso a paragem de origem não exista;
    - caso a paragem de destino não exista;
    - caso o custo e duração seja negativos. */

void l_Command(lista_Carreiras* _carreiras, lista_Paragens* _paragens,
                lista_Ligacoes* _ligacoes);


/* Função principal do comando i, que apresenta as carreiras que intersetam paragens;
    apenas mostra as paragens que tenham duas ou mais carreiras a intersetá-la. */

void i_Command(lista_Paragens* _paragens);


/* Função principal do comando r, que remove uma carreira do programa. */

void r_Command(lista_Carreiras* _carreiras, lista_Ligacoes* _ligacoes);


/* Função principal do comando e, que remove uma paragem do programa. */

void e_Command(lista_Paragens* _paragens, lista_Ligacoes* _ligacoes);


#endif