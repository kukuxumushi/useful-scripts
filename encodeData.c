#include <stdlib.h>

int tableMultiplication(int a, int b);
void addCodeBytes(const unsigned char *source, int size, unsigned char *destination);

extern int *PolyGenerator;
extern int *ParityBytesEncode;
extern int Parity;

void encodeData(unsigned char *source, int size, unsigned char *dst)
{
	int *shiftTable = (int *) calloc((Parity + 1), sizeof(int));

	for (int i = 0; i < size; i++)
	{
		int dbyte = source[i] ^shiftTable[Parity - 1];

		for (int j = Parity - 1; j > 0; j--)
			shiftTable[j] = shiftTable[j - 1] ^ tableMultiplication(PolyGenerator[j], dbyte);
		shiftTable[0] = tableMultiplication(PolyGenerator[0], dbyte);
	}

	for (int i = 0; i < Parity; i++)
		ParityBytesEncode[i] = shiftTable[i];

	addCodeBytes(source, size, dst);

	free(shiftTable);
}