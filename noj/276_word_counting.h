// Problem link: https://noj.tw/problem/276

#include <ctype.h>
#include <string.h>
#include <stdio.h>

void bsort(char w[][101], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            // compare w[j] w[j+1], swap if w[j]>w[j+1]
            if (strcmp(w[j], w[j + 1]) > 0)
            {
                char tmp[101] = {};
                strcpy(tmp, w[j]);
                strcpy(w[j], w[j + 1]);
                strcpy(w[j + 1], tmp);
            }
        }
    }
    return;
}

void count_print(char w[][101], int n)
{
    int ctr = 0;
    char current[101] = {};
    strcpy(current, w[0]);

    for (int i = 0; i < n; i++)
    {
        if (strcmp(current, w[i]) == 0)
            ctr++;
        else
        {
            if (current[0] != '\0')
                printf("%s %d\n", current, ctr);
            strcpy(current, w[i]);
            ctr = 1;
        }
    }
    printf("%s %d\n", current, ctr);
    return;
}

void count_word(char *s)
{
    // find the words, words[0], words[1], ...
    char words[1001][101] = {};

    // w[0]: h e l l o ',': r++, c=0
    // w[1]: ...
    int r = 0, c = 0;
    while (*s != '\0')
    {
        if (ispunct(*s) || isspace(*s))
        {
            r++;
            c = 0;
        }
        else
        {
            words[r][c] = *s;
            c++;
        }
        s++;
    }
    /*
      printf("r=%d\n", r);
      for (int i=0; i<r+1; i++)
        printf("w[%d]: %s\n", i, words[i]);
     */
    // sort the words
    bsort(words, r + 1);

    // count
    count_print(words, r + 1);
    return;
}
