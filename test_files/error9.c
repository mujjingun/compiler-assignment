
int f1(void)
{
    int a;
    return a; 
}

int f2(void)
{
    int a;
    return f1(a); 
}

int f3(void)
{
    int a;
    /* return type mismatch */
    return f2; 
}

int f3(int a[])
{
    /* return type mismatch */
    return a; 
}

int f4(void)
{
    int arr[];
    /* return type mismatch */
    return arr; 
}

void f5(void)
{
}

int f6(void)
{
    /* return type mismatch */
    return f6();
}

void f5(void)
{
    /* illegal return statement */
    return ;
}

void f5(void)
{
    int a;
    /* illegal return of non-void element */
    return a;
}

void main(void)
{
}
