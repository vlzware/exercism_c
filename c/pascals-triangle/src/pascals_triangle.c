#include "pascals_triangle.h"
#include <stdlib.h>

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

		triangle[i][0] = 1;

		for (j = 1; j < cols; j++)
			triangle[i][j] = (j > i)
				? 0
				: (triangle[i - 1][j] +
					triangle[i - 1][j - 1]);
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

#include <stdio.h>
void check_alloc(void *p)
{
	if (p == NULL) {
		fprintf(stderr, "Memory error.\n");
		exit(1);
	}
}
