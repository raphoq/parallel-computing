#include <stdio.h>
#include "mpi.h"

main(int argc, char **argv)
{
	int np, rank;
	//MPI_Status status;
	
	MPI_Init(&argc, &argv);
	//Pobranie aktualnego numeru procesu
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	
	printf("Jestem proces %d na %d \n", rank, np);
	
	MPI_Finalize();
	
	// Kompilacja mpicc prog.c
	// mpirun -np 4 a.out
}