
int fone(void)
{
    int a;
    return a; 
}

int ftwo(void)
{
    return fone(); 
}

int fthree(void)
{
    int a;
    /* return type mismatch */
    return ftwo; 
}

int ffour(int a[])
{
    /* return type mismatch */
    return a; 
}

int ffive(void)
{
    int arr[10];
    /* return type mismatch */
    return arr; 
}

void fsix(void)
{
}

int fseven(void)
{
    /* return type mismatch */
    return fsix();
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
