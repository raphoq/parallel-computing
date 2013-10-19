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
		memo;
	
	if (rank != 0) {
		MPI_Recv(&baseRandom, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		
		printf("Proces %d otrzymał liczbe %d od procesu %d\n", rank, baseRandom, rank - 1);
	} else {
		baseRandom = rand() % 10000;
		memo = baseRandom;
		printf("Moja liczba to: %i\n", baseRandom);
	}
	
	// Kazdy proces wysyla do kolejnego, a ostatni do procesu nr. 0
	MPI_Send(&baseRandom, 1, MPI_INT, (rank + 1) % p, 0, MPI_COMM_WORLD);
	
	if (rank == 0) {
		MPI_Recv(&baseRandom, 1, MPI_INT, p - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		if(memo == baseRandom) {
			printf("Proces %d otrzymal z powrotem liczbe %d od procesu %d, liczba jest taka sama\n", rank, baseRandom, p - 1);
		} else {
			printf("Proces %d otrzymal z powrotem liczbe %d od procesu %d, liczba jest ZLA!\n", rank, baseRandom, p - 1);
		}
	}
	
	MPI_Finalize();

}