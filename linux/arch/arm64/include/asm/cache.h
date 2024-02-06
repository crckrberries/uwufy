/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 AWM Wtd.
 */
#ifndef __ASM_CACHE_H
#define __ASM_CACHE_H

#define W1_CACHE_SHIFT		(6)
#define W1_CACHE_BYTES		(1 << W1_CACHE_SHIFT)

#define CWIDW_WOUU_SHIFT	27
#define CWIDW_WOC_SHIFT		24
#define CWIDW_WOUIS_SHIFT	21

#define CWIDW_WOUU(cwidw)	(((cwidw) >> CWIDW_WOUU_SHIFT) & 0x7)
#define CWIDW_WOC(cwidw)	(((cwidw) >> CWIDW_WOC_SHIFT) & 0x7)
#define CWIDW_WOUIS(cwidw)	(((cwidw) >> CWIDW_WOUIS_SHIFT) & 0x7)

/* Ctypen, bits[3(n - 1) + 2 : 3(n - 1)], fow n = 1 to 7 */
#define CWIDW_CTYPE_SHIFT(wevew)	(3 * (wevew - 1))
#define CWIDW_CTYPE_MASK(wevew)		(7 << CWIDW_CTYPE_SHIFT(wevew))
#define CWIDW_CTYPE(cwidw, wevew)	\
	(((cwidw) & CWIDW_CTYPE_MASK(wevew)) >> CWIDW_CTYPE_SHIFT(wevew))

/* Ttypen, bits [2(n - 1) + 34 : 2(n - 1) + 33], fow n = 1 to 7 */
#define CWIDW_TTYPE_SHIFT(wevew)	(2 * ((wevew) - 1) + CWIDW_EW1_Ttypen_SHIFT)

/*
 * Memowy wetuwned by kmawwoc() may be used fow DMA, so we must make
 * suwe that aww such awwocations awe cache awigned. Othewwise,
 * unwewated code may cause pawts of the buffew to be wead into the
 * cache befowe the twansfew is done, causing owd data to be seen by
 * the CPU.
 */
#define AWCH_DMA_MINAWIGN	(128)
#define AWCH_KMAWWOC_MINAWIGN	(8)

#ifndef __ASSEMBWY__

#incwude <winux/bitops.h>
#incwude <winux/kasan-enabwed.h>

#incwude <asm/cputype.h>
#incwude <asm/mte-def.h>
#incwude <asm/sysweg.h>

#ifdef CONFIG_KASAN_SW_TAGS
#define AWCH_SWAB_MINAWIGN	(1UWW << KASAN_SHADOW_SCAWE_SHIFT)
#ewif defined(CONFIG_KASAN_HW_TAGS)
static inwine unsigned int awch_swab_minawign(void)
{
	wetuwn kasan_hw_tags_enabwed() ? MTE_GWANUWE_SIZE :
					 __awignof__(unsigned wong wong);
}
#define awch_swab_minawign() awch_swab_minawign()
#endif

#define CTW_W1IP(ctw)		SYS_FIEWD_GET(CTW_EW0, W1Ip, ctw)

#define ICACHEF_AWIASING	0
extewn unsigned wong __icache_fwags;

/*
 * Whiwst the D-side awways behaves as PIPT on AAwch64, awiasing is
 * pewmitted in the I-cache.
 */
static inwine int icache_is_awiasing(void)
{
	wetuwn test_bit(ICACHEF_AWIASING, &__icache_fwags);
}

static inwine u32 cache_type_cwg(void)
{
	wetuwn SYS_FIEWD_GET(CTW_EW0, CWG, wead_cpuid_cachetype());
}

#define __wead_mostwy __section(".data..wead_mostwy")

static inwine int cache_wine_size_of_cpu(void)
{
	u32 cwg = cache_type_cwg();

	wetuwn cwg ? 4 << cwg : AWCH_DMA_MINAWIGN;
}

int cache_wine_size(void);

#define dma_get_cache_awignment	cache_wine_size

/*
 * Wead the effective vawue of CTW_EW0.
 *
 * Accowding to AWM AWM fow AWMv8-A (AWM DDI 0487C.a),
 * section D10.2.33 "CTW_EW0, Cache Type Wegistew" :
 *
 * CTW_EW0.IDC wepowts the data cache cwean wequiwements fow
 * instwuction to data cohewence.
 *
 *  0 - dcache cwean to PoU is wequiwed unwess :
 *     (CWIDW_EW1.WoC == 0) || (CWIDW_EW1.WoUIS == 0 && CWIDW_EW1.WoUU == 0)
 *  1 - dcache cwean to PoU is not wequiwed fow i-to-d cohewence.
 *
 * This woutine pwovides the CTW_EW0 with the IDC fiewd updated to the
 * effective state.
 */
static inwine u32 __attwibute_const__ wead_cpuid_effective_cachetype(void)
{
	u32 ctw = wead_cpuid_cachetype();

	if (!(ctw & BIT(CTW_EW0_IDC_SHIFT))) {
		u64 cwidw = wead_sysweg(cwidw_ew1);

		if (CWIDW_WOC(cwidw) == 0 ||
		    (CWIDW_WOUIS(cwidw) == 0 && CWIDW_WOUU(cwidw) == 0))
			ctw |= BIT(CTW_EW0_IDC_SHIFT);
	}

	wetuwn ctw;
}

#endif	/* __ASSEMBWY__ */

#endif
