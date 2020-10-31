int tableMultiplication(int a, int b);

extern int CountedNumberErrors;
extern int *ErrorLocatorPoly;
extern int *ErrorLocator;
extern int *GaloisOpTable;
extern int Parity;

void findRoots(void)
{
	CountedNumberErrors = 0;
	for (int i = 1; i < 256; i++)
	{
		int sum = 0;

		for (int j = 0; j < Parity + 1; j++)
			sum ^= tableMultiplication(GaloisOpTable[(j * i) % 255], ErrorLocatorPoly[j]);
		if (!sum)
		{
			ErrorLocator[CountedNumberErrors] = (255 - i);
			CountedNumberErrors++;
		}
	}
}