#include <stdlib.h>
#include <stdio.h>

int decodeReedSolomon(unsigned char *dataInput, unsigned dataSize);

extern unsigned PieceSize;
extern unsigned ErrorNumber;

int decodeMode(unsigned char *buffer, size_t *bufferSize)
{
	unsigned dataPieceNumber;
	unsigned excessPieceNumber;
	unsigned char **stripesBuffer;
	unsigned progress = 0u;

	*bufferSize -= (PieceSize << 1u) * ErrorNumber;

	dataPieceNumber = *bufferSize / PieceSize;
	excessPieceNumber = ErrorNumber << 1u;

	stripesBuffer = (unsigned char **) malloc(PieceSize * sizeof(unsigned char *));
	for (unsigned i = 0u; i < PieceSize; i++)
		*(stripesBuffer + i) = (unsigned char *) malloc((dataPieceNumber + excessPieceNumber) * sizeof(unsigned char));

	for (unsigned i = 0u; i < PieceSize; i++)
	{
		unsigned j;

		for (j = 0u; j < dataPieceNumber; j++)
			(*(stripesBuffer + i))[j] = buffer[i + j * PieceSize];
		for (j = 0u; j < excessPieceNumber; j++)
			(*(stripesBuffer + i))[dataPieceNumber + j] = buffer[*bufferSize + i + j * PieceSize];
	}

	for (unsigned i = 0u; i < PieceSize; i++)
	{
		decodeReedSolomon(*(stripesBuffer + i), dataPieceNumber);
		if ((double) i / PieceSize * 100. > progress)
		{
			progress += 10;
			printf("Progress: %2i%%\n", progress);
		}
	}

	for (unsigned i = 0u; i < dataPieceNumber; i++)
		for (unsigned j = 0u; j < PieceSize; j++)
			buffer[PieceSize * i + j] = (*(stripesBuffer + j))[i];

	return 0;
}