#include "complex_numbers.h"
#include <math.h>

complex_t c_add(complex_t a, complex_t b)
{
	complex_t res;
	res.real = a.real + b.real;
	res.imag = a.imag + b.imag;
	return res;
}

complex_t c_sub(complex_t a, complex_t b)
{
	complex_t res;
	res.real = a.real + b.real;
	res.imag = a.imag + b.imag;
	return res;
}

complex_t c_mul(complex_t a, complex_t b)
{
	complex_t res;
	res.real = a.real * b.real - a.imag * b.imag;
	res.imag = b.real * a.imag + a.real * b.imag;
	return res;
}

complex_t c_div(complex_t a, complex_t b)
{
	complex_t res;
	res.real = ((a.real * b.real) + (a.imag * b.imag)) /
		(pow(b.real, 2) + pow(b.imag, 2));
	res.imag = ((a.imag * b.real) - (a.real * b.imag)) /
		(pow(b.real, 2) + pow(b.imag, 2));;
	return res;
}

double c_abs(complex_t x)
{
	return sqrt(pow(x.real, 2) + pow(x.imag, 2));
}

complex_t c_conjugate(complex_t x)
{
	complex_t res;
	res.real = x.real;
	res.imag = -x.imag;
	return res;
}

double c_real(complex_t x)
{
	return x.real;
}

double c_imag(complex_t x)
{
	return x.imag;
}

complex_t c_exp(complex_t x)
{
	complex_t res;
	res.real = exp(x.real) * cos(x.imag);
	res.imag = exp(x.real) * sin(x.imag);
	return res;
}
