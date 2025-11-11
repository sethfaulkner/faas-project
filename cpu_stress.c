#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <time.h>

#define NUM_THREADS 2
#define TOTAL_ITERATIONS 10000000000
#define CHECKPOINT 1000000000

void* stress_thread(void* arg) {
    int thread_id = (int)(long)arg;
    unsigned long i;
    double x = 0.0;

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (i = 1; i <= TOTAL_ITERATIONS; i++) {
        x += sqrt(i % 1000);

        if (i % CHECKPOINT == 0) {
            clock_gettime(CLOCK_MONOTONIC, &end);
            double elapsed = (end.tv_sec - start.tv_sec) +
                             (end.tv_nsec - start.tv_nsec) / 1e9;
            printf("Thread %d reached %lu iterations, elapsed: %.3f s\n",
                   thread_id, i, elapsed);
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    double total_elapsed = (end.tv_sec - start.tv_sec) +
                           (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Thread %d finished %lu iterations in %.3f s\n",
           thread_id, (unsigned long)TOTAL_ITERATIONS, total_elapsed);

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, stress_thread, (void*)i);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads finished.\n");
    return 0;
}
