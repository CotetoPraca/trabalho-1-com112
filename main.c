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
  int **vet = malloc (4 * sizeof(int*)); //Vetor de 4 vetores
  int tam[4] = { 10000, 100000, 500000, 1000000 }; //Tamanho dos vetores
  int k = 0;
  int iclock = 0;
  
  //Nome do arquivo gerado com valores aleatórios
  char arquivoEntrada[] = "arquivoTeste.txt";

  //Arquivo de saída
  FILE *arquivoSaida = fopen("arquivoSaida.txt", "w");

  if (arquivoSaida == NULL){
    //printf("Erro na abertura do arquivo de saída\n");
    return -1;
  }

  printf("Programa iniciado\n");
  fprintf(arquivoSaida, "Relatório de Execução");

  for (int i = 0; i < 4; i++){    
    fprintf(arquivoSaida, "\n\n---------------------------------------\n");
    fprintf(arquivoSaida, "Tamanho do vetor de teste: %d\n", tam[i]);
    fprintf(arquivoSaida, "---------------------------------------\n\n");
    
    
    //Gera um arquivo arquivoEntrada.txt com valores aleatorios
  	geraAleatorios(arquivoEntrada, tam[i]);
  
    //Salva os valores no vetor a ser ordenado
    vet[k] = leArquivo(arquivoEntrada, tam[i]);

    //Chama todas as ordenações e salva no arquivo
    ordenaVetor(vet[k], tam[i], arquivoSaida, iclock);
    
    iclock++;
    
    fprintf(arquivoSaida, "\n\n---------------------------------------\n");
    fprintf(arquivoSaida, "---- MELHOR CASO ----\n\n");

      //Salva o vetor ordenado crecente (melhor caso)
    for (int j = 0; j < tam[i]; j++)
      vet[k][i] = j;

    //Chama todas as ordenações e salva no arquivo
    ordenaVetor(vet[k], tam[i], arquivoSaida, iclock);
    
    iclock++;
    
    fprintf(arquivoSaida, "\n\n---------------------------------------\n");
    fprintf(arquivoSaida, "---- PIOR CASO ----\n\n");
    
    //Salva o vetor ordenado descrecente (pior caso)
    for (int j = tam[i]-1; j >= 0; j--){
      vet[k][i] = j;
    }
  
    //Chama todas as ordenações e salva no arquivo
    ordenaVetor(vet[k], tam[i], arquivoSaida, iclock);
    
    k++;
  }
  
  printf("Programa encerrado\n");
  fclose(arquivoSaida);
  return 0;
}