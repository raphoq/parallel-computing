/* RAFAŁ ŁUCZUN */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "mpi.h"

main(int argc, char **argv)
{
	int rank,
		p,
		source,
		dest;

	srand(time(NULL));
	
		
	struct timespec t1, t2;
	
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	
	int size;
	sscanf(argv[1], "%d", &size); 
	
	double *numbers = malloc((size*p) * sizeof *numbers);
	double *numberPart = malloc(size * sizeof *numberPart);
	int singleTestPass = 0;
	int finalTestPass;
	float pi;
	int i;
	int j;
	
	
	MPI_Barrier(MPI_COMM_WORLD);
	
	if(rank == 0) {
		clock_gettime(CLOCK_REALTIME, &t1);
	}
	
	for(i = 0; i < size; i++) {
		numbers[i] = ((double) rand() / (double) (RAND_MAX));
	}
	
	
	for(i = 0; i < size; i += 2) {
		if(((numbers[i] * numbers[i]) + (numbers[i+1] * numbers[i+1])) <= 1.0) {
			singleTestPass += 1;
		}
	}
	
	MPI_Reduce(&singleTestPass, &finalTestPass, p, MPI_INT,MPI_SUM, 0, MPI_COMM_WORLD);
	
	MPI_Barrier(MPI_COMM_WORLD);
	
	if(rank == 0) {
		pi = 4*((double) finalTestPass / ((size*p) / 2));
		printf("Liczba punktów w kwadracie: %i\n", (size*p)/2);
		printf("Liczba punktów w kole: %i\n", finalTestPass);
		printf("Wartosc liczby PI: %lf\n", pi);
	
	
		clock_gettime(CLOCK_REALTIME, &t2);		// Drukowanie czasu działania
		unsigned long nansec = t2.tv_nsec - t1.tv_nsec;
		printf("Czas wykonania: %ld\n", nansec);
	}
	
	
	
	MPI_Finalize();

}