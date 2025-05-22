#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define MEALS 3
#define N 5

sem_t chopsticks[N]; // Declare semaphores for chopsticks

// Philosopher function
void *philosopher(void *num) {
    int id = *(int *)num;
    int left = id;
    int right = (id + 1) % N;
    int meals_eaten = 0;

    while (meals_eaten < MEALS) {
        printf("Philosopher %d is thinking\n", id);
        sleep(1 + rand() % 3);  // Simulate thinking

        printf("Philosopher %d is hungry\n", id);

        // If the philosopher is even, pick up the right chopstick first
        if (id % 2 == 0) {
            sem_wait(&chopsticks[right]);
            printf("Philosopher %d picked up right chopstick %d\n", id, right);
            usleep(1000);  // Simulate the time to pick up the chopstick

            sem_wait(&chopsticks[left]);
            printf("Philosopher %d picked up left chopstick %d\n", id, left);
        } else {
            // If the philosopher is odd, pick up the left chopstick first
            sem_wait(&chopsticks[left]);
            printf("Philosopher %d picked up left chopstick %d\n", id, left);
            usleep(1000);  // Simulate the time to pick up the chopstick

            sem_wait(&chopsticks[right]);
            printf("Philosopher %d picked up right chopstick %d\n", id, right);
        }

        // Now the philosopher is eating
        printf("Philosopher %d is eating\n", id);
        meals_eaten++;
        sleep(1 + rand() % 2);  // Simulate eating time

        // After eating, put down the chopsticks
        sem_post(&chopsticks[left]);
        sem_post(&chopsticks[right]);
        printf("Philosopher %d put down both chopsticks\n", id);
    }

    printf("Philosopher %d has finished all meals\n", id);
    return NULL;
}

int main() {
    pthread_t philosophers[N];
    srand(time(NULL));
    int ids[N];

    // Initialize semaphores (one for each chopstick)
    for (int i = 0; i < N; i++) {
        sem_init(&chopsticks[i], 0, 1);
    }

    // Create threads for philosophers
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    // Join threads to ensure main waits for philosophers to finish
    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy semaphores
    for (int i = 0; i < N; i++) {
        sem_destroy(&chopsticks[i]);
    }

    return 0;
}
