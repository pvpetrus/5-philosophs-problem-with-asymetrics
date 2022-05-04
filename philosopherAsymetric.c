#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

//problem dotyczacy 5 filozofow jedzacych 5 dan 5 widelcami
//filozofowie usadzeni sa przy okraglym stole
//kazdy z filozofow je 2 widelcami jednoczesnie inaczej czeka
//aby zjesc, niektorzy z nich musza czekac az filozof obok nich zje aby otrzymac widelec
pthread_mutex_t forks[5];
void* philosopher(void* argument)
{
    int leftFork = *(int*) argument;
    int rightFork = (leftFork+1) % 5;
    int sleep;
    while(1==1)
    {
        //kazdy z filozofow zaczyna jesc w roznych momentach
        sleep = rand() % 145678;
        usleep(sleep);
        pthread_mutex_lock(&forks[leftFork]);
        printf("%d podniosl lewy widelec (%d) i wciaz mysli\n", leftFork, leftFork);
        pthread_mutex_lock(&forks[rightFork]);
        printf("%d podniosl prawy widelec (%d), konczy myslec i zaczyna jesc\n", leftFork, rightFork);
        sleep = rand() % 1456789;
        //kazdy z filozofow konczy jesc w roznych momentach
        usleep(sleep);
        pthread_mutex_unlock(&forks[leftFork]);
        printf("%d konczy jesc i zaczyna myslec\n", leftFork);
        pthread_mutex_unlock(&forks[rightFork]);
        printf("%d polozyl prawy widelec (%d) i wciaz mysli\n", index, rightFork);
    }
    return NULL;
}
void* philosopher_asymetric(void* argument)
{
    int leftFork = *(int*) argument;
    int rightFork = (leftFork+1) % 5;
    int sleep;
    while(1==1)
    {
        //kazdy z filozofow zaczyna jesc w roznych momentach
        sleep = rand() % 145678;
        usleep(sleep);
        pthread_mutex_lock(&forks[rightFork]);
        printf("%d podnosi prawy widelec i mysli\n", leftFork);
        pthread_mutex_lock(&forks[leftFork]);
        printf("%d podnosi lewy widelec i juz nie mysli i je\n", leftFork);
        sleep = rand() % 1456789;
        //kazdy z filozofow konczy jesc w roznych momentach
        usleep(sleep);
        pthread_mutex_unlock(&forks[rightFork]);
        printf("%d konczy jesc i kladzie prawy widelec\n", leftFork);
        pthread_mutex_unlock(&forks[leftFork]);
        printf("%d kladzie lewy widelec\n", leftFork);
    }
    return NULL;
}
int main()
{
    pthread_t threads[5];
    int i;
    for(i=0;i<4;i++)
    {
        pthread_create(&threads[i],NULL,philosopher,&i);
    }
    pthread_create(&threads[4],NULL,philosopher_asymetric,&i);
    for(int i=0;i<5;i++)
    {
        pthread_join(threads[i],NULL);
    }
    return 0;
}
