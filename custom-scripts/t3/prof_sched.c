#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_THREADS 26          // quantidade de letras no alfabeto

char* buffer;                   // buffer global
int pos_buffer;                 // posicao atual do buffer
int tam_buffer;                 // tamanho do buffer
int num_threads;                // quantidade de threads
int cont_threads[MAX_THREADS];  // contagem de quantas vezes cada thread foi escalonada
sem_t mutex;

// pthread_cond_t cond;

pthread_barrier_t barrier;

void* func_thread(void* arg) // funcao que cada thread vai rodar
{
  char id_thread = *((char*)arg);

  // pthread_cond_wait(&cond, &mutex);
  pthread_barrier_wait(&barrier);

  for (;;) // roda ate todo o buffer ser preenchido
  {
    sem_wait(&mutex);
    if (pos_buffer < tam_buffer)
    {
      buffer[pos_buffer++] = id_thread; // coloca a letra correspondente da thread no buffer global
    }
    else
    {
      sem_post(&mutex);
      break;
    }
    sem_post(&mutex);
  }

  return NULL;
}

int main(int argc, char* argv[]) 
{
  if (argc != 3) 
  {
    printf("Uso: %s <tamanho_do_buffer> <n�mero_de_threads>\n", argv[0]);
    return 1;
  }

  pos_buffer = 0;
  tam_buffer = atoi(argv[1]);
  num_threads = atoi(argv[2]);

  if (tam_buffer <= 0 || num_threads <= 0 || num_threads > MAX_THREADS) // testa os inputs
  {
    printf("Argumentos inv�lidos.\n");
    return 1;
  }

  buffer = (char*)malloc(tam_buffer * sizeof(char));
  if (buffer == NULL) 
  {
    perror("Falha na aloca��o de mem�ria para o buffer\n");
    return 1;
  }

  // pthread_cond_init(&cond, NULL);
  pthread_barrier_init(&barrier, NULL, num_threads + 1);

  sem_init(&mutex, 0, 1);

  pthread_t threads[num_threads];
  char ids_threads[num_threads];

  for (int i = 0; i < num_threads; i++) 
  {
    ids_threads[i] = 'A' + i;
    pthread_create(&threads[i], NULL, func_thread, &ids_threads[i]); // dispara as threads com seus ids (letras) proprios
  }

  // pthread_cond_broadcast(&cond);

  pthread_barrier_wait(&barrier);

  for (int i = 0; i < num_threads; i++) 
  {
    pthread_join(threads[i], NULL); // aguarda todas threads terminarem
  }

  printf("Buffer global: %s\n", buffer);

  char* novo_buffer = (char*)malloc(tam_buffer * sizeof(char)); // buffer que tera o pos processamento do original
  if (novo_buffer == NULL) 
  {
    perror("Falha na aloca��o de mem�ria para o novo buffer\n");
    return 1;
  }
  int cont_pos_novo_buff = 0;
  char char_anterior = buffer[0];

  for (int i = 1; i < tam_buffer; i++) 
  {
    if (buffer[i] == char_anterior) 
    {
      // continua na mesma letra
    }
    else 
    {
      cont_threads[char_anterior - 'A']++; // cada vez que muda de letra, incrementa o contador de "escalonadas" da ultima letra

      novo_buffer[cont_pos_novo_buff++] = char_anterior; // adiciona uma unidade da letra no novo buffer (reduzido)
      char_anterior = buffer[i]; // atualiza o char_anterior para a nova letra
    }
  }

  printf("N�mero de vezes que cada thread foi escalonada:\n");
  for (int i = 0; i < num_threads; i++) 
  {
    printf("%c - %d\n", 'A' + i, cont_threads[i]);
  }

  free(buffer);
  sem_destroy(&mutex);

  return 0;
}
