
void function1(int arr[])
{
    arr[1];
}

void function2(int arr)
{
}

void main( void )
{
    int arr1;
    int arr2[10];

    /* argument type mismatch. Expected array */
    function1(arr1);

    /* argument type mismatch. Expected scalar */
    function2(arr2);
}
