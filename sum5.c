#include "sum5.h"
#include <stdio.h>

static const uint8_t ss[5][5] =
	{
		{3,4,2,0,1},
		{4,2,0,1,3},
		{2,0,1,3,4},
		{0,1,3,4,2},
		{1,3,4,2,0}
	};


static
uint64_t ipow(uint64_t base, unsigned ex)
{
	uint64_t ret = base;
	while(--ex)
	{
		ret *=base;
	}
	return ret;
}


uint64_t sum5(uint64_t a, uint64_t b)
{
	if(a==0 && b==0) return ss[0][0];
	
	if(a<b) return sum5(b,a);
	
	uint64_t ret = 0;
	uint64_t factor = 1;
	
	const uint64_t max_factor = ipow(5,3);
	while(factor<max_factor)
	{
		const unsigned ar = a%5;
		a = a/5;
		
		const unsigned br = b%5;
		b = b/5;
		
		ret += ss[ar][br] * factor;
		
		factor *= 5;
	}
	
	return ret;
}

const unsigned MAX = 125;

int main()
{
	printf("max_factor = %llu.\n\n", (unsigned long long)ipow(5,3));
	printf("    |");
	for(unsigned u=0; u<MAX; ++u)
		printf(" %4u", u);
	printf("\n----+");
	
	for(unsigned u=0; u<MAX; ++u)
		printf("-----");
	printf("\n");
	
	for(unsigned v=0; v<MAX; ++v)
	{
		printf("%4u|", v);
		for(unsigned u=0; u<MAX; ++u)
		{
			printf(" %4llu", (unsigned long long)sum5(u ^ 11,v ^ 11) ^ 21 );
		}
		printf("\n");
	}
}
