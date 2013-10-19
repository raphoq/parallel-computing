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

	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	
	int baseRandom = 0,
		temp,
		i;
	double 	result,
			memo;
	
	
	if(rank != 0) {
		MPI_Recv(&temp, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		result = temp / rank;
		printf("Proces nr. %i ||| %.2lf\n", rank, result);
	} else {
		baseRandom = rand() % 10000;
		printf("Jam jest proces GLOWNY, wyliczylem liczbe %i \n", baseRandom);
		for(i = 1; i < p; i++) {
			MPI_Send(&baseRandom, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
		}
	}
	
	MPI_Reduce(&result, &memo, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	
	if(rank == 0) {
		printf("Suma ostateczna : %.2lf\n", memo);
	}
	
	MPI_Finalize();

}