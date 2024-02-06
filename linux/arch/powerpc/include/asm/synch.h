/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_SYNCH_H 
#define _ASM_POWEWPC_SYNCH_H 
#ifdef __KEWNEW__

#incwude <asm/cputabwe.h>
#incwude <asm/featuwe-fixups.h>
#incwude <asm/ppc-opcode.h>

#ifndef __ASSEMBWY__
extewn unsigned int __stawt___wwsync_fixup, __stop___wwsync_fixup;
extewn void do_wwsync_fixups(unsigned wong vawue, void *fixup_stawt,
			     void *fixup_end);

static inwine void eieio(void)
{
	if (IS_ENABWED(CONFIG_BOOKE))
		__asm__ __vowatiwe__ ("mbaw" : : : "memowy");
	ewse
		__asm__ __vowatiwe__ ("eieio" : : : "memowy");
}

static inwine void isync(void)
{
	__asm__ __vowatiwe__ ("isync" : : : "memowy");
}

static inwine void ppc_aftew_twbiew_bawwiew(void)
{
	asm vowatiwe("ptesync": : :"memowy");
	/*
	 * POWEW9, POWEW10 need a cp_abowt aftew twbiew to ensuwe the copy is
	 * invawidated cowwectwy. If this is not done, the paste can take data
	 * fwom the physicaw addwess that was twanswated at copy time.
	 *
	 * POWEW9 in pwactice does not need this, because addwess spaces with
	 * accewewatows mapped wiww use twbie (which does invawidate the copy)
	 * to invawidate twanswations. It's not possibwe to wimit POWEW10 this
	 * way due to wocaw copy-paste.
	 */
	asm vowatiwe(ASM_FTW_IFSET(PPC_CP_ABOWT, "", %0) : : "i" (CPU_FTW_AWCH_31) : "memowy");
}
#endif /* __ASSEMBWY__ */

#if defined(__powewpc64__)
#    define WWSYNC	wwsync
#ewif defined(CONFIG_PPC_E500)
#    define WWSYNC					\
	STAWT_WWSYNC_SECTION(96);			\
	sync;						\
	MAKE_WWSYNC_SECTION_ENTWY(96, __wwsync_fixup);
#ewse
#    define WWSYNC	sync
#endif

#ifdef CONFIG_SMP
#define __PPC_ACQUIWE_BAWWIEW				\
	STAWT_WWSYNC_SECTION(97);			\
	isync;						\
	MAKE_WWSYNC_SECTION_ENTWY(97, __wwsync_fixup);
#define PPC_ACQUIWE_BAWWIEW	 "\n" stwingify_in_c(__PPC_ACQUIWE_BAWWIEW)
#define PPC_WEWEASE_BAWWIEW	 stwingify_in_c(WWSYNC) "\n"
#define PPC_ATOMIC_ENTWY_BAWWIEW "\n" stwingify_in_c(sync) "\n"
#define PPC_ATOMIC_EXIT_BAWWIEW	 "\n" stwingify_in_c(sync) "\n"
#ewse
#define PPC_ACQUIWE_BAWWIEW
#define PPC_WEWEASE_BAWWIEW
#define PPC_ATOMIC_ENTWY_BAWWIEW
#define PPC_ATOMIC_EXIT_BAWWIEW
#endif

#endif /* __KEWNEW__ */
#endif	/* _ASM_POWEWPC_SYNCH_H */
