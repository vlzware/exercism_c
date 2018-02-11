#include "pascals_triangle.h"
#include <stdlib.h>

int fr(int i);
void check_alloc(void *p);

size_t **create_triangle(int rows)
{
	if (rows < 0)
		return NULL;

	size_t **triangle =
		(size_t **) malloc(sizeof(size_t*) * (rows? rows : 1));
	check_alloc(triangle);

	if (rows == 0) {
		triangle[0] = (size_t *) malloc(sizeof(size_t));
		check_alloc(triangle[0]);
		triangle[0][0] = 0;
		return triangle;
	}

	int i, j, cols = rows;
	for (i = 0; i < rows; i++) {

		triangle[i] = (size_t *) malloc(sizeof(size_t) * cols);
		check_alloc(triangle[i]);

		for (j = 0; j < cols; j++)
			triangle[i][j] = (j > i)?
				0 : fr(i) / (fr(j) * fr(i - j));
	}

	return triangle;
}

void free_triangle(size_t **triangle, int size)
{
	if (size <= 0)
		return;

	while(size--)
		free(triangle[size]);

	free(triangle);
}

int fr(int i)
{
	if (i <= 0)
		return 1;
	return (i * fr(i - 1));
}

#include <stdio.h>
void check_alloc(void *p)
{
	if (p == NULL) {
		fprintf(stderr, "Memory error.\n");
		exit(1);
	}
}
