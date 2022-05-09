/*---------------------------------------------
Alunos                            - Matrículas
Lucas Praça de Souza              - 2018013138
Mateus de Freitas Bonette         - 2020001519
Bruna Rafael Neira Muñoz          - 2020003676
Guilherme Toledo de Resende       - 2019011110
Jennifer Camila Gonçalves         - 2018008399
---------------------------------------------*/

#include "sorting.h"

double clockSelec[32];  //Salva os tempos de execução do Select Sort
double clockQuick[32];  //------------------------------ Quick Sort
double clockMerge[32];  //------------------------------ Merge Sort
double clockSmooth[32]; //------------------------------ Smooth Sort

void ordenaVetor(int *vet, int tam, FILE *arquivoSaida, int iclock){
  //Executa a parte principal do código
  struct timeval ini, fim; //Variáveis para o calculo de tempo de execução
  
  fprintf(arquivoSaida, "\n\n---------------------------------------\n");
  fprintf(arquivoSaida, "Tamanho do vetor de teste: %d\n\n", tam);
  
  fprintf(arquivoSaida, "\n-- Selection Sort --\n");
  gettimeofday(&ini, NULL); //Inicia o timer
  selecao(vet, tam);
  gettimeofday(&fim, NULL); //Finaliza o timer
  
  clockSelec[iclock] = ( (fim.tv_sec - ini.tv_sec) * 1000.0 ); 
  clockSelec[iclock] += ( (fim.tv_usec - ini.tv_usec) / 1000.0 );
  
  fprintf(arquivoSaida, "Tempo de execução: %lf s\n", clockSelec[iclock] * 1000.0);    
  
  fprintf(arquivoSaida, "\n-- Quick Sort --\n");
  gettimeofday(&ini, NULL); //Inicia o timer
  quickSort(vet, 0, tam-1);
  gettimeofday(&fim, NULL); //Finaliza o timer
  
  clockQuick[iclock] = ( (fim.tv_sec - ini.tv_sec) * 1000.0 ); 
  clockQuick[iclock] += ( (fim.tv_usec - ini.tv_usec) / 1000.0 );
  
  fprintf(arquivoSaida, "Tempo de execução: %lf s\n", clockQuick[iclock] * 1000.0);
  
  fprintf(arquivoSaida, "\n-- Merge Sort --\n");
  gettimeofday(&ini, NULL); //Inicia o timer
  mergeSort(vet, 0, tam-1);
  gettimeofday(&fim, NULL); //Finaliza o timer
  
  clockMerge[iclock] = ( (fim.tv_sec - ini.tv_sec) * 1000.0 ); 
  clockMerge[iclock] += ( (fim.tv_usec - ini.tv_usec) / 1000.0 );
  
  fprintf(arquivoSaida, "Tempo de execução: %lf s\n", clockMerge[iclock] * 1000.0);
  
  fprintf(arquivoSaida, "\n-- Smooth Sort --\n");
  gettimeofday(&ini, NULL); //Inicia o timer
  smoothSort(vet, tam-1);
  gettimeofday(&fim, NULL); //Finaliza o timer
  
  clockSmooth[iclock] = ( (fim.tv_sec - ini.tv_sec) * 1000.0 ); 
  clockSmooth[iclock] += ( (fim.tv_usec - ini.tv_usec) / 1000.0 );
  
  fprintf(arquivoSaida, "Tempo de execução: %lf  s\n", clockSmooth[iclock] * 1000.0);
}

// Funções gerais
int geraAleatorios(char *nomeArquivo, int qtd)
{
  //Esta função gera 'qtd' números aleatórios e os escreve no arquivo 'nomeArquivo'
  //A função retorna 0 se funcionou corretamente. Retorna 1 se houve algum erro no processo.
  
  int result;
    
  FILE *arq = fopen("arquivoTeste.txt", "w"); //Cria um arquivo com o nome salvo em nomeArquivo

  if (arq == NULL) //Se não conseguir criar o arquivo
    return 1;

  srand(time(NULL));

  for (int i=0; i<qtd; i++)
  {
    result = fprintf(arq, "%d\n", rand()%1000); //Os tameros variam entre 0 e 1000.
      
    if (result == EOF)
        
      return 1;
  }
  fclose(arq);
    
  return 0;
}

int* leArquivo(char *nomeArquivo, int qtd)
{
  // Esta função lê 'qtd' dados do arquivo 'nomeArquivo' 
  // e os insere em um vetor de inteiros.
  // A função retorna NULL caso haja algum erro no processo.
  int *vet = (int*) malloc (qtd * sizeof(int));
	
  FILE *arq = fopen(nomeArquivo, "r");

  if (arq == NULL)
    return NULL;

  for (int i = 0; i < qtd; i++)
    fscanf(arq, "%d", &vet[i]);

  fclose(arq);
    
  return vet;
}

void copiaVetor(int *backup, int *vet, int tam)
{
  //Esta função copia os valores do vetor de backup
  //de volta para o vetor original
  for (int i; i < tam; i++)
    vet[i] = backup[i];
}

void imprimeVet(int *vet, int tam)
{
  //Esta função recebe um vetor e o imprime na tela
  printf("[");
  for (int i=0; i<tam-1; i++)
    printf("%d, ", vet[i]);
  printf("%d]\n", vet[tam-1]);
}
//---------------------------------------------

//Selection Sort
void selecao(int *vet, int tam)
{
  //Esta função recebe um vetor de inteiros de tamanho 'tam' e o ordena (ordem crescente) utilizando o método seleção
	int i, j, aux, min_index;

	for (i = 0; i < tam-1; i++){
		min_index = i;
		for(j = i+1; j < tam; j++){
			if (vet[j] < vet[min_index])
				min_index = j;
		}
		if (min_index != i){
			aux = vet[min_index];
			vet[min_index] = vet[i];
			vet[i] = aux;
		}
	}
}
//---------------------------------------------

//Quick Sort
void quickSort(int *vet, int inicio, int fim)
{
  //Função QuickSort recursiva
	if (inicio < fim){
		//part_i é o indice de particionamento
		int part_i = particiona(vet, inicio, fim);

		quickSort(vet, inicio, part_i - 1); //Antes do part_i
		quickSort(vet, part_i + 1, fim); //Depois do part_i
	}
}

int particiona(int *vet, int inicio, int fim)
{
  //Função que ordena o elemento pivô.
	int aux; //Valor auxiliar
	
	//Coloca o pivô como o último valor
	int pivo = vet[fim];

	//Indice do menor elemento e a posição mais a direita do pivô até agora
	int i = (inicio - 1);

	for (int j = inicio ; j <= fim - 1; j++)
    {
		//Se o elemento for menor que o pivô 
		if (vet[j] < pivo)
        {
			i++; //Incrementa o indice do menor elemento
			aux = vet[i];
			vet[i] = vet[j];
			vet[j] = aux;
		}
	}
	aux = vet[i + 1];
	vet[i + 1] = vet[fim];
	vet[fim] = aux;

 	//Retorna o indice de particionamento
	return (i + 1);
	
}
//---------------------------------------------

//Merge Sort
void mergeSort(int *vet, int inicio, int fim)
{
//Função Mergesort Recursiva
    
	if (fim > inicio) 
    {
		//Encontra o ponto médio para dividir o vetor no meio
		int meio = inicio + (fim - inicio)/2;

		//Chama o mergeSort para a primeira metade
		mergeSort(vet, inicio, meio);

		//Chama o mergeSort para a segunda metade
		mergeSort(vet, meio+1, fim);

		//Mescla as duas metades 
		merge(vet, inicio, meio, fim);
	}
}

void merge(int *vet, int inicio, int meio, int fim)
{
//Função Merge, que combina dois vetores previamente ordenados
	int i, j, k; //Indices
	int n1 = meio - inicio + 1; //Tamanho da primeira metade
	int n2 = fim - meio; //Tamanho da segunda metade

	int vet_temp1[n1], vet_temp2[n2]; //Vetores temporários da 1° e 2° metade

	//Copia as partes para os vetores temporários
	for (i = 0; i < n1; i++)
		vet_temp1[i] = vet[inicio + i];
	
	for (j = 0; j < n2; j++)
		vet_temp2[j] = vet[meio + 1 + j];

	//Mescla os vetores temporários no vetor
	i = 0; //Indice inicial do primeiro subvetor
	j = 0; //Indice inicial do segundo subvetor
	k = inicio; //Indice inicial do subvetor mesclado
	
	while(i < n1 && j < n2)
    {
		if (vet_temp1[i] <= vet_temp2[j])
        {
			vet[k] = vet_temp1[i];
			i++;
		}
		else 
        {
			vet[k] = vet_temp2[j];
			j++;
		}
		k++;
	}

	//Copia os valores restantes do vet_temp1 se ainda tiver
	while (i < n1)
    {
		vet[k] = vet_temp1[i];
		i++;
		k++;
	}

	//Copia os valores restantes do vet_temp2 se ainda tiver
	while (j < n2)
    {
		vet[k] = vet_temp2[j];
		j++;
		k++;
	}
}
//---------------------------------------------

//Smooth Sort
static const uint32_t L[] = // Números de Leonardo entre 0 e 32bits (2^32)
{
  1UL, 1UL, 3UL, 5UL, 9UL, 15UL, 25UL, 41UL, 67UL, 109UL, 177UL,
  287UL, 465UL, 753UL, 1219UL, 1973UL, 3193UL, 5167UL, 8361UL,
  13529UL, 21891UL, 35421UL, 57313UL, 92735UL, 150049UL,
  242785UL, 392835UL, 635621UL, 1028457UL, 1664079UL, 2692537UL,
  4356617UL, 7049155UL, 11405773UL, 18454929UL, 29860703UL,
  48315633UL, 78176337UL, 126491971UL, 204668309UL, 331160281UL,
  535828591UL, 866988873UL, 1402817465UL, 2269806339UL,
  3672623805UL
};

typedef struct heapsizes
{
  uint64_t mask; // Número de Leonardo em uso (tamanho de heaps existentes)
  int offset;    // Adiciona à posição de cada bit
  // 'mask' sempre termina com um bit '1', 
  // então 'offset' também é o tamanho do menor heap
}heapsizes;
                   
void smoothSort (int *vet, uint32_t tam)
{
  // Se possuir apenas um elemento, finaliza
  if (tam < 2) {
    imprimeVet(vet, tam);
    return;
  }
  
  heapsizes hsz;
  
  // Cria uma lista ordenada de heaps 
  hsz = heapify(vet, tam);

  // Extrai a lista de heaps
  extract(vet, tam, hsz);
}

static heapsizes heapify (int *vet, uint32_t tam)
{
  heapsizes hsz;  // Lista com os tamanhos das heaps existentes
  uint32_t i;     // Índice para percorrer a matriz
    
  // Flag que indica se um heap recém-criado será fundido 
  // posteriormente em um heap maior (wbf!=0) ou não (wbf==0)
  int wbf;

  hsz.mask = 1;   // Cria um heap de tamanho L[1]
  hsz.offset = 1; // contendo o primeiro elemento

  for (i=1; i<tam; i++)
  {
    if (hsz.mask & 2){ // Se forem números Leonardo consecutivos...
      hsz.mask = (hsz.mask>>2) | 1; // funde as últimas duas heaps
      hsz.offset += 2;
    }
    else if (hsz.offset == 1) // Se não, se o último heap tiver tamanho L[1]...
    {
      hsz.mask = (hsz.mask << 1) | 1; // o novo heap será L[0]
      hsz.offset = 0;
    }
    else // Se não, o novo heap será L[1]
    {
      hsz.mask = (hsz.mask << (hsz.offset-1)) | 1;
      hsz.offset = 1;
    }
    
    // O heap atual será fundido no futuro se:
    // a) Os tamanhos desta pilha e da anterior são números Leonardo
    //    contíguos E existe pelo menos mais um elemento na matriz
    // OU
    // b) Este heap tem tamanho L[x] onde x>0 E ainda há espaço para 
    //    um heap de tamanho L[x-1] e mais um elemento 
    //    (L[x]+L[x-1]+1 --> L [x+1])
    wbf = ( (hsz.mask & 2) && i+1 < tam ) || ( hsz.offset > 0 && 1ULL+i+L[hsz.offset-1] < tam );

    if (wbf)                       // Se este novo heap for fundido, 
      sift_in (vet+i, hsz.offset); // não propague a raiz (apenas corrija este heap). 
    else                           // Se não vai ser fundido, 
      interheap_sift (vet+i, hsz); // propaga a raiz através da sequência de
  }                                // heaps para garantir a ordenação correta 
  return hsz;
}

static void extract (int *vet, uint32_t tam, heapsizes hsz)
{
  uint32_t i;     // Índice para percorrer o vetor

  uint32_t ch[2]; // Posição dos filhos (ch-ildren) esquerdo e 
                  // direito de um heap recém-criado
  
  // Extrai os elementos começando do final.
  // Quando restam apenas dois, termina.
  for (i = tam-1; i > 1; i--)
  {
    if (hsz.offset<2) // Se o último heap tiver tamanho L[1] ou L[0] (ambos == 1),
    {
      do // basta remover este heap (atualizar a estrutura heapsizes)
      {  // deixando o elemento único intocado
        hsz.mask >>= 1;
        hsz.offset ++;
      }
      while (!(hsz.mask&1)); // A máscara nunca será 0 porque o loop termina 
    }                        // mais cedo (com dois heaps de tamanhos L[1] e L[0])
    else
    {
      ch[1] = i - 1;                   // Filho da direita
      ch[0] = ch[1] - L[hsz.offset-2]; // e filho da esquerda

      hsz.mask &= ~1ULL; // Remove o heap atual

      for (int j=0; j<2; j++) // Para cada filho do heap (1° esqueda)
      {
        // Adicione heap à lista e garante a ordenação das raízes
        hsz.mask = (hsz.mask << 1) | 1;
        hsz.offset --;
        
        interheap_sift (vet+ch[j], hsz);
      }
    }
  }
}

static inline void sift_in (int * root, int size)
{
  int * left, * right; // Pos. dos filhos do heap
  int * next;          // Filho escolhido (maior raiz)
  int chsz;            // Tamanho do filho escolhido
  int tmp;             // Valor para descer na heap
  
  if (size < 2)  // Se estiver numa folha,
    return;      // não faz nada

  tmp = *root;   // Salva o valor inicial
  
  do  // Enquanto houver filhos na heap...
  {
    // Localiza os filhos
    right = root - 1;
    left = right - L[size-2];
    
    if (*right < *left) // Compara suas raízes
    {
      next = left;      // Seleciona a heap do filho esquerdo
      chsz = size - 1;  // (maior subheap)
    }
    else
    {
      next = right;     // Seleciona a heap do filho direito
      chsz = size - 2;  // (menor subheap)
    }
    if (*next <= tmp) // Se ambas as raízes são menores que a raiz inicial,
      break;          // então atingiu a posição final

    // Se não,
    // empurra a raiz maior e desçe para o próximo nível
    *root = *next;
    root = next;
    size = chsz;
  }
  while (size > 1); // Se chegar a uma folha, para

  *root = tmp; // Escreve o valor inicial em sua posição final
}

static inline void interheap_sift (int * root, heapsizes hsz)
{
  int * next;   // Raiz da próxima heap
  int * left;   // Pos. do filho esquerdo da heap atual
  int * right;  // Pos. do filho direito da heap atual
  int tmp;      // Valor para mover para a esquerda
  int max;      // Valor raiz efetivo da heap atual
  
  tmp = *root;  // Salva o valor inicial
  
  while (hsz.mask != 1)  // Percorre a list de heaps
  {                      // da esqueda para a direita
    max = tmp;
      
    if (hsz.offset > 1) // Se essa heap tiver filhos
    {
      //Localiza os filhos:
      right = root - 1;
      left = right - L[hsz.offset-2];

      // Usa o valor máximo para as comparações abaixo, 
      // pois é a raiz efetiva desse heap
      if (max < *left)
        max = *left;

      if (max < *right)
        max = *right;
    }
      
    next = root - L[hsz.offset]; // Posição da próxima heap

    if (*next <= max) // Se a ordenação está completa,
      break;          // para aqui

    // Se não, empurre a raiz dessa heap e vá para ela
    *root = *next;
    root = next;
    do
    { 
      //Extrai o heap anterior da lista
      //'hsz' é apenas uma cópia temporária
      hsz.mask >>= 1;
      hsz.offset ++;
    }
    while (!(hsz.mask&1));
  }
  *root = tmp;                // Coloque a raiz inicial no heap onde paramos 
  sift_in (root, hsz.offset); // e garanta a ordenação interna correta nele
}
//---------------------------------------------