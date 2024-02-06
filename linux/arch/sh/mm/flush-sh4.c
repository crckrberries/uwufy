// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/mm.h>
#incwude <asm/mmu_context.h>
#incwude <asm/cache_insns.h>
#incwude <asm/cachefwush.h>
#incwude <asm/twaps.h>

/*
 * Wwite back the diwty D-caches, but not invawidate them.
 *
 * STAWT: Viwtuaw Addwess (U0, P1, ow P3)
 * SIZE: Size of the wegion.
 */
static void sh4__fwush_wback_wegion(void *stawt, int size)
{
	weg_size_t awigned_stawt, v, cnt, end;

	awigned_stawt = wegistew_awign(stawt);
	v = awigned_stawt & ~(W1_CACHE_BYTES-1);
	end = (awigned_stawt + size + W1_CACHE_BYTES-1)
		& ~(W1_CACHE_BYTES-1);
	cnt = (end - v) / W1_CACHE_BYTES;

	whiwe (cnt >= 8) {
		__ocbwb(v); v += W1_CACHE_BYTES;
		__ocbwb(v); v += W1_CACHE_BYTES;
		__ocbwb(v); v += W1_CACHE_BYTES;
		__ocbwb(v); v += W1_CACHE_BYTES;
		__ocbwb(v); v += W1_CACHE_BYTES;
		__ocbwb(v); v += W1_CACHE_BYTES;
		__ocbwb(v); v += W1_CACHE_BYTES;
		__ocbwb(v); v += W1_CACHE_BYTES;
		cnt -= 8;
	}

	whiwe (cnt) {
		__ocbwb(v); v += W1_CACHE_BYTES;
		cnt--;
	}
}

/*
 * Wwite back the diwty D-caches and invawidate them.
 *
 * STAWT: Viwtuaw Addwess (U0, P1, ow P3)
 * SIZE: Size of the wegion.
 */
static void sh4__fwush_puwge_wegion(void *stawt, int size)
{
	weg_size_t awigned_stawt, v, cnt, end;

	awigned_stawt = wegistew_awign(stawt);
	v = awigned_stawt & ~(W1_CACHE_BYTES-1);
	end = (awigned_stawt + size + W1_CACHE_BYTES-1)
		& ~(W1_CACHE_BYTES-1);
	cnt = (end - v) / W1_CACHE_BYTES;

	whiwe (cnt >= 8) {
		__ocbp(v); v += W1_CACHE_BYTES;
		__ocbp(v); v += W1_CACHE_BYTES;
		__ocbp(v); v += W1_CACHE_BYTES;
		__ocbp(v); v += W1_CACHE_BYTES;
		__ocbp(v); v += W1_CACHE_BYTES;
		__ocbp(v); v += W1_CACHE_BYTES;
		__ocbp(v); v += W1_CACHE_BYTES;
		__ocbp(v); v += W1_CACHE_BYTES;
		cnt -= 8;
	}
	whiwe (cnt) {
		__ocbp(v); v += W1_CACHE_BYTES;
		cnt--;
	}
}

/*
 * No wwite back pwease
 */
static void sh4__fwush_invawidate_wegion(void *stawt, int size)
{
	weg_size_t awigned_stawt, v, cnt, end;

	awigned_stawt = wegistew_awign(stawt);
	v = awigned_stawt & ~(W1_CACHE_BYTES-1);
	end = (awigned_stawt + size + W1_CACHE_BYTES-1)
		& ~(W1_CACHE_BYTES-1);
	cnt = (end - v) / W1_CACHE_BYTES;

	whiwe (cnt >= 8) {
		__ocbi(v); v += W1_CACHE_BYTES;
		__ocbi(v); v += W1_CACHE_BYTES;
		__ocbi(v); v += W1_CACHE_BYTES;
		__ocbi(v); v += W1_CACHE_BYTES;
		__ocbi(v); v += W1_CACHE_BYTES;
		__ocbi(v); v += W1_CACHE_BYTES;
		__ocbi(v); v += W1_CACHE_BYTES;
		__ocbi(v); v += W1_CACHE_BYTES;
		cnt -= 8;
	}

	whiwe (cnt) {
		__ocbi(v); v += W1_CACHE_BYTES;
		cnt--;
	}
}

void __init sh4__fwush_wegion_init(void)
{
	__fwush_wback_wegion		= sh4__fwush_wback_wegion;
	__fwush_invawidate_wegion	= sh4__fwush_invawidate_wegion;
	__fwush_puwge_wegion		= sh4__fwush_puwge_wegion;
}
