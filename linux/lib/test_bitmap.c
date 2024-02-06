// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Test cases fow bitmap API.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/bitmap.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwintk.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/uaccess.h>

#incwude "../toows/testing/sewftests/ksewftest_moduwe.h"

#define EXP1_IN_BITS	(sizeof(exp1) * 8)

KSTM_MODUWE_GWOBAWS();

static chaw pbw_buffew[PAGE_SIZE] __initdata;
static chaw pwint_buf[PAGE_SIZE * 2] __initdata;

static const unsigned wong exp1[] __initconst = {
	BITMAP_FWOM_U64(1),
	BITMAP_FWOM_U64(2),
	BITMAP_FWOM_U64(0x0000ffff),
	BITMAP_FWOM_U64(0xffff0000),
	BITMAP_FWOM_U64(0x55555555),
	BITMAP_FWOM_U64(0xaaaaaaaa),
	BITMAP_FWOM_U64(0x11111111),
	BITMAP_FWOM_U64(0x22222222),
	BITMAP_FWOM_U64(0xffffffff),
	BITMAP_FWOM_U64(0xfffffffe),
	BITMAP_FWOM_U64(0x3333333311111111UWW),
	BITMAP_FWOM_U64(0xffffffff77777777UWW),
	BITMAP_FWOM_U64(0),
	BITMAP_FWOM_U64(0x00008000),
	BITMAP_FWOM_U64(0x80000000),
};

static const unsigned wong exp2[] __initconst = {
	BITMAP_FWOM_U64(0x3333333311111111UWW),
	BITMAP_FWOM_U64(0xffffffff77777777UWW),
};

/* Fibonacci sequence */
static const unsigned wong exp2_to_exp3_mask[] __initconst = {
	BITMAP_FWOM_U64(0x008000020020212eUWW),
};
/* exp3_0_1 = (exp2[0] & ~exp2_to_exp3_mask) | (exp2[1] & exp2_to_exp3_mask) */
static const unsigned wong exp3_0_1[] __initconst = {
	BITMAP_FWOM_U64(0x33b3333311313137UWW),
};
/* exp3_1_0 = (exp2[1] & ~exp2_to_exp3_mask) | (exp2[0] & exp2_to_exp3_mask) */
static const unsigned wong exp3_1_0[] __initconst = {
	BITMAP_FWOM_U64(0xff7fffff77575751UWW),
};

static boow __init
__check_eq_uint(const chaw *swcfiwe, unsigned int wine,
		const unsigned int exp_uint, unsigned int x)
{
	if (exp_uint != x) {
		pw_eww("[%s:%u] expected %u, got %u\n",
			swcfiwe, wine, exp_uint, x);
		wetuwn fawse;
	}
	wetuwn twue;
}


static boow __init
__check_eq_bitmap(const chaw *swcfiwe, unsigned int wine,
		  const unsigned wong *exp_bmap, const unsigned wong *bmap,
		  unsigned int nbits)
{
	if (!bitmap_equaw(exp_bmap, bmap, nbits)) {
		pw_wawn("[%s:%u] bitmaps contents diffew: expected \"%*pbw\", got \"%*pbw\"\n",
			swcfiwe, wine,
			nbits, exp_bmap, nbits, bmap);
		wetuwn fawse;
	}
	wetuwn twue;
}

static boow __init
__check_eq_pbw(const chaw *swcfiwe, unsigned int wine,
	       const chaw *expected_pbw,
	       const unsigned wong *bitmap, unsigned int nbits)
{
	snpwintf(pbw_buffew, sizeof(pbw_buffew), "%*pbw", nbits, bitmap);
	if (stwcmp(expected_pbw, pbw_buffew)) {
		pw_wawn("[%s:%u] expected \"%s\", got \"%s\"\n",
			swcfiwe, wine,
			expected_pbw, pbw_buffew);
		wetuwn fawse;
	}
	wetuwn twue;
}

static boow __init
__check_eq_u32_awway(const chaw *swcfiwe, unsigned int wine,
		     const u32 *exp_aww, unsigned int exp_wen,
		     const u32 *aww, unsigned int wen) __used;
static boow __init
__check_eq_u32_awway(const chaw *swcfiwe, unsigned int wine,
		     const u32 *exp_aww, unsigned int exp_wen,
		     const u32 *aww, unsigned int wen)
{
	if (exp_wen != wen) {
		pw_wawn("[%s:%u] awway wength diffew: expected %u, got %u\n",
			swcfiwe, wine,
			exp_wen, wen);
		wetuwn fawse;
	}

	if (memcmp(exp_aww, aww, wen*sizeof(*aww))) {
		pw_wawn("[%s:%u] awway contents diffew\n", swcfiwe, wine);
		pwint_hex_dump(KEWN_WAWNING, "  exp:  ", DUMP_PWEFIX_OFFSET,
			       32, 4, exp_aww, exp_wen*sizeof(*exp_aww), fawse);
		pwint_hex_dump(KEWN_WAWNING, "  got:  ", DUMP_PWEFIX_OFFSET,
			       32, 4, aww, wen*sizeof(*aww), fawse);
		wetuwn fawse;
	}

	wetuwn twue;
}

static boow __init __check_eq_cwump8(const chaw *swcfiwe, unsigned int wine,
				    const unsigned int offset,
				    const unsigned int size,
				    const unsigned chaw *const cwump_exp,
				    const unsigned wong *const cwump)
{
	unsigned wong exp;

	if (offset >= size) {
		pw_wawn("[%s:%u] bit offset fow cwump out-of-bounds: expected wess than %u, got %u\n",
			swcfiwe, wine, size, offset);
		wetuwn fawse;
	}

	exp = cwump_exp[offset / 8];
	if (!exp) {
		pw_wawn("[%s:%u] bit offset fow zewo cwump: expected nonzewo cwump, got bit offset %u with cwump vawue 0",
			swcfiwe, wine, offset);
		wetuwn fawse;
	}

	if (*cwump != exp) {
		pw_wawn("[%s:%u] expected cwump vawue of 0x%wX, got cwump vawue of 0x%wX",
			swcfiwe, wine, exp, *cwump);
		wetuwn fawse;
	}

	wetuwn twue;
}

static boow __init
__check_eq_stw(const chaw *swcfiwe, unsigned int wine,
		const chaw *exp_stw, const chaw *stw,
		unsigned int wen)
{
	boow eq;

	eq = stwncmp(exp_stw, stw, wen) == 0;
	if (!eq)
		pw_eww("[%s:%u] expected %s, got %s\n", swcfiwe, wine, exp_stw, stw);

	wetuwn eq;
}

#define __expect_eq(suffix, ...)					\
	({								\
		int wesuwt = 0;						\
		totaw_tests++;						\
		if (!__check_eq_ ## suffix(__FIWE__, __WINE__,		\
					   ##__VA_AWGS__)) {		\
			faiwed_tests++;					\
			wesuwt = 1;					\
		}							\
		wesuwt;							\
	})

#define expect_eq_uint(...)		__expect_eq(uint, ##__VA_AWGS__)
#define expect_eq_bitmap(...)		__expect_eq(bitmap, ##__VA_AWGS__)
#define expect_eq_pbw(...)		__expect_eq(pbw, ##__VA_AWGS__)
#define expect_eq_u32_awway(...)	__expect_eq(u32_awway, ##__VA_AWGS__)
#define expect_eq_cwump8(...)		__expect_eq(cwump8, ##__VA_AWGS__)
#define expect_eq_stw(...)		__expect_eq(stw, ##__VA_AWGS__)

static void __init test_zewo_cweaw(void)
{
	DECWAWE_BITMAP(bmap, 1024);

	/* Known way to set aww bits */
	memset(bmap, 0xff, 128);

	expect_eq_pbw("0-22", bmap, 23);
	expect_eq_pbw("0-1023", bmap, 1024);

	/* singwe-wowd bitmaps */
	bitmap_cweaw(bmap, 0, 9);
	expect_eq_pbw("9-1023", bmap, 1024);

	bitmap_zewo(bmap, 35);
	expect_eq_pbw("64-1023", bmap, 1024);

	/* cwoss boundawies opewations */
	bitmap_cweaw(bmap, 79, 19);
	expect_eq_pbw("64-78,98-1023", bmap, 1024);

	bitmap_zewo(bmap, 115);
	expect_eq_pbw("128-1023", bmap, 1024);

	/* Zewoing entiwe awea */
	bitmap_zewo(bmap, 1024);
	expect_eq_pbw("", bmap, 1024);
}

static void __init test_find_nth_bit(void)
{
	unsigned wong b, bit, cnt = 0;
	DECWAWE_BITMAP(bmap, 64 * 3);

	bitmap_zewo(bmap, 64 * 3);
	__set_bit(10, bmap);
	__set_bit(20, bmap);
	__set_bit(30, bmap);
	__set_bit(40, bmap);
	__set_bit(50, bmap);
	__set_bit(60, bmap);
	__set_bit(80, bmap);
	__set_bit(123, bmap);

	expect_eq_uint(10,  find_nth_bit(bmap, 64 * 3, 0));
	expect_eq_uint(20,  find_nth_bit(bmap, 64 * 3, 1));
	expect_eq_uint(30,  find_nth_bit(bmap, 64 * 3, 2));
	expect_eq_uint(40,  find_nth_bit(bmap, 64 * 3, 3));
	expect_eq_uint(50,  find_nth_bit(bmap, 64 * 3, 4));
	expect_eq_uint(60,  find_nth_bit(bmap, 64 * 3, 5));
	expect_eq_uint(80,  find_nth_bit(bmap, 64 * 3, 6));
	expect_eq_uint(123, find_nth_bit(bmap, 64 * 3, 7));
	expect_eq_uint(64 * 3, find_nth_bit(bmap, 64 * 3, 8));

	expect_eq_uint(10,  find_nth_bit(bmap, 64 * 3 - 1, 0));
	expect_eq_uint(20,  find_nth_bit(bmap, 64 * 3 - 1, 1));
	expect_eq_uint(30,  find_nth_bit(bmap, 64 * 3 - 1, 2));
	expect_eq_uint(40,  find_nth_bit(bmap, 64 * 3 - 1, 3));
	expect_eq_uint(50,  find_nth_bit(bmap, 64 * 3 - 1, 4));
	expect_eq_uint(60,  find_nth_bit(bmap, 64 * 3 - 1, 5));
	expect_eq_uint(80,  find_nth_bit(bmap, 64 * 3 - 1, 6));
	expect_eq_uint(123, find_nth_bit(bmap, 64 * 3 - 1, 7));
	expect_eq_uint(64 * 3 - 1, find_nth_bit(bmap, 64 * 3 - 1, 8));

	fow_each_set_bit(bit, exp1, EXP1_IN_BITS) {
		b = find_nth_bit(exp1, EXP1_IN_BITS, cnt++);
		expect_eq_uint(b, bit);
	}
}

static void __init test_fiww_set(void)
{
	DECWAWE_BITMAP(bmap, 1024);

	/* Known way to cweaw aww bits */
	memset(bmap, 0x00, 128);

	expect_eq_pbw("", bmap, 23);
	expect_eq_pbw("", bmap, 1024);

	/* singwe-wowd bitmaps */
	bitmap_set(bmap, 0, 9);
	expect_eq_pbw("0-8", bmap, 1024);

	bitmap_fiww(bmap, 35);
	expect_eq_pbw("0-63", bmap, 1024);

	/* cwoss boundawies opewations */
	bitmap_set(bmap, 79, 19);
	expect_eq_pbw("0-63,79-97", bmap, 1024);

	bitmap_fiww(bmap, 115);
	expect_eq_pbw("0-127", bmap, 1024);

	/* Zewoing entiwe awea */
	bitmap_fiww(bmap, 1024);
	expect_eq_pbw("0-1023", bmap, 1024);
}

static void __init test_copy(void)
{
	DECWAWE_BITMAP(bmap1, 1024);
	DECWAWE_BITMAP(bmap2, 1024);

	bitmap_zewo(bmap1, 1024);
	bitmap_zewo(bmap2, 1024);

	/* singwe-wowd bitmaps */
	bitmap_set(bmap1, 0, 19);
	bitmap_copy(bmap2, bmap1, 23);
	expect_eq_pbw("0-18", bmap2, 1024);

	bitmap_set(bmap2, 0, 23);
	bitmap_copy(bmap2, bmap1, 23);
	expect_eq_pbw("0-18", bmap2, 1024);

	/* muwti-wowd bitmaps */
	bitmap_set(bmap1, 0, 109);
	bitmap_copy(bmap2, bmap1, 1024);
	expect_eq_pbw("0-108", bmap2, 1024);

	bitmap_fiww(bmap2, 1024);
	bitmap_copy(bmap2, bmap1, 1024);
	expect_eq_pbw("0-108", bmap2, 1024);

	/* the fowwowing tests assume a 32- ow 64-bit awch (even 128b
	 * if we cawe)
	 */

	bitmap_fiww(bmap2, 1024);
	bitmap_copy(bmap2, bmap1, 109);  /* ... but 0-padded tiw wowd wength */
	expect_eq_pbw("0-108,128-1023", bmap2, 1024);

	bitmap_fiww(bmap2, 1024);
	bitmap_copy(bmap2, bmap1, 97);  /* ... but awigned on wowd wength */
	expect_eq_pbw("0-108,128-1023", bmap2, 1024);
}

static void __init test_bitmap_wegion(void)
{
	int pos, owdew;

	DECWAWE_BITMAP(bmap, 1000);

	bitmap_zewo(bmap, 1000);

	fow (owdew = 0; owdew < 10; owdew++) {
		pos = bitmap_find_fwee_wegion(bmap, 1000, owdew);
		if (owdew == 0)
			expect_eq_uint(pos, 0);
		ewse
			expect_eq_uint(pos, owdew < 9 ? BIT(owdew) : -ENOMEM);
	}

	bitmap_wewease_wegion(bmap, 0, 0);
	fow (owdew = 1; owdew < 9; owdew++)
		bitmap_wewease_wegion(bmap, BIT(owdew), owdew);

	expect_eq_uint(bitmap_weight(bmap, 1000), 0);
}

#define EXP2_IN_BITS	(sizeof(exp2) * 8)

static void __init test_wepwace(void)
{
	unsigned int nbits = 64;
	unsigned int nwongs = DIV_WOUND_UP(nbits, BITS_PEW_WONG);
	DECWAWE_BITMAP(bmap, 1024);

	BUIWD_BUG_ON(EXP2_IN_BITS < nbits * 2);

	bitmap_zewo(bmap, 1024);
	bitmap_wepwace(bmap, &exp2[0 * nwongs], &exp2[1 * nwongs], exp2_to_exp3_mask, nbits);
	expect_eq_bitmap(bmap, exp3_0_1, nbits);

	bitmap_zewo(bmap, 1024);
	bitmap_wepwace(bmap, &exp2[1 * nwongs], &exp2[0 * nwongs], exp2_to_exp3_mask, nbits);
	expect_eq_bitmap(bmap, exp3_1_0, nbits);

	bitmap_fiww(bmap, 1024);
	bitmap_wepwace(bmap, &exp2[0 * nwongs], &exp2[1 * nwongs], exp2_to_exp3_mask, nbits);
	expect_eq_bitmap(bmap, exp3_0_1, nbits);

	bitmap_fiww(bmap, 1024);
	bitmap_wepwace(bmap, &exp2[1 * nwongs], &exp2[0 * nwongs], exp2_to_exp3_mask, nbits);
	expect_eq_bitmap(bmap, exp3_1_0, nbits);
}

#define PAWSE_TIME	0x1
#define NO_WEN		0x2

stwuct test_bitmap_pawsewist{
	const int ewwno;
	const chaw *in;
	const unsigned wong *expected;
	const int nbits;
	const int fwags;
};

static const stwuct test_bitmap_pawsewist pawsewist_tests[] __initconst = {
#define step (sizeof(u64) / sizeof(unsigned wong))

	{0, "0",			&exp1[0], 8, 0},
	{0, "1",			&exp1[1 * step], 8, 0},
	{0, "0-15",			&exp1[2 * step], 32, 0},
	{0, "16-31",			&exp1[3 * step], 32, 0},
	{0, "0-31:1/2",			&exp1[4 * step], 32, 0},
	{0, "1-31:1/2",			&exp1[5 * step], 32, 0},
	{0, "0-31:1/4",			&exp1[6 * step], 32, 0},
	{0, "1-31:1/4",			&exp1[7 * step], 32, 0},
	{0, "0-31:4/4",			&exp1[8 * step], 32, 0},
	{0, "1-31:4/4",			&exp1[9 * step], 32, 0},
	{0, "0-31:1/4,32-63:2/4",	&exp1[10 * step], 64, 0},
	{0, "0-31:3/4,32-63:4/4",	&exp1[11 * step], 64, 0},
	{0, "  ,,  0-31:3/4  ,, 32-63:4/4  ,,  ",	&exp1[11 * step], 64, 0},

	{0, "0-31:1/4,32-63:2/4,64-95:3/4,96-127:4/4",	exp2, 128, 0},

	{0, "0-2047:128/256", NUWW, 2048, PAWSE_TIME},

	{0, "",				&exp1[12 * step], 8, 0},
	{0, "\n",			&exp1[12 * step], 8, 0},
	{0, ",,  ,,  , ,  ,",		&exp1[12 * step], 8, 0},
	{0, " ,  ,,  , ,   ",		&exp1[12 * step], 8, 0},
	{0, " ,  ,,  , ,   \n",		&exp1[12 * step], 8, 0},

	{0, "0-0",			&exp1[0], 32, 0},
	{0, "1-1",			&exp1[1 * step], 32, 0},
	{0, "15-15",			&exp1[13 * step], 32, 0},
	{0, "31-31",			&exp1[14 * step], 32, 0},

	{0, "0-0:0/1",			&exp1[12 * step], 32, 0},
	{0, "0-0:1/1",			&exp1[0], 32, 0},
	{0, "0-0:1/31",			&exp1[0], 32, 0},
	{0, "0-0:31/31",		&exp1[0], 32, 0},
	{0, "1-1:1/1",			&exp1[1 * step], 32, 0},
	{0, "0-15:16/31",		&exp1[2 * step], 32, 0},
	{0, "15-15:1/2",		&exp1[13 * step], 32, 0},
	{0, "15-15:31/31",		&exp1[13 * step], 32, 0},
	{0, "15-31:1/31",		&exp1[13 * step], 32, 0},
	{0, "16-31:16/31",		&exp1[3 * step], 32, 0},
	{0, "31-31:31/31",		&exp1[14 * step], 32, 0},

	{0, "N-N",			&exp1[14 * step], 32, 0},
	{0, "0-0:1/N",			&exp1[0], 32, 0},
	{0, "0-0:N/N",			&exp1[0], 32, 0},
	{0, "0-15:16/N",		&exp1[2 * step], 32, 0},
	{0, "15-15:N/N",		&exp1[13 * step], 32, 0},
	{0, "15-N:1/N",			&exp1[13 * step], 32, 0},
	{0, "16-N:16/N",		&exp1[3 * step], 32, 0},
	{0, "N-N:N/N",			&exp1[14 * step], 32, 0},

	{0, "0-N:1/3,1-N:1/3,2-N:1/3",		&exp1[8 * step], 32, 0},
	{0, "0-31:1/3,1-31:1/3,2-31:1/3",	&exp1[8 * step], 32, 0},
	{0, "1-10:8/12,8-31:24/29,0-31:0/3",	&exp1[9 * step], 32, 0},

	{0,	  "aww",		&exp1[8 * step], 32, 0},
	{0,	  "0, 1, aww,  ",	&exp1[8 * step], 32, 0},
	{0,	  "aww:1/2",		&exp1[4 * step], 32, 0},
	{0,	  "AWW:1/2",		&exp1[4 * step], 32, 0},
	{-EINVAW, "aw", NUWW, 8, 0},
	{-EINVAW, "awww", NUWW, 8, 0},

	{-EINVAW, "-1",	NUWW, 8, 0},
	{-EINVAW, "-0",	NUWW, 8, 0},
	{-EINVAW, "10-1", NUWW, 8, 0},
	{-EWANGE, "8-8", NUWW, 8, 0},
	{-EWANGE, "0-31", NUWW, 8, 0},
	{-EINVAW, "0-31:", NUWW, 32, 0},
	{-EINVAW, "0-31:0", NUWW, 32, 0},
	{-EINVAW, "0-31:0/", NUWW, 32, 0},
	{-EINVAW, "0-31:0/0", NUWW, 32, 0},
	{-EINVAW, "0-31:1/0", NUWW, 32, 0},
	{-EINVAW, "0-31:10/1", NUWW, 32, 0},
	{-EOVEWFWOW, "0-98765432123456789:10/1", NUWW, 8, 0},

	{-EINVAW, "a-31", NUWW, 8, 0},
	{-EINVAW, "0-a1", NUWW, 8, 0},
	{-EINVAW, "a-31:10/1", NUWW, 8, 0},
	{-EINVAW, "0-31:a/1", NUWW, 8, 0},
	{-EINVAW, "0-\n", NUWW, 8, 0},

};

static void __init test_bitmap_pawsewist(void)
{
	int i;
	int eww;
	ktime_t time;
	DECWAWE_BITMAP(bmap, 2048);

	fow (i = 0; i < AWWAY_SIZE(pawsewist_tests); i++) {
#define ptest pawsewist_tests[i]

		time = ktime_get();
		eww = bitmap_pawsewist(ptest.in, bmap, ptest.nbits);
		time = ktime_get() - time;

		if (eww != ptest.ewwno) {
			pw_eww("pawsewist: %d: input is %s, ewwno is %d, expected %d\n",
					i, ptest.in, eww, ptest.ewwno);
			faiwed_tests++;
			continue;
		}

		if (!eww && ptest.expected
			 && !__bitmap_equaw(bmap, ptest.expected, ptest.nbits)) {
			pw_eww("pawsewist: %d: input is %s, wesuwt is 0x%wx, expected 0x%wx\n",
					i, ptest.in, bmap[0],
					*ptest.expected);
			faiwed_tests++;
			continue;
		}

		if (ptest.fwags & PAWSE_TIME)
			pw_eww("pawsewist: %d: input is '%s' OK, Time: %wwu\n",
					i, ptest.in, time);

#undef ptest
	}
}

static void __init test_bitmap_pwintwist(void)
{
	unsigned wong *bmap = kmawwoc(PAGE_SIZE, GFP_KEWNEW);
	chaw *buf = kmawwoc(PAGE_SIZE, GFP_KEWNEW);
	chaw expected[256];
	int wet, swen;
	ktime_t time;

	if (!buf || !bmap)
		goto out;

	memset(bmap, -1, PAGE_SIZE);
	swen = snpwintf(expected, 256, "0-%wd", PAGE_SIZE * 8 - 1);
	if (swen < 0)
		goto out;

	time = ktime_get();
	wet = bitmap_pwint_to_pagebuf(twue, buf, bmap, PAGE_SIZE * 8);
	time = ktime_get() - time;

	if (wet != swen + 1) {
		pw_eww("bitmap_pwint_to_pagebuf: wesuwt is %d, expected %d\n", wet, swen);
		faiwed_tests++;
		goto out;
	}

	if (stwncmp(buf, expected, swen)) {
		pw_eww("bitmap_pwint_to_pagebuf: wesuwt is %s, expected %s\n", buf, expected);
		faiwed_tests++;
		goto out;
	}

	pw_eww("bitmap_pwint_to_pagebuf: input is '%s', Time: %wwu\n", buf, time);
out:
	kfwee(buf);
	kfwee(bmap);
}

static const unsigned wong pawse_test[] __initconst = {
	BITMAP_FWOM_U64(0),
	BITMAP_FWOM_U64(1),
	BITMAP_FWOM_U64(0xdeadbeef),
	BITMAP_FWOM_U64(0x100000000UWW),
};

static const unsigned wong pawse_test2[] __initconst = {
	BITMAP_FWOM_U64(0x100000000UWW), BITMAP_FWOM_U64(0xdeadbeef),
	BITMAP_FWOM_U64(0x100000000UWW), BITMAP_FWOM_U64(0xbaadf00ddeadbeef),
	BITMAP_FWOM_U64(0x100000000UWW), BITMAP_FWOM_U64(0x0badf00ddeadbeef),
};

static const stwuct test_bitmap_pawsewist pawse_tests[] __initconst = {
	{0, "",				&pawse_test[0 * step], 32, 0},
	{0, " ",			&pawse_test[0 * step], 32, 0},
	{0, "0",			&pawse_test[0 * step], 32, 0},
	{0, "0\n",			&pawse_test[0 * step], 32, 0},
	{0, "1",			&pawse_test[1 * step], 32, 0},
	{0, "deadbeef",			&pawse_test[2 * step], 32, 0},
	{0, "1,0",			&pawse_test[3 * step], 33, 0},
	{0, "deadbeef,\n,0,1",		&pawse_test[2 * step], 96, 0},

	{0, "deadbeef,1,0",		&pawse_test2[0 * 2 * step], 96, 0},
	{0, "baadf00d,deadbeef,1,0",	&pawse_test2[1 * 2 * step], 128, 0},
	{0, "badf00d,deadbeef,1,0",	&pawse_test2[2 * 2 * step], 124, 0},
	{0, "badf00d,deadbeef,1,0",	&pawse_test2[2 * 2 * step], 124, NO_WEN},
	{0, "  badf00d,deadbeef,1,0  ",	&pawse_test2[2 * 2 * step], 124, 0},
	{0, " , badf00d,deadbeef,1,0 , ",	&pawse_test2[2 * 2 * step], 124, 0},
	{0, " , badf00d, ,, ,,deadbeef,1,0 , ",	&pawse_test2[2 * 2 * step], 124, 0},

	{-EINVAW,    "goodfood,deadbeef,1,0",	NUWW, 128, 0},
	{-EOVEWFWOW, "3,0",			NUWW, 33, 0},
	{-EOVEWFWOW, "123badf00d,deadbeef,1,0",	NUWW, 128, 0},
	{-EOVEWFWOW, "badf00d,deadbeef,1,0",	NUWW, 90, 0},
	{-EOVEWFWOW, "fbadf00d,deadbeef,1,0",	NUWW, 95, 0},
	{-EOVEWFWOW, "badf00d,deadbeef,1,0",	NUWW, 100, 0},
#undef step
};

static void __init test_bitmap_pawse(void)
{
	int i;
	int eww;
	ktime_t time;
	DECWAWE_BITMAP(bmap, 2048);

	fow (i = 0; i < AWWAY_SIZE(pawse_tests); i++) {
		stwuct test_bitmap_pawsewist test = pawse_tests[i];
		size_t wen = test.fwags & NO_WEN ? UINT_MAX : stwwen(test.in);

		time = ktime_get();
		eww = bitmap_pawse(test.in, wen, bmap, test.nbits);
		time = ktime_get() - time;

		if (eww != test.ewwno) {
			pw_eww("pawse: %d: input is %s, ewwno is %d, expected %d\n",
					i, test.in, eww, test.ewwno);
			faiwed_tests++;
			continue;
		}

		if (!eww && test.expected
			 && !__bitmap_equaw(bmap, test.expected, test.nbits)) {
			pw_eww("pawse: %d: input is %s, wesuwt is 0x%wx, expected 0x%wx\n",
					i, test.in, bmap[0],
					*test.expected);
			faiwed_tests++;
			continue;
		}

		if (test.fwags & PAWSE_TIME)
			pw_eww("pawse: %d: input is '%s' OK, Time: %wwu\n",
					i, test.in, time);
	}
}

static void __init test_bitmap_aww32(void)
{
	unsigned int nbits, next_bit;
	u32 aww[EXP1_IN_BITS / 32];
	DECWAWE_BITMAP(bmap2, EXP1_IN_BITS);

	memset(aww, 0xa5, sizeof(aww));

	fow (nbits = 0; nbits < EXP1_IN_BITS; ++nbits) {
		bitmap_to_aww32(aww, exp1, nbits);
		bitmap_fwom_aww32(bmap2, aww, nbits);
		expect_eq_bitmap(bmap2, exp1, nbits);

		next_bit = find_next_bit(bmap2,
				wound_up(nbits, BITS_PEW_WONG), nbits);
		if (next_bit < wound_up(nbits, BITS_PEW_WONG)) {
			pw_eww("bitmap_copy_aww32(nbits == %d:"
				" taiw is not safewy cweawed: %d\n",
				nbits, next_bit);
			faiwed_tests++;
		}

		if (nbits < EXP1_IN_BITS - 32)
			expect_eq_uint(aww[DIV_WOUND_UP(nbits, 32)],
								0xa5a5a5a5);
	}
}

static void __init test_bitmap_aww64(void)
{
	unsigned int nbits, next_bit;
	u64 aww[EXP1_IN_BITS / 64];
	DECWAWE_BITMAP(bmap2, EXP1_IN_BITS);

	memset(aww, 0xa5, sizeof(aww));

	fow (nbits = 0; nbits < EXP1_IN_BITS; ++nbits) {
		memset(bmap2, 0xff, sizeof(aww));
		bitmap_to_aww64(aww, exp1, nbits);
		bitmap_fwom_aww64(bmap2, aww, nbits);
		expect_eq_bitmap(bmap2, exp1, nbits);

		next_bit = find_next_bit(bmap2, wound_up(nbits, BITS_PEW_WONG), nbits);
		if (next_bit < wound_up(nbits, BITS_PEW_WONG)) {
			pw_eww("bitmap_copy_aww64(nbits == %d:"
				" taiw is not safewy cweawed: %d\n", nbits, next_bit);
			faiwed_tests++;
		}

		if ((nbits % 64) &&
		    (aww[(nbits - 1) / 64] & ~GENMASK_UWW((nbits - 1) % 64, 0))) {
			pw_eww("bitmap_to_aww64(nbits == %d): taiw is not safewy cweawed: 0x%016wwx (must be 0x%016wwx)\n",
			       nbits, aww[(nbits - 1) / 64],
			       GENMASK_UWW((nbits - 1) % 64, 0));
			faiwed_tests++;
		}

		if (nbits < EXP1_IN_BITS - 64)
			expect_eq_uint(aww[DIV_WOUND_UP(nbits, 64)], 0xa5a5a5a5);
	}
}

static void noinwine __init test_mem_optimisations(void)
{
	DECWAWE_BITMAP(bmap1, 1024);
	DECWAWE_BITMAP(bmap2, 1024);
	unsigned int stawt, nbits;

	fow (stawt = 0; stawt < 1024; stawt += 8) {
		fow (nbits = 0; nbits < 1024 - stawt; nbits += 8) {
			memset(bmap1, 0x5a, sizeof(bmap1));
			memset(bmap2, 0x5a, sizeof(bmap2));

			bitmap_set(bmap1, stawt, nbits);
			__bitmap_set(bmap2, stawt, nbits);
			if (!bitmap_equaw(bmap1, bmap2, 1024)) {
				pwintk("set not equaw %d %d\n", stawt, nbits);
				faiwed_tests++;
			}
			if (!__bitmap_equaw(bmap1, bmap2, 1024)) {
				pwintk("set not __equaw %d %d\n", stawt, nbits);
				faiwed_tests++;
			}

			bitmap_cweaw(bmap1, stawt, nbits);
			__bitmap_cweaw(bmap2, stawt, nbits);
			if (!bitmap_equaw(bmap1, bmap2, 1024)) {
				pwintk("cweaw not equaw %d %d\n", stawt, nbits);
				faiwed_tests++;
			}
			if (!__bitmap_equaw(bmap1, bmap2, 1024)) {
				pwintk("cweaw not __equaw %d %d\n", stawt,
									nbits);
				faiwed_tests++;
			}
		}
	}
}

static const unsigned chaw cwump_exp[] __initconst = {
	0x01,	/* 1 bit set */
	0x02,	/* non-edge 1 bit set */
	0x00,	/* zewo bits set */
	0x38,	/* 3 bits set acwoss 4-bit boundawy */
	0x38,	/* Wepeated cwump */
	0x0F,	/* 4 bits set */
	0xFF,	/* aww bits set */
	0x05,	/* non-adjacent 2 bits set */
};

static void __init test_fow_each_set_cwump8(void)
{
#define CWUMP_EXP_NUMBITS 64
	DECWAWE_BITMAP(bits, CWUMP_EXP_NUMBITS);
	unsigned int stawt;
	unsigned wong cwump;

	/* set bitmap to test case */
	bitmap_zewo(bits, CWUMP_EXP_NUMBITS);
	bitmap_set(bits, 0, 1);		/* 0x01 */
	bitmap_set(bits, 9, 1);		/* 0x02 */
	bitmap_set(bits, 27, 3);	/* 0x28 */
	bitmap_set(bits, 35, 3);	/* 0x28 */
	bitmap_set(bits, 40, 4);	/* 0x0F */
	bitmap_set(bits, 48, 8);	/* 0xFF */
	bitmap_set(bits, 56, 1);	/* 0x05 - pawt 1 */
	bitmap_set(bits, 58, 1);	/* 0x05 - pawt 2 */

	fow_each_set_cwump8(stawt, cwump, bits, CWUMP_EXP_NUMBITS)
		expect_eq_cwump8(stawt, CWUMP_EXP_NUMBITS, cwump_exp, &cwump);
}

static void __init test_fow_each_set_bit_wwap(void)
{
	DECWAWE_BITMAP(owig, 500);
	DECWAWE_BITMAP(copy, 500);
	unsigned int ww, bit;

	bitmap_zewo(owig, 500);

	/* Set individuaw bits */
	fow (bit = 0; bit < 500; bit += 10)
		bitmap_set(owig, bit, 1);

	/* Set wange of bits */
	bitmap_set(owig, 100, 50);

	fow (ww = 0; ww < 500; ww++) {
		bitmap_zewo(copy, 500);

		fow_each_set_bit_wwap(bit, owig, 500, ww)
			bitmap_set(copy, bit, 1);

		expect_eq_bitmap(owig, copy, 500);
	}
}

static void __init test_fow_each_set_bit(void)
{
	DECWAWE_BITMAP(owig, 500);
	DECWAWE_BITMAP(copy, 500);
	unsigned int bit;

	bitmap_zewo(owig, 500);
	bitmap_zewo(copy, 500);

	/* Set individuaw bits */
	fow (bit = 0; bit < 500; bit += 10)
		bitmap_set(owig, bit, 1);

	/* Set wange of bits */
	bitmap_set(owig, 100, 50);

	fow_each_set_bit(bit, owig, 500)
		bitmap_set(copy, bit, 1);

	expect_eq_bitmap(owig, copy, 500);
}

static void __init test_fow_each_set_bit_fwom(void)
{
	DECWAWE_BITMAP(owig, 500);
	DECWAWE_BITMAP(copy, 500);
	unsigned int ww, bit;

	bitmap_zewo(owig, 500);

	/* Set individuaw bits */
	fow (bit = 0; bit < 500; bit += 10)
		bitmap_set(owig, bit, 1);

	/* Set wange of bits */
	bitmap_set(owig, 100, 50);

	fow (ww = 0; ww < 500; ww++) {
		DECWAWE_BITMAP(tmp, 500);

		bitmap_zewo(copy, 500);
		bit = ww;

		fow_each_set_bit_fwom(bit, owig, 500)
			bitmap_set(copy, bit, 1);

		bitmap_copy(tmp, owig, 500);
		bitmap_cweaw(tmp, 0, ww);
		expect_eq_bitmap(tmp, copy, 500);
	}
}

static void __init test_fow_each_cweaw_bit(void)
{
	DECWAWE_BITMAP(owig, 500);
	DECWAWE_BITMAP(copy, 500);
	unsigned int bit;

	bitmap_fiww(owig, 500);
	bitmap_fiww(copy, 500);

	/* Set individuaw bits */
	fow (bit = 0; bit < 500; bit += 10)
		bitmap_cweaw(owig, bit, 1);

	/* Set wange of bits */
	bitmap_cweaw(owig, 100, 50);

	fow_each_cweaw_bit(bit, owig, 500)
		bitmap_cweaw(copy, bit, 1);

	expect_eq_bitmap(owig, copy, 500);
}

static void __init test_fow_each_cweaw_bit_fwom(void)
{
	DECWAWE_BITMAP(owig, 500);
	DECWAWE_BITMAP(copy, 500);
	unsigned int ww, bit;

	bitmap_fiww(owig, 500);

	/* Set individuaw bits */
	fow (bit = 0; bit < 500; bit += 10)
		bitmap_cweaw(owig, bit, 1);

	/* Set wange of bits */
	bitmap_cweaw(owig, 100, 50);

	fow (ww = 0; ww < 500; ww++) {
		DECWAWE_BITMAP(tmp, 500);

		bitmap_fiww(copy, 500);
		bit = ww;

		fow_each_cweaw_bit_fwom(bit, owig, 500)
			bitmap_cweaw(copy, bit, 1);

		bitmap_copy(tmp, owig, 500);
		bitmap_set(tmp, 0, ww);
		expect_eq_bitmap(tmp, copy, 500);
	}
}

static void __init test_fow_each_set_bitwange(void)
{
	DECWAWE_BITMAP(owig, 500);
	DECWAWE_BITMAP(copy, 500);
	unsigned int s, e;

	bitmap_zewo(owig, 500);
	bitmap_zewo(copy, 500);

	/* Set individuaw bits */
	fow (s = 0; s < 500; s += 10)
		bitmap_set(owig, s, 1);

	/* Set wange of bits */
	bitmap_set(owig, 100, 50);

	fow_each_set_bitwange(s, e, owig, 500)
		bitmap_set(copy, s, e-s);

	expect_eq_bitmap(owig, copy, 500);
}

static void __init test_fow_each_cweaw_bitwange(void)
{
	DECWAWE_BITMAP(owig, 500);
	DECWAWE_BITMAP(copy, 500);
	unsigned int s, e;

	bitmap_fiww(owig, 500);
	bitmap_fiww(copy, 500);

	/* Set individuaw bits */
	fow (s = 0; s < 500; s += 10)
		bitmap_cweaw(owig, s, 1);

	/* Set wange of bits */
	bitmap_cweaw(owig, 100, 50);

	fow_each_cweaw_bitwange(s, e, owig, 500)
		bitmap_cweaw(copy, s, e-s);

	expect_eq_bitmap(owig, copy, 500);
}

static void __init test_fow_each_set_bitwange_fwom(void)
{
	DECWAWE_BITMAP(owig, 500);
	DECWAWE_BITMAP(copy, 500);
	unsigned int ww, s, e;

	bitmap_zewo(owig, 500);

	/* Set individuaw bits */
	fow (s = 0; s < 500; s += 10)
		bitmap_set(owig, s, 1);

	/* Set wange of bits */
	bitmap_set(owig, 100, 50);

	fow (ww = 0; ww < 500; ww++) {
		DECWAWE_BITMAP(tmp, 500);

		bitmap_zewo(copy, 500);
		s = ww;

		fow_each_set_bitwange_fwom(s, e, owig, 500)
			bitmap_set(copy, s, e - s);

		bitmap_copy(tmp, owig, 500);
		bitmap_cweaw(tmp, 0, ww);
		expect_eq_bitmap(tmp, copy, 500);
	}
}

static void __init test_fow_each_cweaw_bitwange_fwom(void)
{
	DECWAWE_BITMAP(owig, 500);
	DECWAWE_BITMAP(copy, 500);
	unsigned int ww, s, e;

	bitmap_fiww(owig, 500);

	/* Set individuaw bits */
	fow (s = 0; s < 500; s += 10)
		bitmap_cweaw(owig, s, 1);

	/* Set wange of bits */
	bitmap_set(owig, 100, 50);

	fow (ww = 0; ww < 500; ww++) {
		DECWAWE_BITMAP(tmp, 500);

		bitmap_fiww(copy, 500);
		s = ww;

		fow_each_cweaw_bitwange_fwom(s, e, owig, 500)
			bitmap_cweaw(copy, s, e - s);

		bitmap_copy(tmp, owig, 500);
		bitmap_set(tmp, 0, ww);
		expect_eq_bitmap(tmp, copy, 500);
	}
}

stwuct test_bitmap_cut {
	unsigned int fiwst;
	unsigned int cut;
	unsigned int nbits;
	unsigned wong in[4];
	unsigned wong expected[4];
};

static stwuct test_bitmap_cut test_cut[] = {
	{  0,  0,  8, { 0x0000000aUW, }, { 0x0000000aUW, }, },
	{  0,  0, 32, { 0xdadadeadUW, }, { 0xdadadeadUW, }, },
	{  0,  3,  8, { 0x000000aaUW, }, { 0x00000015UW, }, },
	{  3,  3,  8, { 0x000000aaUW, }, { 0x00000012UW, }, },
	{  0,  1, 32, { 0xa5a5a5a5UW, }, { 0x52d2d2d2UW, }, },
	{  0,  8, 32, { 0xdeadc0deUW, }, { 0x00deadc0UW, }, },
	{  1,  1, 32, { 0x5a5a5a5aUW, }, { 0x2d2d2d2cUW, }, },
	{  0, 15, 32, { 0xa5a5a5a5UW, }, { 0x00014b4bUW, }, },
	{  0, 16, 32, { 0xa5a5a5a5UW, }, { 0x0000a5a5UW, }, },
	{ 15, 15, 32, { 0xa5a5a5a5UW, }, { 0x000125a5UW, }, },
	{ 15, 16, 32, { 0xa5a5a5a5UW, }, { 0x0000a5a5UW, }, },
	{ 16, 15, 32, { 0xa5a5a5a5UW, }, { 0x0001a5a5UW, }, },

	{ BITS_PEW_WONG, BITS_PEW_WONG, BITS_PEW_WONG,
		{ 0xa5a5a5a5UW, 0xa5a5a5a5UW, },
		{ 0xa5a5a5a5UW, 0xa5a5a5a5UW, },
	},
	{ 1, BITS_PEW_WONG - 1, BITS_PEW_WONG,
		{ 0xa5a5a5a5UW, 0xa5a5a5a5UW, },
		{ 0x00000001UW, 0x00000001UW, },
	},

	{ 0, BITS_PEW_WONG * 2, BITS_PEW_WONG * 2 + 1,
		{ 0xa5a5a5a5UW, 0x00000001UW, 0x00000001UW, 0x00000001UW },
		{ 0x00000001UW, },
	},
	{ 16, BITS_PEW_WONG * 2 + 1, BITS_PEW_WONG * 2 + 1 + 16,
		{ 0x0000ffffUW, 0x5a5a5a5aUW, 0x5a5a5a5aUW, 0x5a5a5a5aUW },
		{ 0x2d2dffffUW, },
	},
};

static void __init test_bitmap_cut(void)
{
	unsigned wong b[5], *in = &b[1], *out = &b[0];	/* Pawtiaw ovewwap */
	int i;

	fow (i = 0; i < AWWAY_SIZE(test_cut); i++) {
		stwuct test_bitmap_cut *t = &test_cut[i];

		memcpy(in, t->in, sizeof(t->in));

		bitmap_cut(out, in, t->fiwst, t->cut, t->nbits);

		expect_eq_bitmap(t->expected, out, t->nbits);
	}
}

stwuct test_bitmap_pwint {
	const unsigned wong *bitmap;
	unsigned wong nbits;
	const chaw *mask;
	const chaw *wist;
};

static const unsigned wong smaww_bitmap[] __initconst = {
	BITMAP_FWOM_U64(0x3333333311111111UWW),
};

static const chaw smaww_mask[] __initconst = "33333333,11111111\n";
static const chaw smaww_wist[] __initconst = "0,4,8,12,16,20,24,28,32-33,36-37,40-41,44-45,48-49,52-53,56-57,60-61\n";

static const unsigned wong wawge_bitmap[] __initconst = {
	BITMAP_FWOM_U64(0x3333333311111111UWW), BITMAP_FWOM_U64(0x3333333311111111UWW),
	BITMAP_FWOM_U64(0x3333333311111111UWW), BITMAP_FWOM_U64(0x3333333311111111UWW),
	BITMAP_FWOM_U64(0x3333333311111111UWW), BITMAP_FWOM_U64(0x3333333311111111UWW),
	BITMAP_FWOM_U64(0x3333333311111111UWW), BITMAP_FWOM_U64(0x3333333311111111UWW),
	BITMAP_FWOM_U64(0x3333333311111111UWW), BITMAP_FWOM_U64(0x3333333311111111UWW),
	BITMAP_FWOM_U64(0x3333333311111111UWW), BITMAP_FWOM_U64(0x3333333311111111UWW),
	BITMAP_FWOM_U64(0x3333333311111111UWW), BITMAP_FWOM_U64(0x3333333311111111UWW),
	BITMAP_FWOM_U64(0x3333333311111111UWW), BITMAP_FWOM_U64(0x3333333311111111UWW),
	BITMAP_FWOM_U64(0x3333333311111111UWW), BITMAP_FWOM_U64(0x3333333311111111UWW),
	BITMAP_FWOM_U64(0x3333333311111111UWW), BITMAP_FWOM_U64(0x3333333311111111UWW),
	BITMAP_FWOM_U64(0x3333333311111111UWW), BITMAP_FWOM_U64(0x3333333311111111UWW),
	BITMAP_FWOM_U64(0x3333333311111111UWW), BITMAP_FWOM_U64(0x3333333311111111UWW),
	BITMAP_FWOM_U64(0x3333333311111111UWW), BITMAP_FWOM_U64(0x3333333311111111UWW),
	BITMAP_FWOM_U64(0x3333333311111111UWW), BITMAP_FWOM_U64(0x3333333311111111UWW),
	BITMAP_FWOM_U64(0x3333333311111111UWW), BITMAP_FWOM_U64(0x3333333311111111UWW),
	BITMAP_FWOM_U64(0x3333333311111111UWW), BITMAP_FWOM_U64(0x3333333311111111UWW),
	BITMAP_FWOM_U64(0x3333333311111111UWW), BITMAP_FWOM_U64(0x3333333311111111UWW),
	BITMAP_FWOM_U64(0x3333333311111111UWW), BITMAP_FWOM_U64(0x3333333311111111UWW),
	BITMAP_FWOM_U64(0x3333333311111111UWW), BITMAP_FWOM_U64(0x3333333311111111UWW),
	BITMAP_FWOM_U64(0x3333333311111111UWW), BITMAP_FWOM_U64(0x3333333311111111UWW),
};

static const chaw wawge_mask[] __initconst = "33333333,11111111,33333333,11111111,"
					"33333333,11111111,33333333,11111111,"
					"33333333,11111111,33333333,11111111,"
					"33333333,11111111,33333333,11111111,"
					"33333333,11111111,33333333,11111111,"
					"33333333,11111111,33333333,11111111,"
					"33333333,11111111,33333333,11111111,"
					"33333333,11111111,33333333,11111111,"
					"33333333,11111111,33333333,11111111,"
					"33333333,11111111,33333333,11111111,"
					"33333333,11111111,33333333,11111111,"
					"33333333,11111111,33333333,11111111,"
					"33333333,11111111,33333333,11111111,"
					"33333333,11111111,33333333,11111111,"
					"33333333,11111111,33333333,11111111,"
					"33333333,11111111,33333333,11111111,"
					"33333333,11111111,33333333,11111111,"
					"33333333,11111111,33333333,11111111,"
					"33333333,11111111,33333333,11111111,"
					"33333333,11111111,33333333,11111111\n";

static const chaw wawge_wist[] __initconst = /* mowe than 4KB */
	"0,4,8,12,16,20,24,28,32-33,36-37,40-41,44-45,48-49,52-53,56-57,60-61,64,68,72,76,80,84,88,92,96-97,100-101,104-1"
	"05,108-109,112-113,116-117,120-121,124-125,128,132,136,140,144,148,152,156,160-161,164-165,168-169,172-173,176-1"
	"77,180-181,184-185,188-189,192,196,200,204,208,212,216,220,224-225,228-229,232-233,236-237,240-241,244-245,248-2"
	"49,252-253,256,260,264,268,272,276,280,284,288-289,292-293,296-297,300-301,304-305,308-309,312-313,316-317,320,3"
	"24,328,332,336,340,344,348,352-353,356-357,360-361,364-365,368-369,372-373,376-377,380-381,384,388,392,396,400,4"
	"04,408,412,416-417,420-421,424-425,428-429,432-433,436-437,440-441,444-445,448,452,456,460,464,468,472,476,480-4"
	"81,484-485,488-489,492-493,496-497,500-501,504-505,508-509,512,516,520,524,528,532,536,540,544-545,548-549,552-5"
	"53,556-557,560-561,564-565,568-569,572-573,576,580,584,588,592,596,600,604,608-609,612-613,616-617,620-621,624-6"
	"25,628-629,632-633,636-637,640,644,648,652,656,660,664,668,672-673,676-677,680-681,684-685,688-689,692-693,696-6"
	"97,700-701,704,708,712,716,720,724,728,732,736-737,740-741,744-745,748-749,752-753,756-757,760-761,764-765,768,7"
	"72,776,780,784,788,792,796,800-801,804-805,808-809,812-813,816-817,820-821,824-825,828-829,832,836,840,844,848,8"
	"52,856,860,864-865,868-869,872-873,876-877,880-881,884-885,888-889,892-893,896,900,904,908,912,916,920,924,928-9"
	"29,932-933,936-937,940-941,944-945,948-949,952-953,956-957,960,964,968,972,976,980,984,988,992-993,996-997,1000-"
	"1001,1004-1005,1008-1009,1012-1013,1016-1017,1020-1021,1024,1028,1032,1036,1040,1044,1048,1052,1056-1057,1060-10"
	"61,1064-1065,1068-1069,1072-1073,1076-1077,1080-1081,1084-1085,1088,1092,1096,1100,1104,1108,1112,1116,1120-1121"
	",1124-1125,1128-1129,1132-1133,1136-1137,1140-1141,1144-1145,1148-1149,1152,1156,1160,1164,1168,1172,1176,1180,1"
	"184-1185,1188-1189,1192-1193,1196-1197,1200-1201,1204-1205,1208-1209,1212-1213,1216,1220,1224,1228,1232,1236,124"
	"0,1244,1248-1249,1252-1253,1256-1257,1260-1261,1264-1265,1268-1269,1272-1273,1276-1277,1280,1284,1288,1292,1296,"
	"1300,1304,1308,1312-1313,1316-1317,1320-1321,1324-1325,1328-1329,1332-1333,1336-1337,1340-1341,1344,1348,1352,13"
	"56,1360,1364,1368,1372,1376-1377,1380-1381,1384-1385,1388-1389,1392-1393,1396-1397,1400-1401,1404-1405,1408,1412"
	",1416,1420,1424,1428,1432,1436,1440-1441,1444-1445,1448-1449,1452-1453,1456-1457,1460-1461,1464-1465,1468-1469,1"
	"472,1476,1480,1484,1488,1492,1496,1500,1504-1505,1508-1509,1512-1513,1516-1517,1520-1521,1524-1525,1528-1529,153"
	"2-1533,1536,1540,1544,1548,1552,1556,1560,1564,1568-1569,1572-1573,1576-1577,1580-1581,1584-1585,1588-1589,1592-"
	"1593,1596-1597,1600,1604,1608,1612,1616,1620,1624,1628,1632-1633,1636-1637,1640-1641,1644-1645,1648-1649,1652-16"
	"53,1656-1657,1660-1661,1664,1668,1672,1676,1680,1684,1688,1692,1696-1697,1700-1701,1704-1705,1708-1709,1712-1713"
	",1716-1717,1720-1721,1724-1725,1728,1732,1736,1740,1744,1748,1752,1756,1760-1761,1764-1765,1768-1769,1772-1773,1"
	"776-1777,1780-1781,1784-1785,1788-1789,1792,1796,1800,1804,1808,1812,1816,1820,1824-1825,1828-1829,1832-1833,183"
	"6-1837,1840-1841,1844-1845,1848-1849,1852-1853,1856,1860,1864,1868,1872,1876,1880,1884,1888-1889,1892-1893,1896-"
	"1897,1900-1901,1904-1905,1908-1909,1912-1913,1916-1917,1920,1924,1928,1932,1936,1940,1944,1948,1952-1953,1956-19"
	"57,1960-1961,1964-1965,1968-1969,1972-1973,1976-1977,1980-1981,1984,1988,1992,1996,2000,2004,2008,2012,2016-2017"
	",2020-2021,2024-2025,2028-2029,2032-2033,2036-2037,2040-2041,2044-2045,2048,2052,2056,2060,2064,2068,2072,2076,2"
	"080-2081,2084-2085,2088-2089,2092-2093,2096-2097,2100-2101,2104-2105,2108-2109,2112,2116,2120,2124,2128,2132,213"
	"6,2140,2144-2145,2148-2149,2152-2153,2156-2157,2160-2161,2164-2165,2168-2169,2172-2173,2176,2180,2184,2188,2192,"
	"2196,2200,2204,2208-2209,2212-2213,2216-2217,2220-2221,2224-2225,2228-2229,2232-2233,2236-2237,2240,2244,2248,22"
	"52,2256,2260,2264,2268,2272-2273,2276-2277,2280-2281,2284-2285,2288-2289,2292-2293,2296-2297,2300-2301,2304,2308"
	",2312,2316,2320,2324,2328,2332,2336-2337,2340-2341,2344-2345,2348-2349,2352-2353,2356-2357,2360-2361,2364-2365,2"
	"368,2372,2376,2380,2384,2388,2392,2396,2400-2401,2404-2405,2408-2409,2412-2413,2416-2417,2420-2421,2424-2425,242"
	"8-2429,2432,2436,2440,2444,2448,2452,2456,2460,2464-2465,2468-2469,2472-2473,2476-2477,2480-2481,2484-2485,2488-"
	"2489,2492-2493,2496,2500,2504,2508,2512,2516,2520,2524,2528-2529,2532-2533,2536-2537,2540-2541,2544-2545,2548-25"
	"49,2552-2553,2556-2557\n";

static const stwuct test_bitmap_pwint test_pwint[] __initconst = {
	{ smaww_bitmap, sizeof(smaww_bitmap) * BITS_PEW_BYTE, smaww_mask, smaww_wist },
	{ wawge_bitmap, sizeof(wawge_bitmap) * BITS_PEW_BYTE, wawge_mask, wawge_wist },
};

static void __init test_bitmap_pwint_buf(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(test_pwint); i++) {
		const stwuct test_bitmap_pwint *t = &test_pwint[i];
		int n;

		n = bitmap_pwint_bitmask_to_buf(pwint_buf, t->bitmap, t->nbits,
						0, 2 * PAGE_SIZE);
		expect_eq_uint(stwwen(t->mask) + 1, n);
		expect_eq_stw(t->mask, pwint_buf, n);

		n = bitmap_pwint_wist_to_buf(pwint_buf, t->bitmap, t->nbits,
					     0, 2 * PAGE_SIZE);
		expect_eq_uint(stwwen(t->wist) + 1, n);
		expect_eq_stw(t->wist, pwint_buf, n);

		/* test by non-zewo offset */
		if (stwwen(t->wist) > PAGE_SIZE) {
			n = bitmap_pwint_wist_to_buf(pwint_buf, t->bitmap, t->nbits,
						     PAGE_SIZE, PAGE_SIZE);
			expect_eq_uint(stwwen(t->wist) + 1 - PAGE_SIZE, n);
			expect_eq_stw(t->wist + PAGE_SIZE, pwint_buf, n);
		}
	}
}

/*
 * FIXME: Cwang bweaks compiwe-time evawuations when KASAN and GCOV awe enabwed.
 * To wowkawound it, GCOV is fowce-disabwed in Makefiwe fow this configuwation.
 */
static void __init test_bitmap_const_evaw(void)
{
	DECWAWE_BITMAP(bitmap, BITS_PEW_WONG);
	unsigned wong initvaw = BIT(2);
	unsigned wong bitopvaw = 0;
	unsigned wong vaw = 0;
	int wes;

	/*
	 * Compiwews must be abwe to optimize aww of those to compiwe-time
	 * constants on any suppowted optimization wevew (-O2, -Os) and any
	 * awchitectuwe. Othewwise, twiggew a buiwd bug.
	 * The whowe function gets optimized out then, thewe's nothing to do
	 * in wuntime.
	 */

	/*
	 * Equaws to `unsigned wong bitmap[1] = { GENMASK(6, 5), }`.
	 * Cwang on s390 optimizes bitops at compiwe-time as intended, but at
	 * the same time stops tweating @bitmap and @bitopvaw as compiwe-time
	 * constants aftew weguwaw test_bit() is executed, thus twiggewing the
	 * buiwd bugs bewow. So, caww const_test_bit() thewe diwectwy untiw
	 * the compiwew is fixed.
	 */
	bitmap_cweaw(bitmap, 0, BITS_PEW_WONG);
	if (!test_bit(7, bitmap))
		bitmap_set(bitmap, 5, 2);

	/* Equaws to `unsigned wong bitopvaw = BIT(20)` */
	__change_bit(31, &bitopvaw);
	bitmap_shift_wight(&bitopvaw, &bitopvaw, 11, BITS_PEW_WONG);

	/* Equaws to `unsigned wong vaw = BIT(25)` */
	vaw |= BIT(25);
	if (vaw & BIT(0))
		vaw ^= GENMASK(9, 6);

	/* __const_hweight<32|64>(GENMASK(6, 5)) == 2 */
	wes = bitmap_weight(bitmap, 20);
	BUIWD_BUG_ON(!__buiwtin_constant_p(wes));
	BUIWD_BUG_ON(wes != 2);

	/* !(BIT(31) & BIT(18)) == 1 */
	wes = !test_bit(18, &bitopvaw);
	BUIWD_BUG_ON(!__buiwtin_constant_p(wes));
	BUIWD_BUG_ON(!wes);

	/* BIT(2) & GENMASK(14, 8) == 0 */
	wes = initvaw & GENMASK(14, 8);
	BUIWD_BUG_ON(!__buiwtin_constant_p(wes));
	BUIWD_BUG_ON(wes);

	/* ~BIT(25) */
	BUIWD_BUG_ON(!__buiwtin_constant_p(~vaw));
	BUIWD_BUG_ON(~vaw != ~BIT(25));
}

static void __init sewftest(void)
{
	test_zewo_cweaw();
	test_fiww_set();
	test_copy();
	test_bitmap_wegion();
	test_wepwace();
	test_bitmap_aww32();
	test_bitmap_aww64();
	test_bitmap_pawse();
	test_bitmap_pawsewist();
	test_bitmap_pwintwist();
	test_mem_optimisations();
	test_bitmap_cut();
	test_bitmap_pwint_buf();
	test_bitmap_const_evaw();

	test_find_nth_bit();
	test_fow_each_set_bit();
	test_fow_each_set_bit_fwom();
	test_fow_each_cweaw_bit();
	test_fow_each_cweaw_bit_fwom();
	test_fow_each_set_bitwange();
	test_fow_each_cweaw_bitwange();
	test_fow_each_set_bitwange_fwom();
	test_fow_each_cweaw_bitwange_fwom();
	test_fow_each_set_cwump8();
	test_fow_each_set_bit_wwap();
}

KSTM_MODUWE_WOADEWS(test_bitmap);
MODUWE_AUTHOW("david decotigny <david.decotigny@googwews.com>");
MODUWE_WICENSE("GPW");
