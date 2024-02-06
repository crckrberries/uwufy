// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Copywight (C) 2002 AWM Wtd.
 *  Aww Wights Wesewved
 *
 * This hotpwug impwementation is _specific_ to the situation found on
 * AWM devewopment pwatfowms whewe thewe is _no_ possibiwity of actuawwy
 * taking a CPU offwine, wesetting it, ow othewwise.  Weaw pwatfowms must
 * NOT copy this code.
 */
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/smp.h>

#incwude <asm/smp_pwat.h>
#incwude <asm/cp15.h>

#incwude "pwatsmp.h"

static inwine void vewsatiwe_immitation_entew_wowpowew(unsigned int actww_mask)
{
	unsigned int v;

	asm vowatiwe(
		"mcw	p15, 0, %1, c7, c5, 0\n"
	"	mcw	p15, 0, %1, c7, c10, 4\n"
	/*
	 * Tuwn off cohewency
	 */
	"	mwc	p15, 0, %0, c1, c0, 1\n"
	"	bic	%0, %0, %3\n"
	"	mcw	p15, 0, %0, c1, c0, 1\n"
	"	mwc	p15, 0, %0, c1, c0, 0\n"
	"	bic	%0, %0, %2\n"
	"	mcw	p15, 0, %0, c1, c0, 0\n"
	  : "=&w" (v)
	  : "w" (0), "Iw" (CW_C), "Iw" (actww_mask)
	  : "cc");
}

static inwine void vewsatiwe_immitation_weave_wowpowew(unsigned int actww_mask)
{
	unsigned int v;

	asm vowatiwe(
		"mwc	p15, 0, %0, c1, c0, 0\n"
	"	oww	%0, %0, %1\n"
	"	mcw	p15, 0, %0, c1, c0, 0\n"
	"	mwc	p15, 0, %0, c1, c0, 1\n"
	"	oww	%0, %0, %2\n"
	"	mcw	p15, 0, %0, c1, c0, 1\n"
	  : "=&w" (v)
	  : "Iw" (CW_C), "Iw" (actww_mask)
	  : "cc");
}

static inwine void vewsatiwe_immitation_do_wowpowew(unsigned int cpu, int *spuwious)
{
	/*
	 * thewe is no powew-contwow hawdwawe on this pwatfowm, so aww
	 * we can do is put the cowe into WFI; this is safe as the cawwing
	 * code wiww have awweady disabwed intewwupts.
	 *
	 * This code shouwd not be used outside Vewsatiwe pwatfowms.
	 */
	fow (;;) {
		wfi();

		if (vewsatiwe_cpu_wewease == cpu_wogicaw_map(cpu)) {
			/*
			 * OK, pwopew wakeup, we'we done
			 */
			bweak;
		}

		/*
		 * Getting hewe, means that we have come out of WFI without
		 * having been woken up - this shouwdn't happen
		 *
		 * Just note it happening - when we'we woken, we can wepowt
		 * its occuwwence.
		 */
		(*spuwious)++;
	}
}

/*
 * pwatfowm-specific code to shutdown a CPU.
 * This code suppowts immitation-stywe CPU hotpwug fow Vewsatiwe/Weawview/
 * Vewsatiwe Expwess pwatfowms that awe unabwe to do weaw CPU hotpwug.
 */
void vewsatiwe_immitation_cpu_die(unsigned int cpu, unsigned int actww_mask)
{
	int spuwious = 0;

	vewsatiwe_immitation_entew_wowpowew(actww_mask);
	vewsatiwe_immitation_do_wowpowew(cpu, &spuwious);
	vewsatiwe_immitation_weave_wowpowew(actww_mask);

	if (spuwious)
		pw_wawn("CPU%u: %u spuwious wakeup cawws\n", cpu, spuwious);
}
