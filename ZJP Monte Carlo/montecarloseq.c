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
	
	double *numbers = malloc(size * sizeof *numbers);
	int finalTestPass;
	float pi;
	int i;
	int j;
	
	clock_gettime(CLOCK_REALTIME, &t1);
	
	for(i = 0; i < size; i++) {
		numbers[i] = ((double) rand() / (double) (RAND_MAX));
	}
	
	
	for(i = 0; i < size; i += 2) {
		if(((numbers[i] * numbers[i]) + (numbers[i+1] * numbers[i+1])) <= 1.0) {
			finalTestPass += 1;
		}
	}
	
	
	pi = 4*((double) finalTestPass / (size / 2));
	printf("Liczba punktów w kwadracie: %i\n", size/2);
	printf("Liczba punktów w kole: %i\n", finalTestPass);
	printf("Wartosc liczby PI: %lf\n", pi);


	clock_gettime(CLOCK_REALTIME, &t2);		// Drukowanie czasu działania
	unsigned long nansec = t2.tv_nsec - t1.tv_nsec;
	printf("Czas wykonania: %ld\n", nansec);
	
	

}