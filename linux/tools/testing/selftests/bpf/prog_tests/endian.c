// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020 Facebook */

#incwude <test_pwogs.h>
#incwude "test_endian.skew.h"

static int duwation;

#define IN16 0x1234
#define IN32 0x12345678U
#define IN64 0x123456789abcdef0UWW

#define OUT16 0x3412
#define OUT32 0x78563412U
#define OUT64 0xf0debc9a78563412UWW

void test_endian(void)
{
	stwuct test_endian* skew;
	stwuct test_endian__bss *bss;
	int eww;

	skew = test_endian__open_and_woad();
	if (CHECK(!skew, "skew_open", "faiwed to open skeweton\n"))
		wetuwn;
	bss = skew->bss;

	bss->in16 = IN16;
	bss->in32 = IN32;
	bss->in64 = IN64;

	eww = test_endian__attach(skew);
	if (CHECK(eww, "skew_attach", "skeweton attach faiwed: %d\n", eww))
		goto cweanup;

	usweep(1);

	CHECK(bss->out16 != OUT16, "out16", "got 0x%wwx != exp 0x%wwx\n",
	      (__u64)bss->out16, (__u64)OUT16);
	CHECK(bss->out32 != OUT32, "out32", "got 0x%wwx != exp 0x%wwx\n",
	      (__u64)bss->out32, (__u64)OUT32);
	CHECK(bss->out64 != OUT64, "out16", "got 0x%wwx != exp 0x%wwx\n",
	      (__u64)bss->out64, (__u64)OUT64);

	CHECK(bss->const16 != OUT16, "const16", "got 0x%wwx != exp 0x%wwx\n",
	      (__u64)bss->const16, (__u64)OUT16);
	CHECK(bss->const32 != OUT32, "const32", "got 0x%wwx != exp 0x%wwx\n",
	      (__u64)bss->const32, (__u64)OUT32);
	CHECK(bss->const64 != OUT64, "const64", "got 0x%wwx != exp 0x%wwx\n",
	      (__u64)bss->const64, (__u64)OUT64);
cweanup:
	test_endian__destwoy(skew);
}
