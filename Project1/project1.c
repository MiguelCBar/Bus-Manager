#include <stdio.h>
#include <string.h>

#define MAX_CARREIRAS 200
#define MAX_PARAGENS 10000
#define MAX_LIGACOES 30000

#define MAX_NOME_CARREIRA 21
#define MAX_NOME_PARAGEM 51
#define INVERSO 8
#define INVERSO_STRING "inverso"

typedef struct {
    char nome[MAX_NOME_PARAGEM];
    double latitude;
    double longitude;  
} Paragem;

typedef struct {                                                               
    char nome[MAX_NOME_CARREIRA];
    char par_origem[MAX_NOME_PARAGEM];
    char par_destino[MAX_NOME_PARAGEM];
    int contador_par;
} Carreira;

typedef struct {
    char nome_carreira[MAX_NOME_CARREIRA];
    char par_origem[MAX_NOME_PARAGEM];
    char par_destino[MAX_NOME_PARAGEM];
    float custo;
    float duracao;
} Ligacao;

/* Total de paragens e array global de paragens */

int _totalparagens = 0;
Paragem _array_paragens[MAX_PARAGENS];


/* Total das carreiras e array global de carreiras */

int _totalcarreiras = 0;
Carreira _array_carreiras[MAX_CARREIRAS];


/* Total das ligacoes e array global de ligações */

int _totalligacoes = 0;
Ligacao _array_ligacoes[MAX_LIGACOES];



/* ||Funções Auxiliares|| */


/* Devolve 1 se o caracter c é um espaço ou um TAB; caso contrário, devolve 0. */

int caracter_branco(char c) {
    return c == ' ' || c == '\t';
}


/* Devolve 1 se o input para o inverso estiver escrito conforme as restrições
    do enunciado; caso contrário, devolve 0. */

int carreira_inverso_test(char s[INVERSO]) {
    int tamanho = strlen(s);
    if(tamanho > 2)
        return(!strncmp(s, INVERSO_STRING, tamanho));
    return 0;
}


/* Devolve o índice da posição da carreira no array global _array_carreiras, caso
    esta exista; caso contrário, é levantado um erro e devolve -1. */

int carreiraNaoExistente_l_Command(char carreira[MAX_NOME_CARREIRA]) {
    int i, valor = -1;
    for (i = 0; i < _totalcarreiras; i++)
        if (!(strcmp(carreira, _array_carreiras[i].nome))) {
            valor = i;
            return valor;       
        }
    printf("%s: no such line.\n", carreira);
    return valor;
}


/* Devolve 1 se paragem existir no array global de paragens; caso contrário,
    é levantado um erro e devolve -1.*/   

int paragemNaoExistente_l_Command(char paragem[MAX_NOME_PARAGEM]) {
    int i, valor = -1;
    for (i = 0; i < _totalparagens; i++)
        if(!(strcmp(paragem, _array_paragens[i].nome))) {
            valor = 1;
            return valor;
        }
    printf("%s: no such stop.\n", paragem);
    return valor;
}


/* Devolve 1 se carreira não existe no array global _array_carreiras; devolve
    2 se a ligação que se está a tentar criar é válida tendo em conta
    os seus requisitos no enunciado; caso contrário, é levantado um erro e 
    devolve -1. */

int ligacaoNaoExistente_l_Command(Ligacao ligacao, int indice) {
    int i, valor = -1;

    for (i = 0; i < _totalligacoes; i++)
        if (!strcmp(ligacao.nome_carreira, _array_ligacoes[i].nome_carreira)) {
            if(!strcmp(_array_carreiras[indice].par_origem,
                ligacao.par_destino) || 
               !strcmp(_array_carreiras[indice].par_destino,
                ligacao.par_origem)) {
                    valor = 1;
                    return valor;
            }
            printf("link cannot be associated with bus line.\n");
            return valor;                    
        }
    valor = 2;
    return valor;
}


/* Devolve o índice de carreira no vetor global _array_carreiras se carreira
    existir no array global _array_carreiras; caso contrário, devolve -1. */

int carreiraNaoExistente(char carreira[MAX_NOME_CARREIRA]) {
    int i;
    for (i = 0; i < _totalcarreiras; i++)
        if (!strcmp(carreira, _array_carreiras[i].nome))
            return i;
    return -1;
}


/* O array custo_duração é alterado de forma a conter o custo e duração totais
    ao percorrer uma só carreira na sua totalidade, consoante o preço de cada 
    ligação. */

void custo_duracao_totais(char carreira[MAX_NOME_CARREIRA], 
                                    float custo_duracao[2]) {   
    int i;
    for (i = 0; i < _totalligacoes; i++)
        if (!strcmp(carreira,_array_ligacoes[i].nome_carreira)) {
            custo_duracao[0] += _array_ligacoes[i].custo;
            custo_duracao[1] += _array_ligacoes[i].duracao;
        }
}


/* Devolve 1 se paragem for igual à paragem de origem da carreira OU se for
    igual à paragem de destino da carreira; caso contrário, devolve 0. */

int compara_paragens_carreira(int indice, char paragem[MAX_NOME_PARAGEM]) {
    return (!strcmp(_array_ligacoes[indice].par_origem, paragem) ||
            !strcmp(_array_ligacoes[indice].par_destino, paragem));
}


/* Devolve 1 se carreira existir no array global _array_carreiras; caso
    contrário, devolve 0. */

int carreira_existente_Array(char carreira[MAX_NOME_CARREIRA], 
            char array[MAX_CARREIRAS][MAX_NOME_CARREIRA], int tamanho_array) {
    int i;
    for (i = 0; i < tamanho_array; i++)
        if(!strcmp(array[i], carreira))
            return 1;
    return 0;
}


/* Devolve o número de carreiras que passam numa paragem; primeiro, percorre
    todas as ligações e, se a carreira ainda não se encontrar no array
    auxiliar, verifica se uma das paragens da ligação, origem ou destino,
    corresponde à paragem em questão; se sim,
    é adicionada mais uma carreira ao array e +1 ao tamanho_array. */

int contadorCarreiras(char paragem[MAX_NOME_PARAGEM], 
                        char array[MAX_CARREIRAS][MAX_NOME_CARREIRA]) {
    int i, tamanho_array = 0;
    for (i = 0; i < _totalligacoes; i++)
        if (!carreira_existente_Array(_array_ligacoes[i].nome_carreira, 
                                    array, 
                                    tamanho_array)) {
            if (compara_paragens_carreira(i, paragem)) {
                    strcpy(array[tamanho_array], 
                            _array_ligacoes[i].nome_carreira);
                    tamanho_array++; 
            }
        }
    return tamanho_array;
}


/* Compara e dá print às paragens de uma carreira, pela sua ordem correta;
    paragem é inicializada como a origem da carreira e, ao percorrer o array
    global _array_ligacoes, quando é encontrada uma ligação com a carreira
    dada, se a par_origem da ligação corresponder a paragem, então dá-se
    print de paragem e esta é atualizada para a par_destino da ligação. */

void compara_paragens(char carreira[MAX_NOME_CARREIRA], 
                        char paragem[MAX_NOME_PARAGEM], int contador[1]) {
    int i;
    for (i = 0; i < _totalligacoes; i++)
        if (!strcmp(carreira, _array_ligacoes[i].nome_carreira))
            if (!strcmp(paragem, _array_ligacoes[i].par_origem)) {
                printf("%s, ", paragem);
                strcpy(paragem, _array_ligacoes[i].par_destino);
                contador[0]--;
            }
                
}


/* Função principal de apresentar as paragens de uma carreira; paragem_atual
    é inicializada como a origem da carreira e, enquanto não sobrar apenas
    uma paragem por apresentar, a função compara_paragens é chamada as vezes
    que forem necessárias (no caso em que apenas se adicionam ligações que
    expandam o lado da origem da carreira, o ciclo irá ser percorrido mais
    vezes); após sair do ciclo, é dado print da última paragem por apresentar.) */

void print_paragens(char carreira[MAX_NOME_CARREIRA], int indice, 
                                            int contador_paragens) {
    char paragem_atual[MAX_NOME_PARAGEM];
    int contador[1];
    if (_array_carreiras[indice].contador_par > 0) {
        contador[0] = contador_paragens;
        strcpy(paragem_atual, _array_carreiras[indice].par_origem);
        while (contador[0] > 1)  
            compara_paragens(carreira, paragem_atual, contador);

        printf("%s\n", paragem_atual);
    }
}


/* Semelhante à função compara_paragens, mas no caso especial do inverso, onde
    paragem, neste caso, corresponde ao destino da carreira e, sempre que
    esta é atualizada por ter encontrado correspondência com uma ligação com
    par_destino igual, passa a ser a par_origem dessa mesma ligação; o ciclo
    é percorrido pela ordem inversa apenas devido à maior probabilidade de 
    encontrar uma ligação válida mais cedo, percorrendo-o menos vezes. */

void compara_paragens_inverso(char carreira[MAX_NOME_CARREIRA], 
                            char paragem[MAX_NOME_PARAGEM], int contador[1]) { 
    int i;
    for (i = _totalligacoes - 1; i >= 0; i--)
        if (!strcmp(carreira, _array_ligacoes[i].nome_carreira))
            if (!strcmp(paragem, _array_ligacoes[i].par_destino)) {
                printf("%s, ", paragem);
                strcpy(paragem, _array_ligacoes[i].par_origem);
                contador[0]--;
            }

}


/* Semelhante à função print_paragens, mas paragem_atual corresponde agora ao
    destino da carreira. */

void print_paragens_inverso(char carreira[MAX_NOME_CARREIRA], int indice, 
                                int contador_paragens) {
    char paragem_atual[MAX_NOME_PARAGEM];
    int contador[1];
    if(_array_carreiras[indice].contador_par > 0) {
        contador[0] = contador_paragens;
        strcpy(paragem_atual, _array_carreiras[indice].par_destino);
        while (contador[0] > 1)
            compara_paragens_inverso(carreira, paragem_atual, contador);

        printf("%s\n", paragem_atual);
    }

}



/* ||Algoritmo de Ordenacao: Bubble Sort|| */

void bubble_sort(char array[MAX_CARREIRAS][MAX_NOME_CARREIRA],
                 int tamanho) {
  int i, j, alteracoes;
  char aux[MAX_NOME_CARREIRA];
  
  for (i = 0; i < tamanho-1; i++){
    alteracoes = 1;
    for (j = tamanho-1; j > i; j--) 
      if (strcmp(array[j-1], array[j]) > 0) {
	    strcpy(aux, array[j]);
	    strcpy(array[j], array[j-1]);
	    strcpy(array[j-1], aux);
	    alteracoes = 0;
      }
    if (alteracoes) break;
  }
}



/* ||Funcoes de Leitura de Input|| */


/* No caso do input do nome de uma paragem, por causa das aspas('"'), foi
    usado getchar() em vez de scanf() para a sua leitura; dá return do nome
    da paragem, sem aspas, caso estas existam no input. */

char scanf_nomeParagem(char s[MAX_NOME_PARAGEM], char c) {
    int i;
    while (c == ' ' || c == '\t') 
        c = getchar();
    if (c != '\"') {
        for (i = 0; !caracter_branco(c) && c != '\n'; i++) {
            s[i] = c;
            c = getchar();
        }
        s[i] = '\0';
    }
    else {
        for (i = 0; (c = getchar()) != '\"'; i++) 
            s[i] = c;
        c = getchar();    
        s[i] = '\0';
    }
    return c;
}


/* Leitura de input para o comando p; dá return do número de argumentos lidos,
    excluindo a chave que difere os comandos (neste caso, p). */

int le_p_CommandLine(char nome[MAX_NOME_PARAGEM], double localizacao[2]) {    
    char c;
    int args = 0;
    c = getchar();
    if (caracter_branco(c)) {
        c = scanf_nomeParagem(nome, c);
        args++;
    }
    else
        return args;
    if (caracter_branco(c)) {
            args+= scanf("%lf%lf", &localizacao[0], &localizacao[1]);
            return args;
    }
    else    
        return args;
}


/* Leitura do input para o comando c; dá return do número de argumentos lidos,
    excluindo a chave que difere os comandos; caso o argumento que represente 
    o inverso não esteja escrito consoante o pretendido, é levantado um erro
    e devolvido -1. */

int le_c_CommandLine(char nome[MAX_NOME_CARREIRA]) {
    char c;
    int args = 0;
    char inverso[INVERSO];
    c = getchar();
    if (caracter_branco(c))
        args = scanf("%s", nome);
    else
        return args;
    c = getchar();
    if (caracter_branco(c)) {
        args += scanf("%s", inverso);
        if (carreira_inverso_test(inverso))
            return args;
        else {
            printf("incorrect sort option.\n");
            return -1;
        }
    }
    return args;
}


/* Leitura do input para o comando l. */

void le_l_CommandLine(char q[MAX_NOME_CARREIRA], 
        char par_orig[MAX_NOME_PARAGEM], char par_dest[MAX_NOME_PARAGEM]) {
    char c = getchar();
    if (scanf("%s", q))
        c = getchar();
    scanf_nomeParagem(par_orig, c);
    scanf_nomeParagem(par_dest, c);
}



/* ||Funcões Principais|| */


/* Função principal para o comando p; caso se esteja a tentar apresentar
    a localização de uma paragem que não existe, é levantado um erro e o
    comando acaba; caso se esteja a criar uma paragem que já existe, é levantado
    um erro e o comando acaba; no caso de um comando correto:
    - é criada uma nova paragem;
    - é apresentada a localização da paragem;
    - as paragens são apresentadas a seguinte forma, pela ordem de criação
        -> <nome-de-paragem>: <latitude> <longitude> <número-de-carreiras>,
        onde  <número-de-carreiras> representa o número de carreiras que
        passam na paragem correspondente. */

void p_Command() {
    Paragem paragem_atual;
    int valor, i, contador_carreiras;
    double localizacao[2];
    char aux_array[MAX_CARREIRAS][MAX_NOME_CARREIRA];
    valor = le_p_CommandLine(paragem_atual.nome, localizacao);
    if (valor == 0) {
        for (i = 0; i < _totalparagens; i++) {
            contador_carreiras = contadorCarreiras(_array_paragens[i].nome, 
                                                            aux_array);
            printf("%s: %16.12f %16.12f %d\n", _array_paragens[i].nome,
                _array_paragens[i].latitude, _array_paragens[i].longitude,
                contador_carreiras);
        }
        return;
    }
    else if(valor == 1) {
        for (i = 0; i < _totalparagens; i++)
            if (!strcmp(paragem_atual.nome, _array_paragens[i].nome)) {
                printf("%16.12f %16.12f\n", _array_paragens[i].latitude, 
                        _array_paragens[i].longitude);
                return;
            }
        printf("%s: no such stop.\n", paragem_atual.nome);
    }
    else {
        for (i = 0; i < _totalparagens; i++)
            if (!strcmp(paragem_atual.nome, _array_paragens[i].nome)) {
                printf("%s: stop already exists.\n", paragem_atual.nome);
                return;
            }
        paragem_atual.latitude = localizacao[0];
        paragem_atual.longitude = localizacao[1];
        _array_paragens[_totalparagens] = paragem_atual;
        _totalparagens++;
    }    
}


/* Função principal para o comando c; no caso de um comando correto:
    - é criada uma nova carreira;
    - as paragens dessa carreira são apresentadas pela ordem desde a origem
        até ao destino (se "inverso" for aplicado, é ao contrário);
    - as carreiras são apresentadas, pela ordem de criação, da seguinte forma:
        -> <nome-da-carreira> <paragem-origem> <paragem-destino> 
            <número-de-paragens> <custo-total> <duração-total>, 
        e omitir as paragens no caso da carreira não ter ligações.*/

void c_Command() {
    int i, valor, indice;
    float custo_duracao[2];
    Carreira carreira;
    valor = le_c_CommandLine(carreira.nome);

    if (valor < 0)
        return;
    else if (valor == 0) {
        for (i = 0; i < _totalcarreiras; i++) {
            if (_array_carreiras[i].contador_par == 0) 
                printf("%s %d 0.00 0.00\n", _array_carreiras[i].nome,
                _array_carreiras[i].contador_par);
            
            else {
                custo_duracao[0] = 0;
                custo_duracao[1] = 0;
                custo_duracao_totais(_array_carreiras[i].nome,
                custo_duracao);
                printf("%s %s %s %d %.2f %.2f\n", _array_carreiras[i].nome,
                    _array_carreiras[i].par_origem, 
                    _array_carreiras[i].par_destino, 
                    _array_carreiras[i].contador_par,
                    custo_duracao[0], custo_duracao[1]);
            }
        }
    }
    else if (valor == 1) {
        indice = carreiraNaoExistente(carreira.nome);
        if(indice < 0) {
            carreira.contador_par = 0;
            _array_carreiras[_totalcarreiras] = carreira;
            _totalcarreiras++;
            return;
        } 
        print_paragens(_array_carreiras[indice].nome, 
                    indice, 
                    _array_carreiras[indice].contador_par); 
    }
    else {
        for (i = 0; i < _totalcarreiras; i++)
            if (!strcmp(_array_carreiras[i].nome, carreira.nome)) {
                print_paragens_inverso(_array_carreiras[i].nome,
                                    i,
                                    _array_carreiras[i].contador_par);
                break;
            }
    }
}


/* Função principal para o comando l; custos e durações negativas devem geral
    um erro e terminal o comando; no caso de um comando correto:
    - é criada uma nova ligação e, no caso da carreira não ter paragens,
        a origem da ligação corresponde à origem da carreira e o destino da
        ligação corresponde ao destino da carreira. */

void l_Command() {
    int  valor, indice_carreira;
    Ligacao ligacao_atual;

    le_l_CommandLine(ligacao_atual.nome_carreira, ligacao_atual.par_origem,
                        ligacao_atual.par_destino);

    indice_carreira = carreiraNaoExistente_l_Command(ligacao_atual.nome_carreira);

    if (indice_carreira < 0)
        return;
    if (paragemNaoExistente_l_Command(ligacao_atual.par_origem) < 0)
        return;
    if (paragemNaoExistente_l_Command(ligacao_atual.par_destino) < 0)
        return;
    valor = ligacaoNaoExistente_l_Command(ligacao_atual,indice_carreira);
    if (valor < 0)
        return;
    
    else if (valor == 2) {
        if(scanf("%f%f", &ligacao_atual.custo, &ligacao_atual.duracao)
            && (ligacao_atual.custo < 0 || ligacao_atual.duracao < 0)) {
                printf("negative cost or duration.\n");
                return;
        }
        _array_ligacoes[_totalligacoes] = ligacao_atual;
        _totalligacoes++;
        strcpy(_array_carreiras[indice_carreira].par_origem, 
                ligacao_atual.par_origem);
        strcpy(_array_carreiras[indice_carreira].par_destino, 
                ligacao_atual.par_destino);
        _array_carreiras[indice_carreira].contador_par += 2;
    }

    else {
        if(scanf("%f%f", &ligacao_atual.custo, &ligacao_atual.duracao)
            && (ligacao_atual.custo < 0 || ligacao_atual.duracao < 0)) {
                printf("negative cost or duration.\n");
                return;
        }
        _array_ligacoes[_totalligacoes] = ligacao_atual;
        _totalligacoes++;
        if (!strcmp(ligacao_atual.par_origem, 
            _array_carreiras[indice_carreira].par_destino))
            strcpy(_array_carreiras[indice_carreira].par_destino, 
                ligacao_atual.par_destino);
        else 
            strcpy(_array_carreiras[indice_carreira].par_origem, 
                ligacao_atual.par_origem);
        _array_carreiras[indice_carreira].contador_par ++;
    }
}


/* Função principal para o comando i:
    - apresenta as paragens que correspondam a interseções de carreiras, da 
        seguinte forma:
        -> <nome-de-paragem> <número-de-carreiras>: <nome-de-carreira> ...,
        onde os nomes das carreiras são listado alfabeticamente. */

void i_Command() {
    int i, j, contador_carreiras = 0;
    char aux_array[MAX_CARREIRAS][MAX_NOME_CARREIRA];
    for (i = 0; i < _totalparagens; i++) {
        contador_carreiras = contadorCarreiras(_array_paragens[i].nome, 
                                                            aux_array);
        if(contador_carreiras > 1) {
            bubble_sort(aux_array, contador_carreiras);
            printf("%s %d:", _array_paragens[i].nome, contador_carreiras);
            for (j = 0; j < contador_carreiras; j++)
                printf(" %s", aux_array[j]);
            putchar('\n');
        }
    }
}



/* ||Função main|| */


/* apenas lê a primeira letra a que correspondem os comandos. */

int main() {
    char comando;
    while((comando = getchar()) != 'q')
        switch(comando) {
            case 'c':
                c_Command();
                break;
            case 'p':
                p_Command();
                break;
            case 'l':
                l_Command();
                break;
            case 'i':
                i_Command();
                break;
        }
    return 0;
}