#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>

void soma_paralela(int start, int end,int soma, int *vetor) {
    for (int i = start; i < end; i++) {
        soma+= vetor[i];
    }
}

int main(){
    int shmid1 = shmget(IPC_PRIVATE, 2 * sizeof(int), IPC_CREAT | 0666);

     int *A = (int *)shmat(shmid1, NULL, 0);

    int tam = 10000;
    int vetor[tam];

    for(int i = 0; i<tam;i++){
        vetor[i] = rand()%100000;
    }

    int meio = tam/2;
    pid_t pid1 = fork();
    int soma1 = 0;
    int soma2 = 0;

    if(pid1 ==0){





}