#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include <pthread.h>
#define limit1    4
#define limit2    40
#define num_th   3
void *printPrimeThreadCalculation(void *threadid);
void primeCheckerThread(int num1, int num2, int numOfThreads);
using namespace std;

int main() {
    primeCheckerThread(limit1, limit2, num_th);
    pthread_exit(NULL);
    return 0;
}

void *printPrimeThreadCalculation(void *threadid) {
    long tid;
    tid = (long) threadid;
    static int cnt=0; 
    int num1 = limit1+(limit2-limit1)*cnt/num_th;
    int num2 = limit1+(limit2-limit1)*(cnt+1)/num_th;
    cnt+=1;
    int isPrime, i;

    while (num1 <= num2) {
        isPrime = 1;

        for (i = 2; i < num1 && isPrime; i++) {
            if (num1 % i == 0) {
                isPrime = 0;
            }
        }
        if (isPrime == 1) {
        	ofstream escribirPrimos("primosP.txt",ios::out | std::ofstream::app);
        	escribirPrimos<<num1<<endl;
            printf("%d ", num1);
        }
        num1++;
    }
    printf("\n");
}

void primeCheckerThread(int num1, int num2, int numOfThreads) {
    pthread_t threads[numOfThreads];
    int rc;
    long t;
    for (t = 0; t < numOfThreads; t++) {
        rc = pthread_create(&threads[t], NULL, printPrimeThreadCalculation, (void *)t);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }  pthread_join(threads[t],NULL);

    }

}
