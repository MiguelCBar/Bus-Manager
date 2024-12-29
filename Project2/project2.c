#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "estruturas.h"
#include "funcoes.h"
#include "constantes.h"


void erroMemoria() {
    printf("No memory.\n");
    exit(1);
}


lista_Carreiras* cria_lista_carreiras() {
    lista_Carreiras* _carreiras;
    if((_carreiras = (lista_Carreiras*)malloc(sizeof(lista_Carreiras))) == NULL)
        erroMemoria();
    _carreiras->inicio = NULL;
    _carreiras->fim = NULL;
    _carreiras->_total_Carreiras = 0; 
    return _carreiras;
}

lista_Paragens* cria_lista_paragens() {
    lista_Paragens* _paragens;
    if((_paragens = (lista_Paragens*)malloc(sizeof(lista_Paragens))) == NULL)
        erroMemoria();
    _paragens->inicio = NULL;
    _paragens->fim = NULL;
    return _paragens;
}

lista_Ligacoes* cria_lista_ligacoes() {
    lista_Ligacoes* _ligacoes;
    if((_ligacoes = (lista_Ligacoes*)malloc(sizeof(lista_Ligacoes))) == NULL)
        erroMemoria();
    _ligacoes->inicio = NULL;
    _ligacoes->fim = NULL;
    return _ligacoes;
}



int caracter_branco(char c) {
    return c == ' ' || c == '\t';
}


int leEspacos() {
    int c;
    while ((c = getchar()) == ' ' || c == '\t');
    if (c == '\n') 
        return 0;
    ungetc(c, stdin);
    return 1;
}

void leNome(char s[]) {
    int i = 0, c;
    s[0] = getchar();
    if (s[0] != '"') {
        i = 1;
        while ((c = getchar()) != ' ' && c != '\t' && c != '\n')
            s[i++] = c;
        ungetc(c, stdin);
    }
    else {
        while((c = getchar()) != '"')
            s[i++] = c;
    }
    s[i++] = '\0';
}

void leAteFinalLinha(char s[]) {
    char c;
    int i = 0;
    while ((c = getchar()) != '\n') {
        s[i++] = c;
    }
    s[i] = '\0';
}



void libertaLigacao(Ligacao* lig) {
    free(lig);
}

void libertaCarreira(Carreira* carreira) {
    free(carreira->nome);
    free(carreira->par_origem);
    carreira->par_origem = NULL;
    free(carreira->par_destino);
    carreira->par_destino = NULL;
    free(carreira);
}

void libertaParagem(Paragem* paragem) {
    CarreirasParagem* aux, *inicio = paragem->carreiras->inicio;
    for(aux = inicio; aux != NULL; aux = inicio) {
        inicio = aux->next;
        free(aux);
    }
    free(paragem->nome);
    free(paragem->carreiras);
    free(paragem);
}



void atualizaCarreiras(Carreira* carreira, lista_Carreiras* _carreiras) {
    if (carreira == _carreiras->inicio)
        _carreiras->inicio = carreira->next;
    else if(carreira == _carreiras->fim) {
        _carreiras->fim = carreira->prev;
        _carreiras->fim->next = NULL;
    }
    else {
        carreira->next->prev = carreira->prev; 
        carreira->prev->next = carreira->next;
    }
}

void atualizaParagens(Paragem* paragem, lista_Paragens* _paragens) {
    if (paragem == _paragens->inicio) {
        _paragens->inicio = paragem->next;
    }
    else if(paragem == _paragens->fim) {
        _paragens->fim = paragem->prev;
        _paragens->fim->next = NULL;
    }
    else {
        paragem->next->prev = paragem->prev;
        paragem->prev->next = paragem->next;
    }
}

void atualizaLigacoes(Ligacao* ligacao, lista_Ligacoes* _ligacoes) {
    if (ligacao == _ligacoes->inicio)
        _ligacoes->inicio = ligacao->next;
    else if(ligacao == _ligacoes->fim) {
        _ligacoes->fim = ligacao->prev;
        _ligacoes->fim->next = NULL;
    }
    else {
        ligacao->next->prev = ligacao->prev;
        ligacao->prev->next = ligacao->next;
    }
}




void liberta_memoria(lista_Carreiras* _carreiras,
                        lista_Ligacoes* _ligacoes,
                        lista_Paragens* _paragens) {
    
    Carreira* carreira;
    Ligacao* ligacao;
    Paragem* paragem;

    for(ligacao = _ligacoes->inicio; ligacao != NULL; ligacao = _ligacoes->inicio) {
        _ligacoes->inicio = ligacao->next;
        libertaLigacao(ligacao);
    }

    for(paragem = _paragens->inicio; paragem != NULL; paragem = _paragens->inicio) {
        _paragens->inicio = paragem->next;
        libertaParagem(paragem);
    }

    for(carreira = _carreiras->inicio; carreira != NULL; carreira = _carreiras->inicio) {
        _carreiras->inicio = carreira->next;
        libertaCarreira(carreira);
    }

    free(_carreiras);
    free(_ligacoes);
    free(_paragens);
}





int carreira_inverso_test(char s[]) {
    int tamanho = strlen(s);
    if(tamanho > 2 && tamanho < 8)
        return(!strncmp(s, INVERSO_STRING, tamanho));
    return ERRO;
}


void apresentaCarreiras(lista_Carreiras* _carreiras) {
    Carreira* node;
    for(node = _carreiras->inicio; node != NULL; node = node->next) {
        printf("%s ", node->nome);
        if(node->contador_par > 0)
            printf("%s %s %d %.2f %.2f\n", node->par_origem,
                    node->par_destino, node->contador_par, node->custoTotal,
                    node->duracaoTotal);
        else
            printf("%d %.2f %.2f\n", 0, 0.00, 0.00);
    }

}

Carreira* carreiraNaoExistente(char carreira[], lista_Carreiras* _carreiras) {
    Carreira* node;
    for(node = _carreiras->inicio; node != NULL; node = node->next)
        if(!strcmp(node->nome, carreira))
            return node;
    return NAOEXISTENTE;
}

void colocaCarreira(lista_Carreiras* _carreiras, Carreira* node) {
    node->prev = _carreiras->fim;
    node->next = NULL;
    if (_carreiras->fim != NULL)
        _carreiras->fim->next = node;
    _carreiras->fim = node;
    if(_carreiras->inicio == NULL)
        _carreiras->inicio = node;
}


void criaCarreira(char s[], lista_Carreiras* _carreiras) {
    Carreira* node;
    if((node = (Carreira*)malloc(sizeof(Carreira))) == NULL)
        erroMemoria();
    if((node->nome = (char*)malloc(sizeof(char) * (strlen(s) + 1))) == NULL)
        erroMemoria();
    strcpy(node->nome, s);
    node->contador_par = 0;
    node->custoTotal = 0;
    node->duracaoTotal = 0;
    node->par_origem = NULL;
    node->par_destino = NULL;
    node->id_carreira = _carreiras->_total_Carreiras++;
    colocaCarreira(_carreiras, node);
}


void mostraParagens_carreira(Carreira* carreira, lista_Ligacoes* _ligacoes) {
    int id_carreira = carreira->id_carreira;
    int id_ligProcurar = carreira->id_LigacaoOrigem;
    int flag = DENTRO;
    Ligacao* lig_aux;
    while(flag) {
        for(lig_aux = _ligacoes->inicio; lig_aux != NULL; lig_aux = lig_aux->next)
            if(id_ligProcurar == lig_aux->id_ligacao && 
                id_carreira == lig_aux->id_carreira) {
                    if (id_ligProcurar == carreira->id_LigacaoDestino) {
                        printf("%s, %s\n", lig_aux->par_origem->nome, 
                                            lig_aux->par_destino->nome);
                        flag = FORA;
                        break;
                    }
                    else
                        printf("%s, ", lig_aux->par_origem->nome);
                id_ligProcurar++;
            }
    }
}

void mostraParagens_carreira_Inverso(Carreira* carreira, 
                                        lista_Ligacoes* _ligacoes) {

    int id_carreira = carreira->id_carreira;
    int id_ligProcurar = carreira->id_LigacaoDestino;
    int flag = DENTRO;
    Ligacao* lig_aux;
    while(flag) {
        for(lig_aux = _ligacoes->inicio; lig_aux != NULL; lig_aux = lig_aux->next)
            if(id_ligProcurar == lig_aux->id_ligacao && 
                id_carreira == lig_aux->id_carreira) {
                    if(id_ligProcurar == carreira->id_LigacaoOrigem) {
                        printf("%s, %s\n", lig_aux->par_destino->nome, 
                                            lig_aux->par_origem->nome);
                        flag = FORA;
                        break;
                    }
                    else
                        printf("%s, ", lig_aux->par_destino->nome);
                id_ligProcurar--; 
            }
    }
}




void c_Command(lista_Carreiras* _carreiras, lista_Ligacoes* _ligacoes) {
    char s[BUFSIZE], buffer[BUFSIZE];
    Carreira* node;

    if(!leEspacos()) {
        apresentaCarreiras(_carreiras);
        return;
    }  
    leNome(s);
    node = carreiraNaoExistente(s, _carreiras);
    if(!leEspacos()) {
        if(node == NAOEXISTENTE)
            criaCarreira(s, _carreiras);
        else if(node->contador_par > 0)
            mostraParagens_carreira(node, _ligacoes);
    }
    else {
        leNome(s);
        if (carreira_inverso_test(s)) {
            if(node == NAOEXISTENTE)
                return;
            if(node->contador_par > 0)
                mostraParagens_carreira_Inverso(node, _ligacoes);
        }
        else
            printf("incorrect sort option.\n");
        leAteFinalLinha(buffer);
    }
}


void apresentaParagens(lista_Paragens* _paragens) {
    Paragem* node;
    for(node = _paragens->inicio; node != NULL; node = node->next)
        printf("%s: %16.12f %16.12f %d\n", node->nome, node->latitude,
            node->longitude, node->numCarreiras);

}

Paragem* encontraParagem(char s[], lista_Paragens* _paragens) {
    Paragem* node;
    for(node = _paragens->inicio; node != NULL; node = node->next)
        if (!strcmp(node->nome, s))
            return node;
    return NAOEXISTENTE;
}

void colocaParagem(lista_Paragens* _paragens, Paragem* node) {
    node->prev = _paragens->fim;
    node->next = NULL;
    if (_paragens->fim != NULL)
        _paragens->fim->next = node;
    _paragens->fim = node;
    if(_paragens->inicio == NULL) 
        _paragens->inicio = node;
}

void criaParagem(char s[], double latitude, double longitude, 
                    lista_Paragens* _paragens) {
    Paragem* node;
    if((node = (Paragem*)malloc(sizeof(Paragem))) == NULL)
        erroMemoria();
    if((node->nome = (char*)malloc(sizeof(char) * (strlen(s) + 1))) == NULL)
        erroMemoria();
    if((node->carreiras = 
        (lista_carreirasParagem*)malloc(sizeof(lista_carreirasParagem))) == NULL)
            erroMemoria();
    node->carreiras->inicio = NULL;
    node->carreiras->fim = NULL;
    strcpy(node->nome, s);
    node->latitude = latitude;
    node->longitude = longitude;
    node->numCarreiras = 0;
    colocaParagem(_paragens, node);
}




void p_Command(lista_Paragens* _paragens) {

    char s[BUFSIZE], buffer[BUFSIZE];
    Paragem* node;

    if(!leEspacos()) {
        apresentaParagens(_paragens);
        return;
    }
    leNome(s);
    if(!leEspacos()) {
        if((node = encontraParagem(s, _paragens)) == NAOEXISTENTE)
            printf("%s: no such stop.\n", s);
        else
            printf("%16.12f %16.12f\n", node->latitude, node->longitude); 
    }
    else {
        double latitude, longitude;
        scanf("%lf%lf", &latitude, &longitude);
        if(encontraParagem(s, _paragens) == NAOEXISTENTE)
            criaParagem(s, latitude, longitude, _paragens);
        else
            printf("%s: stop already exists.\n", s);
        leAteFinalLinha(buffer);
    }
}



void colocaLigacao(lista_Ligacoes* _ligacoes, Ligacao* ligacao) {
    ligacao->prev = _ligacoes->fim;
    ligacao->next = NULL;
    if (_ligacoes->fim != NULL)
        _ligacoes->fim->next = ligacao;
    _ligacoes->fim = ligacao;
    if(_ligacoes->inicio == NULL)
        _ligacoes->inicio = ligacao;
}


Ligacao* criaLigacao(Carreira* nodeCarreira, Paragem* parOrigem, 
                    Paragem* parDestino, double custo, double duracao,
                    int id_Ligacao) {
    
    Ligacao* nodeLigacao;
    if((nodeLigacao = (Ligacao*)malloc(sizeof(Ligacao))) == NULL)
        erroMemoria();
    nodeLigacao->custo = custo;
    nodeLigacao->duracao = duracao;
    nodeLigacao->id_carreira = nodeCarreira->id_carreira;
    nodeLigacao->id_ligacao = id_Ligacao;
    nodeLigacao->par_origem = parOrigem;
    nodeLigacao->par_destino = parDestino;
    return nodeLigacao;
}



void leNomesComando(char nomeCarreira[], char nomeOrigem[], char nomeDestino[]) {
    leEspacos();
    leNome(nomeCarreira);
    leEspacos();
    leNome(nomeOrigem);
    leEspacos();
    leNome(nomeDestino);
}


void colocaCarreira_na_Paragem(CarreirasParagem* nova_carreira,
                            lista_carreirasParagem* carreirasParagem) {
    nova_carreira->prev = carreirasParagem->fim;
    nova_carreira->next = NULL;
    if(carreirasParagem->fim != NULL)
        carreirasParagem->fim->next = nova_carreira;
    carreirasParagem->fim = nova_carreira;
    if(carreirasParagem->inicio == NULL)
        carreirasParagem->inicio = nova_carreira;

}




void adicionaCarreiraParagem(Paragem* nodeParagem, Carreira* nodeCarreira) {
    CarreirasParagem* nova_carreira;
    if((nova_carreira = (CarreirasParagem*)malloc(sizeof(CarreirasParagem))) == NULL)
        erroMemoria(); 
    nodeParagem->numCarreiras++;
    nova_carreira->carreira = nodeCarreira;
    colocaCarreira_na_Paragem(nova_carreira, nodeParagem->carreiras);
}


int encontraParagemCarreira(Paragem* paragem, Carreira* carreira) {
    CarreirasParagem* aux;
    int id_Carreira = carreira->id_carreira;
    for(aux = paragem->carreiras->inicio; aux != NULL; aux = aux->next)
        if (id_Carreira == aux->carreira->id_carreira) 
            return ENCONTRADO;
    return NAOENCONTRADO;
}



Ligacao* adicionaPrimeiraLigacao(Carreira* nodeCarreira, Paragem* nodeParOrigem,
                        Paragem* nodeParDestino, double custo, double duracao) {
    
    Ligacao* ligacao;

    adicionaCarreiraParagem(nodeParOrigem, nodeCarreira);
    if (strcmp(nodeParOrigem->nome,nodeParDestino->nome))
        adicionaCarreiraParagem(nodeParDestino, nodeCarreira);

    nodeCarreira->id_LigacaoOrigem = 0;
    nodeCarreira->id_LigacaoDestino = 0;
    nodeCarreira->contador_par = 2;
    if((nodeCarreira->par_origem = 
        (char*)malloc(sizeof(char) * (strlen(nodeParOrigem->nome) + 1))) == NULL)
            erroMemoria();
    strcpy(nodeCarreira->par_origem, nodeParOrigem->nome);
    if((nodeCarreira->par_destino = 
        (char*)malloc(sizeof(char) * (strlen(nodeParDestino->nome) + 1))) == NULL)
            erroMemoria();
    strcpy(nodeCarreira->par_destino, nodeParDestino->nome);
    nodeCarreira->custoTotal += custo;
    nodeCarreira->duracaoTotal += duracao;

    ligacao = criaLigacao(nodeCarreira, nodeParOrigem, nodeParDestino, custo,
                            duracao, nodeCarreira->id_LigacaoDestino);
    return ligacao;
}


Ligacao* adicionaLigacaoFim(Carreira* nodeCarreira, Paragem* nodeParOrigem, 
                        Paragem* nodeParDestino, double custo, double duracao) {

    Ligacao* ligacao;                     

    if(encontraParagemCarreira(nodeParDestino, nodeCarreira) == NAOENCONTRADO)
        adicionaCarreiraParagem(nodeParDestino, nodeCarreira);
    
    nodeCarreira->id_LigacaoDestino++;
    nodeCarreira->contador_par++;
    if((nodeCarreira->par_destino =
        (char*)realloc(nodeCarreira->par_destino, 
                    sizeof(char) * (strlen(nodeParDestino->nome) + 1))) == NULL)
        erroMemoria();
    strcpy(nodeCarreira->par_destino, nodeParDestino->nome);
    nodeCarreira->custoTotal += custo;
    nodeCarreira->duracaoTotal += duracao;

    ligacao = criaLigacao(nodeCarreira, nodeParOrigem, nodeParDestino, custo,
                            duracao, nodeCarreira->id_LigacaoDestino);
    return ligacao;
}


Ligacao* adicionaLigacaoInicio(Carreira* nodeCarreira, Paragem* nodeParOrigem,
                        Paragem* nodeParDestino, double custo, double duracao) {

    Ligacao* ligacao;                      

    if(encontraParagemCarreira(nodeParOrigem, nodeCarreira) == NAOENCONTRADO)
        adicionaCarreiraParagem(nodeParOrigem, nodeCarreira);
    
    nodeCarreira->id_LigacaoOrigem--;
    nodeCarreira->contador_par++;
    if((nodeCarreira->par_origem =
        (char*)realloc(nodeCarreira->par_origem, 
                    sizeof(char) * (strlen(nodeParOrigem->nome) + 1))) == NULL)
        erroMemoria();
    strcpy(nodeCarreira->par_origem, nodeParOrigem->nome);
    nodeCarreira->custoTotal += custo;
    nodeCarreira->duracaoTotal += duracao;

    ligacao = criaLigacao(nodeCarreira, nodeParOrigem, nodeParDestino, custo,
                            duracao, nodeCarreira->id_LigacaoOrigem);
    return ligacao;
}



void adicionaLigacao(Carreira* nodeCarreira, Paragem* nodeParOrigem,
                        Paragem* nodeParDestino, double custo, double duracao,
                        lista_Ligacoes* _ligacoes) {
    
    Ligacao* ligacao;
    if (nodeCarreira->contador_par == 0)
        ligacao = adicionaPrimeiraLigacao(nodeCarreira, nodeParOrigem, 
                                        nodeParDestino, custo, duracao);
    else {
        if (!strcmp(nodeParOrigem->nome, nodeCarreira->par_destino))
            ligacao = adicionaLigacaoFim(nodeCarreira,nodeParOrigem, 
                                        nodeParDestino, custo, duracao);

        else if(!strcmp(nodeParDestino->nome, nodeCarreira->par_origem))
            ligacao = adicionaLigacaoInicio(nodeCarreira, nodeParOrigem, 
                                            nodeParDestino, custo, duracao);

        else {
            printf("link cannot be associated with bus line.\n");
            return;
        }
    }
    colocaLigacao(_ligacoes, ligacao);   
}



void l_Command(lista_Carreiras* _carreiras, lista_Paragens* _paragens,
                lista_Ligacoes* _ligacoes) {
    
    char nomeCarreira[BUFSIZE], paragemOrigem[BUFSIZE], paragemDestino[BUFSIZE],
        buffer[BUFSIZE];
    double custo, duracao;
    Carreira* nodeCarreira;
    Paragem* nodeParOrigem, *nodeParDestino;
    leNomesComando(nomeCarreira, paragemOrigem, paragemDestino);
    scanf("%lf%lf", &custo, &duracao);
    leAteFinalLinha(buffer);
    nodeCarreira = carreiraNaoExistente(nomeCarreira, _carreiras);
    if (nodeCarreira == NAOEXISTENTE)
        printf("%s: no such line.\n", nomeCarreira);
    else {
        nodeParOrigem = encontraParagem(paragemOrigem, _paragens);
        if (nodeParOrigem == NAOEXISTENTE)
            printf("%s: no such stop.\n", paragemOrigem);
        else {
            nodeParDestino = encontraParagem(paragemDestino, _paragens);
            if (nodeParDestino == NAOEXISTENTE)
                printf("%s: no such stop.\n", paragemDestino);
            else if (custo < 0.0 || duracao < 0.0)
                printf("negative cost or duration.\n");
            else
                adicionaLigacao(nodeCarreira, nodeParOrigem, nodeParDestino,
                                custo, duracao, _ligacoes);        
        }   
    }
}





void organiza_carreiras(CarreirasParagem* carreiras[], int tamanho) {
    int i, j, alteracoes;
    CarreirasParagem *aux;
  
    for (i = 0; i < tamanho-1; i++) {
        alteracoes = 1;
        for (j = tamanho-1; j > i; j--) 
            if (strcmp(carreiras[j-1]->carreira->nome, 
                                        carreiras[j]->carreira->nome) > 0) {
	            aux = carreiras[j];
	            carreiras[j] = carreiras[j-1];
	            carreiras[j-1] = aux;
	            alteracoes = 0;
            }
        if (alteracoes) break;
    }
}


void apresenta_intersecoes(Paragem* paragem, CarreirasParagem* vetorCarreiras[]) {
    int i;
    printf("%s %d:", paragem->nome, paragem->numCarreiras);
    for (i = 0; i < paragem->numCarreiras; i++) {
        printf(" %s", vetorCarreiras[i]->carreira->nome);
    }
    putchar('\n');
}

void libertaIntersecoesAux(lista_carreirasParagem* lista, CarreirasParagem* *vetor) {
    CarreirasParagem* aux;
    for(aux = lista->inicio; aux != NULL; aux = lista->inicio) {
        lista->inicio = aux->next;
        free(aux);
    }
    free(vetor);
    free(lista);  
}


void adicionaNodeAux(CarreirasParagem* nodeCar, lista_carreirasParagem* aux) {

    CarreirasParagem* nodeAux;
    if((nodeAux = (CarreirasParagem*)malloc(sizeof(CarreirasParagem))) == NULL)
        erroMemoria();
    nodeAux->carreira = nodeCar->carreira;
    colocaCarreira_na_Paragem(nodeAux, aux); 
}



void cria_vetor_intersecoes(Paragem* paragem, int tamanho) {
    int i;
    lista_carreirasParagem* aux;
    lista_carreirasParagem* carreiras = paragem->carreiras;
    CarreirasParagem* nodeCar;
    CarreirasParagem* *vetorCarreirasParagem;
    if((aux = (lista_carreirasParagem*)malloc(sizeof(lista_carreirasParagem))) == NULL)
        erroMemoria(); 
    if((vetorCarreirasParagem = 
        (CarreirasParagem**)malloc(sizeof(CarreirasParagem) * tamanho)) == NULL)
        erroMemoria();
    aux->inicio = NULL;
    aux->fim = NULL;

    for(nodeCar = carreiras->inicio; nodeCar != NULL; nodeCar = nodeCar->next)
        adicionaNodeAux(nodeCar, aux);

    for(i = 0, nodeCar = aux->inicio; i < tamanho; 
                                    i++, nodeCar = nodeCar->next)
        vetorCarreirasParagem[i] = nodeCar;
    organiza_carreiras(vetorCarreirasParagem, tamanho);
    apresenta_intersecoes(paragem, vetorCarreirasParagem);
    libertaIntersecoesAux(aux, vetorCarreirasParagem);             
}


void i_Command(lista_Paragens* _paragens) {
    char buffer[BUFSIZE];
    Paragem* paragem;
    int tamanho;
    leAteFinalLinha(buffer);
    for (paragem = _paragens->inicio; paragem != NULL; paragem = paragem->next)
        if (paragem->numCarreiras > 1) {
            tamanho = paragem->numCarreiras;
            cria_vetor_intersecoes(paragem, tamanho);
        }
}





void atualizaCarreirasParagem(Paragem* paragem, CarreirasParagem* carreira) {
    if(carreira == paragem->carreiras->inicio) 
       paragem->carreiras->inicio = carreira->next;

    else if(carreira == paragem->carreiras->fim) {
        paragem->carreiras->fim = carreira->prev;
        paragem->carreiras->fim->next = NULL;
    }
    else {
        carreira->next->prev = carreira->prev;
        carreira->prev->next = carreira->next;
    } 
}

void removeCarreiraParagem(Paragem* paragem, int idCarreira) {
    CarreirasParagem* aux, *prox_par;
    for(aux = paragem->carreiras->inicio; aux != NULL; aux = prox_par) {
        prox_par = aux->next;
        if((aux->carreira->id_carreira == idCarreira)) {
            atualizaCarreirasParagem(paragem, aux);
            free(aux);
            paragem->numCarreiras--;
            break;
        }
    }
        
}

void removeCarreiraLigacoes(int idCarreira, lista_Ligacoes* _ligacoes) {

    Ligacao* lig, *prox_lig;
    for (lig = _ligacoes->inicio; lig != NULL; lig = prox_lig) {
        prox_lig = lig->next;
        if(idCarreira == lig->id_carreira) {
            atualizaLigacoes(lig, _ligacoes);
            removeCarreiraParagem(lig->par_origem, idCarreira);
            removeCarreiraParagem(lig->par_destino, idCarreira);
            libertaLigacao(lig);
        }
    }
}


void r_Command(lista_Carreiras* _carreiras, lista_Ligacoes* _ligacoes) {

    char s[BUFSIZE], buffer[BUFSIZE];
    Carreira* carreira;
    leEspacos();
    leNome(s);
    leAteFinalLinha(buffer);
    carreira = carreiraNaoExistente(s, _carreiras);
    if (carreira == NAOEXISTENTE)
        printf("%s: no such line.\n", s);
    else {
        if (carreira->contador_par > 0)
            removeCarreiraLigacoes(carreira->id_carreira, _ligacoes);
        atualizaCarreiras(carreira, _carreiras);
        libertaCarreira(carreira);
    }
}





void atualizaValoresCarreira(double duracao, double custo, int par_contador,
    Carreira* carreira, int id_LigacaoDestino_Novo, char* par_destino) {
        carreira->custoTotal -= custo;
        carreira->duracaoTotal -= duracao;
        carreira->contador_par -= par_contador;
        carreira->id_LigacaoOrigem = carreira->id_LigacaoDestino + 1;
        carreira->id_LigacaoDestino = id_LigacaoDestino_Novo;
        if((carreira->par_destino = (char*)realloc(carreira->par_destino, 
            sizeof(char) * (strlen(par_destino) + 1))) == NULL)
            erroMemoria();
        strcpy(carreira->par_destino, par_destino);
    }

void resetCarreira(Carreira* carreira) {
    carreira->custoTotal = 0;
    carreira->duracaoTotal = 0;
    carreira->contador_par = 0;
    free(carreira->par_destino);
    free(carreira->par_origem);
    carreira->par_origem = NULL;
    carreira->par_destino = NULL;
}


Ligacao* procuraParagemInicio(Paragem* paragem, Carreira* carreira, 
                                            lista_Ligacoes* _ligacoes) {
    Ligacao* aux, *prox_lig;
    int id_ligacaoAtual = carreira->id_LigacaoOrigem;
    int id_carreira = carreira->id_carreira;
    int flag = DENTRO;
    while(flag) 
        for(aux = _ligacoes->inicio; aux != NULL; aux = prox_lig) {

            prox_lig = aux->next;
            if (id_ligacaoAtual == aux->id_ligacao && 
                    id_carreira == aux->id_carreira) {
                if (strcmp(paragem->nome, aux->par_origem->nome) ||
                    id_ligacaoAtual == carreira->id_LigacaoDestino) {
                    flag = FORA;
                    break;
                }
                carreira->custoTotal -= aux->custo;
                carreira->duracaoTotal -= aux->duracao;
                carreira->contador_par--;
                atualizaLigacoes(aux, _ligacoes);
                libertaLigacao(aux);
                id_ligacaoAtual++;
            }
        } 
    if(!strcmp(aux->par_origem->nome, paragem->nome) && 
        !strcmp(aux->par_destino->nome, paragem->nome)) 
            return FINAL;
    else if(!strcmp(aux->par_origem->nome, paragem->nome) &&
        strcmp(aux->par_destino->nome, paragem->nome)) {
            removeCarreiraParagem(aux->par_destino, carreira->id_carreira);
            return FINAL;
        }
    else {
        if((carreira->par_origem = 
            (char*)realloc(carreira->par_origem, 
                sizeof(char) * (strlen(aux->par_origem->nome) + 1))) == NULL)
                    erroMemoria();
        strcpy(carreira->par_origem, aux->par_origem->nome);
    }
    return aux;
}

void extendeLigacao(double *duracao, double *custo, Ligacao* lig) {
    *custo += lig->custo;
    *duracao += lig->duracao;
}

void resetDuracaoCusto(double *duracao, double *custo) {
    *duracao = 0;
    *custo = 0;
}

void mudaLigacao(Ligacao* lig, Paragem* par, double* custo, double* duracao, int id) {
    lig->par_origem = par;
    lig->custo += *custo;
    lig->duracao += *duracao;
    lig->id_ligacao = id;
}

void procuraParagemMeio(Paragem* paragem, Carreira* carreira, 
                                lista_Ligacoes* _ligacoes, Ligacao* ligacao) {
    
    Ligacao *lig_aux, *prox_lig;
    Paragem *par_temp = ligacao->par_origem;
    int flag = DENTRO, paragem_contador = 0, novo_id = carreira->id_LigacaoDestino + 1;
    double duracao = 0, custo = 0;
    int id_ligacaoAtual = ligacao->id_ligacao;
    int id_carreira = carreira->id_carreira;
    while(flag == DENTRO)
        for(lig_aux = _ligacoes->inicio; lig_aux != NULL; lig_aux = prox_lig) {
            prox_lig = lig_aux->next;
            if(id_ligacaoAtual == lig_aux->id_ligacao && 
                id_carreira == lig_aux->id_carreira) {

                if(strcmp(paragem->nome, lig_aux->par_destino->nome)) {
                    mudaLigacao(lig_aux, par_temp, &custo, &duracao, novo_id);
                    resetDuracaoCusto(&duracao, &custo);
                    novo_id++;
                    par_temp = lig_aux->par_destino;
                }
                else{
                    extendeLigacao(&duracao, &custo, lig_aux);
                    paragem_contador++;
                    atualizaLigacoes(lig_aux, _ligacoes);
                    libertaLigacao(lig_aux);
                }
                if(carreira->id_LigacaoDestino == id_ligacaoAtual) {
                    if (novo_id == carreira->id_LigacaoDestino + 1) {
                        removeCarreiraParagem(par_temp, id_carreira);
                        resetCarreira(carreira);
                    }
                    else 
                        atualizaValoresCarreira(duracao, custo, paragem_contador,
                            carreira, novo_id - 1, par_temp->nome);
                    flag = FORA;
                    break;
                }
                id_ligacaoAtual++;
            }
        }
}

void removeParagemCarreiras(Paragem* paragem, lista_Ligacoes* _ligacoes) {
    CarreirasParagem* aux;
    Ligacao* ligacao;
    for(aux = paragem->carreiras->inicio; aux != NULL; aux = aux->next) {
        ligacao = procuraParagemInicio(paragem, aux->carreira, _ligacoes);
        if(ligacao != FINAL)
            procuraParagemMeio(paragem, aux->carreira, _ligacoes, ligacao);
        else
            resetCarreira(aux->carreira);
    }
}   


void e_Command(lista_Paragens* _paragens, lista_Ligacoes* _ligacoes) {
    
    char s[BUFSIZE], buffer[BUFSIZE];
    Paragem* paragem;
    leEspacos();
    leNome(s);
    leAteFinalLinha(buffer);
    paragem = encontraParagem(s, _paragens);
    if(paragem == NAOEXISTENTE)
        printf("%s: no such stop.\n", s);
    else {
        if(paragem->numCarreiras > 0)
            removeParagemCarreiras(paragem, _ligacoes);
        atualizaParagens(paragem, _paragens);
        libertaParagem(paragem);
    }
}






int main() {
    printf("ola");
    int c;
    lista_Carreiras* _carreiras = cria_lista_carreiras();
    lista_Paragens* _paragens = cria_lista_paragens();
    lista_Ligacoes* _ligacoes = cria_lista_ligacoes();
    do {
        c = getchar();
        switch(c) {
            case 'c':
                c_Command(_carreiras, _ligacoes);
                break;
            case 'p':
                p_Command(_paragens);
                break;
            case 'l':
                l_Command(_carreiras, _paragens, _ligacoes);
                break;
            case 'i':
                i_Command(_paragens);
                break;
	        case 'q':
                liberta_memoria(_carreiras, _ligacoes, _paragens);
	            break;
            case 'r':
                r_Command(_carreiras, _ligacoes);
                break;
            case 'e':
                e_Command( _paragens, _ligacoes);
                break;
            case 'a':
                liberta_memoria(_carreiras, _ligacoes, _paragens);
                _carreiras = cria_lista_carreiras();
                _paragens = cria_lista_paragens();
                _ligacoes = cria_lista_ligacoes();
                break;
            default:
	            if (caracter_branco(c) || c == '\n') 
                    break;
        }
    } 
    while (c != 'q')
        ;
    return 0;
}