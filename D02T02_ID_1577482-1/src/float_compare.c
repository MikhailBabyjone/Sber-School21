#include <stdio.h>
#include <math.h>
 
double fun();
 
int main() {
    double res = fun();
  
    
    if (fabs(res)<1e-6)
       printf("OK!");
 
    return 0;
}
 

double fun() {
    return (1.0 / 13) * (pow(((2 - 1.0) / (2 + 1.0)), 20));
}
 

