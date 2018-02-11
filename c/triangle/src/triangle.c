#include "triangle.h"

int is_equilateral(triangle_t triangle)
{
	if (
		triangle.a == triangle.b &&
		triangle.a == triangle.c
	)
		return 1;
	return 0;
}

int is_isosceles(triangle_t triangle)
{
	if (
		triangle.a == triangle.b ||
		triangle.a == triangle.c ||
		triangle.b == triangle.c
	)
		return 1;
	return 0;
}

int is_scalene(triangle_t triangle)
{
	if (
		triangle.a != triangle.b &&
		triangle.a != triangle.c &&
		triangle.b != triangle.c
	)
		return 1;
	return 0;
}
