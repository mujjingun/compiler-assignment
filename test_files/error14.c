
int arr[100];

void functionone(void)
{
    
}

int functiontwo(void)
{
    
}

void main(void)
{
    int a; 
    int b; 
    int c; 

    c = a + b; 

    c = functiontwo() + b; 

    /* type mismatch */
    c = functionone() + b; 

    c = arr[a] + b; 

    /* type mismatch */
    c = arr + b; 


    c = a - b; 

    c = functiontwo() - b; 

    /* type mismatch */
    c = functionone() - b; 

    c = arr[a] - b; 

    /* type mismatch */
    c = arr / b; 

    c = a / b; 

    c = functiontwo() / b; 

    /* type mismatch */
    c = functionone() / b; 

    c = arr[a] / b; 

    /* type mismatch */
    c = arr / b; 

    /* type mismatch */
    c = arr * b; 

    c = a * b; 

    c = functiontwo() * b; 

    /* type mismatch */
    c = functionone() * b; 

    c = arr[a] * b; 

    /* type mismatch */
    c = arr * b; 


    c = a == b; 

    c = functiontwo() == b; 

    /* type mismatch */
    c = functionone() == b; 

    c = arr[a] == b; 

    /* type mismatch */
    c = arr == b; 

    c = a != b; 

    c = functiontwo() != b; 

    /* type mismatch */
    c = functionone() != b; 

    c = arr[a] != b; 

    /* type mismatch */
    c = arr != b; 

    c = a > b; 

    c = functiontwo() > b; 

    /* type mismatch */
    c = functionone() > b; 

    c = arr[a] > b; 

    /* type mismatch */
    c = arr > b; 

    c = a >= b; 

    c = functiontwo() >= b; 

    /* type mismatch */
    c = functionone() >= b; 

    c = arr[a] >= b; 

    /* type mismatch */
    c = arr >= b; 

    c = a < b; 

    c = functiontwo() < b; 

    /* type mismatch */
    c = functionone() < b; 

    c = arr[a] < b; 

    /* type mismatch */
    c = arr <= b; 

    c = a <= b; 

    c = functiontwo() <= b; 

    /* type mismatch */
    c = functionone() <= b; 

    c = arr[a] <= b; 

    /* type mismatch */
    c = arr <= b; 
}
