#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

pthread_mutex_t lock;
pthread_cond_t signal;
int flag=0;
void *ThePing(void *args ){
        int count=0;
        while(1){
                pthread_mutex_lock(&lock);
                //printf("Ping\n");
                while(flag!=1){
                pthread_cond_wait(&signal,&lock);
                printf("I'm waitng for the flag to be removed\n");
                }
                printf("Ping\n");
                flag=0;
                count++;
                pthread_cond_signal(&signal);
                pthread_mutex_unlock(&lock);
        }
}

void *ThePong(void *args){
        int count=0;
        while(1){
                pthread_mutex_lock(&lock);
          while(count<200){
                pthread_mutex_lock(&lock);
                while(flag!=0){
                        pthread_cond_wait(&signal,&lock);
                        printf("I'm waitng for the flag to be cleared by ping\n");
                }
                printf("Pong\n");
                flag=1;
                count++;
                pthread_cond_signal(&signal);
                pthread_mutex_unlock(&lock);
        }
}

int main()
{
        pthread_t t1,t2;
        pthread_mutex_init(&lock,NULL);
        pthread_cond_init(&signal,NULL);

        pthread_create(&t1,NULL,&ThePing,NULL);
        pthread_create(&t2,NULL,&ThePong,NULL);

        pthread_join(t1,NULL);
        pthread_join(t2,NULL);

        pthread_mutex_destroy(&lock);

}