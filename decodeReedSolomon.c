#include <stdlib.h>

void initReedSolomon(void);
void decodeData(const unsigned char *data, int size);
int correctErrors(unsigned char *codeword, int size);

extern int *GaloisOpTable;
extern int *GaloisMulTable;
extern int *ParityBytesEncode;
extern int *PolyGenerator;
extern int *ErrorLocatorPoly;
extern int *ErrorEvaluatorPoly;
extern int *ErrorLocator;
extern int *ErasureLocator;
extern int *SyndromeBytes;
extern int Parity;
extern int Degree;

int decodeReedSolomon(unsigned char *dataInput, unsigned dataSize)
{
	GaloisOpTable = (int *) calloc(512, sizeof(int));
	GaloisMulTable = (int *) calloc(256, sizeof(int));
	ParityBytesEncode = (int *) calloc(Degree, sizeof(int));
	SyndromeBytes = (int *) calloc(Degree, sizeof(int));
	PolyGenerator = (int *) calloc(Degree * 2, sizeof(int));
	ErrorLocatorPoly = (int *) calloc(Degree, sizeof(int));
	ErrorEvaluatorPoly = (int *) calloc(Degree, sizeof(int));
	ErrorLocator = (int *) calloc(256, sizeof(int));
	ErasureLocator = (int *) calloc(256, sizeof(int));

	for (int i = 0; i < Degree; i++)
		SyndromeBytes[i] = 0;

	initReedSolomon();
	decodeData(dataInput, (int) dataSize + Parity);
	correctErrors(dataInput, (int) dataSize + Parity);

	free(GaloisOpTable);
	free(GaloisMulTable);
	free(ParityBytesEncode);
	free(SyndromeBytes);
	free(PolyGenerator);
	free(ErrorLocatorPoly);
	free(ErrorEvaluatorPoly);
	free(ErrorLocator);
	free(ErasureLocator);

	return 0;
}