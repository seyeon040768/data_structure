#include <stdio.h>

#define MAX_DEGREE 101

typedef struct
{
    int degree;
    float coef[MAX_DEGREE];
} Polynomial;

Polynomial AddPolynomial(Polynomial a, Polynomial b)
{
    if (a.degree < b.degree)
    {
        Polynomial temp = a;
        a = b;
        b = temp;
    }

    int highestDiff = a.degree - b.degree;
    for (int i = 0; i <= b.degree; ++i)
    {
        a.coef[i + highestDiff] += b.coef[i];
    }

    return a;
}

void PrintPolynomial(Polynomial poly)
{
    printf("%gx^%d", poly.coef[0], poly.degree);
    for (int i = 1; i < poly.degree; ++i)
    {
        if (poly.coef[i] == 0)
        {
            continue;
        }
        printf("%+gx^%d", poly.coef[i], poly.degree - i);
    }
    printf("%+g\n", poly.coef[poly.degree]);
}

int main(void)
{
    Polynomial poly1 = { .degree = 2, .coef = { 1.0f, 2.0f, 3.0f } }; // 1x^2+2x+3
    Polynomial poly2 = { .degree = 5, .coef = { 1.1f, 2.2f, 0.0f, 0.0f, 3.3f, 0.0f } }; // 1.1x^5+2.2x^4+3.3x

    PrintPolynomial(AddPolynomial(poly1, poly2)); // 1.1x^5+2.2x^4+1x^2+5.3x^1+3

    return 0;
}