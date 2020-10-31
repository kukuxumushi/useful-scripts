#include <stdlib.h>

void multiplicationZetPoly(int *src);
void copyPoly(int *dst, int *src);
void setZeroPoly(int *poly);
void scalePoly(int k, int *poly);
void addPoly(int *dst, int *src);

extern int CountedNumberErasures;
extern int *ErasureLocator;
extern int *GaloisOpTable;
extern int Degree;

void initErasureLocatorPoly(int *gamma)
{
	int *temp = (int *) malloc(Degree * sizeof(int));

	setZeroPoly(gamma);
	setZeroPoly(temp);
	gamma[0] = 1;

	for (int i = 0; i < CountedNumberErasures; i++)
	{
		copyPoly(temp, gamma);
		scalePoly(GaloisOpTable[ErasureLocator[i]], temp);
		multiplicationZetPoly(temp);
		addPoly(gamma, temp);
	}

	free(temp);
}