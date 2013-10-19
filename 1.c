#include <stdio.h>

main ()
{
	int idChild[3];
	int pids[4];
	idChild[0] = fork();
	
	
	if (idChild[0] == 0) {
		printf("Proces nr. 2 | ID : %d\n", getpid());
		pids[1] = getpid();
		idChild[1] = fork();
		if (idChild[1] == 0) {
			printf("Proces nr. 3 | ID : %d\n", getpid());
			pids[2] = getpid();
			idChild[2] = fork();
			if (idChild[2] == 0) {
				printf("Proces nr. 4 | ID : %d\n", getpid());
				pids[3] = getpid();
			}
		}
	} else {
		printf("Proces nr. 1 | ID : %d\n", getpid());
		pids[0] = getpid();
		waitpid(pids[3]);
	}
}