/* A program to perform selection sort on a 10element array. */

int x[10];

/* A
 * Multiline
 * Comment
 *
 */
int minloc(int a[], int low, int high)
{
    int i;
    int x;
    int k;
    k = low;
    x = a[low];
    i = low + 1;
    while (i < high) {
        if (a[i] < x) {
            x = a[i];
            k = i;
        }
        i = i + 1;
    }
    return k;
}
/* *********/
