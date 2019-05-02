/* a program to perform Euclid's
   Algorithm to compute gcd. */

int x[20];
int y[123];

int gcd(int u[], int v)
{
    if (v == 0) return u;
    else return gcd(v, u - u / v * v);
    /* u - u/v * v == u mod v */
}

void main( void )
{
    int x; int y;
    x[1] = 2;
    x = input(); y = input();
    output(gcd(x, y));
}
