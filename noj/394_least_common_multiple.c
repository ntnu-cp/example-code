#include <stdio.h>
#define min(a, b) ((a) < (b) ? (a) : (b))

int main()
{
    int a, b, c, d;
    scanf("%d%d%d%d", &a, &b, &c, &d);

    int g = a;
    for (int i = min(g, b); i >= 1; i--)
    {
        if (g % i == 0 && b % i == 0)
        {
            g = g / i * b;
            break;
        }
    }
    for (int i = min(g, c); i >= 1; i--)
    {
        if (g % i == 0 && c % i == 0)
        {
            g = g / i * c;
            break;
        }
    }
    for (int i = min(g, d); i >= 1; i--)
    {
        if (g % i == 0 && d % i == 0)
        {
            g = g / i * d;
            break;
        }
    }

    printf("%d\n", g);

    return 0;
}
