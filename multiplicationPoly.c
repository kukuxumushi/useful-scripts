#include <stdlib.h>

int tableMultiplication(int a, int b);

extern int Degree;

void multiplicationPoly(int *dst, int *p1, int *p2)
{
	int *temp = (int *) malloc(Degree * 2 * sizeof(int));

	for (int i = 0; i < (Degree * 2); i++)
		dst[i] = 0;

	for (int i = 0; i < Degree; i++)
	{
		for (int j = Degree; j < (Degree * 2); j++)
			temp[j] = 0;
		for (int j = 0; j < Degree; j++)
			temp[j] = tableMultiplication(p2[j], p1[i]);
		for (int j = (Degree * 2) - 1; j >= i; j--)
			temp[j] = temp[j - i];
		for (int j = 0; j < i; j++)
			temp[j] = 0;
		for (int j = 0; j < (Degree * 2); j++)
			dst[j] ^= temp[j];
	}

	free(temp);
}