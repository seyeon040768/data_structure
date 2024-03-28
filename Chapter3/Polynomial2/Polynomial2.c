#include <stdio.h>
#include <string.h>

#define MAX_TERMS 101

typedef struct
{
	float coef;
	int exponent;
} Term;

typedef struct
{
	Term terms[MAX_TERMS];
	int availIndex;
} Polynomial;

int AttachTerm(Polynomial* target, Term term)
{
    if (target->availIndex >= MAX_TERMS)
    {
        return 0;
    }

    target->terms[target->availIndex] = term;
    ++(target->availIndex);

    return 1;
}

Polynomial AddPolynomial(Polynomial a, Polynomial b)
{
    Polynomial res = { .availIndex = 0 };
    int aIndex = 0;
    int bIndex = 0;

    while (aIndex < a.availIndex && bIndex < b.availIndex)
    {
        float aExpon = a.terms[aIndex].exponent;
        float bExpon = b.terms[bIndex].exponent;

        if (aExpon > bExpon)
        {
            AttachTerm(&res, a.terms[aIndex]);
            ++aIndex;
        }
        else if (aExpon < bExpon)
        {
            AttachTerm(&res, b.terms[bIndex]);
            ++bIndex;
        }
        else
        {
            AttachTerm(&res, (Term){ a.terms[aIndex].coef + b.terms[bIndex].coef, a.terms[aIndex].exponent });

            ++aIndex;
            ++bIndex;
        }
    }

    for (int i = aIndex; i < a.availIndex; ++i)
    {
        AttachTerm(&res, a.terms[i]);
    }
    for (int i = bIndex; i < b.availIndex; ++i)
    {
        AttachTerm(&res, b.terms[i]);
    }

    return res;
}

void PrintPolynomial(Polynomial poly)
{
    printf("%gx^%d", poly.terms[0].coef, poly.terms[0].exponent);

    for (int i = 1; i < poly.availIndex - 1; ++i)
    {
        printf("%+gx^%d", poly.terms[i].coef, poly.terms[i].exponent);
    }

    if (poly.terms[poly.availIndex - 1].exponent == 0)
    {
        printf("%+g\n", poly.terms[poly.availIndex - 1].coef);
    }
    else
    {
        printf("%+gx^%d\n", poly.terms[poly.availIndex - 1].coef, poly.terms[poly.availIndex - 1].exponent);
    }
}

int main(void)
{
    Polynomial poly1 = { .terms = { {1, 2}, {2, 1}, {3, 0} }, .availIndex = 3 }; // 1x^2+2x+3
    Polynomial poly2 = { .terms = { {1.1f, 5}, {2.2f, 4}, {3.3f, 1} }, .availIndex = 3 }; // 1.1x^5+2.2x^4+3.3x

    PrintPolynomial(AddPolynomial(poly1, poly2)); // 1.1x^5+2.2x^4+1x^2+5.3x^1+3

    return 0;
}