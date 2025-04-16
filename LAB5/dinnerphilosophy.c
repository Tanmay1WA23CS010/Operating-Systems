
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define N 5 // Number of philosophers
#define MEALS 3 // Number of meals per philosopher

sem_t chopsticks[N];

void* philosopher(void* num) {
    int id = *(int*)num;
    int left = id;
    int right = (id + 1) % N;
    int meals_eaten = 0;

    while (meals_eaten < MEALS) {
        // Thinking
        printf("Philosopher %d is thinking...\n", id);
        sleep(1 + rand() % 3);

        // Hungry 
        printf("Philosopher %d is hungry\n", id);

        if (id % 2 == 0) {
  
            sem_wait(&chopsticks[right]);
            printf("\tPhilosopher %d picked up right chopstick %d\n", id, right);
            usleep(100000); // Small delay
            sem_wait(&chopsticks[left]);
            printf("\tPhilosopher %d picked up left chopstick %d\n", id, left);
        } else {
            // Odd philosopher: left then right
            sem_wait(&chopsticks[left]);
            printf("\tPhilosopher %d picked up left chopstick %d\n", id, left);
            usleep(100000); // Small delay
            sem_wait(&chopsticks[right]);
            printf("\tPhilosopher %d picked up right chopstick %d\n", id, right);
        }

        // Eating
        printf("Philosopher %d is eating (meal %d/%d)\n", id, meals_eaten+1, MEALS);
        sleep(1 + rand() % 2);
        meals_eaten++;

   
        sem_post(&chopsticks[left]);
        sem_post(&chopsticks[right]);
        printf("\tPhilosopher %d put down chopsticks %d and %d\n", id, left, right);
    }

    printf("Philosopher %d finished all meals and left\n", id);
    return NULL;
}

int main() {
    pthread_t philosophers[N];
    int ids[N];
    srand(time(NULL));

s
    for (int i = 0; i < N; i++) {
        sem_init(&chopsticks[i], 0, 1);
    }


    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }


    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Cleanup
    for (int i = 0; i < N; i++) {
        sem_destroy(&chopsticks[i]);
    }

    printf("All philosophers finished eating. No deadlock occurred.\n");
    return 0;
}
