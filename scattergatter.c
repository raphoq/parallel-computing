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

	int i;
	
	srand(time(NULL));

	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	
	int *array = malloc((p * 10) * sizeof *array);
	
	int arrayPart[10];
	double subAvg;
	int temp = 0;
	double *avgs = NULL;
	
	if(rank == 0) {
		for(i = 0; i < (p * 10); i++) {
			array[i] = rand() % 1000;
		}
		for(i = 0; i < (p * 10); i++) {
			printf("%i\n", array[i]);
		}
		avgs = malloc(p * sizeof *avgs);
	}
	
	MPI_Scatter(array, 10, MPI_INT, &arrayPart, 10, MPI_INT, 0, MPI_COMM_WORLD);
	
		
	for(i = 0; i < 10; i++) {
		temp += arrayPart[i];
	}

	subAvg = temp / 10;
	
	MPI_Gather(&subAvg, 1, MPI_DOUBLE, avgs, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	
	MPI_Barrier(MPI_COMM_WORLD);
	
	if(rank == 0) {
		for(i = 0; i < p; i++) {
			printf("%.2lf | ", avgs[i]);
		}
		printf("\n");
	}
	
	
	MPI_Finalize();

}