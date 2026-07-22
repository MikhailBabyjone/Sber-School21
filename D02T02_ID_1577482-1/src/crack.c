#include <stdio.h>

int main(void){
    double x, y;
    int input;
    input = scanf("%lf %lf", &x, &y);
    if (input != 2){
        printf("n/a");
        return 0;
    }
    if (((x*x) + (y*y))<25) {
        printf("GOTCHA");
        return 0;
    }
    else {
        printf("MISS");
        return 0;
    }

}