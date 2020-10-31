#include <stdio.h>
#include <stdlib.h>
#include "erasure.h"

extern unsigned PieceSize;

int writeEncoded(const char *filenameMask, const unsigned char *buffer, size_t bufferSize)
{
	unsigned totalPieceNumber;

	totalPieceNumber = bufferSize / PieceSize;

	system("mkdir " OUTPUT_DIR "> nul 2> nul");

	for (unsigned i = 0u; i < totalPieceNumber; i++)
	{
		FILE *output;
		char filenameCurrent[256];

		sprintf(filenameCurrent, OUTPUT_DIR "/%s%03u" OUTPUT_EXT, filenameMask, i);
		output = fopen(filenameCurrent, "wb");

		fwrite(buffer + PieceSize * i, sizeof(unsigned char), PieceSize, output);

		fclose(output);
	}

//	system("move /y *" OUTPUT_EXT " " OUTPUT_DIR "> nul 2> nul");

	printf("Data encoded\n");

	return 0;
}