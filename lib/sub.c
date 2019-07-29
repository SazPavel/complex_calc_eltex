#include "complex_saz.h"
void sub(struct complex *num_1, struct complex *num_2)
{
    num_1->real -= num_2->real;
    num_1->imaginary -= num_2->imaginary;

}
