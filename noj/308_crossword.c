// Problem link: https://noj.tw/problem/349

#include <stdio.h>
#include <string.h>
#include "crossword.h"

typedef struct ind
{
    int r, c;
} IND;

int in_table(int i, int j, int r, int c)
{
    return (0 <= i && i < r && 0 <= j && j < c);
}

IND find_blank(char table[][N], int r, int c)
{
    IND ans;
    ans.r = -1;
    ans.c = -1;

    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            if (table[i][j] == BLANK)
            {
                ans.r = i;
                ans.c = j;
                return ans;
            }
    return ans;
}

char *find_word(char t[][N], int r, int c, IND pos, char w[], int d[])
{
    char *ans;
    int sr = pos.r, sc = pos.c, nr = pos.r - d[0], nc = pos.c - d[1];

    while (in_table(nr, nc, r, c) && t[nr][nc] != BLOCK)
    {
        sr = nr;
        sc = nc;
        nr -= d[0];
        nc -= d[1];
    }
    ans = &t[sr][sc];
    nr = sr;
    nc = sc;
    for (int i = 0; in_table(nr, nc, r, c) && t[nr][nc] != BLOCK; i++)
    {
        w[i] = t[nr][nc];
        nr += d[0];
        nc += d[1];
    }
    return ans;
}

void replace_word(char *pos, char w[], int dir[])
{
    int l = strlen(w);
    for (int i = 0; i < l; i++)
    {
        *pos = w[i];
        pos += N * dir[0] + dir[1];
    }
    return;
}

int match(char a[], char b[])
{
    int la = strlen(a), lb = strlen(b);
    if (la != lb)
        return 0;

    for (int i = 0; i < la; i++)
    {
        if (a[i] == BLANK || b[i] == BLANK || a[i] == b[i])
            continue;
        return 0;
    }
    return 1;
}

int fill(char t[][N], int r, int c, char dict[][N], int dict_len, int used[])
{
    IND blank_pos = find_blank(t, r, c);
    // terminal condition
    if (blank_pos.r == -1)
        return 1;

    // recursive formula
    int d[2][2] = {{1, 0}, {0, 1}};

    for (int i = 0; i < 2; i++)
    {
        char w[N] = {}, *cptr;
        cptr = find_word(t, r, c, blank_pos, w, d[i]);

        for (int j = 0; j < dict_len; j++)
        {
            if (match(dict[j], w))
            {
                replace_word(cptr, dict[j], d[i]);
                used[j] = 1;
                if (fill(t, r, c, dict, dict_len, used))
                    return 1;
                replace_word(cptr, w, d[i]);
                used[j] = 0;
            }
        }
    }
    return 0;
}

void crossword(char table[][N], int row, int col, char dictionary[][N], int dict_len)
{
    int used[M] = {};
    fill(table, row, col, dictionary, dict_len, used);
    return;
}