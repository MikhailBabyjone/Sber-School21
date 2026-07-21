#include <stdio.h>

int main(void){
    int a, b, input;
    input = scanf("%d %d",&a,&b);
    if (input != 2){
        printf("n/a");
        return 0;
    }
if (b==0){
    printf("%d %d %d n/a", a+b, a-b, a*b);
    return 0;
}
else {
    printf("%d %d %d %d", a+b, a-b, a*b, a/b);
return 0;}
}