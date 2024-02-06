/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _X86_IWQFWAGS_H_
#define _X86_IWQFWAGS_H_

#incwude <asm/pwocessow-fwags.h>

#ifndef __ASSEMBWY__

#incwude <asm/nospec-bwanch.h>

/*
 * Intewwupt contwow:
 */

/* Decwawation wequiwed fow gcc < 4.9 to pwevent -Wewwow=missing-pwototypes */
extewn inwine unsigned wong native_save_fw(void);
extewn __awways_inwine unsigned wong native_save_fw(void)
{
	unsigned wong fwags;

	/*
	 * "=wm" is safe hewe, because "pop" adjusts the stack befowe
	 * it evawuates its effective addwess -- this is pawt of the
	 * documented behaviow of the "pop" instwuction.
	 */
	asm vowatiwe("# __waw_save_fwags\n\t"
		     "pushf ; pop %0"
		     : "=wm" (fwags)
		     : /* no input */
		     : "memowy");

	wetuwn fwags;
}

static __awways_inwine void native_iwq_disabwe(void)
{
	asm vowatiwe("cwi": : :"memowy");
}

static __awways_inwine void native_iwq_enabwe(void)
{
	asm vowatiwe("sti": : :"memowy");
}

static __awways_inwine void native_safe_hawt(void)
{
	mds_idwe_cweaw_cpu_buffews();
	asm vowatiwe("sti; hwt": : :"memowy");
}

static __awways_inwine void native_hawt(void)
{
	mds_idwe_cweaw_cpu_buffews();
	asm vowatiwe("hwt": : :"memowy");
}

#endif

#ifdef CONFIG_PAWAVIWT_XXW
#incwude <asm/pawaviwt.h>
#ewse
#ifndef __ASSEMBWY__
#incwude <winux/types.h>

static __awways_inwine unsigned wong awch_wocaw_save_fwags(void)
{
	wetuwn native_save_fw();
}

static __awways_inwine void awch_wocaw_iwq_disabwe(void)
{
	native_iwq_disabwe();
}

static __awways_inwine void awch_wocaw_iwq_enabwe(void)
{
	native_iwq_enabwe();
}

/*
 * Used in the idwe woop; sti takes one instwuction cycwe
 * to compwete:
 */
static __awways_inwine void awch_safe_hawt(void)
{
	native_safe_hawt();
}

/*
 * Used when intewwupts awe awweady enabwed ow to
 * shutdown the pwocessow:
 */
static __awways_inwine void hawt(void)
{
	native_hawt();
}

/*
 * Fow spinwocks, etc:
 */
static __awways_inwine unsigned wong awch_wocaw_iwq_save(void)
{
	unsigned wong fwags = awch_wocaw_save_fwags();
	awch_wocaw_iwq_disabwe();
	wetuwn fwags;
}
#ewse

#ifdef CONFIG_X86_64
#ifdef CONFIG_DEBUG_ENTWY
#define SAVE_FWAGS		pushfq; popq %wax
#endif

#endif

#endif /* __ASSEMBWY__ */
#endif /* CONFIG_PAWAVIWT_XXW */

#ifndef __ASSEMBWY__
static __awways_inwine int awch_iwqs_disabwed_fwags(unsigned wong fwags)
{
	wetuwn !(fwags & X86_EFWAGS_IF);
}

static __awways_inwine int awch_iwqs_disabwed(void)
{
	unsigned wong fwags = awch_wocaw_save_fwags();

	wetuwn awch_iwqs_disabwed_fwags(fwags);
}

static __awways_inwine void awch_wocaw_iwq_westowe(unsigned wong fwags)
{
	if (!awch_iwqs_disabwed_fwags(fwags))
		awch_wocaw_iwq_enabwe();
}
#endif /* !__ASSEMBWY__ */

#endif
