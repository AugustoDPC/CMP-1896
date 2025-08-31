#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

void soma_paralela(int comeco, int fim, int *soma, int *vetor) {
    for (int i = comeco; i < fim; i++) {
        *soma += vetor[i];
    }
}

int main() {
    int shmid = shmget(IPC_PRIVATE, 2 * sizeof(int), IPC_CREAT | 0666);

    int *soma = (int *)shmat(shmid, NULL, 0);

    int tam = 10000;

    int *vetor = (int *)malloc(tam * sizeof(int));

    srand(time(NULL));
    for (int i = 0; i < tam; i++) {
        vetor[i] = rand() % 1000;
    }

    int meio = tam / 2;
    pid_t pid1 = fork();

    if (pid1 == 0) { 
        soma_paralela(0, meio, &soma[0], vetor);
        exit(0);
    } else { 
        pid_t pid2 = fork();

        if (pid2 == 0) { 
            soma_paralela(meio, tam, &soma[1], vetor);
            exit(0);
        }
    }

    wait(NULL);
    wait(NULL);
    
    int soma_total = soma[0] + soma[1];

    printf("Soma da primeira metade: %d\n", soma[0]);
    printf("Soma da segunda metade: %d\n", soma[1]);
    printf("Soma total: %d\n", soma_total);
    printf("Média: %.2f\n", (float)soma_total / tam);
    shmdt(soma);
    shmctl(shmid, IPC_RMID, NULL);
    free(vetor);

    return 0;
}