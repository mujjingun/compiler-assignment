
void functionone(int arr[])
{
    arr[1];
}

void functiontwo(int arr)
{
}

void main( void )
{
    int arrone;
    int arrtwo[10];

    /* argument type mismatch. Expected array */
    functionone(arrone);

    /* argument type mismatch. Expected scalar */
    functiontwo(arrtwo);
}
