extern int *GaloisOpTable;
extern int *GaloisMulTable;

void initExpTable(void)
{
	int cBase;
	int c1, c2, c3, c4, c5, c6, c7, c8;

	c1 = 1;
	c2 = c3 = c4 = c5 = c6 = c7 = c8 = 0;

	GaloisOpTable[0] = 1;
	GaloisOpTable[255] = GaloisOpTable[0];
	GaloisMulTable[0] = 0;

	for (int i = 1; i < 256; i++)
	{
		cBase = c8;
		c8 = c7;
		c7 = c6;
		c6 = c5;
		c5 = c4 ^ cBase;
		c4 = c3 ^ cBase;
		c3 = c2 ^ cBase;
		c2 = c1;
		c1 = cBase;
		GaloisOpTable[i] = c1 + c2 * 2 + c3 * 4 + c4 * 8 + c5 * 16 + c6 * 32 + c7 * 64 + c8 * 128;
		GaloisOpTable[i + 255] = GaloisOpTable[i];
	}

	for (int i = 1; i < 256; i++)
		for (int z = 0; z < 256; z++)
			if (GaloisOpTable[z] == i)
			{
				GaloisMulTable[i] = z;
				break;
			}
}