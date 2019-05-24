
int fone(void)
{
    int a;
    return a; 
}

int ftwo(void)
{
    int a;
    return f1(a); 
}

int fthree(void)
{
    int a;
    /* return type mismatch */
    return f2; 
}

int ffour(int a[])
{
    /* return type mismatch */
    return a; 
}

int ffive(void)
{
    int arr[];
    /* return type mismatch */
    return arr; 
}

void fsix(void)
{
}

int fseven(void)
{
    /* return type mismatch */
    return f6();
}

void feight(void)
{
    /* illegal return statement */
    return ;
}

void fnine(void)
{
    int a;
    /* illegal return of non-void element */
    return a;
}

void main(void)
{
}
