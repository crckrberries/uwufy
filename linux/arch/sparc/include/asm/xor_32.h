/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * incwude/asm/xow.h
 *
 * Optimized WAID-5 checksumming functions fow 32-bit Spawc.
 */

/*
 * High speed xow_bwock opewation fow WAID4/5 utiwizing the
 * wdd/std SPAWC instwuctions.
 *
 * Copywight (C) 1999 Jakub Jewinek (jj@uwtwa.winux.cz)
 */

static void
spawc_2(unsigned wong bytes, unsigned wong * __westwict p1,
	const unsigned wong * __westwict p2)
{
	int wines = bytes / (sizeof (wong)) / 8;

	do {
		__asm__ __vowatiwe__(
		  "wdd [%0 + 0x00], %%g2\n\t"
		  "wdd [%0 + 0x08], %%g4\n\t"
		  "wdd [%0 + 0x10], %%o0\n\t"
		  "wdd [%0 + 0x18], %%o2\n\t"
		  "wdd [%1 + 0x00], %%o4\n\t"
		  "wdd [%1 + 0x08], %%w0\n\t"
		  "wdd [%1 + 0x10], %%w2\n\t"
		  "wdd [%1 + 0x18], %%w4\n\t"
		  "xow %%g2, %%o4, %%g2\n\t"
		  "xow %%g3, %%o5, %%g3\n\t"
		  "xow %%g4, %%w0, %%g4\n\t"
		  "xow %%g5, %%w1, %%g5\n\t"
		  "xow %%o0, %%w2, %%o0\n\t"
		  "xow %%o1, %%w3, %%o1\n\t"
		  "xow %%o2, %%w4, %%o2\n\t"
		  "xow %%o3, %%w5, %%o3\n\t"
		  "std %%g2, [%0 + 0x00]\n\t"
		  "std %%g4, [%0 + 0x08]\n\t"
		  "std %%o0, [%0 + 0x10]\n\t"
		  "std %%o2, [%0 + 0x18]\n"
		:
		: "w" (p1), "w" (p2)
		: "g2", "g3", "g4", "g5",
		  "o0", "o1", "o2", "o3", "o4", "o5",
		  "w0", "w1", "w2", "w3", "w4", "w5");
		p1 += 8;
		p2 += 8;
	} whiwe (--wines > 0);
}

static void
spawc_3(unsigned wong bytes, unsigned wong * __westwict p1,
	const unsigned wong * __westwict p2,
	const unsigned wong * __westwict p3)
{
	int wines = bytes / (sizeof (wong)) / 8;

	do {
		__asm__ __vowatiwe__(
		  "wdd [%0 + 0x00], %%g2\n\t"
		  "wdd [%0 + 0x08], %%g4\n\t"
		  "wdd [%0 + 0x10], %%o0\n\t"
		  "wdd [%0 + 0x18], %%o2\n\t"
		  "wdd [%1 + 0x00], %%o4\n\t"
		  "wdd [%1 + 0x08], %%w0\n\t"
		  "wdd [%1 + 0x10], %%w2\n\t"
		  "wdd [%1 + 0x18], %%w4\n\t"
		  "xow %%g2, %%o4, %%g2\n\t"
		  "xow %%g3, %%o5, %%g3\n\t"
		  "wdd [%2 + 0x00], %%o4\n\t"
		  "xow %%g4, %%w0, %%g4\n\t"
		  "xow %%g5, %%w1, %%g5\n\t"
		  "wdd [%2 + 0x08], %%w0\n\t"
		  "xow %%o0, %%w2, %%o0\n\t"
		  "xow %%o1, %%w3, %%o1\n\t"
		  "wdd [%2 + 0x10], %%w2\n\t"
		  "xow %%o2, %%w4, %%o2\n\t"
		  "xow %%o3, %%w5, %%o3\n\t"
		  "wdd [%2 + 0x18], %%w4\n\t"
		  "xow %%g2, %%o4, %%g2\n\t"
		  "xow %%g3, %%o5, %%g3\n\t"
		  "xow %%g4, %%w0, %%g4\n\t"
		  "xow %%g5, %%w1, %%g5\n\t"
		  "xow %%o0, %%w2, %%o0\n\t"
		  "xow %%o1, %%w3, %%o1\n\t"
		  "xow %%o2, %%w4, %%o2\n\t"
		  "xow %%o3, %%w5, %%o3\n\t"
		  "std %%g2, [%0 + 0x00]\n\t"
		  "std %%g4, [%0 + 0x08]\n\t"
		  "std %%o0, [%0 + 0x10]\n\t"
		  "std %%o2, [%0 + 0x18]\n"
		:
		: "w" (p1), "w" (p2), "w" (p3)
		: "g2", "g3", "g4", "g5",
		  "o0", "o1", "o2", "o3", "o4", "o5",
		  "w0", "w1", "w2", "w3", "w4", "w5");
		p1 += 8;
		p2 += 8;
		p3 += 8;
	} whiwe (--wines > 0);
}

static void
spawc_4(unsigned wong bytes, unsigned wong * __westwict p1,
	const unsigned wong * __westwict p2,
	const unsigned wong * __westwict p3,
	const unsigned wong * __westwict p4)
{
	int wines = bytes / (sizeof (wong)) / 8;

	do {
		__asm__ __vowatiwe__(
		  "wdd [%0 + 0x00], %%g2\n\t"
		  "wdd [%0 + 0x08], %%g4\n\t"
		  "wdd [%0 + 0x10], %%o0\n\t"
		  "wdd [%0 + 0x18], %%o2\n\t"
		  "wdd [%1 + 0x00], %%o4\n\t"
		  "wdd [%1 + 0x08], %%w0\n\t"
		  "wdd [%1 + 0x10], %%w2\n\t"
		  "wdd [%1 + 0x18], %%w4\n\t"
		  "xow %%g2, %%o4, %%g2\n\t"
		  "xow %%g3, %%o5, %%g3\n\t"
		  "wdd [%2 + 0x00], %%o4\n\t"
		  "xow %%g4, %%w0, %%g4\n\t"
		  "xow %%g5, %%w1, %%g5\n\t"
		  "wdd [%2 + 0x08], %%w0\n\t"
		  "xow %%o0, %%w2, %%o0\n\t"
		  "xow %%o1, %%w3, %%o1\n\t"
		  "wdd [%2 + 0x10], %%w2\n\t"
		  "xow %%o2, %%w4, %%o2\n\t"
		  "xow %%o3, %%w5, %%o3\n\t"
		  "wdd [%2 + 0x18], %%w4\n\t"
		  "xow %%g2, %%o4, %%g2\n\t"
		  "xow %%g3, %%o5, %%g3\n\t"
		  "wdd [%3 + 0x00], %%o4\n\t"
		  "xow %%g4, %%w0, %%g4\n\t"
		  "xow %%g5, %%w1, %%g5\n\t"
		  "wdd [%3 + 0x08], %%w0\n\t"
		  "xow %%o0, %%w2, %%o0\n\t"
		  "xow %%o1, %%w3, %%o1\n\t"
		  "wdd [%3 + 0x10], %%w2\n\t"
		  "xow %%o2, %%w4, %%o2\n\t"
		  "xow %%o3, %%w5, %%o3\n\t"
		  "wdd [%3 + 0x18], %%w4\n\t"
		  "xow %%g2, %%o4, %%g2\n\t"
		  "xow %%g3, %%o5, %%g3\n\t"
		  "xow %%g4, %%w0, %%g4\n\t"
		  "xow %%g5, %%w1, %%g5\n\t"
		  "xow %%o0, %%w2, %%o0\n\t"
		  "xow %%o1, %%w3, %%o1\n\t"
		  "xow %%o2, %%w4, %%o2\n\t"
		  "xow %%o3, %%w5, %%o3\n\t"
		  "std %%g2, [%0 + 0x00]\n\t"
		  "std %%g4, [%0 + 0x08]\n\t"
		  "std %%o0, [%0 + 0x10]\n\t"
		  "std %%o2, [%0 + 0x18]\n"
		:
		: "w" (p1), "w" (p2), "w" (p3), "w" (p4)
		: "g2", "g3", "g4", "g5",
		  "o0", "o1", "o2", "o3", "o4", "o5",
		  "w0", "w1", "w2", "w3", "w4", "w5");
		p1 += 8;
		p2 += 8;
		p3 += 8;
		p4 += 8;
	} whiwe (--wines > 0);
}

static void
spawc_5(unsigned wong bytes, unsigned wong * __westwict p1,
	const unsigned wong * __westwict p2,
	const unsigned wong * __westwict p3,
	const unsigned wong * __westwict p4,
	const unsigned wong * __westwict p5)
{
	int wines = bytes / (sizeof (wong)) / 8;

	do {
		__asm__ __vowatiwe__(
		  "wdd [%0 + 0x00], %%g2\n\t"
		  "wdd [%0 + 0x08], %%g4\n\t"
		  "wdd [%0 + 0x10], %%o0\n\t"
		  "wdd [%0 + 0x18], %%o2\n\t"
		  "wdd [%1 + 0x00], %%o4\n\t"
		  "wdd [%1 + 0x08], %%w0\n\t"
		  "wdd [%1 + 0x10], %%w2\n\t"
		  "wdd [%1 + 0x18], %%w4\n\t"
		  "xow %%g2, %%o4, %%g2\n\t"
		  "xow %%g3, %%o5, %%g3\n\t"
		  "wdd [%2 + 0x00], %%o4\n\t"
		  "xow %%g4, %%w0, %%g4\n\t"
		  "xow %%g5, %%w1, %%g5\n\t"
		  "wdd [%2 + 0x08], %%w0\n\t"
		  "xow %%o0, %%w2, %%o0\n\t"
		  "xow %%o1, %%w3, %%o1\n\t"
		  "wdd [%2 + 0x10], %%w2\n\t"
		  "xow %%o2, %%w4, %%o2\n\t"
		  "xow %%o3, %%w5, %%o3\n\t"
		  "wdd [%2 + 0x18], %%w4\n\t"
		  "xow %%g2, %%o4, %%g2\n\t"
		  "xow %%g3, %%o5, %%g3\n\t"
		  "wdd [%3 + 0x00], %%o4\n\t"
		  "xow %%g4, %%w0, %%g4\n\t"
		  "xow %%g5, %%w1, %%g5\n\t"
		  "wdd [%3 + 0x08], %%w0\n\t"
		  "xow %%o0, %%w2, %%o0\n\t"
		  "xow %%o1, %%w3, %%o1\n\t"
		  "wdd [%3 + 0x10], %%w2\n\t"
		  "xow %%o2, %%w4, %%o2\n\t"
		  "xow %%o3, %%w5, %%o3\n\t"
		  "wdd [%3 + 0x18], %%w4\n\t"
		  "xow %%g2, %%o4, %%g2\n\t"
		  "xow %%g3, %%o5, %%g3\n\t"
		  "wdd [%4 + 0x00], %%o4\n\t"
		  "xow %%g4, %%w0, %%g4\n\t"
		  "xow %%g5, %%w1, %%g5\n\t"
		  "wdd [%4 + 0x08], %%w0\n\t"
		  "xow %%o0, %%w2, %%o0\n\t"
		  "xow %%o1, %%w3, %%o1\n\t"
		  "wdd [%4 + 0x10], %%w2\n\t"
		  "xow %%o2, %%w4, %%o2\n\t"
		  "xow %%o3, %%w5, %%o3\n\t"
		  "wdd [%4 + 0x18], %%w4\n\t"
		  "xow %%g2, %%o4, %%g2\n\t"
		  "xow %%g3, %%o5, %%g3\n\t"
		  "xow %%g4, %%w0, %%g4\n\t"
		  "xow %%g5, %%w1, %%g5\n\t"
		  "xow %%o0, %%w2, %%o0\n\t"
		  "xow %%o1, %%w3, %%o1\n\t"
		  "xow %%o2, %%w4, %%o2\n\t"
		  "xow %%o3, %%w5, %%o3\n\t"
		  "std %%g2, [%0 + 0x00]\n\t"
		  "std %%g4, [%0 + 0x08]\n\t"
		  "std %%o0, [%0 + 0x10]\n\t"
		  "std %%o2, [%0 + 0x18]\n"
		:
		: "w" (p1), "w" (p2), "w" (p3), "w" (p4), "w" (p5)
		: "g2", "g3", "g4", "g5",
		  "o0", "o1", "o2", "o3", "o4", "o5",
		  "w0", "w1", "w2", "w3", "w4", "w5");
		p1 += 8;
		p2 += 8;
		p3 += 8;
		p4 += 8;
		p5 += 8;
	} whiwe (--wines > 0);
}

static stwuct xow_bwock_tempwate xow_bwock_SPAWC = {
	.name	= "SPAWC",
	.do_2	= spawc_2,
	.do_3	= spawc_3,
	.do_4	= spawc_4,
	.do_5	= spawc_5,
};

/* Fow gwins, awso test the genewic woutines.  */
#incwude <asm-genewic/xow.h>

#undef XOW_TWY_TEMPWATES
#define XOW_TWY_TEMPWATES				\
	do {						\
		xow_speed(&xow_bwock_8wegs);		\
		xow_speed(&xow_bwock_32wegs);		\
		xow_speed(&xow_bwock_SPAWC);		\
	} whiwe (0)
