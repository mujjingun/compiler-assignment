
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
    int localone;

    /* duplicated declaration of local variable */
    int localone;

    if(localone == localone)
    {
        /* duplicated declaration of local variable across scopes */
        int localone;

        int localtwo;
        /* duplicated declaration of local variable level 2 */
        int localtwo;

        while(localone)
        {
            /* duplicated declaration of local variable across two scopes */
            int localone;

            /* duplicated declaration of local variable across three scopes */
            int localtwo;

            int localthree;
            /* duplicated declaration of local variable level 2 */
            int localthree;
        }
    }
}
