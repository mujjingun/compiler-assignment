
void main()
{
    int a = 1;
    int b = 1;
    int c = 1;

    a = b + c;
    if(a)
    {
        int d = 1;
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
