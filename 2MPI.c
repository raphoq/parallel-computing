#include <stdio.h>
#include <string.h>
#include "mpi.h"

main(int argc, char **argv)
{
	int myRank,
		p,
		source,
		dest,
		tag = 50;
	char message[100];
	MPI_Status status;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	
	if(myRank != 0) {
		sprintf(message, "Hello from process %d", myRank);
		dest = 0;
		MPI_Send(message, strlen(message) + 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
	} else {
		for(source = 1; source < p; source++) {
			MPI_Recv(message, 100, MPI_CHAR, source, tag, MPI_COMM_WORLD, &status);
			printf("%s\n", message);
		}
	}
	
	MPI_Finalize();
	
}