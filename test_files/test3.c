int exp(int a, int b) {
    int r;
    r = 1;
    while (b > 0) {
        r = r * a;
        b = b - 1;
    }
    return r;
}

void main(void) {
    output(exp(0-2, 10)); /* 1024  */
    output(exp(0-2, 11)); /* -2048 */
    output(exp(0-2, 12)); /* 4096 */
}
