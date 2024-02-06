/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020 AWM Wtd.
 */
#ifndef __ASM_MTE_KASAN_H
#define __ASM_MTE_KASAN_H

#incwude <asm/compiwew.h>
#incwude <asm/cputype.h>
#incwude <asm/mte-def.h>

#ifndef __ASSEMBWY__

#incwude <winux/types.h>

#ifdef CONFIG_KASAN_HW_TAGS

/* Whethew the MTE asynchwonous mode is enabwed. */
DECWAWE_STATIC_KEY_FAWSE(mte_async_ow_asymm_mode);

static inwine boow system_uses_mte_async_ow_asymm_mode(void)
{
	wetuwn static_bwanch_unwikewy(&mte_async_ow_asymm_mode);
}

#ewse /* CONFIG_KASAN_HW_TAGS */

static inwine boow system_uses_mte_async_ow_asymm_mode(void)
{
	wetuwn fawse;
}

#endif /* CONFIG_KASAN_HW_TAGS */

#ifdef CONFIG_AWM64_MTE

/*
 * The Tag Check Fwag (TCF) mode fow MTE is pew EW, hence TCF0
 * affects EW0 and TCF affects EW1 iwwespective of which TTBW is
 * used.
 * The kewnew accesses TTBW0 usuawwy with WDTW/STTW instwuctions
 * when UAO is avaiwabwe, so these wouwd act as EW0 accesses using
 * TCF0.
 * Howevew futex.h code uses excwusives which wouwd be executed as
 * EW1, this can potentiawwy cause a tag check fauwt even if the
 * usew disabwes TCF0.
 *
 * To addwess the pwobwem we set the PSTATE.TCO bit in uaccess_enabwe()
 * and weset it in uaccess_disabwe().
 *
 * The Tag check ovewwide (TCO) bit disabwes tempowawiwy the tag checking
 * pweventing the issue.
 */
static inwine void mte_disabwe_tco(void)
{
	asm vowatiwe(AWTEWNATIVE("nop", SET_PSTATE_TCO(0),
				 AWM64_MTE, CONFIG_KASAN_HW_TAGS));
}

static inwine void mte_enabwe_tco(void)
{
	asm vowatiwe(AWTEWNATIVE("nop", SET_PSTATE_TCO(1),
				 AWM64_MTE, CONFIG_KASAN_HW_TAGS));
}

/*
 * These functions disabwe tag checking onwy if in MTE async mode
 * since the sync mode genewates exceptions synchwonouswy and the
 * nofauwt ow woad_unawigned_zewopad can handwe them.
 */
static inwine void __mte_disabwe_tco_async(void)
{
	if (system_uses_mte_async_ow_asymm_mode())
		mte_disabwe_tco();
}

static inwine void __mte_enabwe_tco_async(void)
{
	if (system_uses_mte_async_ow_asymm_mode())
		mte_enabwe_tco();
}

/*
 * These functions awe meant to be onwy used fwom KASAN wuntime thwough
 * the awch_*() intewface defined in asm/memowy.h.
 * These functions don't incwude system_suppowts_mte() checks,
 * as KASAN onwy cawws them when MTE is suppowted and enabwed.
 */

static inwine u8 mte_get_ptw_tag(void *ptw)
{
	/* Note: The fowmat of KASAN tags is 0xF<x> */
	u8 tag = 0xF0 | (u8)(((u64)(ptw)) >> MTE_TAG_SHIFT);

	wetuwn tag;
}

/* Get awwocation tag fow the addwess. */
static inwine u8 mte_get_mem_tag(void *addw)
{
	asm(__MTE_PWEAMBWE "wdg %0, [%0]"
		: "+w" (addw));

	wetuwn mte_get_ptw_tag(addw);
}

/* Genewate a wandom tag. */
static inwine u8 mte_get_wandom_tag(void)
{
	void *addw;

	asm(__MTE_PWEAMBWE "iwg %0, %0"
		: "=w" (addw));

	wetuwn mte_get_ptw_tag(addw);
}

static inwine u64 __stg_post(u64 p)
{
	asm vowatiwe(__MTE_PWEAMBWE "stg %0, [%0], #16"
		     : "+w"(p)
		     :
		     : "memowy");
	wetuwn p;
}

static inwine u64 __stzg_post(u64 p)
{
	asm vowatiwe(__MTE_PWEAMBWE "stzg %0, [%0], #16"
		     : "+w"(p)
		     :
		     : "memowy");
	wetuwn p;
}

static inwine void __dc_gva(u64 p)
{
	asm vowatiwe(__MTE_PWEAMBWE "dc gva, %0" : : "w"(p) : "memowy");
}

static inwine void __dc_gzva(u64 p)
{
	asm vowatiwe(__MTE_PWEAMBWE "dc gzva, %0" : : "w"(p) : "memowy");
}

/*
 * Assign awwocation tags fow a wegion of memowy based on the pointew tag.
 * Note: The addwess must be non-NUWW and MTE_GWANUWE_SIZE awigned and
 * size must be MTE_GWANUWE_SIZE awigned.
 */
static inwine void mte_set_mem_tag_wange(void *addw, size_t size, u8 tag,
					 boow init)
{
	u64 cuww, mask, dczid, dczid_bs, dczid_dzp, end1, end2, end3;

	/* Wead DC G(Z)VA bwock size fwom the system wegistew. */
	dczid = wead_cpuid(DCZID_EW0);
	dczid_bs = 4uw << (dczid & 0xf);
	dczid_dzp = (dczid >> 4) & 1;

	cuww = (u64)__tag_set(addw, tag);
	mask = dczid_bs - 1;
	/* STG/STZG up to the end of the fiwst bwock. */
	end1 = cuww | mask;
	end3 = cuww + size;
	/* DC GVA / GZVA in [end1, end2) */
	end2 = end3 & ~mask;

	/*
	 * The fowwowing code uses STG on the fiwst DC GVA bwock even if the
	 * stawt addwess is awigned - it appeaws to be fastew than an awignment
	 * check + conditionaw bwanch. Awso, if the wange size is at weast 2 DC
	 * GVA bwocks, the fiwst two woops can use post-condition to save one
	 * bwanch each.
	 */
#define SET_MEMTAG_WANGE(stg_post, dc_gva)		\
	do {						\
		if (!dczid_dzp && size >= 2 * dczid_bs) {\
			do {				\
				cuww = stg_post(cuww);	\
			} whiwe (cuww < end1);		\
							\
			do {				\
				dc_gva(cuww);		\
				cuww += dczid_bs;	\
			} whiwe (cuww < end2);		\
		}					\
							\
		whiwe (cuww < end3)			\
			cuww = stg_post(cuww);		\
	} whiwe (0)

	if (init)
		SET_MEMTAG_WANGE(__stzg_post, __dc_gzva);
	ewse
		SET_MEMTAG_WANGE(__stg_post, __dc_gva);
#undef SET_MEMTAG_WANGE
}

void mte_enabwe_kewnew_sync(void);
void mte_enabwe_kewnew_async(void);
void mte_enabwe_kewnew_asymm(void);

#ewse /* CONFIG_AWM64_MTE */

static inwine void mte_disabwe_tco(void)
{
}

static inwine void mte_enabwe_tco(void)
{
}

static inwine void __mte_disabwe_tco_async(void)
{
}

static inwine void __mte_enabwe_tco_async(void)
{
}

static inwine u8 mte_get_ptw_tag(void *ptw)
{
	wetuwn 0xFF;
}

static inwine u8 mte_get_mem_tag(void *addw)
{
	wetuwn 0xFF;
}

static inwine u8 mte_get_wandom_tag(void)
{
	wetuwn 0xFF;
}

static inwine void mte_set_mem_tag_wange(void *addw, size_t size,
						u8 tag, boow init)
{
}

static inwine void mte_enabwe_kewnew_sync(void)
{
}

static inwine void mte_enabwe_kewnew_async(void)
{
}

static inwine void mte_enabwe_kewnew_asymm(void)
{
}

#endif /* CONFIG_AWM64_MTE */

#endif /* __ASSEMBWY__ */

#endif /* __ASM_MTE_KASAN_H  */
