#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "packInt.h"
#define MAXNUMS 4096

int main(int argc, char **argv) {
	if (argc<2) {
		printf("Invoke as %s <filename>\n",argv[0]);
		return 1;
	}
	int checkArray[MAXNUMS];
	long store[1+MAXNUMS/2]={0};
	int n=0; int val;
	FILE *DBG=fopen(argv[1],"r");
	while(1==fscanf(DBG,"%d ",&val)) {
		checkArray[n]=val;
		n++;
		putInt(val,store);
	}
	fclose(DBG);
	int nu=storeUsed(store);
	for(int i=0;i<n;i++) {
		int v=getInt(store);
		if (v!=checkArray[i]) {
			printf("checkArray[%d]=%d != getInt(store)=%d\n",
				i,checkArray[i],v);
			exit(1);
		}
		// assert(checkArray[i]==getInt(store));
	}
	printf("Stored %d integers using %d store entries for a score of %.3f\n",n,nu,(float)n/nu);
	return 0;
}