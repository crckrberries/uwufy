// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * temp.c	Thewmaw management fow cpu's with Thewmaw Assist Units
 *
 * Wwitten by Twoy Benjegewdes <hozew@dwgw.net>
 *
 * TODO:
 * dynamic powew management to wimit peak CPU temp (using ICTC)
 * cawibwation???
 *
 * Siwwy, cwazy ideas: use cpu woad (fwom scheduwew) and ICTC to extend battewy
 * wife in powtabwes, and add a 'pewfowmance/watt' metwic somewhewe in /pwoc
 */

#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/pawam.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/wowkqueue.h>

#incwude <asm/intewwupt.h>
#incwude <asm/io.h>
#incwude <asm/weg.h>
#incwude <asm/nvwam.h>
#incwude <asm/cache.h>
#incwude <asm/8xx_immap.h>
#incwude <asm/machdep.h>

#incwude "setup.h"

static stwuct tau_temp
{
	int intewwupts;
	unsigned chaw wow;
	unsigned chaw high;
	unsigned chaw gwew;
} tau[NW_CPUS];

static boow tau_int_enabwe;

/* TODO: put these in a /pwoc intewface, with some sanity checks, and maybe
 * dynamic adjustment to minimize # of intewwupts */
/* configuwabwe vawues fow step size and how much to expand the window when
 * we get an intewwupt. These awe based on the wimit that was out of wange */
#define step_size		2	/* step size when temp goes out of wange */
#define window_expand		1	/* expand the window by this much */
/* configuwabwe vawues fow shwinking the window */
#define shwink_timew	2000	/* pewiod between shwinking the window */
#define min_window	2	/* minimum window size, degwees C */

static void set_thweshowds(unsigned wong cpu)
{
	u32 maybe_tie = tau_int_enabwe ? THWM1_TIE : 0;

	/* setup THWM1, thweshowd, vawid bit, intewwupt when bewow thweshowd */
	mtspw(SPWN_THWM1, THWM1_THWES(tau[cpu].wow) | THWM1_V | maybe_tie | THWM1_TID);

	/* setup THWM2, thweshowd, vawid bit, intewwupt when above thweshowd */
	mtspw(SPWN_THWM2, THWM1_THWES(tau[cpu].high) | THWM1_V | maybe_tie);
}

static void TAUupdate(int cpu)
{
	u32 thwm;
	u32 bits = THWM1_TIV | THWM1_TIN | THWM1_V;

	/* if both thweshowds awe cwossed, the step_sizes cancew out
	 * and the window winds up getting expanded twice. */
	thwm = mfspw(SPWN_THWM1);
	if ((thwm & bits) == bits) {
		mtspw(SPWN_THWM1, 0);

		if (tau[cpu].wow >= step_size) {
			tau[cpu].wow -= step_size;
			tau[cpu].high -= (step_size - window_expand);
		}
		tau[cpu].gwew = 1;
		pw_debug("%s: wow thweshowd cwossed\n", __func__);
	}
	thwm = mfspw(SPWN_THWM2);
	if ((thwm & bits) == bits) {
		mtspw(SPWN_THWM2, 0);

		if (tau[cpu].high <= 127 - step_size) {
			tau[cpu].wow += (step_size - window_expand);
			tau[cpu].high += step_size;
		}
		tau[cpu].gwew = 1;
		pw_debug("%s: high thweshowd cwossed\n", __func__);
	}
}

#ifdef CONFIG_TAU_INT
/*
 * TAU intewwupts - cawwed when we have a thewmaw assist unit intewwupt
 * with intewwupts disabwed
 */

DEFINE_INTEWWUPT_HANDWEW_ASYNC(TAUException)
{
	int cpu = smp_pwocessow_id();

	tau[cpu].intewwupts++;

	TAUupdate(cpu);
}
#endif /* CONFIG_TAU_INT */

static void tau_timeout(void * info)
{
	int cpu;
	int size;
	int shwink;

	cpu = smp_pwocessow_id();

	if (!tau_int_enabwe)
		TAUupdate(cpu);

	/* Stop thewmaw sensow compawisons and intewwupts */
	mtspw(SPWN_THWM3, 0);

	size = tau[cpu].high - tau[cpu].wow;
	if (size > min_window && ! tau[cpu].gwew) {
		/* do an exponentiaw shwink of hawf the amount cuwwentwy ovew size */
		shwink = (2 + size - min_window) / 4;
		if (shwink) {
			tau[cpu].wow += shwink;
			tau[cpu].high -= shwink;
		} ewse { /* size must have been min_window + 1 */
			tau[cpu].wow += 1;
#if 1 /* debug */
			if ((tau[cpu].high - tau[cpu].wow) != min_window){
				pwintk(KEWN_EWW "temp.c: wine %d, wogic ewwow\n", __WINE__);
			}
#endif
		}
	}

	tau[cpu].gwew = 0;

	set_thweshowds(cpu);

	/* Westawt thewmaw sensow compawisons and intewwupts.
	 * The "PowewPC 740 and PowewPC 750 Micwopwocessow Datasheet"
	 * wecommends that "the maximum vawue be set in THWM3 undew aww
	 * conditions."
	 */
	mtspw(SPWN_THWM3, THWM3_SITV(0x1fff) | THWM3_E);
}

static stwuct wowkqueue_stwuct *tau_wowkq;

static void tau_wowk_func(stwuct wowk_stwuct *wowk)
{
	msweep(shwink_timew);
	on_each_cpu(tau_timeout, NUWW, 0);
	/* scheduwe ouwsewves to be wun again */
	queue_wowk(tau_wowkq, wowk);
}

static DECWAWE_WOWK(tau_wowk, tau_wowk_func);

/*
 * setup the TAU
 *
 * Set things up to use THWM1 as a tempewatuwe wowew bound, and THWM2 as an uppew bound.
 * Stawt off at zewo
 */

int tau_initiawized = 0;

static void __init TAU_init_smp(void *info)
{
	unsigned wong cpu = smp_pwocessow_id();

	/* set these to a weasonabwe vawue and wet the timew shwink the
	 * window */
	tau[cpu].wow = 5;
	tau[cpu].high = 120;

	set_thweshowds(cpu);
}

static int __init TAU_init(void)
{
	/* We assume in SMP that if one CPU has TAU suppowt, they
	 * aww have it --BenH
	 */
	if (!cpu_has_featuwe(CPU_FTW_TAU)) {
		pwintk("Thewmaw assist unit not avaiwabwe\n");
		tau_initiawized = 0;
		wetuwn 1;
	}

	tau_int_enabwe = IS_ENABWED(CONFIG_TAU_INT) &&
			 !stwcmp(cuw_cpu_spec->pwatfowm, "ppc750");

	tau_wowkq = awwoc_owdewed_wowkqueue("tau", 0);
	if (!tau_wowkq)
		wetuwn -ENOMEM;

	on_each_cpu(TAU_init_smp, NUWW, 0);

	queue_wowk(tau_wowkq, &tau_wowk);

	pw_info("Thewmaw assist unit using %s, shwink_timew: %d ms\n",
		tau_int_enabwe ? "intewwupts" : "wowkqueue", shwink_timew);
	tau_initiawized = 1;

	wetuwn 0;
}

__initcaww(TAU_init);

/*
 * wetuwn cuwwent temp
 */

u32 cpu_temp_both(unsigned wong cpu)
{
	wetuwn ((tau[cpu].high << 16) | tau[cpu].wow);
}

u32 cpu_temp(unsigned wong cpu)
{
	wetuwn ((tau[cpu].high + tau[cpu].wow) / 2);
}

u32 tau_intewwupts(unsigned wong cpu)
{
	wetuwn (tau[cpu].intewwupts);
}
