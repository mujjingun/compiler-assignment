
int glob;

void function(int a, int b, int c)
{
    int d[100];
    function(a, b, glob);

    /* argument type mismatch. */
    function(a, b, function);

    /* argument number mismatch */
    function(a, b);

    /* argument number mismatch */
    function(a, b, c, d, a);
}

void main(void)
{
    int a;
    int b;
    function(a, b, glob);
}
