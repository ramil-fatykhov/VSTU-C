#include <cstdio>
#include <math.h>

int main()
{
    float a = 0;
    float b = 0;
    float c = 0;
    float x = 0;
    float d = 0;
    std::puts("Please enter a,b and c for 'ax^2+bx+c=0': ");
    std::scanf("%f %f %f", &a, &b, &c);
    d = sqrt(b * b - 4 * a * c);
    if ((b * b - 4 * a * c) >= 0)
    {
        x = (-1 * b + d) / (2 * a);
        std::printf("%f", x);
        x = (-1 * b - d) / (2 * a);
        std::printf("%f", x);
    }
    else
    {
        std::puts("the discriminant is less than zero");
    }
}
