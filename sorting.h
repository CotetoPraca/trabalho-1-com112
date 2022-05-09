/*---------------------------------------------
Alunos                            - Matrículas
Lucas Praça de Souza              - 2018013138
Mateus de Freitas Bonette         - 2020001519
Bruna Rafael Neira Muñoz          - 2020003676
Guilherme Toledo de Resende       - 2019011110
Jennifer Camila Gonçalves         - 2018008399
---------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <sys/time.h> // Apenas sistemas Unix

#ifndef SORTING_H
#define SORTING_H

void ordenaVetor(int *vetor, int tam, FILE *arquivoSaida, int iclock);
//Executa a maior parte do código

int geraAleatorios(char *nomeArquivo, int qtd);
//Esta função gera 'qtd' números aleatórios e os escreve no arquivo 'nomeArquivo'
//Os tameros devem variar entre 0 e 1000.
//A função retorna 0 se funcionou corretamente. Retorna 1 se houve algum erro no processo.
//Pesquisem pelas funções rand() e srand().

int* leArquivo(char *nomeArquivo, int qtd);
//Esta função lê 'qtd' dados do arquivo 'nomeArquivo' e os insere em um vetor de inteiros
//A função retorna NULL caso haja algum erro no processo.

void copiaVetor(int *backup, int *vet, int tam);
//Esta função copia os valores do vetor de backup
//de volta para o vetor original

void imprimeVet(int *vet, int tam);
//Esta função recebe um vetor e o imprime na tela
//A impressão é em linha -> printf("%d ", ...);
//Antes de encerrar, a função imprime uma linha em branco

void selecao(int *vet, int tam);
//Esta função recebe um vetor de inteiros de tamanho 'tam' e o ordena (ordem crescente) utilizando o método seleção

void quickSort(int *vet, int inicio, int fim);
//Função QuickSort recursiva

int particiona(int *vet, int inicio, int fim);
//Função que ordena o elemento pivô.

void mergeSort(int *vet, int inicio, int fim);
//Função Mergesort Recursiva

void merge(int *vet, int inicio, int meio, int fim);
//Função Merge, que combina dois vetores previamente ordenados

void smoothSort(int *vet, uint32_t tam);
//Esta função recebe um vetor de inteiros de tamanho 'tam' e o ordena (ordem crescente) utilizando o método SmoothSort

struct heapsizes;

static struct heapsizes heapify (int *vet, uint32_t tam);

static void extract (int *vet, uint32_t tam, struct heapsizes hsz);

static struct heapsizes heapify (int *vet, uint32_t tam);

static inline void sift_in (int * root, int size);

static inline void interheap_sift (int * root, struct heapsizes hsz);

#endif //SORTING_H