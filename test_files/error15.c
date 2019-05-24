
void main(void)
{
    int a;
    int b;
    int c;

    a = b + c;
    if(a)
    {
        int d;
        a = d + c; 
        d = a + c; 
    }

    if(b)
    {
        int d[100];
        /* illegal type for operation */
        a = d + c; 
        d = a + c; 
    }

    if(c)
    {
        int d[100];
        a = ((a + c) + (b + c)); 

        /* illegal assigned type  */
        d = ((a + c) + (b + c)); 

        /* illegal assigned type  */
        d = ((a + c) + (b + c)); 

        d[100] = ((a + c) + (b + c)); 

        /* illegal assigned type  */
        d[100] = ((a + c) + (b + c)) + d; 
    }
}
