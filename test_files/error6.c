
int arr;

void main(void)
{
    int a = 1;

    /* array subscript illegal for scalar type */
    a[1];

    /* array subscript illegal for scalar type */
    arr[1];

    if(a == 1)
    {
        int b;

        /* array subscript illegal for scalar type */
        a[2];

        /* array subscript illegal for scalar type */
        b[0];

        /* array subscript illegal for scalar type */
        arr[100];

        while(a)
        {
            int c;

            /* array subscript illegal for scalar type */
            a[2];

            /* array subscript illegal for scalar type */
            b[10];

            /* array subscript illegal for scalar type */
            c[100];
        }
    }
}
