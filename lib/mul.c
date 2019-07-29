#include "complex_saz.h"

void mul(struct complex *num_1, struct complex *num_2)
{
    int real = 0, imaginary = 0;
    real = num_1->real * num_2->real - num_1->imaginary * num_2->imaginary;
    imaginary = num_1->imaginary * num_2->real + num_1->real * num_2->imaginary;
    num_1->real = real;
    num_1->imaginary = imaginary;
}
