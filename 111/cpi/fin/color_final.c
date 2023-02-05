#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int sz(int **a)
{ // compute the size of a region
  int ctr=0;
  while (*a != NULL) ctr++, a++;
  return ctr;
}

void bsort(int **reg[], int n, int c[])
{
  for (int i=0; i<n-1; i++)
    for (int j=0; j<n-1-i; j++)
      if (sz(reg[j])<sz(reg[j+1])) {
        int **tmp=reg[j]; // swap region
        reg[j]=reg[j+1];
        reg[j+1]=tmp;
        int tmpc=c[j]; // swap color
        c[j]=c[j+1];
        c[j+1]=tmpc;
      }
  return;
}


void color_array(int **reg[], int n, int c[])
{
  bsort(reg, n, c);
  for (int i=0; i<n; i++) 
    for (int j=0; reg[i][j]!=NULL; j++)
      *reg[i][j]=c[i];
  return;
}

/*
// sample main
int main()
{
	int R=5, C=4;
	int arr[R][C];
	memset(arr, -1, R*C*sizeof(int));
	
	int *r[2][5] = {{&arr[2][0], &arr[2][1], &arr[2][2], NULL},
	                {&arr[1][2], &arr[2][2], &arr[3][2], &arr[4][2], NULL}};
	
	int **reg[2] = {r[0], r[1]};
	int c[2] = {1, 2};
	
	color_array(reg, 2, c);
	
	for(int i=0; i<R; i++){
		for (int j=0; j<C; j++)
			printf("%d ", arr[i][j]);
		printf("\n");
	}
	
	return 0;
}
*/
