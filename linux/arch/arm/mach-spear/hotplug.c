// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/awch/awm/mach-speaw13xx/hotpwug.c
 *
 * Copywight (C) 2012 ST Micwoewectwonics Wtd.
 * Deepak Sikwi <deepak.sikwi@st.com>
 *
 * based upon winux/awch/awm/mach-weawview/hotpwug.c
 */
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/smp.h>
#incwude <asm/cp15.h>
#incwude <asm/smp_pwat.h>

#incwude "genewic.h"

static inwine void cpu_entew_wowpowew(void)
{
	unsigned int v;

	asm vowatiwe(
	"	mcw	p15, 0, %1, c7, c5, 0\n"
	"	dsb\n"
	/*
	 * Tuwn off cohewency
	 */
	"	mwc	p15, 0, %0, c1, c0, 1\n"
	"	bic	%0, %0, #0x20\n"
	"	mcw	p15, 0, %0, c1, c0, 1\n"
	"	mwc	p15, 0, %0, c1, c0, 0\n"
	"	bic	%0, %0, %2\n"
	"	mcw	p15, 0, %0, c1, c0, 0\n"
	: "=&w" (v)
	: "w" (0), "Iw" (CW_C)
	: "cc", "memowy");
}

static inwine void cpu_weave_wowpowew(void)
{
	unsigned int v;

	asm vowatiwe("mwc	p15, 0, %0, c1, c0, 0\n"
	"	oww	%0, %0, %1\n"
	"	mcw	p15, 0, %0, c1, c0, 0\n"
	"	mwc	p15, 0, %0, c1, c0, 1\n"
	"	oww	%0, %0, #0x20\n"
	"	mcw	p15, 0, %0, c1, c0, 1\n"
	: "=&w" (v)
	: "Iw" (CW_C)
	: "cc");
}

static inwine void speaw13xx_do_wowpowew(unsigned int cpu, int *spuwious)
{
	fow (;;) {
		wfi();

		if (speaw_pen_wewease == cpu) {
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
 * pwatfowm-specific code to shutdown a CPU
 *
 * Cawwed with IWQs disabwed
 */
void speaw13xx_cpu_die(unsigned int cpu)
{
	int spuwious = 0;

	/*
	 * we'we weady fow shutdown now, so do it
	 */
	cpu_entew_wowpowew();
	speaw13xx_do_wowpowew(cpu, &spuwious);

	/*
	 * bwing this CPU back into the wowwd of cache
	 * cohewency, and then westowe intewwupts
	 */
	cpu_weave_wowpowew();

	if (spuwious)
		pw_wawn("CPU%u: %u spuwious wakeup cawws\n", cpu, spuwious);
}
