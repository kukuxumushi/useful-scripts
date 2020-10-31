#include <stdio.h>
#include "erasure.h"

extern unsigned FileSize;
extern unsigned PieceSize;
extern unsigned ErrorNumber;

int writeMeta(const char *filename)
{
	FILE *metaFile;

	metaFile = fopen(META_FILE, "w");

	fprintf(metaFile, "File: %s.bak\n", filename);
	fprintf(metaFile, "Size: %u\n", FileSize);
	fprintf(metaFile, "Piece: %u\n", PieceSize);
	fprintf(metaFile, "Error: %u\n", ErrorNumber);

	fclose(metaFile);

	return 0;
}