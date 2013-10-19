#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main()
{	
	struct timespec t1, t2;
	clock_gettime(CLOCK_REALTIME, &t1);
	
	int mainPID = getpid();
	waitpid(mainPID);
	int i,
		j,
		k,
		pid;
	double 	TAB[1000],
			TABRESULTS[10];
	
	for(i = 0; i < 10; i++) TABRESULTS[i] = 0.0;
	
	for(i = 0; i < 1000; i++) {
		TAB[i] = (double) rand() / (double) RAND_MAX;
	}
	
	for(i = 0; i < 10; i++) {
		k = 0;
		pid = fork();
		if(pid == 0) {
			for(j = i * 100; j < j + 100; j++) {
				k++;
				TABRESULTS[i] += TAB[j];
				if(k == 99) {
					printf("Proces nr. %i : PID %d ||| MOJA SUMA : %lf\n", i, getpid(), TABRESULTS[i]);
					waitpid(pid);
				}
			}
			break;
		}
		if(i == 9) {
			waitpid(pid);
			clock_gettime(CLOCK_REALTIME, &t2);
			long nansec = t2.tv_nsec - t1.tv_nsec;
			printf("Czas wykonania: %ld\n", nansec);
		}
	}
	
	
	
	return 0;
}