
int f1()
{
    int a;
    return a; 
}

int f2()
{
    int a;
    return f1(a); 
}

int f3()
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

int f4()
{
    int arr[];
    /* return type mismatch */
    return arr; 
}

void f5()
{
}

int f6()
{
    /* return type mismatch */
    return f6();
}

void f5()
{
    /* illegal return statement */
    return ;
}

void f5()
{
    int a;
    /* illegal return of non-void element */
    return a;
}

void main()
{
}
