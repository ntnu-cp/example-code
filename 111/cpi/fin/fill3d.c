#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mymin(int a, int b, int c)
{
  int ans = (a<b)?a:b;
  return (c<ans)?c:ans;
}

int mymax(int a, int b, int c)
{
  int ans = (a>b)?a:b;
  return (c>ans)?c:ans;
}

int in_range(int l, int r, int c, int ls, int rs, int cs, int le, int re, int ce)
{
  int is_in=1;
  if (l<ls || l>le) is_in=0;
  if (r<rs || r>re) is_in=0;
  if (c<cs || c>ce) is_in=0;
  return is_in;
}

void fill_3d(int* ptr1, int x1, int x2, int x3,
              int* ptr2, int y1, int y2, int y3,
			  int* ptr3, int z1, int z2, int z3)
{
  int R, C; 
  int a[4] = {y1-x1, y2-x2, y3-x3, ptr2-ptr1}; 
  int b[4] = {z1-y1, z2-y2, z3-y3, ptr3-ptr2};

  int min_l=mymin(x1,y1,z1), max_l=mymax(x1,y1,z1);
  int min_r=mymin(x2,y2,z2), max_r=mymax(x2,y2,z2);
  int min_c=mymin(x3,y3,z3), max_c=mymax(x3,y3,z3);

  if (a[0]==0 && a[1]==0)
    a[0]=x1-z1, a[1]=x2-z2, a[2]=x3-z3, a[3]=ptr1-ptr3;
  if (a[0]*b[1]==a[1]*b[0])
    b[0]=x1-z1, b[1]=x2-z2, b[2]=x3-z3, b[3]=ptr1-ptr3;

  if (a[0]*b[1]==a[1]*b[0]) { 
    // 2D case: all elements in the same layer, i.e. x1=y1=z1
    // Note: This part (lines 45-58) is not necessary
    C = (b[3]-a[3]-b[2]+a[2])/(b[1]-a[1]);
    int *start = ptr1 + ((min_r-x2)*C + (min_c-x3)); 
    int *end = ptr1 + ((max_r-x2)*C + (max_c-x3)); 

    for (int *p=start; p<=end; p++) {
      int dist = (p-ptr1)+(x2*C+x3);
      int r= dist/C;
      int c= dist%C;
      if (in_range(x1,r,c,min_l,min_r,min_c,max_l,max_r,max_c))
        *p=1;
    }
    return;
  }

  // 3D case
  C = (a[0]*b[3]-a[3]*b[0]-a[0]*b[2]+a[2]*b[0])/ (a[0]*b[1]-a[1]*b[0]);
  if (a[0]==0) 
    R = (b[3]-b[2]-b[1]*C)/(b[0]*C);
  else 
    R = (a[3]-a[2]-a[1]*C)/(a[0]*C);

  int *start = ptr1 + ((min_l-x1)*R*C + (min_r-x2)*C + (min_c-x3)); 
  int *end = ptr1 + ((max_l-x1)*R*C + (max_r-x2)*C + (max_c-x3)); 

  for (int *p=start; p<=end; p++) {
    int dist = (p-ptr1)+(x1*R*C+x2*C+x3);
    int l=dist/(R*C);
    int r= (dist%(R*C))/C;
    int c= (dist%(R*C))%C;
    if (in_range(l,r,c,min_l,min_r,min_c,max_l,max_r,max_c))
      *p=1;
  }
  return;
}

/*  
// sample main
int main(){
	int x1, x2, x3, y1, y2, y3, z1, z2, z3;
	scanf("%d%d%d%d%d%d%d%d%d", &x1, &x2, &x3, &y1, &y2, &y3, &z1, &z2, &z3);
	
    // init 3d array & set array to zeros
	int r = 5, c = 5, l=5;
	int arr[l][r][c];
	memset(arr, 0, l*r*c*sizeof(int));
	
	fill_3d(&arr[x1][x2][x3], x1, x2, x3,
			&arr[y1][y2][y3], y1, y2, y3,
			&arr[z1][z2][z3], z1, z2, z3);
	
	// output XY
	for(int k=0; k<l; k++) {
		for(int i=0; i<r; i++) {
            for(int j=0; j<c; j++){
			    printf("%d", arr[k][i][j]);
            }
		    printf("\n");
		}
        printf("\n");
	}
	
	return 0;
}
*/
