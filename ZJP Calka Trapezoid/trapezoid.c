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
	
	int n;
	sscanf(argv[1], "%d", &n); 
	
	double a = -2.0;
	double b = 2.0;
	double xPerProcesor = n / p;
	
	double h = (b - a) / (double) n;
	double e = exp(1);
	
	double localX = -2.0;
	double startRange;
	
	double finalArea = 0.0;
	double singleArea = 0.0;
	
	double fx(double x) {
		return 1/pow(e, pow(x, 2));
	}
	
	MPI_Barrier(MPI_COMM_WORLD);
	
	if(rank == 0) {
		clock_gettime(CLOCK_REALTIME, &t1);
	}
	
	localX += rank*(xPerProcesor * h);
	startRange = localX;
	
	for(localX = localX; localX < (startRange + xPerProcesor*h); localX += h) {
		singleArea += (h*(fx(localX) + fx(localX + h)))/2.0;
	}
	
	MPI_Reduce(&singleArea, &finalArea, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	
	MPI_Barrier(MPI_COMM_WORLD);
	
	if(rank == 0) {
		printf("Wartość całki to: %1.20lf\n", finalArea);
		clock_gettime(CLOCK_REALTIME, &t2);		// Drukowanie czasu działania
		unsigned long nansec = t2.tv_nsec - t1.tv_nsec;
		printf("Czas wykonania: %ld\n", nansec);
	}
	
	MPI_Finalize();

}