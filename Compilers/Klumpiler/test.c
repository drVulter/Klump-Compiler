#include<stdio.h>

float func(void);

int main(void)
{
    float f = func();
    printf("%f", f);
    return 0;
}

float func(void)
{
    return 2;
}
