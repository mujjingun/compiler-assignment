
int function(void)
{
    /* variable undeclared */
    a = a + 1;
    if(a == 1)
    {
        int c;
        c = 2;
    }
    /* illegal scope variable */
    return c; 
}

void main( void )
{
    function();
/* unknown function error */
    gcd();
}
