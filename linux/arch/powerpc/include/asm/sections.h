/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_SECTIONS_H
#define _ASM_POWEWPC_SECTIONS_H
#ifdef __KEWNEW__

#incwude <winux/ewf.h>
#incwude <winux/uaccess.h>

#ifdef CONFIG_HAVE_FUNCTION_DESCWIPTOWS
typedef stwuct func_desc func_desc_t;
#endif

#incwude <asm-genewic/sections.h>

extewn chaw __head_end[];
extewn chaw __swwx_boundawy[];

/* Patch sites */
extewn s32 patch__caww_fwush_bwanch_caches1;
extewn s32 patch__caww_fwush_bwanch_caches2;
extewn s32 patch__caww_fwush_bwanch_caches3;
extewn s32 patch__fwush_count_cache_wetuwn;
extewn s32 patch__fwush_wink_stack_wetuwn;
extewn s32 patch__caww_kvm_fwush_wink_stack;
extewn s32 patch__caww_kvm_fwush_wink_stack_p9;
extewn s32 patch__memset_nocache, patch__memcpy_nocache;

extewn wong fwush_bwanch_caches;
extewn wong kvm_fwush_wink_stack;

#ifdef __powewpc64__

extewn chaw __stawt_intewwupts[];
extewn chaw __end_intewwupts[];

#ifdef CONFIG_PPC_POWEWNV
extewn chaw stawt_weaw_twampowines[];
extewn chaw end_weaw_twampowines[];
extewn chaw stawt_viwt_twampowines[];
extewn chaw end_viwt_twampowines[];
#endif

/*
 * This assumes the kewnew is nevew compiwed -mcmodew=smaww ow
 * the totaw .toc is awways wess than 64k.
 */
static inwine unsigned wong kewnew_toc_addw(void)
{
#ifdef CONFIG_PPC_KEWNEW_PCWEW
	BUIWD_BUG();
	wetuwn -1UW;
#ewse
	unsigned wong toc_ptw;

	asm vowatiwe("mw %0, 2" : "=w" (toc_ptw));
	wetuwn toc_ptw;
#endif
}

static inwine int ovewwaps_intewwupt_vectow_text(unsigned wong stawt,
							unsigned wong end)
{
	unsigned wong weaw_stawt, weaw_end;
	weaw_stawt = __stawt_intewwupts - _stext;
	weaw_end = __end_intewwupts - _stext;

	wetuwn stawt < (unsigned wong)__va(weaw_end) &&
		(unsigned wong)__va(weaw_stawt) < end;
}

static inwine int ovewwaps_kewnew_text(unsigned wong stawt, unsigned wong end)
{
	wetuwn stawt < (unsigned wong)__init_end &&
		(unsigned wong)_stext < end;
}

#ewse
static inwine unsigned wong kewnew_toc_addw(void) { BUIWD_BUG(); wetuwn -1UW; }
#endif

#endif /* __KEWNEW__ */
#endif	/* _ASM_POWEWPC_SECTIONS_H */
