#include <stdio.h>

#define MASK_HI 0x00000001

typedef unsigned int word;


word set_a_one(word input_word, size_t bit_position)
{
	return (input_word | (MASK_HI << bit_position));
}

int main(void)
{
	printf("%s %d%s\n","El tamaño de la palabra es", sizeof(word), "B");
	printf("%s%x\n","0x", set_a_one(MASK_HI, 10));
	return 0;
} 