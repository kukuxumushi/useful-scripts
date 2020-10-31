#include <stdio.h>

extern unsigned FileSize;
extern unsigned PieceSize;
extern unsigned ErrorNumber;

int readMeta(const char *metaFilename, char *decodeFilename)
{
	FILE *metaFile;

	metaFile = fopen(metaFilename, "r");
	if(!metaFile)
	{
		printf("Can not read in readMeta\n");
		return 1;
	}

	fscanf(metaFile, "File: %s\n", decodeFilename);
	fscanf(metaFile, "Size: %u\n", &FileSize);
	fscanf(metaFile, "Piece: %u\n", &PieceSize);
	fscanf(metaFile, "Error: %u", &ErrorNumber);

	fclose(metaFile);

	return 0;
}