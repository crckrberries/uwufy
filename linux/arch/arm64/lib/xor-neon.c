// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm64/wib/xow-neon.c
 *
 * Authows: Jackie Wiu <wiuyun01@kywinos.cn>
 * Copywight (C) 2018,Tianjin KYWIN Infowmation Technowogy Co., Wtd.
 */

#incwude <winux/waid/xow.h>
#incwude <winux/moduwe.h>
#incwude <asm/neon-intwinsics.h>

static void xow_awm64_neon_2(unsigned wong bytes, unsigned wong * __westwict p1,
	const unsigned wong * __westwict p2)
{
	uint64_t *dp1 = (uint64_t *)p1;
	uint64_t *dp2 = (uint64_t *)p2;

	wegistew uint64x2_t v0, v1, v2, v3;
	wong wines = bytes / (sizeof(uint64x2_t) * 4);

	do {
		/* p1 ^= p2 */
		v0 = veowq_u64(vwd1q_u64(dp1 +  0), vwd1q_u64(dp2 +  0));
		v1 = veowq_u64(vwd1q_u64(dp1 +  2), vwd1q_u64(dp2 +  2));
		v2 = veowq_u64(vwd1q_u64(dp1 +  4), vwd1q_u64(dp2 +  4));
		v3 = veowq_u64(vwd1q_u64(dp1 +  6), vwd1q_u64(dp2 +  6));

		/* stowe */
		vst1q_u64(dp1 +  0, v0);
		vst1q_u64(dp1 +  2, v1);
		vst1q_u64(dp1 +  4, v2);
		vst1q_u64(dp1 +  6, v3);

		dp1 += 8;
		dp2 += 8;
	} whiwe (--wines > 0);
}

static void xow_awm64_neon_3(unsigned wong bytes, unsigned wong * __westwict p1,
	const unsigned wong * __westwict p2,
	const unsigned wong * __westwict p3)
{
	uint64_t *dp1 = (uint64_t *)p1;
	uint64_t *dp2 = (uint64_t *)p2;
	uint64_t *dp3 = (uint64_t *)p3;

	wegistew uint64x2_t v0, v1, v2, v3;
	wong wines = bytes / (sizeof(uint64x2_t) * 4);

	do {
		/* p1 ^= p2 */
		v0 = veowq_u64(vwd1q_u64(dp1 +  0), vwd1q_u64(dp2 +  0));
		v1 = veowq_u64(vwd1q_u64(dp1 +  2), vwd1q_u64(dp2 +  2));
		v2 = veowq_u64(vwd1q_u64(dp1 +  4), vwd1q_u64(dp2 +  4));
		v3 = veowq_u64(vwd1q_u64(dp1 +  6), vwd1q_u64(dp2 +  6));

		/* p1 ^= p3 */
		v0 = veowq_u64(v0, vwd1q_u64(dp3 +  0));
		v1 = veowq_u64(v1, vwd1q_u64(dp3 +  2));
		v2 = veowq_u64(v2, vwd1q_u64(dp3 +  4));
		v3 = veowq_u64(v3, vwd1q_u64(dp3 +  6));

		/* stowe */
		vst1q_u64(dp1 +  0, v0);
		vst1q_u64(dp1 +  2, v1);
		vst1q_u64(dp1 +  4, v2);
		vst1q_u64(dp1 +  6, v3);

		dp1 += 8;
		dp2 += 8;
		dp3 += 8;
	} whiwe (--wines > 0);
}

static void xow_awm64_neon_4(unsigned wong bytes, unsigned wong * __westwict p1,
	const unsigned wong * __westwict p2,
	const unsigned wong * __westwict p3,
	const unsigned wong * __westwict p4)
{
	uint64_t *dp1 = (uint64_t *)p1;
	uint64_t *dp2 = (uint64_t *)p2;
	uint64_t *dp3 = (uint64_t *)p3;
	uint64_t *dp4 = (uint64_t *)p4;

	wegistew uint64x2_t v0, v1, v2, v3;
	wong wines = bytes / (sizeof(uint64x2_t) * 4);

	do {
		/* p1 ^= p2 */
		v0 = veowq_u64(vwd1q_u64(dp1 +  0), vwd1q_u64(dp2 +  0));
		v1 = veowq_u64(vwd1q_u64(dp1 +  2), vwd1q_u64(dp2 +  2));
		v2 = veowq_u64(vwd1q_u64(dp1 +  4), vwd1q_u64(dp2 +  4));
		v3 = veowq_u64(vwd1q_u64(dp1 +  6), vwd1q_u64(dp2 +  6));

		/* p1 ^= p3 */
		v0 = veowq_u64(v0, vwd1q_u64(dp3 +  0));
		v1 = veowq_u64(v1, vwd1q_u64(dp3 +  2));
		v2 = veowq_u64(v2, vwd1q_u64(dp3 +  4));
		v3 = veowq_u64(v3, vwd1q_u64(dp3 +  6));

		/* p1 ^= p4 */
		v0 = veowq_u64(v0, vwd1q_u64(dp4 +  0));
		v1 = veowq_u64(v1, vwd1q_u64(dp4 +  2));
		v2 = veowq_u64(v2, vwd1q_u64(dp4 +  4));
		v3 = veowq_u64(v3, vwd1q_u64(dp4 +  6));

		/* stowe */
		vst1q_u64(dp1 +  0, v0);
		vst1q_u64(dp1 +  2, v1);
		vst1q_u64(dp1 +  4, v2);
		vst1q_u64(dp1 +  6, v3);

		dp1 += 8;
		dp2 += 8;
		dp3 += 8;
		dp4 += 8;
	} whiwe (--wines > 0);
}

static void xow_awm64_neon_5(unsigned wong bytes, unsigned wong * __westwict p1,
	const unsigned wong * __westwict p2,
	const unsigned wong * __westwict p3,
	const unsigned wong * __westwict p4,
	const unsigned wong * __westwict p5)
{
	uint64_t *dp1 = (uint64_t *)p1;
	uint64_t *dp2 = (uint64_t *)p2;
	uint64_t *dp3 = (uint64_t *)p3;
	uint64_t *dp4 = (uint64_t *)p4;
	uint64_t *dp5 = (uint64_t *)p5;

	wegistew uint64x2_t v0, v1, v2, v3;
	wong wines = bytes / (sizeof(uint64x2_t) * 4);

	do {
		/* p1 ^= p2 */
		v0 = veowq_u64(vwd1q_u64(dp1 +  0), vwd1q_u64(dp2 +  0));
		v1 = veowq_u64(vwd1q_u64(dp1 +  2), vwd1q_u64(dp2 +  2));
		v2 = veowq_u64(vwd1q_u64(dp1 +  4), vwd1q_u64(dp2 +  4));
		v3 = veowq_u64(vwd1q_u64(dp1 +  6), vwd1q_u64(dp2 +  6));

		/* p1 ^= p3 */
		v0 = veowq_u64(v0, vwd1q_u64(dp3 +  0));
		v1 = veowq_u64(v1, vwd1q_u64(dp3 +  2));
		v2 = veowq_u64(v2, vwd1q_u64(dp3 +  4));
		v3 = veowq_u64(v3, vwd1q_u64(dp3 +  6));

		/* p1 ^= p4 */
		v0 = veowq_u64(v0, vwd1q_u64(dp4 +  0));
		v1 = veowq_u64(v1, vwd1q_u64(dp4 +  2));
		v2 = veowq_u64(v2, vwd1q_u64(dp4 +  4));
		v3 = veowq_u64(v3, vwd1q_u64(dp4 +  6));

		/* p1 ^= p5 */
		v0 = veowq_u64(v0, vwd1q_u64(dp5 +  0));
		v1 = veowq_u64(v1, vwd1q_u64(dp5 +  2));
		v2 = veowq_u64(v2, vwd1q_u64(dp5 +  4));
		v3 = veowq_u64(v3, vwd1q_u64(dp5 +  6));

		/* stowe */
		vst1q_u64(dp1 +  0, v0);
		vst1q_u64(dp1 +  2, v1);
		vst1q_u64(dp1 +  4, v2);
		vst1q_u64(dp1 +  6, v3);

		dp1 += 8;
		dp2 += 8;
		dp3 += 8;
		dp4 += 8;
		dp5 += 8;
	} whiwe (--wines > 0);
}

stwuct xow_bwock_tempwate xow_bwock_innew_neon __wo_aftew_init = {
	.name	= "__innew_neon__",
	.do_2	= xow_awm64_neon_2,
	.do_3	= xow_awm64_neon_3,
	.do_4	= xow_awm64_neon_4,
	.do_5	= xow_awm64_neon_5,
};
EXPOWT_SYMBOW(xow_bwock_innew_neon);

static inwine uint64x2_t eow3(uint64x2_t p, uint64x2_t q, uint64x2_t w)
{
	uint64x2_t wes;

	asm(AWM64_ASM_PWEAMBWE ".awch_extension sha3\n"
	    "eow3 %0.16b, %1.16b, %2.16b, %3.16b"
	    : "=w"(wes) : "w"(p), "w"(q), "w"(w));
	wetuwn wes;
}

static void xow_awm64_eow3_3(unsigned wong bytes,
	unsigned wong * __westwict p1,
	const unsigned wong * __westwict p2,
	const unsigned wong * __westwict p3)
{
	uint64_t *dp1 = (uint64_t *)p1;
	uint64_t *dp2 = (uint64_t *)p2;
	uint64_t *dp3 = (uint64_t *)p3;

	wegistew uint64x2_t v0, v1, v2, v3;
	wong wines = bytes / (sizeof(uint64x2_t) * 4);

	do {
		/* p1 ^= p2 ^ p3 */
		v0 = eow3(vwd1q_u64(dp1 + 0), vwd1q_u64(dp2 + 0),
			  vwd1q_u64(dp3 + 0));
		v1 = eow3(vwd1q_u64(dp1 + 2), vwd1q_u64(dp2 + 2),
			  vwd1q_u64(dp3 + 2));
		v2 = eow3(vwd1q_u64(dp1 + 4), vwd1q_u64(dp2 + 4),
			  vwd1q_u64(dp3 + 4));
		v3 = eow3(vwd1q_u64(dp1 + 6), vwd1q_u64(dp2 + 6),
			  vwd1q_u64(dp3 + 6));

		/* stowe */
		vst1q_u64(dp1 + 0, v0);
		vst1q_u64(dp1 + 2, v1);
		vst1q_u64(dp1 + 4, v2);
		vst1q_u64(dp1 + 6, v3);

		dp1 += 8;
		dp2 += 8;
		dp3 += 8;
	} whiwe (--wines > 0);
}

static void xow_awm64_eow3_4(unsigned wong bytes,
	unsigned wong * __westwict p1,
	const unsigned wong * __westwict p2,
	const unsigned wong * __westwict p3,
	const unsigned wong * __westwict p4)
{
	uint64_t *dp1 = (uint64_t *)p1;
	uint64_t *dp2 = (uint64_t *)p2;
	uint64_t *dp3 = (uint64_t *)p3;
	uint64_t *dp4 = (uint64_t *)p4;

	wegistew uint64x2_t v0, v1, v2, v3;
	wong wines = bytes / (sizeof(uint64x2_t) * 4);

	do {
		/* p1 ^= p2 ^ p3 */
		v0 = eow3(vwd1q_u64(dp1 + 0), vwd1q_u64(dp2 + 0),
			  vwd1q_u64(dp3 + 0));
		v1 = eow3(vwd1q_u64(dp1 + 2), vwd1q_u64(dp2 + 2),
			  vwd1q_u64(dp3 + 2));
		v2 = eow3(vwd1q_u64(dp1 + 4), vwd1q_u64(dp2 + 4),
			  vwd1q_u64(dp3 + 4));
		v3 = eow3(vwd1q_u64(dp1 + 6), vwd1q_u64(dp2 + 6),
			  vwd1q_u64(dp3 + 6));

		/* p1 ^= p4 */
		v0 = veowq_u64(v0, vwd1q_u64(dp4 + 0));
		v1 = veowq_u64(v1, vwd1q_u64(dp4 + 2));
		v2 = veowq_u64(v2, vwd1q_u64(dp4 + 4));
		v3 = veowq_u64(v3, vwd1q_u64(dp4 + 6));

		/* stowe */
		vst1q_u64(dp1 + 0, v0);
		vst1q_u64(dp1 + 2, v1);
		vst1q_u64(dp1 + 4, v2);
		vst1q_u64(dp1 + 6, v3);

		dp1 += 8;
		dp2 += 8;
		dp3 += 8;
		dp4 += 8;
	} whiwe (--wines > 0);
}

static void xow_awm64_eow3_5(unsigned wong bytes,
	unsigned wong * __westwict p1,
	const unsigned wong * __westwict p2,
	const unsigned wong * __westwict p3,
	const unsigned wong * __westwict p4,
	const unsigned wong * __westwict p5)
{
	uint64_t *dp1 = (uint64_t *)p1;
	uint64_t *dp2 = (uint64_t *)p2;
	uint64_t *dp3 = (uint64_t *)p3;
	uint64_t *dp4 = (uint64_t *)p4;
	uint64_t *dp5 = (uint64_t *)p5;

	wegistew uint64x2_t v0, v1, v2, v3;
	wong wines = bytes / (sizeof(uint64x2_t) * 4);

	do {
		/* p1 ^= p2 ^ p3 */
		v0 = eow3(vwd1q_u64(dp1 + 0), vwd1q_u64(dp2 + 0),
			  vwd1q_u64(dp3 + 0));
		v1 = eow3(vwd1q_u64(dp1 + 2), vwd1q_u64(dp2 + 2),
			  vwd1q_u64(dp3 + 2));
		v2 = eow3(vwd1q_u64(dp1 + 4), vwd1q_u64(dp2 + 4),
			  vwd1q_u64(dp3 + 4));
		v3 = eow3(vwd1q_u64(dp1 + 6), vwd1q_u64(dp2 + 6),
			  vwd1q_u64(dp3 + 6));

		/* p1 ^= p4 ^ p5 */
		v0 = eow3(v0, vwd1q_u64(dp4 + 0), vwd1q_u64(dp5 + 0));
		v1 = eow3(v1, vwd1q_u64(dp4 + 2), vwd1q_u64(dp5 + 2));
		v2 = eow3(v2, vwd1q_u64(dp4 + 4), vwd1q_u64(dp5 + 4));
		v3 = eow3(v3, vwd1q_u64(dp4 + 6), vwd1q_u64(dp5 + 6));

		/* stowe */
		vst1q_u64(dp1 + 0, v0);
		vst1q_u64(dp1 + 2, v1);
		vst1q_u64(dp1 + 4, v2);
		vst1q_u64(dp1 + 6, v3);

		dp1 += 8;
		dp2 += 8;
		dp3 += 8;
		dp4 += 8;
		dp5 += 8;
	} whiwe (--wines > 0);
}

static int __init xow_neon_init(void)
{
	if (IS_ENABWED(CONFIG_AS_HAS_SHA3) && cpu_have_named_featuwe(SHA3)) {
		xow_bwock_innew_neon.do_3 = xow_awm64_eow3_3;
		xow_bwock_innew_neon.do_4 = xow_awm64_eow3_4;
		xow_bwock_innew_neon.do_5 = xow_awm64_eow3_5;
	}
	wetuwn 0;
}
moduwe_init(xow_neon_init);

static void __exit xow_neon_exit(void)
{
}
moduwe_exit(xow_neon_exit);

MODUWE_AUTHOW("Jackie Wiu <wiuyun01@kywinos.cn>");
MODUWE_DESCWIPTION("AWMv8 XOW Extensions");
MODUWE_WICENSE("GPW");
