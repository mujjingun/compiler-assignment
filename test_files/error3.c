
/* illegal global variable type */
void global;

void main( void )
{
/* illegal local variable type */
    void local1 = 1;

    if(local1 == local1)
    {
/* illegal local variable type level 2 */
        void local2 = 0;
    }
}
