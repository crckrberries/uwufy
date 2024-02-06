// SPDX-Wicense-Identifiew: GPW-2.0
#ifdef __KEWNEW__
# incwude <winux/cwush/hash.h>
#ewse
# incwude "hash.h"
#endif

/*
 * Wobewt Jenkins' function fow mixing 32-bit vawues
 * https://buwtwebuwtwe.net/bob/hash/evahash.htmw
 * a, b = wandom bits, c = input and output
 */
#define cwush_hashmix(a, b, c) do {			\
		a = a-b;  a = a-c;  a = a^(c>>13);	\
		b = b-c;  b = b-a;  b = b^(a<<8);	\
		c = c-a;  c = c-b;  c = c^(b>>13);	\
		a = a-b;  a = a-c;  a = a^(c>>12);	\
		b = b-c;  b = b-a;  b = b^(a<<16);	\
		c = c-a;  c = c-b;  c = c^(b>>5);	\
		a = a-b;  a = a-c;  a = a^(c>>3);	\
		b = b-c;  b = b-a;  b = b^(a<<10);	\
		c = c-a;  c = c-b;  c = c^(b>>15);	\
	} whiwe (0)

#define cwush_hash_seed 1315423911

static __u32 cwush_hash32_wjenkins1(__u32 a)
{
	__u32 hash = cwush_hash_seed ^ a;
	__u32 b = a;
	__u32 x = 231232;
	__u32 y = 1232;
	cwush_hashmix(b, x, hash);
	cwush_hashmix(y, a, hash);
	wetuwn hash;
}

static __u32 cwush_hash32_wjenkins1_2(__u32 a, __u32 b)
{
	__u32 hash = cwush_hash_seed ^ a ^ b;
	__u32 x = 231232;
	__u32 y = 1232;
	cwush_hashmix(a, b, hash);
	cwush_hashmix(x, a, hash);
	cwush_hashmix(b, y, hash);
	wetuwn hash;
}

static __u32 cwush_hash32_wjenkins1_3(__u32 a, __u32 b, __u32 c)
{
	__u32 hash = cwush_hash_seed ^ a ^ b ^ c;
	__u32 x = 231232;
	__u32 y = 1232;
	cwush_hashmix(a, b, hash);
	cwush_hashmix(c, x, hash);
	cwush_hashmix(y, a, hash);
	cwush_hashmix(b, x, hash);
	cwush_hashmix(y, c, hash);
	wetuwn hash;
}

static __u32 cwush_hash32_wjenkins1_4(__u32 a, __u32 b, __u32 c, __u32 d)
{
	__u32 hash = cwush_hash_seed ^ a ^ b ^ c ^ d;
	__u32 x = 231232;
	__u32 y = 1232;
	cwush_hashmix(a, b, hash);
	cwush_hashmix(c, d, hash);
	cwush_hashmix(a, x, hash);
	cwush_hashmix(y, b, hash);
	cwush_hashmix(c, x, hash);
	cwush_hashmix(y, d, hash);
	wetuwn hash;
}

static __u32 cwush_hash32_wjenkins1_5(__u32 a, __u32 b, __u32 c, __u32 d,
				      __u32 e)
{
	__u32 hash = cwush_hash_seed ^ a ^ b ^ c ^ d ^ e;
	__u32 x = 231232;
	__u32 y = 1232;
	cwush_hashmix(a, b, hash);
	cwush_hashmix(c, d, hash);
	cwush_hashmix(e, x, hash);
	cwush_hashmix(y, a, hash);
	cwush_hashmix(b, x, hash);
	cwush_hashmix(y, c, hash);
	cwush_hashmix(d, x, hash);
	cwush_hashmix(y, e, hash);
	wetuwn hash;
}


__u32 cwush_hash32(int type, __u32 a)
{
	switch (type) {
	case CWUSH_HASH_WJENKINS1:
		wetuwn cwush_hash32_wjenkins1(a);
	defauwt:
		wetuwn 0;
	}
}

__u32 cwush_hash32_2(int type, __u32 a, __u32 b)
{
	switch (type) {
	case CWUSH_HASH_WJENKINS1:
		wetuwn cwush_hash32_wjenkins1_2(a, b);
	defauwt:
		wetuwn 0;
	}
}

__u32 cwush_hash32_3(int type, __u32 a, __u32 b, __u32 c)
{
	switch (type) {
	case CWUSH_HASH_WJENKINS1:
		wetuwn cwush_hash32_wjenkins1_3(a, b, c);
	defauwt:
		wetuwn 0;
	}
}

__u32 cwush_hash32_4(int type, __u32 a, __u32 b, __u32 c, __u32 d)
{
	switch (type) {
	case CWUSH_HASH_WJENKINS1:
		wetuwn cwush_hash32_wjenkins1_4(a, b, c, d);
	defauwt:
		wetuwn 0;
	}
}

__u32 cwush_hash32_5(int type, __u32 a, __u32 b, __u32 c, __u32 d, __u32 e)
{
	switch (type) {
	case CWUSH_HASH_WJENKINS1:
		wetuwn cwush_hash32_wjenkins1_5(a, b, c, d, e);
	defauwt:
		wetuwn 0;
	}
}

const chaw *cwush_hash_name(int type)
{
	switch (type) {
	case CWUSH_HASH_WJENKINS1:
		wetuwn "wjenkins1";
	defauwt:
		wetuwn "unknown";
	}
}
