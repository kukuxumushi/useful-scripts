#include <string.h>
#include <stdlib.h>
#include "erasure.h"

extern unsigned PieceNumber;
extern unsigned ErrorNumber;

unsigned parseInput(int argc, char **argv, char **encodeFilename, char **metaFilename)
{
	int i = 0;
	unsigned flag = 0;

	if (argc == 1)
		flag = FLAG_ERROR;
	while (!(flag & FLAG_ERROR) && ++i < argc)
	{
		if (!strcmp("-c", argv[i]))
			flag |= FLAG_CLEANUP;
		else if (!strcmp("-e", argv[i]))
		{
			if (++i < argc)
			{
				*encodeFilename = argv[i];
				flag |= FLAG_ENCODE;
			}
			else
				flag = FLAG_ERROR;
		}
		else if (!strcmp("-d", argv[i]))
		{
			if (++i < argc)
			{
				*metaFilename = argv[i];
				flag |= FLAG_DECODE;
			}
			else
				flag = FLAG_ERROR;
		}
		else if (!strcmp("-o", argv[i]))
		{
			if (++i < argc)
				*metaFilename = argv[i];
			else
				flag = FLAG_ERROR;
		}
		else if (!strcmp("-n", argv[i]))
		{
			if (++i < argc)
			{
				PieceNumber = strtoul(argv[i], NULL, 0);
				if (!PieceNumber)
					flag = FLAG_ERROR;
			}
			else
				flag = FLAG_ERROR;
		}
		else if (!strcmp("-x", argv[i]))
		{
			if (++i < argc)
			{
				ErrorNumber = strtoul(argv[i], NULL, 0);
				if (!ErrorNumber)
					flag = FLAG_ERROR;
			}
			else
				flag = FLAG_ERROR;
		}
		else
			flag = FLAG_ERROR;

		if ((flag & FLAG_ENCODE) && (flag & FLAG_DECODE))
			flag = FLAG_ERROR;
	}

	if (!(flag & FLAG_ENCODE) && !(flag & FLAG_DECODE) && !(flag & FLAG_CLEANUP))
		flag = FLAG_ERROR;
	return flag;
}