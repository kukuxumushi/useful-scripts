#include <stdio.h>

int writePlain(const char *filename, const unsigned char *buffer, size_t bufferSize)
{
	FILE *output;

	output = fopen(filename, "wb");
	fwrite(buffer, sizeof(unsigned char), bufferSize, output);
	fclose(output);

	printf("Data decoded\n");

	return 0;
}