#include <stdlib.h>

void createGenPoly(int size, int *generationPoly);
void initExpTable(void);
void multiplicationPoly(int *dst, int *p1, int *p2);

extern int *GaloisOpTable;
extern int *GaloisMulTable;
extern int *PolyGenerator;
extern int *ParityBytesEncode;
extern int *SyndromeBytes;
extern int *ErrorLocatorPoly;
extern int *ErrorEvaluatorPoly;
extern int Parity;
extern int Degree;

void setZeroPoly(int *poly)
{
	for (int i = 0; i < Degree; i++)
		poly[i] = 0;
}

int tableMultiplication(int a, int b)
{
	if (!a || !b)
		return 0;

	return GaloisOpTable[GaloisMulTable[a] + GaloisMulTable[b]];
}

int tableInversion(int inv)
{
	return GaloisOpTable[255 - GaloisMulTable[inv]];
}

void initReedSolomon(void)
{
	initExpTable();
	createGenPoly(Parity, PolyGenerator);
}

void addCodeBytes(const unsigned char *source, int size, unsigned char *destination)
{
	for (int i = 0; i < size; i++)
		destination[i] = source[i];
	for (int i = 0; i < Parity; i++)
		destination[i + size] = ParityBytesEncode[Parity - 1 - i];
}

void decodeData(const unsigned char *data, int size)
{
	for (int i = 0; i < Parity; i++)
	{
		int sum = 0;
		for (int j = 0; j < size; j++)
			sum = data[j] ^ tableMultiplication(GaloisOpTable[i + 1], sum);
		SyndromeBytes[i] = sum;
	}
}

void computeModifiedOmega(void)
{
	int *product = (int *) malloc(Degree * 2 * sizeof(int));

	multiplicationPoly(product, ErrorLocatorPoly, SyndromeBytes);
	setZeroPoly(ErrorEvaluatorPoly);
	for (int i = 0; i < Parity; i++)
		ErrorEvaluatorPoly[i] = product[i];

	free(product);
}

int computeDiscrepancy(int *lambda, int *S, int L, int n)
{
	int sum = 0;

	for (int i = 0; i <= L; i++)
		sum ^= tableMultiplication(lambda[i], S[n - i]);

	return sum;
}

void addPoly(int *dst, int *src)
{
	for (int i = 0; i < Degree; i++)
		dst[i] ^= src[i];
}

void copyPoly(int *dst, int *src)
{
	for (int i = 0; i < Degree; i++)
		dst[i] = src[i];
}

void scalePoly(int k, int *poly)
{
	for (int i = 0; i < Degree; i++)
		poly[i] = tableMultiplication(k, poly[i]);
}

void multiplicationZetPoly(int *src)
{
	for (int i = Degree - 1; i > 0; i--)
		src[i] = src[i - 1];
	src[0] = 0;
}