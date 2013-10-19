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
	int number;
	int nthreads;
	nthreads = omp_get_num_threads();
    int i;
	double tab[10000];
	
	srand(time(NULL));
	tid = omp_get_thread_num();
		
	#pragma omp parallel shared(nthreads) private(tid)
	{
		int chunkSize = (int) 10000/nthreads;
		
		
		
		#pragma omp parallel for shared(tid, tab) private(chunkSize, nthreads, i)
		for (i = tid*chunkSize; i < (tid*chunkSize + chunkSize); i++) {
			// tab[i] = sin(i*3.14/180.0);
			tab[i] = i;
		}
	
		#pragma omp single
		{
			for(i = 0; i < 10000; i++) {
				printf("%lf\n", tab[i]);
			}
		}
	}
	
		
    
    return 0;
}