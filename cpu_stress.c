#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>

unsigned long NUM_THREADS;
unsigned long TOTAL_ITERATIONS;
unsigned long CHECKPOINT;

void* stress_thread(void* arg) {
    long thread_id = (long)arg;
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
            printf("Thread %ld reached %lu iterations, elapsed: %.3f s\n",
                   thread_id, i, elapsed);
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    double total_elapsed = (end.tv_sec - start.tv_sec) +
                           (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Thread %ld finished %lu iterations in %.3f s\n",
           thread_id, TOTAL_ITERATIONS, total_elapsed);

    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        printf("Usage: %s <num_threads> <total_iterations> <checkpoint>\n", argv[0]);
        return 1;
    }

    NUM_THREADS = strtoul(argv[1], NULL, 10);
    TOTAL_ITERATIONS = strtoul(argv[2], NULL, 10);
    CHECKPOINT = strtoul(argv[3], NULL, 10);

    pthread_t threads[NUM_THREADS];

    for (long i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, stress_thread, (void*)i) != 0) {
            perror("pthread_create");
            return 1;
        }
    }

    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads finished.\n");
    return 0;
}
