
int global;
void gcd(void)
{}

/* duplicated declaration of global variable */
int global;

/* duplicated declaration of function */
void gcd(void)
{}

void main( void )
{
    int local1 = 1;

    /* duplicated declaration of local variable */
    int local1 = 1;

    if(local1 == local1)
    {
        /* duplicated declaration of local variable across scopes */
        int local1;

        int local2 = 0;
        /* duplicated declaration of local variable level 2 */
        int local2 = 0;

        while(local1)
        {
            /* duplicated declaration of local variable across two scopes */
            int local1 = 0;

            /* duplicated declaration of local variable across three scopes */
            int local2 = 0;

            int local3 = 0;
            /* duplicated declaration of local variable level 2 */
            int local3 = 0;
        }
    }
}
