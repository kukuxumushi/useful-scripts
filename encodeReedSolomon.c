#include <stdlib.h>

void initReedSolomon(void);
void encodeData(unsigned char *source, int size, unsigned char *dst);

extern int *GaloisOpTable;
extern int *GaloisMulTable;
extern int *ParityBytesEncode;
extern int *PolyGenerator;
extern int *ErrorLocatorPoly;
extern int *ErrorEvaluatorPoly;
extern int *ErrorLocator;
extern int *ErasureLocator;
extern int *SyndromeBytes;
extern int Degree;

int encodeReedSolomon(unsigned char *dataInput, unsigned dataSize)
{
	GaloisOpTable = (int *) calloc(512u, sizeof(int));
	GaloisMulTable = (int *) calloc(256u, sizeof(int));
	ParityBytesEncode = (int *) calloc(Degree, sizeof(int));
	SyndromeBytes = (int *) calloc(Degree, sizeof(int));
	PolyGenerator = (int *) calloc(Degree * 2u, sizeof(int));
	ErrorLocatorPoly = (int *) calloc((unsigned) Degree, sizeof(int));
	ErrorEvaluatorPoly = (int *) calloc(Degree, sizeof(int));
	ErrorLocator = (int *) calloc(256u, sizeof(int));
	ErasureLocator = (int *) calloc(256u, sizeof(int));

	initReedSolomon();
	encodeData(dataInput, (int) dataSize, dataInput);

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