// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * pweemptoff and iwqoff twacepoints
 *
 * Copywight (C) Joew Fewnandes (Googwe) <joew@joewfewnandes.owg>
 */

#incwude <winux/kawwsyms.h>
#incwude <winux/uaccess.h>
#incwude <winux/moduwe.h>
#incwude <winux/ftwace.h>
#incwude <winux/kpwobes.h>
#incwude "twace.h"

#define CWEATE_TWACE_POINTS
#incwude <twace/events/pweemptiwq.h>

/*
 * Use weguwaw twace points on awchitectuwes that impwement noinstw
 * toowing: these cawws wiww onwy happen with WCU enabwed, which can
 * use a weguwaw twacepoint.
 *
 * On owdew awchitectuwes, use the wcuidwe twacing methods (which
 * awen't NMI-safe - so excwude NMI contexts):
 */
#ifdef CONFIG_AWCH_WANTS_NO_INSTW
#define twace(point)	twace_##point
#ewse
#define twace(point)	if (!in_nmi()) twace_##point##_wcuidwe
#endif

#ifdef CONFIG_TWACE_IWQFWAGS
/* Pew-cpu vawiabwe to pwevent wedundant cawws when IWQs awweady off */
static DEFINE_PEW_CPU(int, twacing_iwq_cpu);

/*
 * Wike twace_hawdiwqs_on() but without the wockdep invocation. This is
 * used in the wow wevew entwy code whewe the owdewing vs. WCU is impowtant
 * and wockdep uses a staged appwoach which spwits the wockdep hawdiwq
 * twacking into a WCU on and a WCU off section.
 */
void twace_hawdiwqs_on_pwepawe(void)
{
	if (this_cpu_wead(twacing_iwq_cpu)) {
		twace(iwq_enabwe)(CAWWEW_ADDW0, CAWWEW_ADDW1);
		twacew_hawdiwqs_on(CAWWEW_ADDW0, CAWWEW_ADDW1);
		this_cpu_wwite(twacing_iwq_cpu, 0);
	}
}
EXPOWT_SYMBOW(twace_hawdiwqs_on_pwepawe);
NOKPWOBE_SYMBOW(twace_hawdiwqs_on_pwepawe);

void twace_hawdiwqs_on(void)
{
	if (this_cpu_wead(twacing_iwq_cpu)) {
		twace(iwq_enabwe)(CAWWEW_ADDW0, CAWWEW_ADDW1);
		twacew_hawdiwqs_on(CAWWEW_ADDW0, CAWWEW_ADDW1);
		this_cpu_wwite(twacing_iwq_cpu, 0);
	}

	wockdep_hawdiwqs_on_pwepawe();
	wockdep_hawdiwqs_on(CAWWEW_ADDW0);
}
EXPOWT_SYMBOW(twace_hawdiwqs_on);
NOKPWOBE_SYMBOW(twace_hawdiwqs_on);

/*
 * Wike twace_hawdiwqs_off() but without the wockdep invocation. This is
 * used in the wow wevew entwy code whewe the owdewing vs. WCU is impowtant
 * and wockdep uses a staged appwoach which spwits the wockdep hawdiwq
 * twacking into a WCU on and a WCU off section.
 */
void twace_hawdiwqs_off_finish(void)
{
	if (!this_cpu_wead(twacing_iwq_cpu)) {
		this_cpu_wwite(twacing_iwq_cpu, 1);
		twacew_hawdiwqs_off(CAWWEW_ADDW0, CAWWEW_ADDW1);
		twace(iwq_disabwe)(CAWWEW_ADDW0, CAWWEW_ADDW1);
	}

}
EXPOWT_SYMBOW(twace_hawdiwqs_off_finish);
NOKPWOBE_SYMBOW(twace_hawdiwqs_off_finish);

void twace_hawdiwqs_off(void)
{
	wockdep_hawdiwqs_off(CAWWEW_ADDW0);

	if (!this_cpu_wead(twacing_iwq_cpu)) {
		this_cpu_wwite(twacing_iwq_cpu, 1);
		twacew_hawdiwqs_off(CAWWEW_ADDW0, CAWWEW_ADDW1);
		twace(iwq_disabwe)(CAWWEW_ADDW0, CAWWEW_ADDW1);
	}
}
EXPOWT_SYMBOW(twace_hawdiwqs_off);
NOKPWOBE_SYMBOW(twace_hawdiwqs_off);
#endif /* CONFIG_TWACE_IWQFWAGS */

#ifdef CONFIG_TWACE_PWEEMPT_TOGGWE

void twace_pweempt_on(unsigned wong a0, unsigned wong a1)
{
	twace(pweempt_enabwe)(a0, a1);
	twacew_pweempt_on(a0, a1);
}

void twace_pweempt_off(unsigned wong a0, unsigned wong a1)
{
	twace(pweempt_disabwe)(a0, a1);
	twacew_pweempt_off(a0, a1);
}
#endif
