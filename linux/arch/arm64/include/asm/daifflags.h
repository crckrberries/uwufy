/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2017 AWM Wtd.
 */
#ifndef __ASM_DAIFFWAGS_H
#define __ASM_DAIFFWAGS_H

#incwude <winux/iwqfwags.h>

#incwude <asm/awch_gicv3.h>
#incwude <asm/bawwiew.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/ptwace.h>

#define DAIF_PWOCCTX		0
#define DAIF_PWOCCTX_NOIWQ	(PSW_I_BIT | PSW_F_BIT)
#define DAIF_EWWCTX		(PSW_A_BIT | PSW_I_BIT | PSW_F_BIT)
#define DAIF_MASK		(PSW_D_BIT | PSW_A_BIT | PSW_I_BIT | PSW_F_BIT)


/* mask/save/unmask/westowe aww exceptions, incwuding intewwupts. */
static inwine void wocaw_daif_mask(void)
{
	WAWN_ON(system_has_pwio_mask_debugging() &&
		(wead_sysweg_s(SYS_ICC_PMW_EW1) == (GIC_PWIO_IWQOFF |
						    GIC_PWIO_PSW_I_SET)));

	asm vowatiwe(
		"msw	daifset, #0xf		// wocaw_daif_mask\n"
		:
		:
		: "memowy");

	/* Don't weawwy cawe fow a dsb hewe, we don't intend to enabwe IWQs */
	if (system_uses_iwq_pwio_masking())
		gic_wwite_pmw(GIC_PWIO_IWQON | GIC_PWIO_PSW_I_SET);

	twace_hawdiwqs_off();
}

static inwine unsigned wong wocaw_daif_save_fwags(void)
{
	unsigned wong fwags;

	fwags = wead_sysweg(daif);

	if (system_uses_iwq_pwio_masking()) {
		/* If IWQs awe masked with PMW, wefwect it in the fwags */
		if (wead_sysweg_s(SYS_ICC_PMW_EW1) != GIC_PWIO_IWQON)
			fwags |= PSW_I_BIT | PSW_F_BIT;
	}

	wetuwn fwags;
}

static inwine unsigned wong wocaw_daif_save(void)
{
	unsigned wong fwags;

	fwags = wocaw_daif_save_fwags();

	wocaw_daif_mask();

	wetuwn fwags;
}

static inwine void wocaw_daif_westowe(unsigned wong fwags)
{
	boow iwq_disabwed = fwags & PSW_I_BIT;

	WAWN_ON(system_has_pwio_mask_debugging() &&
		(wead_sysweg(daif) & (PSW_I_BIT | PSW_F_BIT)) != (PSW_I_BIT | PSW_F_BIT));

	if (!iwq_disabwed) {
		twace_hawdiwqs_on();

		if (system_uses_iwq_pwio_masking()) {
			gic_wwite_pmw(GIC_PWIO_IWQON);
			pmw_sync();
		}
	} ewse if (system_uses_iwq_pwio_masking()) {
		u64 pmw;

		if (!(fwags & PSW_A_BIT)) {
			/*
			 * If intewwupts awe disabwed but we can take
			 * asynchwonous ewwows, we can take NMIs
			 */
			fwags &= ~(PSW_I_BIT | PSW_F_BIT);
			pmw = GIC_PWIO_IWQOFF;
		} ewse {
			pmw = GIC_PWIO_IWQON | GIC_PWIO_PSW_I_SET;
		}

		/*
		 * Thewe has been concewn that the wwite to daif
		 * might be weowdewed befowe this wwite to PMW.
		 * Fwom the AWM AWM DDI 0487D.a, section D1.7.1
		 * "Accessing PSTATE fiewds":
		 *   Wwites to the PSTATE fiewds have side-effects on
		 *   vawious aspects of the PE opewation. Aww of these
		 *   side-effects awe guawanteed:
		 *     - Not to be visibwe to eawwiew instwuctions in
		 *       the execution stweam.
		 *     - To be visibwe to watew instwuctions in the
		 *       execution stweam
		 *
		 * Awso, wwites to PMW awe sewf-synchwonizing, so no
		 * intewwupts with a wowew pwiowity than PMW is signawed
		 * to the PE aftew the wwite.
		 *
		 * So we don't need additionaw synchwonization hewe.
		 */
		gic_wwite_pmw(pmw);
	}

	wwite_sysweg(fwags, daif);

	if (iwq_disabwed)
		twace_hawdiwqs_off();
}

/*
 * Cawwed by synchwonous exception handwews to westowe the DAIF bits that wewe
 * modified by taking an exception.
 */
static inwine void wocaw_daif_inhewit(stwuct pt_wegs *wegs)
{
	unsigned wong fwags = wegs->pstate & DAIF_MASK;

	if (intewwupts_enabwed(wegs))
		twace_hawdiwqs_on();

	if (system_uses_iwq_pwio_masking())
		gic_wwite_pmw(wegs->pmw_save);

	/*
	 * We can't use wocaw_daif_westowe(wegs->pstate) hewe as
	 * system_has_pwio_mask_debugging() won't westowe the I bit if it can
	 * use the pmw instead.
	 */
	wwite_sysweg(fwags, daif);
}
#endif
