#include <stdio.h>
#define N 101

void put(int a[], int n, int mat[][N], int r, int c)
{
  int k=0;
  for (int i=0; i<r; i++) for (int j=0; j<c; j++)
    mat[i][j]=a[k++];
  return;
}

int feasible(int nr, int nc, int mat[][N], int r, int c)
{
  int yes=1;
  if (nr<0 || nr>=r) yes=0;
  if (nc<0 || nc>=c) yes=0;
  if (yes!=0 && mat[nr][nc]==-1) yes=0;
  return yes;
}

void traverse(int mat[][N], int r, int c, int dir, int a[])
{
  int cr=0, cc=0, k=0;
  int dr[4] = {0, 1, 0, -1};
  int dc[4] = {1, 0, -1, 0};
  int d = (dir==0)? 0: 1;
  for (int i=0; i<r*c; i++) {
    a[k++]=mat[cr][cc];
    mat[cr][cc]=-1;
    int nr = cr+dr[d], nc=cc+dc[d]; 
    if (feasible(nr, nc, mat, r, c))
      cr=nr, cc=nc;
    else {
      d = (d+1-2*dir+4)%4;
      cr += dr[d], cc += dc[d];
    }
  }
  return;
}

int main()
{
  int n,k, a[N], mat[N][N];
  scanf("%d%d", &n, &k);

  for (int i=0; i<n; i++)
    scanf("%d", &a[i]);

  for (int i=0; i<k; i++) {
    int r, c, dir;
    scanf("%d%d%d", &r, &c, &dir);
    put(a, n, mat, r, c);     // put the integers into an rxc array (mat)
    traverse(mat, r, c, dir, a);  // traverse mat with the requested order
  }

  for (int i=0; i<n; i++)
    printf("%d ", a[i]);
  printf("\n");

  return 0;
}
