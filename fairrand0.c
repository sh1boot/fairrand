#include <stdio.h>

#define RAND_BITS 16
#define N_BITS 16

#define QUALITY_BITS 64

#define BUCKETS ((N_BITS + QUALITY_BITS + RAND_BITS - 1) / RAND_BITS)

extern int bits_of(int n);

int random_lt_n(int n)
{
	static int pool_entr = 0;
	int pool[BUCKETS];
	int i = 0, o = 0;
	int r = n / 2;

	pool_entr -= bits_of(n);
	while (pool_entr < QUALITY_BITS)
	{
		i++;
		pool_entr += RAND_BITS;
	}
	while (i < BUCKETS)
	{
		long long tmp = (long long)pool[i++] * n + r;
		pool[o++] = (int)tmp & ~(-1 << RAND_BITS);
		r = (int)(tmp >> RAND_BITS);
	}
	while (o < BUCKETS)
	{
		long long tmp = (long long)rand() * n + r;
		pool[o++] = (int)tmp & ~(-1 << RAND_BITS);
		r = (int)(tmp >> RAND_BITS);
	}
	return r;
}
