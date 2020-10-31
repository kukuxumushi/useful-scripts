#include <stdio.h>
#include "parse.h"

int ax;
int bx;
int heap[HEAP_SIZE];

Command commandList = {0, NULL, NULL, NULL};
Identifier identifierList = {NULL, 0, NULL};
Sector sectorList = {NULL, NULL, NULL};

typedef enum _Flags Flags;
enum _Flags
{
	FLAG_EQUAL = 0x1,
	FLAG_MORE = 0x2,
	FLAG_LESS = 0x4
};

void execute(void)
{
	Command *current = commandList.next;
	Flags flags = 0;

	while (current)
	{
		if (current->com == ASM_MOV)
			*(current->left) = *(current->right);
		else if (current->com == ASM_ADD)
			*(current->left) += *(current->right);
		else if (current->com == ASM_SUB)
			*(current->left) -= *(current->right);
		else if (current->com == ASM_SAR)
			*(current->left) >>= *(current->right);
		else if (current->com == ASM_SAL)
			*(current->left) <<= *(current->right);
		else if (current->com == ASM_MUL)
			*(current->left) *= *(current->right);
		else if (current->com == ASM_DIV)
			*(current->left) /= *(current->right);
		else if (current->com == ASM_AND)
			*(current->left) &= *(current->right);
		else if (current->com == ASM_OR)
			*(current->left) |= *(current->right);
		else if (current->com == ASM_XOR)
			*(current->left) ^= *(current->right);
		else if (current->com == ASM_CMP)
		{
			if (*(current->left) > *(current->right))
				flags = FLAG_MORE;
			else if (*(current->left) < *(current->right))
				flags = FLAG_LESS;
			else
				flags = FLAG_EQUAL;
		}
		else if (current->com == CMP_EQUAL)
			*(current->left) = (flags & FLAG_EQUAL) ? 1 : 0;
		else if (current->com == CMP_NOT_EQUAL)
			*(current->left) = (flags & FLAG_EQUAL) ? 0 : 1;
		else if (current->com == CMP_MORE_EQUAL)
			*(current->left) = (flags & (FLAG_EQUAL | FLAG_MORE)) ? 1 : 0;
		else if (current->com == CMP_MORE)
			*(current->left) = (flags & FLAG_MORE) ? 1 : 0;
		else if (current->com == CMP_LESS_EQUAL)
			*(current->left) = (flags & (FLAG_EQUAL | FLAG_LESS)) ? 1 : 0;
		else if (current->com == CMP_LESS)
			*(current->left) = (flags & FLAG_LESS) ? 1 : 0;
		else if (current->com == ASM_CALL)
			printf("%i\n", *(current->left));
		else if (current->com == ASM_NEG)
			*(current->left) = -*(current->left);
		else if (current->com == ASM_NOT)
			*(current->left) = ~*(current->left);
		else if (current->com == ASM_JMP)
			current = current->jump->com;
		else if (current->com == ASM_JE)
			if (flags & FLAG_EQUAL)
				current = current->jump->com;

		current = current->next;
	}
}
