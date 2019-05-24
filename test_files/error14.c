
int arr[100];

void function1(void)
{
    
}

int function2(void)
{
    
}

void main(void)
{
    int a = 1; 
    int b = 10; 
    int c; 


    c = a + b; 

    c = function2() + b; 

    /* type mismatch */
    c = function1() + b; 

    c = arr[a] + b; 

    /* type mismatch */
    c = arr + b; 


    c = a - b; 

    c = function2() - b; 

    /* type mismatch */
    c = function1() - b; 

    c = arr[a] - b; 

    /* type mismatch */
    c = arr / b; 

    c = a / b; 

    c = function2() / b; 

    /* type mismatch */
    c = function1() / b; 

    c = arr[a] / b; 

    /* type mismatch */
    c = arr / b; 

    /* type mismatch */
    c = arr * b; 

    c = a * b; 

    c = function2() * b; 

    /* type mismatch */
    c = function1() * b; 

    c = arr[a] * b; 

    /* type mismatch */
    c = arr * b; 


    c = a == b; 

    c = function2() == b; 

    /* type mismatch */
    c = function1() == b; 

    c = arr[a] == b; 

    /* type mismatch */
    c = arr == b; 

    c = a != b; 

    c = function2() != b; 

    /* type mismatch */
    c = function1() != b; 

    c = arr[a] != b; 

    /* type mismatch */
    c = arr != b; 

    c = a > b; 

    c = function2() > b; 

    /* type mismatch */
    c = function1() > b; 

    c = arr[a] > b; 

    /* type mismatch */
    c = arr > b; 

    c = a >= b; 

    c = function2() >= b; 

    /* type mismatch */
    c = function1() >= b; 

    c = arr[a] >= b; 

    /* type mismatch */
    c = arr >= b; 

    c = a < b; 

    c = function2() < b; 

    /* type mismatch */
    c = function1() < b; 

    c = arr[a] < b; 

    /* type mismatch */
    c = arr <= b; 

    c = a <= b; 

    c = function2() <= b; 

    /* type mismatch */
    c = function1() <= b; 

    c = arr[a] <= b; 

    /* type mismatch */
    c = arr <= b; 
}
