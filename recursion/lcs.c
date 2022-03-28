// by hlwang
// find "an" lcs of two strings recursively.

#include <stdio.h>
#include <string.h>

#define N 20 // upper bound on the lengths of the input strings

int lcs(char s[], char t[], int ls, int lt, char ans[], int pos)
{
    // terminal condition
    if (ls == 0 || lt == 0)
        return 0;

    // recursive formula
    if (s[0] == t[0])
    {
        ans[pos] = s[0];
        return 1 + lcs(s + 1, t + 1, ls - 1, lt - 1, ans, pos + 1);
    }
    else
    {
        char tmp1[N] = {}, tmp2[N] = {};
        strcpy(tmp1, ans);
        strcpy(tmp2, ans);

        int l1 = lcs(s + 1, t, ls - 1, lt, tmp1, pos);
        int l2 = lcs(s, t + 1, ls, lt - 1, tmp2, pos);

        if (l1 > l2)
        {
            strcpy(ans, tmp1);
            return l1;
        }
        else
        {
            strcpy(ans, tmp2);
            return l2;
        }
    }
}

int main()
{
    char s[N] = {}, t[N] = {};

    scanf("%s%s", s, t);

    char ans[N] = {};
    int ls = strlen(s), lt = strlen(t);

    printf("length: %d\n", lcs(s, t, ls, lt, ans, 0));
    printf("lcs: %s\n", ans);

    return 0;
}
