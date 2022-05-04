#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <syslog.h>
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
        //kazdy z filozofow zaczyna jesc w roznych momentach
        sleep = rand() % 145678;
        usleep(sleep);
        pthread_mutex_lock(&forks[leftFork]);
        syslog(LOG_NOTICE,"%d podnosi lewy widelec i mysli\n", leftFork);
        pthread_mutex_lock(&forks[rightFork]);
        syslog(LOG_NOTICE,"%d podnosi prawy widelec i je\n", leftFork);
        sleep = rand() % 1456789;
        //kazdy z filozofow konczy jesc w roznych momentach
        usleep(sleep);
        pthread_mutex_unlock(&forks[leftFork]);
        syslog(LOG_NOTICE,"%d konczy jesc i  mysli\n", leftFork);
        pthread_mutex_unlock(&forks[rightFork]);
        syslog(LOG_NOTICE,"%d polozyl prawy widelec\n", leftFork);
    
    return NULL;
}
void* philosopher_asymetric(void* argument)
{
    int leftFork = *(int*) argument;
    int rightFork = (leftFork+1) % 5;
    int sleep;
        //kazdy z filozofow zaczyna jesc w roznych momentach
        sleep = rand() % 145678;
        usleep(sleep);
        pthread_mutex_lock(&forks[rightFork]);
        syslog(LOG_NOTICE,"%d podnosi prawy widelec i mysli\n", leftFork);
        pthread_mutex_lock(&forks[leftFork]);
        syslog(LOG_NOTICE,"%d podnosi lewy widelec i juz nie mysli i je\n", leftFork);
        sleep = rand() % 1456789;
        //kazdy z filozofow konczy jesc w roznych momentach
        usleep(sleep);
        pthread_mutex_unlock(&forks[rightFork]);
        syslog(LOG_NOTICE,"%d konczy jesc i kladzie prawy widelec\n", leftFork);
        pthread_mutex_unlock(&forks[leftFork]);
        syslog(LOG_NOTICE,"%d kladzie lewy widelec\n", leftFork);
    return NULL;
}
int main()
{

    openlog("filozofowie", LOG_PID,LOG_DAEMON);
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
