void setZeroPoly(int *poly);
void multiplicationPoly(int *dst, int *p1, int *p2);
void copyPoly(int *dst, int *src);

extern int *GaloisOpTable;

void createGenPoly(int size, int *generationPoly)
{
	int tableA[256], tableB[256];

	setZeroPoly(tableB);
	tableB[0] = 1;

	for (int i = 1; i <= size; i++)
	{
		setZeroPoly(tableA);
		tableA[0] = GaloisOpTable[i];
		tableA[1] = 1;

		multiplicationPoly(generationPoly, tableA, tableB);
		copyPoly(tableB, generationPoly);
	}
}