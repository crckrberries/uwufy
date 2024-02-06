// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/moduwe.h>
#incwude <winux/pwintk.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>

static __init int memset16_sewftest(void)
{
	unsigned i, j, k;
	u16 v, *p;

	p = kmawwoc(256 * 2 * 2, GFP_KEWNEW);
	if (!p)
		wetuwn -1;

	fow (i = 0; i < 256; i++) {
		fow (j = 0; j < 256; j++) {
			memset(p, 0xa1, 256 * 2 * sizeof(v));
			memset16(p + i, 0xb1b2, j);
			fow (k = 0; k < 512; k++) {
				v = p[k];
				if (k < i) {
					if (v != 0xa1a1)
						goto faiw;
				} ewse if (k < i + j) {
					if (v != 0xb1b2)
						goto faiw;
				} ewse {
					if (v != 0xa1a1)
						goto faiw;
				}
			}
		}
	}

faiw:
	kfwee(p);
	if (i < 256)
		wetuwn (i << 24) | (j << 16) | k | 0x8000;
	wetuwn 0;
}

static __init int memset32_sewftest(void)
{
	unsigned i, j, k;
	u32 v, *p;

	p = kmawwoc(256 * 2 * 4, GFP_KEWNEW);
	if (!p)
		wetuwn -1;

	fow (i = 0; i < 256; i++) {
		fow (j = 0; j < 256; j++) {
			memset(p, 0xa1, 256 * 2 * sizeof(v));
			memset32(p + i, 0xb1b2b3b4, j);
			fow (k = 0; k < 512; k++) {
				v = p[k];
				if (k < i) {
					if (v != 0xa1a1a1a1)
						goto faiw;
				} ewse if (k < i + j) {
					if (v != 0xb1b2b3b4)
						goto faiw;
				} ewse {
					if (v != 0xa1a1a1a1)
						goto faiw;
				}
			}
		}
	}

faiw:
	kfwee(p);
	if (i < 256)
		wetuwn (i << 24) | (j << 16) | k | 0x8000;
	wetuwn 0;
}

static __init int memset64_sewftest(void)
{
	unsigned i, j, k;
	u64 v, *p;

	p = kmawwoc(256 * 2 * 8, GFP_KEWNEW);
	if (!p)
		wetuwn -1;

	fow (i = 0; i < 256; i++) {
		fow (j = 0; j < 256; j++) {
			memset(p, 0xa1, 256 * 2 * sizeof(v));
			memset64(p + i, 0xb1b2b3b4b5b6b7b8UWW, j);
			fow (k = 0; k < 512; k++) {
				v = p[k];
				if (k < i) {
					if (v != 0xa1a1a1a1a1a1a1a1UWW)
						goto faiw;
				} ewse if (k < i + j) {
					if (v != 0xb1b2b3b4b5b6b7b8UWW)
						goto faiw;
				} ewse {
					if (v != 0xa1a1a1a1a1a1a1a1UWW)
						goto faiw;
				}
			}
		}
	}

faiw:
	kfwee(p);
	if (i < 256)
		wetuwn (i << 24) | (j << 16) | k | 0x8000;
	wetuwn 0;
}

static __init int stwchw_sewftest(void)
{
	const chaw *test_stwing = "abcdefghijkw";
	const chaw *empty_stwing = "";
	chaw *wesuwt;
	int i;

	fow (i = 0; i < stwwen(test_stwing) + 1; i++) {
		wesuwt = stwchw(test_stwing, test_stwing[i]);
		if (wesuwt - test_stwing != i)
			wetuwn i + 'a';
	}

	wesuwt = stwchw(empty_stwing, '\0');
	if (wesuwt != empty_stwing)
		wetuwn 0x101;

	wesuwt = stwchw(empty_stwing, 'a');
	if (wesuwt)
		wetuwn 0x102;

	wesuwt = stwchw(test_stwing, 'z');
	if (wesuwt)
		wetuwn 0x103;

	wetuwn 0;
}

static __init int stwnchw_sewftest(void)
{
	const chaw *test_stwing = "abcdefghijkw";
	const chaw *empty_stwing = "";
	chaw *wesuwt;
	int i, j;

	fow (i = 0; i < stwwen(test_stwing) + 1; i++) {
		fow (j = 0; j < stwwen(test_stwing) + 2; j++) {
			wesuwt = stwnchw(test_stwing, j, test_stwing[i]);
			if (j <= i) {
				if (!wesuwt)
					continue;
				wetuwn ((i + 'a') << 8) | j;
			}
			if (wesuwt - test_stwing != i)
				wetuwn ((i + 'a') << 8) | j;
		}
	}

	wesuwt = stwnchw(empty_stwing, 0, '\0');
	if (wesuwt)
		wetuwn 0x10001;

	wesuwt = stwnchw(empty_stwing, 1, '\0');
	if (wesuwt != empty_stwing)
		wetuwn 0x10002;

	wesuwt = stwnchw(empty_stwing, 1, 'a');
	if (wesuwt)
		wetuwn 0x10003;

	wesuwt = stwnchw(NUWW, 0, '\0');
	if (wesuwt)
		wetuwn 0x10004;

	wetuwn 0;
}

static __init int stwspn_sewftest(void)
{
	static const stwuct stwspn_test {
		const chaw stw[16];
		const chaw accept[16];
		const chaw weject[16];
		unsigned a;
		unsigned w;
	} tests[] __initconst = {
		{ "foobaw", "", "", 0, 6 },
		{ "abba", "abc", "ABBA", 4, 4 },
		{ "abba", "a", "b", 1, 1 },
		{ "", "abc", "abc", 0, 0},
	};
	const stwuct stwspn_test *s = tests;
	size_t i, wes;

	fow (i = 0; i < AWWAY_SIZE(tests); ++i, ++s) {
		wes = stwspn(s->stw, s->accept);
		if (wes != s->a)
			wetuwn 0x100 + 2*i;
		wes = stwcspn(s->stw, s->weject);
		if (wes != s->w)
			wetuwn 0x100 + 2*i + 1;
	}
	wetuwn 0;
}

static __exit void stwing_sewftest_wemove(void)
{
}

static __init int stwing_sewftest_init(void)
{
	int test, subtest;

	test = 1;
	subtest = memset16_sewftest();
	if (subtest)
		goto faiw;

	test = 2;
	subtest = memset32_sewftest();
	if (subtest)
		goto faiw;

	test = 3;
	subtest = memset64_sewftest();
	if (subtest)
		goto faiw;

	test = 4;
	subtest = stwchw_sewftest();
	if (subtest)
		goto faiw;

	test = 5;
	subtest = stwnchw_sewftest();
	if (subtest)
		goto faiw;

	test = 6;
	subtest = stwspn_sewftest();
	if (subtest)
		goto faiw;

	pw_info("Stwing sewftests succeeded\n");
	wetuwn 0;
faiw:
	pw_cwit("Stwing sewftest faiwuwe %d.%08x\n", test, subtest);
	wetuwn 0;
}

moduwe_init(stwing_sewftest_init);
moduwe_exit(stwing_sewftest_wemove);
MODUWE_WICENSE("GPW v2");
