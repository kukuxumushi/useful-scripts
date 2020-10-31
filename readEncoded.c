#include <stdio.h>
#include <stdlib.h>
#include "erasure.h"

extern unsigned PieceSize;
extern unsigned ErrorNumber;

int readEncoded(const char *filenameMask, unsigned char **buffer, size_t *bufferSize, unsigned fileSize)
{
	unsigned totalPieceNumber;
	size_t allocSize = 0u;
	size_t readTotal = 0u;

	*buffer = NULL;
	*bufferSize = 0u;

	totalPieceNumber = fileSize / PieceSize + ((fileSize % PieceSize) != 0 ? 1 : 0) + (ErrorNumber << 1u);

//	system("copy " OUTPUT_DIR "\\*" OUTPUT_EXT "." "> nul 2> nul");

	for (unsigned i = 0u; i < totalPieceNumber; i++)
	{
		FILE *input;
		char filenameCurrent[256];

		sprintf(filenameCurrent, OUTPUT_DIR "/%s%03u" OUTPUT_EXT, filenameMask, i);
		input = fopen(filenameCurrent, "rb");

		while (PieceSize * (i + 1) > allocSize)
		{
			allocSize += BUFFER_PART;
			*buffer = (unsigned char *) realloc(*buffer, (allocSize) * sizeof(unsigned char));
		}

		if (input)
		{
			readTotal += fread(*buffer + PieceSize * i, sizeof(unsigned char), PieceSize, input);
			fclose(input);
		}
		else
			for (unsigned j = 0u; j < PieceSize; j++)
				(*buffer)[PieceSize * i + j] = '\0';
	}

//	system("del /q *" OUTPUT_EXT "> nul 2> nul");

	*bufferSize = totalPieceNumber * PieceSize;

	return 0;
}