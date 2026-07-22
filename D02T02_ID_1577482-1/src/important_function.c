#include <math.h>
#include <stdio.h>

int main(void){
    double x;
    double y;
    int input;
    input = scanf("%lf", &x);
    if (input!=1){
        printf("n/a");
        return 0;

    }
    y = 7e-3 * pow(x,4) + 
        ((22.8 * pow(x,(1.0/3.0)) - 1e3) * x + 3) / (pow(x,2)/ 2) - x * pow((10 + x),(2/x)) - 1.01;
     printf("%.1f", y);
}