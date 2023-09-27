#include <cstdio>
#include <cmath>

int main()
{
    std::puts("Введите a, b и c для 'ax^2 + bx + c = 0':");
    float a = 0;
    float b = 0;
    float c = 0;
    std::scanf("%f %f %f", &a, &b, &c);
    float d = b * b - 4 * a * c;
    if (d >= 0)
    {
        float x1 = (-b + std::sqrt(d)) / (2 * a);
        float x2 = (-b - std::sqrt(d)) / (2 * a);
        std::printf("solution: %.2f %.2f \n", x1, x2);
    }
    else
    {
        std::printf("solution: undefined \n");
    }
}