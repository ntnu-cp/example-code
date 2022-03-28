// by hlwang
// Recursively generate all permutations of {1, ..., n}
// Note: not in lexicographic order


#include <stdio.h>
#define N 15

void print_permutation(int n, int p[])
{
  for (int i=0; i<n; i++) printf("%d ", p[i]); printf("\n");
  return;
}

void swap(int p[], int i, int j)
{
  int tmp = p[i]; 
  p[i] = p[j];
  p[j] = tmp;
  return;
}

void permute(int n, int p[], int k)
{
  // the first k elements are fixed
  // permute the remaining n-k elements

  // terminal condition
  if (k==n) {
    print_permutation(n, p);
    return;
  }

  // recursive formula
  for (int i=k; i<n; i++) {
    swap(p, k, i);
    permute(n, p, k+1);
    swap(p, k, i);
  }
  return;
}
