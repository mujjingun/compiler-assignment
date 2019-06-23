int garr[10];

void modify(int arr[]) {
    output(arr[5]);
    arr[5] = 123123;
    output(arr[5]);
}

void main(void) {
    int larr[10];

    garr[5] = 7;
    output(garr[5]);
    modify(garr);
    output(garr[5]);

    larr[5] = 7;
    output(larr[5]);
    modify(larr);
    output(larr[5]);
}

/* 7 7 123123 123123 */
/* 7 7 123123 123123 */
