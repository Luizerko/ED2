/*
Exercício Programa 3

Aluno: Luis Vitor Zerkowski
NUSP: 9837201
Disciplina: Algoritmos e Estruturas de dados II
Professora: Cristina G. Fernandes

cliente.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ABB.h"
#include "ARN.h"
#include "tries.h"
#include "hash_linear.h"
#include "hash_encadeamento.h"
#include "hash_encadeamento_MTF.h"
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
Node_hash_encadeamento** vetor_hash_encadeamento_MTF;

//Função que adiciona palavras encontradas pelo parser à estrutura de dados escolhida.
void adiciona_palavra(char* palavra, int contador) {
    //raiz_ABB = ABB_put(raiz_ABB, palavra);
    //raiz_ARN = ARN_put(raiz_ARN, palavra);
    //raiz_trie = trie_put(raiz_trie, palavra, 0, contador);
    //vetor_hash_linear = hash_linear_put(vetor_hash_linear, palavra);
    //vetor_hash_encadeamento = hash_encadeamento_put(vetor_hash_encadeamento, palavra);
    vetor_hash_encadeamento_MTF = hash_encadeamento_MTF_put(vetor_hash_encadeamento_MTF, palavra);
}

//Função que imprime todas as palavras na estrutura de dados escolhida com a suas respectivas frequências.
void imprime_palavras() {
    //ABB_imprime(raiz_ABB);
    //ARN_imprime(raiz_ARN);
    //trie_imprime(raiz_trie, 0);
    //hash_linear_imprime(vetor_hash_linear);
    //hash_encadeamento_imprime(vetor_hash_encadeamento);
    hash_encadeamento_MTF_imprime(vetor_hash_encadeamento_MTF);
}

//Função que imprime o número de chaves encontradas na estrutura escolhida.
void imprime_numero_chaves() {
    //ABB_imprime_chaves();
    //ARN_imprime_chaves();
    //trie_imprime_chaves();
    //hash_linear_imprime_chaves();
    //hash_encadeamento_imprime_chaves();
    hash_encadeamento_MTF_imprime_chaves();
}

//Função que testa a busca de uma dada palavra na estrutura de dados escolhida e imprime a palavra encontrada, quando
//encontrada, junto com a sua frequência.
void testa_gets(char* palavra, int tamanho) {
    //Node_ABB* aux = ABB_get(raiz_ABB, palavra);
    //Node_ARN* aux = ARN_get(raiz_ARN, palavra);
    //Node_trie* aux = trie_get(raiz_trie, palavra, 0, tamanho);
    //Node_hash_linear* aux = hash_linear_get(vetor_hash_linear, palavra);
    //Node_hash_encadeamento* aux = hash_encadeamento_get(vetor_hash_encadeamento, palavra);
    Node_hash_encadeamento* aux = hash_encadeamento_MTF_get(vetor_hash_encadeamento_MTF, palavra);

    if(aux != NULL)
        printf("\nFrequencia da palavra %s: %d\n",palavra, aux->frequencia);
    else
        printf("\nPalavra não encontrada na estrutura!\n");
}

//Função que libera a estrutura de dados escolhida.
void libera_estrutura() {
    //raiz_ABB = ABB_free(raiz_ABB);
    //raiz_ARN = ARN_free(raiz_ARN);
    //raiz_trie = trie_free(raiz_trie);
    //hash_linear_free(vetor_hash_linear);
    //hash_encadeamento_free(vetor_hash_encadeamento);
    hash_encadeamento_MTF_free(vetor_hash_encadeamento_MTF);

    printf("Estrutura liberada com sucesso!\n");
}

//Função principal do cliente. Pega o texto passado como argumento e faz a tokenização das palavras, adicionando cada
//uma delas nas estruturas de dados.
int main(int argc, char* argv[]) {

    //Arquivo escolhido
    char* texto = argv[1];
    printf("\nNome do arquivo: %s\n\n", texto);

    //Inicialização de todas as estruturas.
    raiz_ABB = ABB_init();
    raiz_ARN = ARN_init();
    raiz_trie = trie_init();
    vetor_hash_linear = hash_linear_init();
    vetor_hash_encadeamento = hash_encadeamento_init();
    vetor_hash_encadeamento_MTF = hash_encadeamento_MTF_init();

    FILE* file;
    char c;
    int contador = 0;
    char palavra_aux[100];
    int numero_palavras = 0;

    file = fopen(texto, "r");
    if(file == NULL)
        exit(EXIT_FAILURE);

    //Início de contabilização do tempo
    clock_t ini, fim;
    ini = clock();

    //Início do parser no arquivo file, lendo letra por letra do arquivo e separando as devidas palavras.
    //Como o foco do EP eram as estruturas, meu parser é bem simples e não pega palavra com hífen e nem palavras com
    //acento.
    while((c = getc(file)) != EOF) {
        //Transforma letras maiúsculas em letras minúsculas
        if(c >= 'A' && c <= 'Z') {
            c += 32;
        }

        //Adiciona letra na palavra atual
        if(c >= 'a' && c <= 'z') {
            palavra_aux[contador] = c;
            contador++;
        }

        else {
            if(contador > 0) {

                //Aloca uma string para a palvra que será colocada na estrutura e coloca \0 no final da mesma
                char* palavra = malloc((contador+1)*sizeof(char));
                for(int i = 0; i < contador; i++) {
                    palavra[i] = palavra_aux[i];
                }
                palavra[contador] = '\0';
                
                //Adiciona palavra na estrutura, reseta o contador para parsear uma nova palavra e incrimenta o contador
                //de palavras
                adiciona_palavra(palavra, contador);
                contador = 0;
                numero_palavras++;
            }
        }
        
    }

    //Termina o contador de tempo de construção das estruturas e imprime os resultados obtidos. Aqui são impressos
    //o tempo de construção, o número de palavras no texto, o número de diferentes chaves no texto e o sucesso da
    //liberação da estrutura.
    fim = clock();
    printf("Tempo de construção: %lf\n", (double)(fim - ini)/CLOCKS_PER_SEC);
    printf("Número de palavras no texto: %d\n", numero_palavras);
    imprime_numero_chaves();
    libera_estrutura();
    
    //Testes:

    /*
    //Criação de arquivos de texto para fazer médias colocadas no relatório!
    char testes[100];
    testes[0] = 'l';
    testes[1] = 'u';
    testes[2] = 'i';
    for(int i = 3; i < 3 + strlen(texto); i++)
        testes[i] = texto[i-3];
    testes[strlen(texto)] = '\0';
    FILE* f = fopen(testes, "a+");
    fprintf(f, "%lf\n", (double)(fim - ini)/CLOCKS_PER_SEC);
    fclose(f);

    fclose(file);

    //Teste de busca para uma palavra digitada
    char teste_busca[50];
    printf("\nTeste de busca. Digite uma palavra: ");
    scanf("%s", teste_busca);
    testa_gets(teste_busca, strlen(teste_busca));

    //Teste de tempo de busca da palavra "a"
    ini = clock();
    
    char teste_busca[2];
    teste_busca[0] = 'a';
    teste_busca[1] = '\0';
    testa_gets(teste_busca, 1);

    fim = clock();
    printf("Tempo de busca: %lf\n", (double)(fim - ini)/CLOCKS_PER_SEC);

    //Teste de impressão de palavras e frequências da estrutura escolhida
    imprime_palavras();
    */

    return 0;
}