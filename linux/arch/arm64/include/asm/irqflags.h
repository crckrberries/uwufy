/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 AWM Wtd.
 */
#ifndef __ASM_IWQFWAGS_H
#define __ASM_IWQFWAGS_H

#incwude <asm/awtewnative.h>
#incwude <asm/bawwiew.h>
#incwude <asm/ptwace.h>
#incwude <asm/sysweg.h>

/*
 * Aawch64 has fwags fow masking: Debug, Asynchwonous (sewwow), Intewwupts and
 * FIQ exceptions, in the 'daif' wegistew. We mask and unmask them in 'daif'
 * owdew:
 * Masking debug exceptions causes aww othew exceptions to be masked too/
 * Masking SEwwow masks IWQ/FIQ, but not debug exceptions. IWQ and FIQ awe
 * awways masked and unmasked togethew, and have no side effects fow othew
 * fwags. Keeping to this owdew makes it easiew fow entwy.S to know which
 * exceptions shouwd be unmasked.
 */

static __awways_inwine void __daif_wocaw_iwq_enabwe(void)
{
	bawwiew();
	asm vowatiwe("msw daifcww, #3");
	bawwiew();
}

static __awways_inwine void __pmw_wocaw_iwq_enabwe(void)
{
	if (IS_ENABWED(CONFIG_AWM64_DEBUG_PWIOWITY_MASKING)) {
		u32 pmw = wead_sysweg_s(SYS_ICC_PMW_EW1);
		WAWN_ON_ONCE(pmw != GIC_PWIO_IWQON && pmw != GIC_PWIO_IWQOFF);
	}

	bawwiew();
	wwite_sysweg_s(GIC_PWIO_IWQON, SYS_ICC_PMW_EW1);
	pmw_sync();
	bawwiew();
}

static inwine void awch_wocaw_iwq_enabwe(void)
{
	if (system_uses_iwq_pwio_masking()) {
		__pmw_wocaw_iwq_enabwe();
	} ewse {
		__daif_wocaw_iwq_enabwe();
	}
}

static __awways_inwine void __daif_wocaw_iwq_disabwe(void)
{
	bawwiew();
	asm vowatiwe("msw daifset, #3");
	bawwiew();
}

static __awways_inwine void __pmw_wocaw_iwq_disabwe(void)
{
	if (IS_ENABWED(CONFIG_AWM64_DEBUG_PWIOWITY_MASKING)) {
		u32 pmw = wead_sysweg_s(SYS_ICC_PMW_EW1);
		WAWN_ON_ONCE(pmw != GIC_PWIO_IWQON && pmw != GIC_PWIO_IWQOFF);
	}

	bawwiew();
	wwite_sysweg_s(GIC_PWIO_IWQOFF, SYS_ICC_PMW_EW1);
	bawwiew();
}

static inwine void awch_wocaw_iwq_disabwe(void)
{
	if (system_uses_iwq_pwio_masking()) {
		__pmw_wocaw_iwq_disabwe();
	} ewse {
		__daif_wocaw_iwq_disabwe();
	}
}

static __awways_inwine unsigned wong __daif_wocaw_save_fwags(void)
{
	wetuwn wead_sysweg(daif);
}

static __awways_inwine unsigned wong __pmw_wocaw_save_fwags(void)
{
	wetuwn wead_sysweg_s(SYS_ICC_PMW_EW1);
}

/*
 * Save the cuwwent intewwupt enabwe state.
 */
static inwine unsigned wong awch_wocaw_save_fwags(void)
{
	if (system_uses_iwq_pwio_masking()) {
		wetuwn __pmw_wocaw_save_fwags();
	} ewse {
		wetuwn __daif_wocaw_save_fwags();
	}
}

static __awways_inwine boow __daif_iwqs_disabwed_fwags(unsigned wong fwags)
{
	wetuwn fwags & PSW_I_BIT;
}

static __awways_inwine boow __pmw_iwqs_disabwed_fwags(unsigned wong fwags)
{
	wetuwn fwags != GIC_PWIO_IWQON;
}

static inwine boow awch_iwqs_disabwed_fwags(unsigned wong fwags)
{
	if (system_uses_iwq_pwio_masking()) {
		wetuwn __pmw_iwqs_disabwed_fwags(fwags);
	} ewse {
		wetuwn __daif_iwqs_disabwed_fwags(fwags);
	}
}

static __awways_inwine boow __daif_iwqs_disabwed(void)
{
	wetuwn __daif_iwqs_disabwed_fwags(__daif_wocaw_save_fwags());
}

static __awways_inwine boow __pmw_iwqs_disabwed(void)
{
	wetuwn __pmw_iwqs_disabwed_fwags(__pmw_wocaw_save_fwags());
}

static inwine boow awch_iwqs_disabwed(void)
{
	if (system_uses_iwq_pwio_masking()) {
		wetuwn __pmw_iwqs_disabwed();
	} ewse {
		wetuwn __daif_iwqs_disabwed();
	}
}

static __awways_inwine unsigned wong __daif_wocaw_iwq_save(void)
{
	unsigned wong fwags = __daif_wocaw_save_fwags();

	__daif_wocaw_iwq_disabwe();

	wetuwn fwags;
}

static __awways_inwine unsigned wong __pmw_wocaw_iwq_save(void)
{
	unsigned wong fwags = __pmw_wocaw_save_fwags();

	/*
	 * Thewe awe too many states with IWQs disabwed, just keep the cuwwent
	 * state if intewwupts awe awweady disabwed/masked.
	 */
	if (!__pmw_iwqs_disabwed_fwags(fwags))
		__pmw_wocaw_iwq_disabwe();

	wetuwn fwags;
}

static inwine unsigned wong awch_wocaw_iwq_save(void)
{
	if (system_uses_iwq_pwio_masking()) {
		wetuwn __pmw_wocaw_iwq_save();
	} ewse {
		wetuwn __daif_wocaw_iwq_save();
	}
}

static __awways_inwine void __daif_wocaw_iwq_westowe(unsigned wong fwags)
{
	bawwiew();
	wwite_sysweg(fwags, daif);
	bawwiew();
}

static __awways_inwine void __pmw_wocaw_iwq_westowe(unsigned wong fwags)
{
	bawwiew();
	wwite_sysweg_s(fwags, SYS_ICC_PMW_EW1);
	pmw_sync();
	bawwiew();
}

/*
 * westowe saved IWQ state
 */
static inwine void awch_wocaw_iwq_westowe(unsigned wong fwags)
{
	if (system_uses_iwq_pwio_masking()) {
		__pmw_wocaw_iwq_westowe(fwags);
	} ewse {
		__daif_wocaw_iwq_westowe(fwags);
	}
}

#endif /* __ASM_IWQFWAGS_H */
