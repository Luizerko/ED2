/*
Exercício 2

Aluno: Luis Vitor Zerkowski
NUSP: 9837201
Disciplina: Algoritmos e Estruturas de Dados II (MAC-0323)
Professora: Cristina Gomes
Monitor: Marcos Siolin
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define infinito 10000

typedef struct node {
    int chave;
    int valor;
    struct node** proximo;
}Node;

Node* first;
Node* last;
int n;
int maxNiveis = 100;
int niveis;

//Cria um novo nó que estará em 'levels' níveis
Node* newNode(int chave, int valor, int levels) {
    Node* novo = malloc(sizeof(Node));
    novo->chave = chave;
    novo->valor = valor;
    novo->proximo = malloc(levels*sizeof(Node*));
    for(int i = 0; i < levels; i++) {
        novo->proximo[i] = NULL;
    }
    return novo;
}

//Inicia a lista com 'maxNiveis' níveis e com todos os apontadores de first->proximo apontando para last.
//A chave de last é 10000 para representar infinito no contexto de testes.
void init() {
    first = malloc(sizeof(Node));
    last = malloc(sizeof(Node));
    niveis = 1;
    first->proximo = malloc(maxNiveis*sizeof(Node*));
    last->proximo = malloc(maxNiveis*sizeof(Node*));
    for(int i = 0; i < maxNiveis; i++) {
        first->proximo[i] = last;
        last->proximo[i] = NULL;
    }
    last->chave = infinito;
}

//Imprime toda a lista em todos os seus níveis. Os níveis de cima são impressos antes dos níveis de baixo.
void imprimeLista() {
    printf("\n");
    int k = niveis-1;
    Node* aux = first->proximo[k];
    while(k >= 0) {
        if(aux == last) {
            k--;
            aux = first->proximo[k];
            printf("\n");
        }
        else {
            printf(" -> (chave: %d, valor: %d)", aux->chave, aux->valor);
            aux = aux->proximo[k];
        }
    }
    printf("\n");
}

//Devolve o valor da chave que fora passada como parâmetro
int getChave(int chave) {
    Node* aux = first;
    int k = niveis;
    while(k >= 0) {
        if(aux != last && chave == aux->proximo[k]->chave)
            return aux->proximo[k]->valor;
        if(aux != last && chave > aux->proximo[k]->chave) {
            aux = aux->proximo[k];
        }
        else if(aux != last && chave < aux->proximo[k]->chave) {
            k--;
        }
        else
            return -1;            
    }
    return -1;
}

//Procura a posição correta para inserir um nó - primeira posição para a qual a sua chave é menor do que a do nó seguinte -
//em cada nível da skip list. Insere esse nó após anterior[k] nos níveis para os quais foi sorteado.
void putNode(int chave, int valor) {
    int flag_modifica = 0;
    Node* aux = first;
    Node** anterior = malloc(maxNiveis*sizeof(Node*));
    for(int i = 0; i < maxNiveis; i++) {
        anterior[i] = first;
    }
    int k = niveis-1;
    while(k >= 0) {
        if(aux != last && chave == aux->proximo[k]->chave) {
            aux->proximo[k]->valor = valor;
            k--;
            flag_modifica = 1;
            if(k < 0)
                break;
        }
        if(aux != last && chave > aux->proximo[k]->chave) {
            aux = aux->proximo[k];
        }
        else if(aux != last && chave < aux->proximo[k]->chave) {
            anterior[k] = aux;
            k--;
        }
        else
            break;          
    }
    if(flag_modifica == 0) {
        int i;
        for(i = 0; i < niveis && i < maxNiveis; i++) {
            if(rand()%2 != 1)
                break;
        }
        if(i == niveis && niveis < maxNiveis)
            niveis++;
        Node* novo = newNode(chave, valor, niveis);
        for(int j = 0; j <= i; j++) {
            novo->proximo[j] = anterior[j]->proximo[j];
            anterior[j]->proximo[j] = novo;
        }
    }
}

//Procura o nó anterior ao nó-chave passado para todos os k níveis da skip list. Achado esse nó anterior,
//o nó-chave é "pulado" para que possa ser deletado de todos os níveis da lista.
void deleteNode(int chave) {
    Node* aux = first;
    Node** anterior = malloc(maxNiveis*sizeof(Node*));
    for(int i = 0; i < maxNiveis; i++) {
        anterior[i] = first;
    }
    int k = niveis-1;
    while(k >= 0) {
        if(aux != last && chave == aux->proximo[k]->chave) {
            anterior[k] = aux;
            k--;
        }
        else if(aux != last && chave > aux->proximo[k]->chave) {
            aux = aux->proximo[k];
        }
        else if(aux != last && chave < aux->proximo[k]->chave) {
            k--;
        }
        else
            break;          
    }
    int flag_existencia = 0;
    for(k = niveis-1; k >= 0; k--) {
        if(anterior[k]->proximo[k]->chave == chave) {
            anterior[k]->proximo[k] = anterior[k]->proximo[k]->proximo[k];
            flag_existencia = 1;
        }
    }
    if(flag_existencia == 0) {
        printf("\nChave não encontrada na lista... \n");
    }
}

int main() {
    srand(time(NULL));
    
    //Teste para criar lista
    init();
    imprimeLista();

    //Teste para esvaziar a lista
    putNode(1, 3);
    deleteNode(1);
    imprimeLista();

    //Teste para inserir nós
    for(int i = 0; i < 15; i++) {
        int chave = rand()%15;
        printf("Adicionando (%d, %d)\n", chave, i);
        putNode(chave, i);
    }
    imprimeLista();

    //Teste para deletar nós
    for(int i = 0; i < 5; i++) {
        int chave = rand()%15;
        printf("Removendo (%d)\n", chave);
        deleteNode(chave);
    }
    imprimeLista();

    //Teste para procurar nós
    for(int i = 0; i < 5; i++) {
        int chave = rand()%15;
        printf("Procurando (%d) -> %d\n", chave, getChave(chave));
    }
    imprimeLista();

    return 0;
}