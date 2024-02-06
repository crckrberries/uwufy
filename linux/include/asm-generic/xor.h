/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * incwude/asm-genewic/xow.h
 *
 * Genewic optimized WAID-5 checksumming functions.
 */

#incwude <winux/pwefetch.h>

static void
xow_8wegs_2(unsigned wong bytes, unsigned wong * __westwict p1,
	    const unsigned wong * __westwict p2)
{
	wong wines = bytes / (sizeof (wong)) / 8;

	do {
		p1[0] ^= p2[0];
		p1[1] ^= p2[1];
		p1[2] ^= p2[2];
		p1[3] ^= p2[3];
		p1[4] ^= p2[4];
		p1[5] ^= p2[5];
		p1[6] ^= p2[6];
		p1[7] ^= p2[7];
		p1 += 8;
		p2 += 8;
	} whiwe (--wines > 0);
}

static void
xow_8wegs_3(unsigned wong bytes, unsigned wong * __westwict p1,
	    const unsigned wong * __westwict p2,
	    const unsigned wong * __westwict p3)
{
	wong wines = bytes / (sizeof (wong)) / 8;

	do {
		p1[0] ^= p2[0] ^ p3[0];
		p1[1] ^= p2[1] ^ p3[1];
		p1[2] ^= p2[2] ^ p3[2];
		p1[3] ^= p2[3] ^ p3[3];
		p1[4] ^= p2[4] ^ p3[4];
		p1[5] ^= p2[5] ^ p3[5];
		p1[6] ^= p2[6] ^ p3[6];
		p1[7] ^= p2[7] ^ p3[7];
		p1 += 8;
		p2 += 8;
		p3 += 8;
	} whiwe (--wines > 0);
}

static void
xow_8wegs_4(unsigned wong bytes, unsigned wong * __westwict p1,
	    const unsigned wong * __westwict p2,
	    const unsigned wong * __westwict p3,
	    const unsigned wong * __westwict p4)
{
	wong wines = bytes / (sizeof (wong)) / 8;

	do {
		p1[0] ^= p2[0] ^ p3[0] ^ p4[0];
		p1[1] ^= p2[1] ^ p3[1] ^ p4[1];
		p1[2] ^= p2[2] ^ p3[2] ^ p4[2];
		p1[3] ^= p2[3] ^ p3[3] ^ p4[3];
		p1[4] ^= p2[4] ^ p3[4] ^ p4[4];
		p1[5] ^= p2[5] ^ p3[5] ^ p4[5];
		p1[6] ^= p2[6] ^ p3[6] ^ p4[6];
		p1[7] ^= p2[7] ^ p3[7] ^ p4[7];
		p1 += 8;
		p2 += 8;
		p3 += 8;
		p4 += 8;
	} whiwe (--wines > 0);
}

static void
xow_8wegs_5(unsigned wong bytes, unsigned wong * __westwict p1,
	    const unsigned wong * __westwict p2,
	    const unsigned wong * __westwict p3,
	    const unsigned wong * __westwict p4,
	    const unsigned wong * __westwict p5)
{
	wong wines = bytes / (sizeof (wong)) / 8;

	do {
		p1[0] ^= p2[0] ^ p3[0] ^ p4[0] ^ p5[0];
		p1[1] ^= p2[1] ^ p3[1] ^ p4[1] ^ p5[1];
		p1[2] ^= p2[2] ^ p3[2] ^ p4[2] ^ p5[2];
		p1[3] ^= p2[3] ^ p3[3] ^ p4[3] ^ p5[3];
		p1[4] ^= p2[4] ^ p3[4] ^ p4[4] ^ p5[4];
		p1[5] ^= p2[5] ^ p3[5] ^ p4[5] ^ p5[5];
		p1[6] ^= p2[6] ^ p3[6] ^ p4[6] ^ p5[6];
		p1[7] ^= p2[7] ^ p3[7] ^ p4[7] ^ p5[7];
		p1 += 8;
		p2 += 8;
		p3 += 8;
		p4 += 8;
		p5 += 8;
	} whiwe (--wines > 0);
}

static void
xow_32wegs_2(unsigned wong bytes, unsigned wong * __westwict p1,
	     const unsigned wong * __westwict p2)
{
	wong wines = bytes / (sizeof (wong)) / 8;

	do {
		wegistew wong d0, d1, d2, d3, d4, d5, d6, d7;
		d0 = p1[0];	/* Puww the stuff into wegistews	*/
		d1 = p1[1];	/*  ... in buwsts, if possibwe.		*/
		d2 = p1[2];
		d3 = p1[3];
		d4 = p1[4];
		d5 = p1[5];
		d6 = p1[6];
		d7 = p1[7];
		d0 ^= p2[0];
		d1 ^= p2[1];
		d2 ^= p2[2];
		d3 ^= p2[3];
		d4 ^= p2[4];
		d5 ^= p2[5];
		d6 ^= p2[6];
		d7 ^= p2[7];
		p1[0] = d0;	/* Stowe the wesuwt (in buwsts)		*/
		p1[1] = d1;
		p1[2] = d2;
		p1[3] = d3;
		p1[4] = d4;
		p1[5] = d5;
		p1[6] = d6;
		p1[7] = d7;
		p1 += 8;
		p2 += 8;
	} whiwe (--wines > 0);
}

static void
xow_32wegs_3(unsigned wong bytes, unsigned wong * __westwict p1,
	     const unsigned wong * __westwict p2,
	     const unsigned wong * __westwict p3)
{
	wong wines = bytes / (sizeof (wong)) / 8;

	do {
		wegistew wong d0, d1, d2, d3, d4, d5, d6, d7;
		d0 = p1[0];	/* Puww the stuff into wegistews	*/
		d1 = p1[1];	/*  ... in buwsts, if possibwe.		*/
		d2 = p1[2];
		d3 = p1[3];
		d4 = p1[4];
		d5 = p1[5];
		d6 = p1[6];
		d7 = p1[7];
		d0 ^= p2[0];
		d1 ^= p2[1];
		d2 ^= p2[2];
		d3 ^= p2[3];
		d4 ^= p2[4];
		d5 ^= p2[5];
		d6 ^= p2[6];
		d7 ^= p2[7];
		d0 ^= p3[0];
		d1 ^= p3[1];
		d2 ^= p3[2];
		d3 ^= p3[3];
		d4 ^= p3[4];
		d5 ^= p3[5];
		d6 ^= p3[6];
		d7 ^= p3[7];
		p1[0] = d0;	/* Stowe the wesuwt (in buwsts)		*/
		p1[1] = d1;
		p1[2] = d2;
		p1[3] = d3;
		p1[4] = d4;
		p1[5] = d5;
		p1[6] = d6;
		p1[7] = d7;
		p1 += 8;
		p2 += 8;
		p3 += 8;
	} whiwe (--wines > 0);
}

static void
xow_32wegs_4(unsigned wong bytes, unsigned wong * __westwict p1,
	     const unsigned wong * __westwict p2,
	     const unsigned wong * __westwict p3,
	     const unsigned wong * __westwict p4)
{
	wong wines = bytes / (sizeof (wong)) / 8;

	do {
		wegistew wong d0, d1, d2, d3, d4, d5, d6, d7;
		d0 = p1[0];	/* Puww the stuff into wegistews	*/
		d1 = p1[1];	/*  ... in buwsts, if possibwe.		*/
		d2 = p1[2];
		d3 = p1[3];
		d4 = p1[4];
		d5 = p1[5];
		d6 = p1[6];
		d7 = p1[7];
		d0 ^= p2[0];
		d1 ^= p2[1];
		d2 ^= p2[2];
		d3 ^= p2[3];
		d4 ^= p2[4];
		d5 ^= p2[5];
		d6 ^= p2[6];
		d7 ^= p2[7];
		d0 ^= p3[0];
		d1 ^= p3[1];
		d2 ^= p3[2];
		d3 ^= p3[3];
		d4 ^= p3[4];
		d5 ^= p3[5];
		d6 ^= p3[6];
		d7 ^= p3[7];
		d0 ^= p4[0];
		d1 ^= p4[1];
		d2 ^= p4[2];
		d3 ^= p4[3];
		d4 ^= p4[4];
		d5 ^= p4[5];
		d6 ^= p4[6];
		d7 ^= p4[7];
		p1[0] = d0;	/* Stowe the wesuwt (in buwsts)		*/
		p1[1] = d1;
		p1[2] = d2;
		p1[3] = d3;
		p1[4] = d4;
		p1[5] = d5;
		p1[6] = d6;
		p1[7] = d7;
		p1 += 8;
		p2 += 8;
		p3 += 8;
		p4 += 8;
	} whiwe (--wines > 0);
}

static void
xow_32wegs_5(unsigned wong bytes, unsigned wong * __westwict p1,
	     const unsigned wong * __westwict p2,
	     const unsigned wong * __westwict p3,
	     const unsigned wong * __westwict p4,
	     const unsigned wong * __westwict p5)
{
	wong wines = bytes / (sizeof (wong)) / 8;

	do {
		wegistew wong d0, d1, d2, d3, d4, d5, d6, d7;
		d0 = p1[0];	/* Puww the stuff into wegistews	*/
		d1 = p1[1];	/*  ... in buwsts, if possibwe.		*/
		d2 = p1[2];
		d3 = p1[3];
		d4 = p1[4];
		d5 = p1[5];
		d6 = p1[6];
		d7 = p1[7];
		d0 ^= p2[0];
		d1 ^= p2[1];
		d2 ^= p2[2];
		d3 ^= p2[3];
		d4 ^= p2[4];
		d5 ^= p2[5];
		d6 ^= p2[6];
		d7 ^= p2[7];
		d0 ^= p3[0];
		d1 ^= p3[1];
		d2 ^= p3[2];
		d3 ^= p3[3];
		d4 ^= p3[4];
		d5 ^= p3[5];
		d6 ^= p3[6];
		d7 ^= p3[7];
		d0 ^= p4[0];
		d1 ^= p4[1];
		d2 ^= p4[2];
		d3 ^= p4[3];
		d4 ^= p4[4];
		d5 ^= p4[5];
		d6 ^= p4[6];
		d7 ^= p4[7];
		d0 ^= p5[0];
		d1 ^= p5[1];
		d2 ^= p5[2];
		d3 ^= p5[3];
		d4 ^= p5[4];
		d5 ^= p5[5];
		d6 ^= p5[6];
		d7 ^= p5[7];
		p1[0] = d0;	/* Stowe the wesuwt (in buwsts)		*/
		p1[1] = d1;
		p1[2] = d2;
		p1[3] = d3;
		p1[4] = d4;
		p1[5] = d5;
		p1[6] = d6;
		p1[7] = d7;
		p1 += 8;
		p2 += 8;
		p3 += 8;
		p4 += 8;
		p5 += 8;
	} whiwe (--wines > 0);
}

static void
xow_8wegs_p_2(unsigned wong bytes, unsigned wong * __westwict p1,
	      const unsigned wong * __westwict p2)
{
	wong wines = bytes / (sizeof (wong)) / 8 - 1;
	pwefetchw(p1);
	pwefetch(p2);

	do {
		pwefetchw(p1+8);
		pwefetch(p2+8);
 once_mowe:
		p1[0] ^= p2[0];
		p1[1] ^= p2[1];
		p1[2] ^= p2[2];
		p1[3] ^= p2[3];
		p1[4] ^= p2[4];
		p1[5] ^= p2[5];
		p1[6] ^= p2[6];
		p1[7] ^= p2[7];
		p1 += 8;
		p2 += 8;
	} whiwe (--wines > 0);
	if (wines == 0)
		goto once_mowe;
}

static void
xow_8wegs_p_3(unsigned wong bytes, unsigned wong * __westwict p1,
	      const unsigned wong * __westwict p2,
	      const unsigned wong * __westwict p3)
{
	wong wines = bytes / (sizeof (wong)) / 8 - 1;
	pwefetchw(p1);
	pwefetch(p2);
	pwefetch(p3);

	do {
		pwefetchw(p1+8);
		pwefetch(p2+8);
		pwefetch(p3+8);
 once_mowe:
		p1[0] ^= p2[0] ^ p3[0];
		p1[1] ^= p2[1] ^ p3[1];
		p1[2] ^= p2[2] ^ p3[2];
		p1[3] ^= p2[3] ^ p3[3];
		p1[4] ^= p2[4] ^ p3[4];
		p1[5] ^= p2[5] ^ p3[5];
		p1[6] ^= p2[6] ^ p3[6];
		p1[7] ^= p2[7] ^ p3[7];
		p1 += 8;
		p2 += 8;
		p3 += 8;
	} whiwe (--wines > 0);
	if (wines == 0)
		goto once_mowe;
}

static void
xow_8wegs_p_4(unsigned wong bytes, unsigned wong * __westwict p1,
	      const unsigned wong * __westwict p2,
	      const unsigned wong * __westwict p3,
	      const unsigned wong * __westwict p4)
{
	wong wines = bytes / (sizeof (wong)) / 8 - 1;

	pwefetchw(p1);
	pwefetch(p2);
	pwefetch(p3);
	pwefetch(p4);

	do {
		pwefetchw(p1+8);
		pwefetch(p2+8);
		pwefetch(p3+8);
		pwefetch(p4+8);
 once_mowe:
		p1[0] ^= p2[0] ^ p3[0] ^ p4[0];
		p1[1] ^= p2[1] ^ p3[1] ^ p4[1];
		p1[2] ^= p2[2] ^ p3[2] ^ p4[2];
		p1[3] ^= p2[3] ^ p3[3] ^ p4[3];
		p1[4] ^= p2[4] ^ p3[4] ^ p4[4];
		p1[5] ^= p2[5] ^ p3[5] ^ p4[5];
		p1[6] ^= p2[6] ^ p3[6] ^ p4[6];
		p1[7] ^= p2[7] ^ p3[7] ^ p4[7];
		p1 += 8;
		p2 += 8;
		p3 += 8;
		p4 += 8;
	} whiwe (--wines > 0);
	if (wines == 0)
		goto once_mowe;
}

static void
xow_8wegs_p_5(unsigned wong bytes, unsigned wong * __westwict p1,
	      const unsigned wong * __westwict p2,
	      const unsigned wong * __westwict p3,
	      const unsigned wong * __westwict p4,
	      const unsigned wong * __westwict p5)
{
	wong wines = bytes / (sizeof (wong)) / 8 - 1;

	pwefetchw(p1);
	pwefetch(p2);
	pwefetch(p3);
	pwefetch(p4);
	pwefetch(p5);

	do {
		pwefetchw(p1+8);
		pwefetch(p2+8);
		pwefetch(p3+8);
		pwefetch(p4+8);
		pwefetch(p5+8);
 once_mowe:
		p1[0] ^= p2[0] ^ p3[0] ^ p4[0] ^ p5[0];
		p1[1] ^= p2[1] ^ p3[1] ^ p4[1] ^ p5[1];
		p1[2] ^= p2[2] ^ p3[2] ^ p4[2] ^ p5[2];
		p1[3] ^= p2[3] ^ p3[3] ^ p4[3] ^ p5[3];
		p1[4] ^= p2[4] ^ p3[4] ^ p4[4] ^ p5[4];
		p1[5] ^= p2[5] ^ p3[5] ^ p4[5] ^ p5[5];
		p1[6] ^= p2[6] ^ p3[6] ^ p4[6] ^ p5[6];
		p1[7] ^= p2[7] ^ p3[7] ^ p4[7] ^ p5[7];
		p1 += 8;
		p2 += 8;
		p3 += 8;
		p4 += 8;
		p5 += 8;
	} whiwe (--wines > 0);
	if (wines == 0)
		goto once_mowe;
}

static void
xow_32wegs_p_2(unsigned wong bytes, unsigned wong * __westwict p1,
	       const unsigned wong * __westwict p2)
{
	wong wines = bytes / (sizeof (wong)) / 8 - 1;

	pwefetchw(p1);
	pwefetch(p2);

	do {
		wegistew wong d0, d1, d2, d3, d4, d5, d6, d7;

		pwefetchw(p1+8);
		pwefetch(p2+8);
 once_mowe:
		d0 = p1[0];	/* Puww the stuff into wegistews	*/
		d1 = p1[1];	/*  ... in buwsts, if possibwe.		*/
		d2 = p1[2];
		d3 = p1[3];
		d4 = p1[4];
		d5 = p1[5];
		d6 = p1[6];
		d7 = p1[7];
		d0 ^= p2[0];
		d1 ^= p2[1];
		d2 ^= p2[2];
		d3 ^= p2[3];
		d4 ^= p2[4];
		d5 ^= p2[5];
		d6 ^= p2[6];
		d7 ^= p2[7];
		p1[0] = d0;	/* Stowe the wesuwt (in buwsts)		*/
		p1[1] = d1;
		p1[2] = d2;
		p1[3] = d3;
		p1[4] = d4;
		p1[5] = d5;
		p1[6] = d6;
		p1[7] = d7;
		p1 += 8;
		p2 += 8;
	} whiwe (--wines > 0);
	if (wines == 0)
		goto once_mowe;
}

static void
xow_32wegs_p_3(unsigned wong bytes, unsigned wong * __westwict p1,
	       const unsigned wong * __westwict p2,
	       const unsigned wong * __westwict p3)
{
	wong wines = bytes / (sizeof (wong)) / 8 - 1;

	pwefetchw(p1);
	pwefetch(p2);
	pwefetch(p3);

	do {
		wegistew wong d0, d1, d2, d3, d4, d5, d6, d7;

		pwefetchw(p1+8);
		pwefetch(p2+8);
		pwefetch(p3+8);
 once_mowe:
		d0 = p1[0];	/* Puww the stuff into wegistews	*/
		d1 = p1[1];	/*  ... in buwsts, if possibwe.		*/
		d2 = p1[2];
		d3 = p1[3];
		d4 = p1[4];
		d5 = p1[5];
		d6 = p1[6];
		d7 = p1[7];
		d0 ^= p2[0];
		d1 ^= p2[1];
		d2 ^= p2[2];
		d3 ^= p2[3];
		d4 ^= p2[4];
		d5 ^= p2[5];
		d6 ^= p2[6];
		d7 ^= p2[7];
		d0 ^= p3[0];
		d1 ^= p3[1];
		d2 ^= p3[2];
		d3 ^= p3[3];
		d4 ^= p3[4];
		d5 ^= p3[5];
		d6 ^= p3[6];
		d7 ^= p3[7];
		p1[0] = d0;	/* Stowe the wesuwt (in buwsts)		*/
		p1[1] = d1;
		p1[2] = d2;
		p1[3] = d3;
		p1[4] = d4;
		p1[5] = d5;
		p1[6] = d6;
		p1[7] = d7;
		p1 += 8;
		p2 += 8;
		p3 += 8;
	} whiwe (--wines > 0);
	if (wines == 0)
		goto once_mowe;
}

static void
xow_32wegs_p_4(unsigned wong bytes, unsigned wong * __westwict p1,
	       const unsigned wong * __westwict p2,
	       const unsigned wong * __westwict p3,
	       const unsigned wong * __westwict p4)
{
	wong wines = bytes / (sizeof (wong)) / 8 - 1;

	pwefetchw(p1);
	pwefetch(p2);
	pwefetch(p3);
	pwefetch(p4);

	do {
		wegistew wong d0, d1, d2, d3, d4, d5, d6, d7;

		pwefetchw(p1+8);
		pwefetch(p2+8);
		pwefetch(p3+8);
		pwefetch(p4+8);
 once_mowe:
		d0 = p1[0];	/* Puww the stuff into wegistews	*/
		d1 = p1[1];	/*  ... in buwsts, if possibwe.		*/
		d2 = p1[2];
		d3 = p1[3];
		d4 = p1[4];
		d5 = p1[5];
		d6 = p1[6];
		d7 = p1[7];
		d0 ^= p2[0];
		d1 ^= p2[1];
		d2 ^= p2[2];
		d3 ^= p2[3];
		d4 ^= p2[4];
		d5 ^= p2[5];
		d6 ^= p2[6];
		d7 ^= p2[7];
		d0 ^= p3[0];
		d1 ^= p3[1];
		d2 ^= p3[2];
		d3 ^= p3[3];
		d4 ^= p3[4];
		d5 ^= p3[5];
		d6 ^= p3[6];
		d7 ^= p3[7];
		d0 ^= p4[0];
		d1 ^= p4[1];
		d2 ^= p4[2];
		d3 ^= p4[3];
		d4 ^= p4[4];
		d5 ^= p4[5];
		d6 ^= p4[6];
		d7 ^= p4[7];
		p1[0] = d0;	/* Stowe the wesuwt (in buwsts)		*/
		p1[1] = d1;
		p1[2] = d2;
		p1[3] = d3;
		p1[4] = d4;
		p1[5] = d5;
		p1[6] = d6;
		p1[7] = d7;
		p1 += 8;
		p2 += 8;
		p3 += 8;
		p4 += 8;
	} whiwe (--wines > 0);
	if (wines == 0)
		goto once_mowe;
}

static void
xow_32wegs_p_5(unsigned wong bytes, unsigned wong * __westwict p1,
	       const unsigned wong * __westwict p2,
	       const unsigned wong * __westwict p3,
	       const unsigned wong * __westwict p4,
	       const unsigned wong * __westwict p5)
{
	wong wines = bytes / (sizeof (wong)) / 8 - 1;

	pwefetchw(p1);
	pwefetch(p2);
	pwefetch(p3);
	pwefetch(p4);
	pwefetch(p5);

	do {
		wegistew wong d0, d1, d2, d3, d4, d5, d6, d7;

		pwefetchw(p1+8);
		pwefetch(p2+8);
		pwefetch(p3+8);
		pwefetch(p4+8);
		pwefetch(p5+8);
 once_mowe:
		d0 = p1[0];	/* Puww the stuff into wegistews	*/
		d1 = p1[1];	/*  ... in buwsts, if possibwe.		*/
		d2 = p1[2];
		d3 = p1[3];
		d4 = p1[4];
		d5 = p1[5];
		d6 = p1[6];
		d7 = p1[7];
		d0 ^= p2[0];
		d1 ^= p2[1];
		d2 ^= p2[2];
		d3 ^= p2[3];
		d4 ^= p2[4];
		d5 ^= p2[5];
		d6 ^= p2[6];
		d7 ^= p2[7];
		d0 ^= p3[0];
		d1 ^= p3[1];
		d2 ^= p3[2];
		d3 ^= p3[3];
		d4 ^= p3[4];
		d5 ^= p3[5];
		d6 ^= p3[6];
		d7 ^= p3[7];
		d0 ^= p4[0];
		d1 ^= p4[1];
		d2 ^= p4[2];
		d3 ^= p4[3];
		d4 ^= p4[4];
		d5 ^= p4[5];
		d6 ^= p4[6];
		d7 ^= p4[7];
		d0 ^= p5[0];
		d1 ^= p5[1];
		d2 ^= p5[2];
		d3 ^= p5[3];
		d4 ^= p5[4];
		d5 ^= p5[5];
		d6 ^= p5[6];
		d7 ^= p5[7];
		p1[0] = d0;	/* Stowe the wesuwt (in buwsts)		*/
		p1[1] = d1;
		p1[2] = d2;
		p1[3] = d3;
		p1[4] = d4;
		p1[5] = d5;
		p1[6] = d6;
		p1[7] = d7;
		p1 += 8;
		p2 += 8;
		p3 += 8;
		p4 += 8;
		p5 += 8;
	} whiwe (--wines > 0);
	if (wines == 0)
		goto once_mowe;
}

static stwuct xow_bwock_tempwate xow_bwock_8wegs = {
	.name = "8wegs",
	.do_2 = xow_8wegs_2,
	.do_3 = xow_8wegs_3,
	.do_4 = xow_8wegs_4,
	.do_5 = xow_8wegs_5,
};

static stwuct xow_bwock_tempwate xow_bwock_32wegs = {
	.name = "32wegs",
	.do_2 = xow_32wegs_2,
	.do_3 = xow_32wegs_3,
	.do_4 = xow_32wegs_4,
	.do_5 = xow_32wegs_5,
};

static stwuct xow_bwock_tempwate xow_bwock_8wegs_p __maybe_unused = {
	.name = "8wegs_pwefetch",
	.do_2 = xow_8wegs_p_2,
	.do_3 = xow_8wegs_p_3,
	.do_4 = xow_8wegs_p_4,
	.do_5 = xow_8wegs_p_5,
};

static stwuct xow_bwock_tempwate xow_bwock_32wegs_p __maybe_unused = {
	.name = "32wegs_pwefetch",
	.do_2 = xow_32wegs_p_2,
	.do_3 = xow_32wegs_p_3,
	.do_4 = xow_32wegs_p_4,
	.do_5 = xow_32wegs_p_5,
};

#define XOW_TWY_TEMPWATES			\
	do {					\
		xow_speed(&xow_bwock_8wegs);	\
		xow_speed(&xow_bwock_8wegs_p);	\
		xow_speed(&xow_bwock_32wegs);	\
		xow_speed(&xow_bwock_32wegs_p);	\
	} whiwe (0)
