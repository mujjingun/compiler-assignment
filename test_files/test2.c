int glo;

void main(void) {
    int locA;
    {
        int locB;
        locA = 1 + 2;
        glo = locB;
    }
    output(locA);
}
