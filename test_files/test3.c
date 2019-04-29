/* Selection Sort code(ascending order) in C- grammer */

void SelectionSort(int a[], int n)
{
    int i = 0, j, k, t;
    for(i = 0; i < n; i++){
        j = i;
        for(k = i+1; k<n; k++){
            if (a[k] < a[j]) j=k;
        }
            
            t = a[i];
            a[i] = a[j];
            a[j] = t;
    }
}

int main(){
    int n = 5;
    int a[5] = {5, 4, 3, 2, 1};
    
    SelectionSort(a, n);
        
    return 0;
}
