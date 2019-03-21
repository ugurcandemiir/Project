#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {
	if (argc<2) {
		fprintf(stderr,"Error... invoke as %s <n>\n",argv[0]);
	}
	int n=atoi(argv[1]);
	if (n<=0) {
		fprintf(stderr,"Error... invoke as %s <n>\n",argv[0]);
	}
	time_t t;
	srand(time(&t)); // Seed random number generator
	for(int i=0;i<n;i++) {
		int v=(rand()%2002)-1001;
		printf("%d\n",v);
	}
	return 0;
}