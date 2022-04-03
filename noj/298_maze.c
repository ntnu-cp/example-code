// Problem link: https://noj.tw/problem/298

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
//#include "collect.h"
#define UP '^'
#define DOWN 'v'
#define LEFT '<'
#define RIGHT '>'
#define N 50

int in_my_maze(int r, int c, int m, int n)
{
    return (0 <= r && r < m && 0 <= c && c < n);
}

void find_max_and_mouse(char maze[][N], int m, int n, int *sr, int *sc, char *k)
{
    *k = '0';
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
        {
            if (maze[i][j] == '@')
            {
                *sr = i;
                *sc = j;
            }
            if ('0' <= maze[i][j] && maze[i][j] <= '9')
                *k = (maze[i][j] > *k) ? maze[i][j] : *k;
        }
    return;
}

int go(char maze[][N], int m, int n, int r, int c, char x, char k)
{
    // currently at maze[r][c]
    // to collect "x"
    // return value: 0 not a feasible route; 1 otherwise

    // terminal condition
    if (maze[r][c] == k)
        return 1;

    // recursive formula
    // mark the current step
    // find the next step (check feasiblity)

    int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};
    char dir[4] = {UP, DOWN, LEFT, RIGHT};

    // try next step in 4 different directions

    if (maze[r][c] == x)
        x++;

    for (int i = 0; i < 4; i++)
    {
        int nr = r + dr[i], nc = c + dc[i];

        // check if maze[nr][nc] is feasible or not
        if (in_my_maze(nr, nc, m, n) == 0)
            continue;
        if (maze[nr][nc] != '.' && maze[nr][nc] != x)
            continue;

        // if feasible, mark maze[r][c] by the direction to proceed
        char tmp = maze[r][c];
        maze[r][c] = dir[i];
        if (go(maze, m, n, nr, nc, x, k) == 1)
            return 1;
        // change the mark back
        maze[r][c] = tmp;
    }
    return 0;
}

int collect(char maze[][N], int m, int n)
{
    // find the mouse's position
    // find the max number
    int sr, sc;
    char k;
    find_max_and_mouse(maze, m, n, &sr, &sc, &k);

    printf("mouse at [%d][%d]\n, k=%c\n", sr, sc, k);
    // go maze
    go(maze, m, n, sr, sc, '0', k);

    return 1;
}

// main() for user test
int main()
{
    int m, n;
    scanf("%d %d", &m, &n);

    char maze[N][N];
    fgets(maze[0], N, stdin);
    for (int i = 0; i < m; i++)
        fgets(maze[i], N, stdin);

    printf("Initial maze:\n");
    for (int i = 0; i < m; i++)
    {
        printf("%s", maze[i]);
    }

    collect(maze, m, n);

    printf("\nResult:\n");
    for (int i = 0; i < m; i++)
    {
        printf("%s", maze[i]);
    }

    return 0;
}
