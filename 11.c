#include <stdio.h>
#include <math.h>
#include <time.h>

void endFunction(void)
{
	printf("Koniec działania programu i wątku macierzystego\n");
}

void threadsCounter(int processCount)
{
	struct timespec t1, t2;
	clock_gettime(CLOCK_REALTIME, &t1);
	
	waitpid(getpid());
	
	int i,
		pid,
		pids[processCount];
		
	for(i = 0; i < processCount; i++) {
		pid = fork();
		if(pid != 0) waitpid(pid);
		pids[i] = pid;
		if(pid == 0) {
			printf("Proces nr. %i : PID %d \n", i, getpid());
			break;
		}
	}
	
	if(pid != 0) {
		endFunction();
		
		clock_gettime(CLOCK_REALTIME, &t2);
		long nansec = t2.tv_nsec - t1.tv_nsec;
		printf("Czas wykonania: %ld\n", nansec);
	}
	
	
}

int main()
{
	threadsCounter(10);
	return 0;
}