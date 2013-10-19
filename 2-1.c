/* RAFAŁ ŁUCZUN */

#include <stdio.h>
#include <math.h>
#include "mpi.h"

void numbersRange(int itemsCount, int parts) {
	
}


main(int argc, char **argv)
{
	int rank,
		p,
		source,
		dest,
		numbersCount = 1000;
		
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	
	int parts = p,
		collection[p][2],
		start = 1,
		stop,
		i,
		j = 0,
		k,
		result;
	double items;
	
	for(i = parts; i > 0; i--) {
		items = round(numbersCount / i);	// Jedna z części zaokrąglona
		stop = start + items - 1;			// Końcowy element to pierwszy plus ilość
		collection[j][0] = start;
		collection[j][1] = stop;
		start += items;						// Ustawiam początek kolejnego zakresu
		numbersCount -= items;				// Zmniejszanie liczby elementów o powyższy zakres
		j++;
	}
	
	int singleResult = 0;
	
	for(k = 0; k < p; k++) {
		if(rank == k) {
			int n = collection[k][1] - collection[k][0] + 1;
			
			singleResult = ((collection[k][0] + collection[k][1]) * n) / 2;
			
			printf("Proces nr. %i :: Suma przedziału [%i, %i] :: %i\n", k, collection[k][0], collection[k][1], singleResult);
		}
	}
			
	MPI_Reduce(&singleResult, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	
	if(rank == 0) {
		printf("Suma: %i\n", result);
	}
	
	MPI_Finalize();

}