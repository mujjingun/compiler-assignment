int fact(int a) {
    if (a == 1) return 1;
    else return a * fact(a - 1);
}

void main(void) {
    output(fact(5)); /* 120 */
}
