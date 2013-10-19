// Kompilacja 
// gcc -fopenmp pierwszy.c -o pierwszy
//
// Uruchamianie na 5 watkach
// env OMP_NUM_THREADS=5 ./pierwszy
//
#include <omp.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main()
{

	int	tid;
	int *tab;
	int number;
	int nthreads;
    
    #pragma omp parallel private(tid, number) shared(tab)
    {
		srand(time(NULL));
		nthreads = omp_get_num_threads();
		tab = malloc(nthreads * sizeof *tab);
		tid = omp_get_thread_num();
		number = ((int) rand()) % 10;
		// printf("Process %i get %i\n", tid, number);
		tab[tid] = number;
		
		#pragma omp barrier
		
		#pragma omp single
		{
			int i;
			for(i = 0; i < nthreads; i++) {
				printf("%i\n", tab[i]);
			}
		}
    
    }
    
    return 0;
}