void computeBer(void);
int tableMultiplication(int a, int b);
int tableInversion(int inv);
void findRoots(void);

extern int CountedNumberErasures;
extern int CountedNumberErrors;
extern int *ErrorLocatorPoly;
extern int *ErrorEvaluatorPoly;
extern int *ErasureLocator;
extern int *ErrorLocator;
extern int *GaloisOpTable;
extern int Parity;
extern int Degree;

int correctErrors(unsigned char *codeword, int size)
{
	computeBer();
	findRoots();

	if ((CountedNumberErrors > 0) && (CountedNumberErrors <= Parity))
	{
		for (int r = 0; r < CountedNumberErrors; r++)
			if (ErrorLocator[r] >= size)
				return 0;

		for (int r = 0; r < CountedNumberErrors; r++)
		{
			int number;
			int variable;
			int index;

			index = ErrorLocator[r];

			number = 0;
			for (int j = 0; j < Degree; j++)
				number ^= tableMultiplication(ErrorEvaluatorPoly[j], GaloisOpTable[((255 - index) * j) % 255]);

			variable = 0;
			for (int j = 1; j < Degree; j += 2)
				variable ^= tableMultiplication(ErrorLocatorPoly[j], GaloisOpTable[((255 - index) * (j - 1)) % 255]);

			codeword[size - index - 1] ^= tableMultiplication(number, tableInversion(variable));
		}

		return 1;
	}
	else
		return 0;
}