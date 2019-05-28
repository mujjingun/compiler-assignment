 int a;
 int func(void) {
     a = 10;
     return a;
 }
 void main(void) {
     a = func() + 1;
     a;
 }
