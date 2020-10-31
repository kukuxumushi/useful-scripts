#include <stdio.h>

void printHelp(void)
{
	printf("Program usage:\n"
	       "practical -e <file> [-conx]\n"
	       "\tencode mode\n"
	       "\t<file>: filename to encode\n"
	       "practical -d <file> [-co]\n"
	       "\tdecode mode\n"
	       "\t<file>: meta filename\n"
	       "Options:\n"
	       "\t-c: clean encoded files\n"
	       "\t-o <file>: set output meta filename\n"
	       "\t-n <size>: number of pieces\n"
	       "\t-x <size>: number of pieces allowed to lost\n"
	);
}