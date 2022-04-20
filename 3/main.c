#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int DECK_SIZE = 52;
int globalCount = 0;
pthread_mutex_t mutex;

void SwapInts(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

double globalTimeForRand = 0;

void *FuncForThread(void *arg) {
    int localCount = 0;
    int roundsNumber = *((int *)arg);
    int deck[DECK_SIZE];
    int i, j, k;
    double threadTimeForRand = 0;
    for (k = 0; k < roundsNumber; ++k) {
        for (i = 0; i < DECK_SIZE; ++i) {
            deck[i] = (i + 1) % 13;  // cards value from 2 to 14 (or from 0 to 12)
        }
        for (i = DECK_SIZE - 1; i >= 0; --i) {
            struct timespec firstRandTime, lastRandTime;
            clock_gettime(CLOCK_MONOTONIC, &firstRandTime);
            j = rand() % (i + 1);
            clock_gettime(CLOCK_MONOTONIC, &lastRandTime);
            double localTimeForRand = (lastRandTime.tv_sec - firstRandTime.tv_sec);
            localTimeForRand += (lastRandTime.tv_nsec - firstRandTime.tv_nsec) / 1000000000.0;
            SwapInts(&deck[i], &deck[j]);
            threadTimeForRand += localTimeForRand;
        }
        if (deck[0] == deck[1]) {
            ++localCount;
        }
    }
    globalTimeForRand += threadTimeForRand;
    pthread_mutex_lock(&mutex);
    globalCount += localCount;
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Bad input, use ./a.out *number of rounds* *number of threads*\n");
        return 0;
    }
    int roundsNumber = atoi(argv[1]);
    int threadsNumber = atoi(argv[2]);
    struct timespec firstTime, lastTime;
    pthread_t threadsArray[threadsNumber];

    // Initializing mutex
    if (pthread_mutex_init(&mutex, NULL) < 0) {
        perror("pthread_mutex_init");
        exit(EXIT_FAILURE);
    }

    // Fix starting time
    clock_gettime(CLOCK_MONOTONIC, &firstTime);

    // Launching threads
    int roundsPerThread = roundsNumber / threadsNumber;
    for (int i = 0; i < threadsNumber; ++i) {
        if (pthread_create(&threadsArray[i], NULL, FuncForThread, &roundsPerThread) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    // Destroying threads
    for (int i = 0; i < threadsNumber; ++i) {
        if (pthread_join(threadsArray[i], NULL) != 0) {
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }

    // Fix ending time
    clock_gettime(CLOCK_MONOTONIC, &lastTime);
    double allTime = (lastTime.tv_sec - firstTime.tv_sec);
    allTime += (lastTime.tv_nsec - firstTime.tv_nsec) / 1000000000.0;

    // Destroying mutex
    if (pthread_mutex_destroy(&mutex) < 0) {
        perror("pthread_mutex_destroy");
        exit(EXIT_FAILURE);
    }

    printf("Probability is %.3lf\n", (double)globalCount / roundsNumber);
    printf("Counted for %lf seconds\n", allTime);
    printf("Time for rand() is %lf seconds\n", globalTimeForRand);
    printf("Average time for rand() is %lf per thread\n", globalTimeForRand / threadsNumber);
    printf("Time without rand is %lf\n", allTime - globalTimeForRand / threadsNumber);
    fflush(stdout);

    return 0;
}
