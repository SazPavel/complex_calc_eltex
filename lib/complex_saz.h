#ifndef complex_saz_h
#define complex_saz_h

struct complex
{
    int real;
    int imaginary;
};

void Sum(struct complex *, struct complex *);
void Sub(struct complex *, struct complex *);
void Mul(struct complex *, struct complex *);
void Div(struct complex *, struct complex *);
#endif
