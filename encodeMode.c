#include <stdlib.h>
#include <stdio.h>

int encodeReedSolomon(unsigned char *dataInput, unsigned dataSize);

extern unsigned PieceSize;
extern unsigned ErrorNumber;

int encodeMode(unsigned char **buffer, size_t *bufferSize)
{
	unsigned dataPieceNumber;
	unsigned excessPieceNumber;
	unsigned char **stripesBuffer;
	unsigned progress = 0u;

	dataPieceNumber = *bufferSize / PieceSize;
	if ((*bufferSize % PieceSize) != 0)
		dataPieceNumber++;
	excessPieceNumber = ErrorNumber << 1u;

	*buffer = (unsigned char *) realloc(*buffer, PieceSize * (dataPieceNumber + excessPieceNumber));

	while (*bufferSize % PieceSize != 0)
		(*buffer)[(*bufferSize)++] = '\0';

	stripesBuffer = (unsigned char **) malloc(PieceSize * sizeof(unsigned char *));
	for (unsigned i = 0u; i < PieceSize; i++)
		*(stripesBuffer + i) = (unsigned char *) malloc((dataPieceNumber + excessPieceNumber) * sizeof(unsigned char));

	for (unsigned i = 0u; i < PieceSize; i++)
	{
		unsigned j;

		for (j = 0u; j < dataPieceNumber; j++)
			(*(stripesBuffer + i))[j] = (*buffer)[i + j * PieceSize];
		for (j = 0u; j < excessPieceNumber; j++)
			(*(stripesBuffer + i))[dataPieceNumber + j] = '\0';
	}

	for (unsigned i = 0u; i < PieceSize; i++)
	{
		encodeReedSolomon(*(stripesBuffer + i), dataPieceNumber);
		if ((double) i / PieceSize * 100. > progress)
		{
			progress += 10u;
			printf("Progress: %2i%%\n", progress);
		}
	}

	for (unsigned i = 0u; i < excessPieceNumber; i++)
		for (unsigned j = 0u; j < PieceSize; j++)
			(*buffer)[*bufferSize + PieceSize * i + j] = (*(stripesBuffer + j))[dataPieceNumber + i];

	*bufferSize += PieceSize * excessPieceNumber;
	return 0;
}