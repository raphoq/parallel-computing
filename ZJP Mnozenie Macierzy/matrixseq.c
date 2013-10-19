/* RAFAŁ ŁUCZUN */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

main(int argc, char **argv)
{
	srand(time(NULL));
		
	struct timespec t1, t2;
	
	int size;
	sscanf(argv[1], "%d", &size); 
	
	int *matrixFull = malloc((size*size) * sizeof *matrixFull);
	int *vector = malloc(size * sizeof *vector);
	int *fullResult = malloc(size * sizeof *fullResult);
	int i;
	int j;
	int k;
	
	
	
	for(i = 0; i < size * size; i++) {
		matrixFull[i] = rand() % 100;
	}
	for(i = 0; i < size; i++) {
		vector[i] = rand() % 100;
		
	}
	clock_gettime(CLOCK_REALTIME, &t1);
	
	
	for(i = 0; i < size; i++) {
		fullResult[i] = 0;
	}
	
	k = 1;
	for(i = 0; i < size*size; i = i + size) {
		for(j = i; j < size * k; j++) {
			fullResult[k - 1] += sin(matrixFull[j] * vector[j % size]);
		}
		k++;
	}
	
	
	// for(i = 0; i < size; i++) {
		// printf("--------\n%i\n", fullResult[i]);
	// }
	printf("\n\n");

	clock_gettime(CLOCK_REALTIME, &t2);
	unsigned long nansec = t2.tv_nsec - t1.tv_nsec;
	printf("Czas wykonania: %ld\n", nansec);
	
	
}