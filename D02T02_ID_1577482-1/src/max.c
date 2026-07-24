#include <stdio.h>
    int max (int a, int b);
int main(void) {
    int a, b;
    int input;
    input = scanf("%d %d", &a, &b);
    if (input != 2){
        printf("n/a");
        return 0;
    }
    printf("%d", max(a,b));
    return 0;} 
int max(int a, int b) {
    if (a>b) {return a;}
    else if (b>a) {return b;}
    else {return a;}

}
  