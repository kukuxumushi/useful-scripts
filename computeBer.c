#include <stdlib.h>

void initErasureLocatorPoly(int *gamma);
void multiplicationZetPoly(int *src);
void copyPoly(int *dst, int *src);
int computeDiscrepancy(int *lambda, int *S, int L, int n);
void computeModifiedOmega(void);
int tableMultiplication(int a, int b);
int tableInversion(int inv);

extern int *SyndromeBytes;
extern int *ErrorLocatorPoly;
extern int CountedNumberErasures;
extern int Parity;
extern int Degree;

void computeBer(void)
{
	int lA, lB, K;
	int discrepancy;
	int *psiFieldA, *psiFieldB, *poly, *gamma;

	psiFieldA = (int *) malloc(Degree * sizeof(int));
	psiFieldB = (int *) malloc(Degree * sizeof(int));
	poly = (int *) malloc(Degree * sizeof(int));
	gamma = (int *) malloc(Degree * sizeof(int));

	initErasureLocatorPoly(gamma);
	copyPoly(poly, gamma);
	multiplicationZetPoly(poly);
	copyPoly(psiFieldA, gamma);
	lA = CountedNumberErasures;
	K = -1;

	for (int i = CountedNumberErasures; i < Parity; i++)
	{
		discrepancy = computeDiscrepancy(psiFieldA, SyndromeBytes, lA, i);
		if (discrepancy)
		{
			for (int j = 0; j < Degree; j++)
				psiFieldB[j] = psiFieldA[j] ^ tableMultiplication(discrepancy, poly[j]);

			if (lA < (i - K))
			{
				lB = i - K;
				K = i - lA;

				for (int j = 0; j < Degree; j++)
					poly[j] = tableMultiplication(psiFieldA[j], tableInversion(discrepancy));
				lA = lB;
			}

			for (int j = 0; j < Degree; j++)
				psiFieldA[j] = psiFieldB[j];
		}

		multiplicationZetPoly(poly);
	}

	for (int i = 0; i < Degree; i++)
		ErrorLocatorPoly[i] = psiFieldA[i];
	computeModifiedOmega();

	free(psiFieldA);
	free(psiFieldB);
	free(poly);
	free(gamma);
}