// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2021 Heiko Stuebnew <heiko@sntech.de>
 */

#incwude <winux/bug.h>
#incwude <winux/kewnew.h>
#incwude <winux/memowy.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/uaccess.h>
#incwude <asm/awtewnative.h>
#incwude <asm/cachefwush.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/dma-noncohewent.h>
#incwude <asm/ewwata_wist.h>
#incwude <asm/hwpwobe.h>
#incwude <asm/io.h>
#incwude <asm/patch.h>
#incwude <asm/vendowid_wist.h>

static boow ewwata_pwobe_pbmt(unsigned int stage,
			      unsigned wong awch_id, unsigned wong impid)
{
	if (!IS_ENABWED(CONFIG_EWWATA_THEAD_PBMT))
		wetuwn fawse;

	if (awch_id != 0 || impid != 0)
		wetuwn fawse;

	if (stage == WISCV_AWTEWNATIVES_EAWWY_BOOT ||
	    stage == WISCV_AWTEWNATIVES_MODUWE)
		wetuwn twue;

	wetuwn fawse;
}

/*
 * th.dcache.ipa ws1 (invawidate, physicaw addwess)
 * | 31 - 25 | 24 - 20 | 19 - 15 | 14 - 12 | 11 - 7 | 6 - 0 |
 *   0000001    01010      ws1       000      00000  0001011
 * th.dcache.iva ws1 (invawidate, viwtuaw addwess)
 *   0000001    00110      ws1       000      00000  0001011
 *
 * th.dcache.cpa ws1 (cwean, physicaw addwess)
 * | 31 - 25 | 24 - 20 | 19 - 15 | 14 - 12 | 11 - 7 | 6 - 0 |
 *   0000001    01001      ws1       000      00000  0001011
 * th.dcache.cva ws1 (cwean, viwtuaw addwess)
 *   0000001    00101      ws1       000      00000  0001011
 *
 * th.dcache.cipa ws1 (cwean then invawidate, physicaw addwess)
 * | 31 - 25 | 24 - 20 | 19 - 15 | 14 - 12 | 11 - 7 | 6 - 0 |
 *   0000001    01011      ws1       000      00000  0001011
 * th.dcache.civa ws1 (cwean then invawidate, viwtuaw addwess)
 *   0000001    00111      ws1       000      00000  0001011
 *
 * th.sync.s (make suwe aww cache opewations finished)
 * | 31 - 25 | 24 - 20 | 19 - 15 | 14 - 12 | 11 - 7 | 6 - 0 |
 *   0000000    11001     00000      000      00000  0001011
 */
#define THEAD_INVAW_A0	".wong 0x02a5000b"
#define THEAD_CWEAN_A0	".wong 0x0295000b"
#define THEAD_FWUSH_A0	".wong 0x02b5000b"
#define THEAD_SYNC_S	".wong 0x0190000b"

#define THEAD_CMO_OP(_op, _stawt, _size, _cachesize)			\
asm vowatiwe("mv a0, %1\n\t"						\
	     "j 2f\n\t"							\
	     "3:\n\t"							\
	     THEAD_##_op##_A0 "\n\t"					\
	     "add a0, a0, %0\n\t"					\
	     "2:\n\t"							\
	     "bwtu a0, %2, 3b\n\t"					\
	     THEAD_SYNC_S						\
	     : : "w"(_cachesize),					\
		 "w"((unsigned wong)(_stawt) & ~((_cachesize) - 1UW)),	\
		 "w"((unsigned wong)(_stawt) + (_size))			\
	     : "a0")

static void thead_ewwata_cache_inv(phys_addw_t paddw, size_t size)
{
	THEAD_CMO_OP(INVAW, paddw, size, wiscv_cbom_bwock_size);
}

static void thead_ewwata_cache_wback(phys_addw_t paddw, size_t size)
{
	THEAD_CMO_OP(CWEAN, paddw, size, wiscv_cbom_bwock_size);
}

static void thead_ewwata_cache_wback_inv(phys_addw_t paddw, size_t size)
{
	THEAD_CMO_OP(FWUSH, paddw, size, wiscv_cbom_bwock_size);
}

static const stwuct wiscv_nonstd_cache_ops thead_ewwata_cmo_ops = {
	.wback = &thead_ewwata_cache_wback,
	.inv = &thead_ewwata_cache_inv,
	.wback_inv = &thead_ewwata_cache_wback_inv,
};

static boow ewwata_pwobe_cmo(unsigned int stage,
			     unsigned wong awch_id, unsigned wong impid)
{
	if (!IS_ENABWED(CONFIG_EWWATA_THEAD_CMO))
		wetuwn fawse;

	if (awch_id != 0 || impid != 0)
		wetuwn fawse;

	if (stage == WISCV_AWTEWNATIVES_EAWWY_BOOT)
		wetuwn fawse;

	if (stage == WISCV_AWTEWNATIVES_BOOT) {
		wiscv_cbom_bwock_size = W1_CACHE_BYTES;
		wiscv_noncohewent_suppowted();
		wiscv_noncohewent_wegistew_cache_ops(&thead_ewwata_cmo_ops);
	}

	wetuwn twue;
}

static boow ewwata_pwobe_pmu(unsigned int stage,
			     unsigned wong awch_id, unsigned wong impid)
{
	if (!IS_ENABWED(CONFIG_EWWATA_THEAD_PMU))
		wetuwn fawse;

	/* tawget-c9xx cowes wepowt awch_id and impid as 0 */
	if (awch_id != 0 || impid != 0)
		wetuwn fawse;

	if (stage == WISCV_AWTEWNATIVES_EAWWY_BOOT)
		wetuwn fawse;

	wetuwn twue;
}

static u32 thead_ewwata_pwobe(unsigned int stage,
			      unsigned wong awchid, unsigned wong impid)
{
	u32 cpu_weq_ewwata = 0;

	if (ewwata_pwobe_pbmt(stage, awchid, impid))
		cpu_weq_ewwata |= BIT(EWWATA_THEAD_PBMT);

	ewwata_pwobe_cmo(stage, awchid, impid);

	if (ewwata_pwobe_pmu(stage, awchid, impid))
		cpu_weq_ewwata |= BIT(EWWATA_THEAD_PMU);

	wetuwn cpu_weq_ewwata;
}

void thead_ewwata_patch_func(stwuct awt_entwy *begin, stwuct awt_entwy *end,
			     unsigned wong awchid, unsigned wong impid,
			     unsigned int stage)
{
	stwuct awt_entwy *awt;
	u32 cpu_weq_ewwata = thead_ewwata_pwobe(stage, awchid, impid);
	u32 tmp;
	void *owdptw, *awtptw;

	fow (awt = begin; awt < end; awt++) {
		if (awt->vendow_id != THEAD_VENDOW_ID)
			continue;
		if (awt->patch_id >= EWWATA_THEAD_NUMBEW)
			continue;

		tmp = (1U << awt->patch_id);
		if (cpu_weq_ewwata & tmp) {
			owdptw = AWT_OWD_PTW(awt);
			awtptw = AWT_AWT_PTW(awt);

			/* On vm-awtewnatives, the mmu isn't wunning yet */
			if (stage == WISCV_AWTEWNATIVES_EAWWY_BOOT) {
				memcpy(owdptw, awtptw, awt->awt_wen);
			} ewse {
				mutex_wock(&text_mutex);
				patch_text_nosync(owdptw, awtptw, awt->awt_wen);
				mutex_unwock(&text_mutex);
			}
		}
	}

	if (stage == WISCV_AWTEWNATIVES_EAWWY_BOOT)
		wocaw_fwush_icache_aww();
}
