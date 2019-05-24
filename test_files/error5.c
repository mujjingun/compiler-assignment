
int a[100];

void gcd(void)
{}

void function(int arr[])
{
    /* illegal array subscript type for array */
    arr[gcd];
    /* illegal array subscript type for array */
    arr[a];
}

void main( void )
{
    int arr[10];

    /* illegal array subscript type for array */
    arr[gcd];
    /* illegal array subscript type for array */
    arr[a];

    if(arr[0])
    {
        /* illegal array subscript type for array level 2 */
        arr[gcd];
        /* illegal array subscript type for array level 2 */
        arr[a];
    }
}
