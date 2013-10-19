/* RAFAŁ ŁUCZUN */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

main(int argc, char **argv)
{
	srand(time(NULL));
		
	struct timespec t1, t2;
	
	int n;
	sscanf(argv[1], "%d", &n); 
	
	double a = -2.0;
	double b = 2.0;
	
	double h = (b - a) / (double) n;
	double e = exp(1);
	
	double localX;
	
	double finalArea = 0.0;
	
	double fx(double x) {
		return 1/pow(e, pow(x, 2));
	}
	
	clock_gettime(CLOCK_REALTIME, &t1);
	
	for(localX = a; localX < b; localX += h) {
		finalArea += (h*(fx(localX) + fx(localX + h)))/2.0;
	}
	
	printf("Wartość całki to: %1.20lf\n", finalArea);
	clock_gettime(CLOCK_REALTIME, &t2);		// Drukowanie czasu działania
	unsigned long nansec = t2.tv_nsec - t1.tv_nsec;
	printf("Czas wykonania: %ld\n", nansec);
	
}