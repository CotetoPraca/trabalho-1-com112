/*---------------------------------------------
Alunos                            - Matrículas
Lucas Praça de Souza              - 2018013138
Mateus de Freitas Bonette         - 2020001519
Bruna Rafael Neira Muñoz          - 2020003676
Guilherme Toledo de Resende       - 2019011110
Jennifer Camila Gonçalves         - 2018008399
---------------------------------------------*/

#include <stdio.h>
#include <sys/time.h> // Apenas sistema Unix
#include "sorting.h"

int main(void) {
  struct timeval ini, fim;
  int iclock = 0;
  double clockSelec[32];
  double clockQuick[32];
  double clockMerge[32];
  double clockSmooth[32];

  //Nome do arquivo gerado com valores aleatórios
  char arquivoEntrada[] = "arquivoTeste.txt";

  //Arquivo de saída
  FILE *arquivoSaida = fopen("arquivoSaida.txt", "w");

  if (arquivoSaida == NULL){
    //printf("Erro na abertura do arquivo de saída\n");
    return -1;
  }
  
  int *vet, *backup;
  int tam;

  printf("Programa iniciado\n");
  fprintf(arquivoSaida, "Relatório de Execução");
  
  for (tam = 5000; tam < 25001; tam += 5000){
    //Gera um arquivo arquivoEntrada.txt com valores aleatorios
  	geraAleatorios(arquivoEntrada, tam);
  
    //Salva os valores no vetor a ser ordenado
    vet = leArquivo(arquivoEntrada, tam);
  
    //Salva os valores em um vetor de backup
    backup = leArquivo(arquivoEntrada, tam);

    //printf("\n\n---------------------------------------\n");
    fprintf(arquivoSaida, "\n\n---------------------------------------\n");
    //printf("Tamanho do vetor de teste: %d\n\n", tam);
    fprintf(arquivoSaida, "Tamanho do vetor de teste: %d\n\n", tam);
    //printf("\n-- Selection Sort --\n");
    fprintf(arquivoSaida, "\n-- Selection Sort --\n");
    
    gettimeofday(&ini, NULL); //Inicia o timer
  	selecao(vet, tam);
    gettimeofday(&fim, NULL); //Finaliza o timer
    
    clockSelec[iclock] = ( (fim.tv_sec - ini.tv_sec) * 1000.0 ); 
    clockSelec[iclock] += ( (fim.tv_usec - ini.tv_usec) / 1000.0 );
    
    //printf("Tempo de execução: %lf ms\n", clockSelec[iclock]);
    fprintf(arquivoSaida, "Tempo de execução: %lf ms\n", clockSelec[iclock]);

    copiaVetor(backup, vet, tam);
    
    //printf("\n-- Quick Sort --\n");
    fprintf(arquivoSaida, "\n-- Quick Sort --\n");
    
    gettimeofday(&ini, NULL); //Inicia o timer
    quickSort(vet, 0, tam-1);
    gettimeofday(&fim, NULL); //Finaliza o timer
    
    clockQuick[iclock] = ( (fim.tv_sec - ini.tv_sec) * 1000.0 ); 
    clockQuick[iclock] += ( (fim.tv_usec - ini.tv_usec) / 1000.0 );
    
    //printf("Tempo de execução: %lf ms\n", clockQuick[iclock]);
    fprintf(arquivoSaida, "Tempo de execução: %lf ms\n", clockQuick[iclock]);
    
    copiaVetor(backup, vet, tam);
    
    //printf("\n-- Merge Sort --\n");
    fprintf(arquivoSaida, "\n-- Merge Sort --\n");
    
    gettimeofday(&ini, NULL); //Inicia o timer
    mergeSort(vet, 0, tam-1);
    gettimeofday(&fim, NULL); //Finaliza o timer
    
    clockMerge[iclock] = ( (fim.tv_sec - ini.tv_sec) * 1000.0 ); 
    clockMerge[iclock] += ( (fim.tv_usec - ini.tv_usec) / 1000.0 );
    
    //printf("Tempo de execução: %lf ms\n", clockMerge[iclock]);
    fprintf(arquivoSaida, "Tempo de execução: %lf ms\n", clockMerge[iclock]);
    
    copiaVetor(backup, vet, tam);
    
    //printf("\n-- Smooth Sort --\n");
    fprintf(arquivoSaida, "\n-- Smooth Sort --\n");
    
    gettimeofday(&ini, NULL); //Inicia o timer
    smoothSort(vet, tam-1);
    gettimeofday(&fim, NULL); //Finaliza o timer
    
    clockSmooth[iclock] = ( (fim.tv_sec - ini.tv_sec) * 1000.0 ); 
    clockSmooth[iclock] += ( (fim.tv_usec - ini.tv_usec) / 1000.0 );
    
    //printf("Tempo de execução: %lf ms\n", clockSmooth[iclock]);
    fprintf(arquivoSaida, "Tempo de execução: %lf ms\n", clockSmooth[iclock]);
    
    iclock++;
  }
  
  //printf("\n\n---------------------------------------\n");
  fprintf(arquivoSaida, "\n\n---------------------------------------\n");
  //printf("---- MELHOR CASO ----\n\n");
  fprintf(arquivoSaida, "---- MELHOR CASO ----\n\n");
  
  //Salva o vetor ordenado crecente (melhor caso)
  for (int i = 0; i < tam; i++){
    vet[i] = i;
    backup[i] = i;
  }
  
  for (tam = 5000; tam < 25001; tam += 5000){
    //printf("\n\n---------------------------------------\n");
    fprintf(arquivoSaida, "\n\n---------------------------------------\n");
    //printf("Tamanho do vetor de teste: %d\n\n", tam);
    fprintf(arquivoSaida, "Tamanho do vetor de teste: %d\n\n", tam);
    //printf("\n-- Selection Sort --\n");
    fprintf(arquivoSaida, "\n-- Selection Sort --\n");
    
    gettimeofday(&ini, NULL); //Inicia o timer
  	selecao(vet, tam);
    gettimeofday(&fim, NULL); //Finaliza o timer
    
    clockSelec[iclock] = ( (fim.tv_sec - ini.tv_sec) * 1000.0 ); 
    clockSelec[iclock] += ( (fim.tv_usec - ini.tv_usec) / 1000.0 );
    
    //printf("Tempo de execução: %lf ms\n", clockSelec[iclock]);
    fprintf(arquivoSaida, "Tempo de execução: %lf ms\n", clockSelec[iclock]);

    copiaVetor(backup, vet, tam);
    
    //printf("\n-- Quick Sort --\n");
    fprintf(arquivoSaida, "\n-- Quick Sort --\n");
    
    gettimeofday(&ini, NULL); //Inicia o timer
    quickSort(vet, 0, tam-1);
    gettimeofday(&fim, NULL); //Finaliza o timer
    
    clockQuick[iclock] = ( (fim.tv_sec - ini.tv_sec) * 1000.0 ); 
    clockQuick[iclock] += ( (fim.tv_usec - ini.tv_usec) / 1000.0 );
    
    //printf("Tempo de execução: %lf ms\n", clockQuick[iclock]);
    fprintf(arquivoSaida, "Tempo de execução: %lf ms\n", clockQuick[iclock]);
    
    copiaVetor(backup, vet, tam);
    
    //printf("\n-- Merge Sort --\n");
    fprintf(arquivoSaida, "\n-- Merge Sort --\n");
    
    gettimeofday(&ini, NULL); //Inicia o timer
    mergeSort(vet, 0, tam-1);
    gettimeofday(&fim, NULL); //Finaliza o timer
    
    clockMerge[iclock] = ( (fim.tv_sec - ini.tv_sec) * 1000.0 ); 
    clockMerge[iclock] += ( (fim.tv_usec - ini.tv_usec) / 1000.0 );
    
    //printf("Tempo de execução: %lf ms\n", clockMerge[iclock]);
    fprintf(arquivoSaida, "Tempo de execução: %lf ms\n", clockMerge[iclock]);
    
    copiaVetor(backup, vet, tam);
    
    //printf("\n-- Smooth Sort --\n");
    fprintf(arquivoSaida, "\n-- Smooth Sort --\n");
    
    gettimeofday(&ini, NULL); //Inicia o timer
    smoothSort(vet, tam-1);
    gettimeofday(&fim, NULL); //Finaliza o timer
    
    clockSmooth[iclock] = ( (fim.tv_sec - ini.tv_sec) * 1000.0 ); 
    clockSmooth[iclock] += ( (fim.tv_usec - ini.tv_usec) / 1000.0 );
    
    //printf("Tempo de execução: %lf ms\n", clockSmooth[iclock]);
    fprintf(arquivoSaida, "Tempo de execução: %lf ms\n", clockSmooth[iclock]);
    
    iclock++;
  }
  
  //printf("\n\n---------------------------------------\n");
  fprintf(arquivoSaida, "\n\n---------------------------------------\n");
  //printf("---- PIOR CASO ----\n\n");
  fprintf(arquivoSaida, "---- PIOR CASO ----\n\n");
  
  //Salva o vetor ordenado descrecente (pior caso)
  for (int i = tam-1; i >= 0; i--){
    vet[i] = i;
    backup[i] = i;
  }
  
  for (tam = 5000; tam < 25001; tam += 5000){
    //printf("\n\n---------------------------------------\n");
    fprintf(arquivoSaida, "\n\n---------------------------------------\n");
    //printf("Tamanho do vetor de teste: %d\n\n", tam);
    fprintf(arquivoSaida, "Tamanho do vetor de teste: %d\n\n", tam);
    //printf("\n-- Selection Sort --\n");
    fprintf(arquivoSaida, "\n-- Selection Sort --\n");
    
    gettimeofday(&ini, NULL); //Inicia o timer
  	selecao(vet, tam);
    gettimeofday(&fim, NULL); //Finaliza o timer
    
    clockSelec[iclock] = ( (fim.tv_sec - ini.tv_sec) * 1000.0 ); 
    clockSelec[iclock] += ( (fim.tv_usec - ini.tv_usec) / 1000.0 );
    
    //printf("Tempo de execução: %lf ms\n", clockSelec[iclock]);
    fprintf(arquivoSaida, "Tempo de execução: %lf ms\n", clockSelec[iclock]);

    copiaVetor(backup, vet, tam);
    
    //printf("\n-- Quick Sort --\n");
    fprintf(arquivoSaida, "\n-- Quick Sort --\n");
    
    gettimeofday(&ini, NULL); //Inicia o timer
    quickSort(vet, 0, tam-1);
    gettimeofday(&fim, NULL); //Finaliza o timer
    
    clockQuick[iclock] = ( (fim.tv_sec - ini.tv_sec) * 1000.0 ); 
    clockQuick[iclock] += ( (fim.tv_usec - ini.tv_usec) / 1000.0 );
    
    //printf("Tempo de execução: %lf ms\n", clockQuick[iclock]);
    fprintf(arquivoSaida, "Tempo de execução: %lf ms\n", clockQuick[iclock]);
    
    copiaVetor(backup, vet, tam);
    
    //printf("\n-- Merge Sort --\n");
    fprintf(arquivoSaida, "\n-- Merge Sort --\n");
    
    gettimeofday(&ini, NULL); //Inicia o timer
    mergeSort(vet, 0, tam-1);
    gettimeofday(&fim, NULL); //Finaliza o timer
    
    clockMerge[iclock] = ( (fim.tv_sec - ini.tv_sec) * 1000.0 ); 
    clockMerge[iclock] += ( (fim.tv_usec - ini.tv_usec) / 1000.0 );
    
    //printf("Tempo de execução: %lf ms\n", clockMerge[iclock]);
    fprintf(arquivoSaida, "Tempo de execução: %lf ms\n", clockMerge[iclock]);
    
    copiaVetor(backup, vet, tam);
    
    //printf("\n-- Smooth Sort --\n");
    fprintf(arquivoSaida, "\n-- Smooth Sort --\n");
    
    gettimeofday(&ini, NULL); //Inicia o timer
    smoothSort(vet, tam-1);
    gettimeofday(&fim, NULL); //Finaliza o timer
    
    clockSmooth[iclock] = ( (fim.tv_sec - ini.tv_sec) * 1000.0 ); 
    clockSmooth[iclock] += ( (fim.tv_usec - ini.tv_usec) / 1000.0 );
    
    //printf("Tempo de execução: %lf ms\n", clockSmooth[iclock]);
    fprintf(arquivoSaida, "Tempo de execução: %lf ms\n", clockSmooth[iclock]);
    
    iclock++;
  }

  printf("Programa encerrado\n");
  fclose(arquivoSaida);
  return 0;
}