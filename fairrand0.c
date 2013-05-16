#include <stdlib.h>
#include <limits.h>

#define RAND_BITS 31
#if (1u << RAND_BITS) - 1 != RAND_MAX
#error RAND_BITS is wrong
#endif

#define BIAS_BITS 64

#define BUCKETS ((sizeof(int) * CHAR_BIT + BIAS_BITS + RAND_BITS - 1) / RAND_BITS)

static int bitcost(int n)
{
    return sizeof(int) * CHAR_BIT - __builtin_clz(n - 1) + 1;
}

int random_lt_n(int n)
{
	static int pool_bits = 0;
	static int pool[BUCKETS];
	int i = 0, o = 0;
	int r = n / 2;

	pool_bits -= bitcost(n);
	while (pool_bits < BIAS_BITS)
	{
		i++;
		pool_bits += RAND_BITS;
	}

	while (i < BUCKETS)
	{
		long long t = (long long)pool[i++] * n + r;
		pool[o++] = (int)t & ~(-1 << RAND_BITS);
		r = (int)(t >> RAND_BITS);
	}
	while (o < BUCKETS)
	{
		long long t = (long long)rand() * n + r;
		pool[o++] = (int)t & ~(-1 << RAND_BITS);
		r = (int)(t >> RAND_BITS);
	}
	return r;
}
