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
	
	int size;															// Rozmiar macierzy
	sscanf(argv[1], "%d", &size); 
	
	int *matrixFull;
	int *matrixPiece = malloc((size*(size/p)) * sizeof *matrixPiece);	// Fragment macierzy
	int *vector = malloc(size * sizeof *vector);						// Wektor
	int *partialResult = malloc((size/p) * sizeof *partialResult);		// Wynik pojedyńczego procesu
	int *fullResult = malloc(size * sizeof *fullResult);				// Pełen wynik
	int i;
	int j;
	int k;
	
	
	// Generowanie liczb dla macierzy i wektora
	if(rank == 0) {
		matrixFull = malloc((size*size) * sizeof *matrixFull);
		for(i = 0; i < size * size; i++) {
			matrixFull[i] = rand() % 100;
		}
		for(i = 0; i < size; i++) {
			vector[i] = rand() % 100;
			
		}
		clock_gettime(CLOCK_REALTIME, &t1);	// Gdy mamy już przykładowe dane, zaczynamy pomiar czasu
	}
	
	MPI_Bcast(vector, size, MPI_INT, 0, MPI_COMM_WORLD); // Rozsyłamy wektor do wszystkich procesów
	
	MPI_Scatter(matrixFull, size*(size/p), 
		MPI_INT, matrixPiece, size*(size/p), MPI_INT, 0, MPI_COMM_WORLD); // Przesyłamy każdemu procesowi porcję danych
	
	k = 1;
	for(i = 0; i < (size*(size/p)); i = i + size) {	// Standardowy algorytm mnożenia macierzy
		partialResult[k - 1] = 0;
		for(j = i; j < size * k; j++) {
			partialResult[k - 1] += matrixPiece[j] * vector[j % size];
		}
		k++;
	}
	
	
	MPI_Gather(partialResult, size/p, MPI_INT, fullResult, size/p, MPI_INT, 0, MPI_COMM_WORLD);	// Zbieram wyniki
	
	MPI_Barrier(MPI_COMM_WORLD);
	
	if(rank == 0) {
		// Wydruk kontrolny
		// for(i = 0; i < size; i++) {
			// printf("--------\n%i\n", fullResult[i]);	
		// }
		// printf("\n\n");

		clock_gettime(CLOCK_REALTIME, &t2);		// Drukowanie czasu działania
		unsigned long nansec = t2.tv_nsec - t1.tv_nsec;
		printf("Czas wykonania: %ld\n", nansec);
	}
	
	
	MPI_Finalize();

}