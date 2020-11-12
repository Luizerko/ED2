#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ABB.h"
#include "ARN.h"
#include "tries.h"
#include "hash_linear.h"
#include "hash_encadeamento.h"
#include "node_ABB.h"
#include "node_ARN.h"
#include "node_trie.h"
#include "node_hash_linear.h"
#include "node_hash_encadeamento.h"

Node_ABB* raiz_ABB;
Node_ARN* raiz_ARN;
Node_trie* raiz_trie;
Node_hash_linear** vetor_hash_linear;
Node_hash_encadeamento** vetor_hash_encadeamento;


void adiciona_palavra(char* palavra, int contador) {
    //raiz_ABB = ABB_put(raiz_ABB, palavra);
    raiz_ARN = ARN_put(raiz_ARN, palavra);
    //raiz_trie = trie_put(raiz_trie, palavra, 0, contador);
    //vetor_hash_linear = hash_linear_put(vetor_hash_linear, palavra);
    //vetor_hash_encadeamento = hash_encadeamento_put(vetor_hash_encadeamento, palavra);
}

void imprime_palavras() {
    //ABB_imprime(raiz_ABB);
    ARN_imprime(raiz_ARN);
    //trie_imprime(raiz_trie, 0);
    //hash_linear_imprime(vetor_hash_linear);
    //hash_encadeamento_imprime(vetor_hash_encadeamento);
}

void imprime_numero_chaves() {
    //ABB_imprime_chaves();
    ARN_imprime_chaves();
    //trie_imprime_chaves();
    //hash_linear_imprime_chaves();
    //hash_encadeamento_imprime_chaves();
}

void testa_gets(char* palavra, int tamanho) {
    //Node_ABB* aux = ABB_get(raiz_ABB, palavra);
    Node_ARN* aux = ARN_get(raiz_ARN, palavra);
    //Node_trie* aux = trie_get(raiz_trie, palavra, 0, tamanho);
    //Node_hash_linear* aux = hash_linear_get(vetor_hash_linear, palavra);
    //Node_hash_encadeamento* aux = hash_encadeamento_get(vetor_hash_encadeamento, palavra);

    if(aux != NULL)
        printf("Frequencia da palavra %s: %d\n",palavra, aux->frequencia);
    else
        printf("Palavra não encontrada na estrutura!\n");
}

int main(int argc, char* argv[]) {

    char* texto = argv[1];
    printf("\nNome do arquivo: %s\n\n", texto);

    raiz_ABB = ABB_init();
    raiz_ARN = ARN_init();
    raiz_trie = trie_init();
    vetor_hash_linear = hash_linear_init();
    vetor_hash_encadeamento = hash_encadeamento_init();

    FILE* file;
    char c;
    int contador = 0;
    char palavra_aux[100];

    file = fopen(texto, "r");
    if(file == NULL)
        exit(EXIT_FAILURE);

    clock_t ini, fim;
    ini = clock();

    while((c = getc(file)) != EOF) {
        if(c >= 'A' && c <= 'Z') {
            c += 32;
        }
        if(c >= 'a' && c <= 'z') {
            palavra_aux[contador] = c;
            contador++;
        }
        else {
            if(contador > 0) {
                char* palavra = malloc((contador+1)*sizeof(char));
                for(int i = 0; i < contador; i++) {
                    palavra[i] = palavra_aux[i];
                }
                palavra[contador] = '\0';
                adiciona_palavra(palavra, contador);
                //imprime_palavras();
                contador = 0;
            }
        }
        
        /*
        printf("%c -> ", c);
        for(int i = 0; i < contador; i++) {
            printf("%c", palavra_aux[i]);
        }

        printf("\n");
        sleep(1);
        */
    }

    fim = clock();
    printf("Tempo de execução: %lf\n", (double)(fim - ini)/CLOCKS_PER_SEC);

    fclose(file);

    //imprime_palavras();
    
    printf("\n");
    imprime_numero_chaves();
    
    /*
    char teste_busca[50];
    printf("\nTeste de busca. Digite uma palavra: ");
    scanf("%s", teste_busca);
    testa_gets(teste_busca, strlen(teste_busca));
    */

    return 0;
}