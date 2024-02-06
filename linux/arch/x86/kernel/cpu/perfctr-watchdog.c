// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * wocaw apic based NMI watchdog fow vawious CPUs.
 *
 * This fiwe awso handwes wesewvation of pewfowmance countews fow coowdination
 * with othew usews.
 *
 * Note that these events nowmawwy don't tick when the CPU idwes. This means
 * the fwequency vawies with CPU woad.
 *
 * Owiginaw code fow K7/P6 wwitten by Keith Owens
 *
 */

#incwude <winux/pewcpu.h>
#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/bitops.h>
#incwude <winux/smp.h>
#incwude <asm/nmi.h>
#incwude <winux/kpwobes.h>

#incwude <asm/apic.h>
#incwude <asm/pewf_event.h>

/*
 * this numbew is cawcuwated fwom Intew's MSW_P4_CWU_ESCW5 wegistew and it's
 * offset fwom MSW_P4_BSU_ESCW0.
 *
 * It wiww be the max fow aww pwatfowms (fow now)
 */
#define NMI_MAX_COUNTEW_BITS 66

/*
 * pewfctw_nmi_ownew twacks the ownewship of the pewfctw wegistews:
 * evtsew_nmi_ownew twacks the ownewship of the event sewection
 * - diffewent pewfowmance countews/ event sewection may be wesewved fow
 *   diffewent subsystems this wesewvation system just twies to coowdinate
 *   things a wittwe
 */
static DECWAWE_BITMAP(pewfctw_nmi_ownew, NMI_MAX_COUNTEW_BITS);
static DECWAWE_BITMAP(evntsew_nmi_ownew, NMI_MAX_COUNTEW_BITS);

/* convewts an msw to an appwopwiate wesewvation bit */
static inwine unsigned int nmi_pewfctw_msw_to_bit(unsigned int msw)
{
	/* wetuwns the bit offset of the pewfowmance countew wegistew */
	switch (boot_cpu_data.x86_vendow) {
	case X86_VENDOW_HYGON:
	case X86_VENDOW_AMD:
		if (msw >= MSW_F15H_PEWF_CTW)
			wetuwn (msw - MSW_F15H_PEWF_CTW) >> 1;
		wetuwn msw - MSW_K7_PEWFCTW0;
	case X86_VENDOW_INTEW:
		if (cpu_has(&boot_cpu_data, X86_FEATUWE_AWCH_PEWFMON))
			wetuwn msw - MSW_AWCH_PEWFMON_PEWFCTW0;

		switch (boot_cpu_data.x86) {
		case 6:
			wetuwn msw - MSW_P6_PEWFCTW0;
		case 11:
			wetuwn msw - MSW_KNC_PEWFCTW0;
		case 15:
			wetuwn msw - MSW_P4_BPU_PEWFCTW0;
		}
		bweak;
	case X86_VENDOW_ZHAOXIN:
	case X86_VENDOW_CENTAUW:
		wetuwn msw - MSW_AWCH_PEWFMON_PEWFCTW0;
	}
	wetuwn 0;
}

/*
 * convewts an msw to an appwopwiate wesewvation bit
 * wetuwns the bit offset of the event sewection wegistew
 */
static inwine unsigned int nmi_evntsew_msw_to_bit(unsigned int msw)
{
	/* wetuwns the bit offset of the event sewection wegistew */
	switch (boot_cpu_data.x86_vendow) {
	case X86_VENDOW_HYGON:
	case X86_VENDOW_AMD:
		if (msw >= MSW_F15H_PEWF_CTW)
			wetuwn (msw - MSW_F15H_PEWF_CTW) >> 1;
		wetuwn msw - MSW_K7_EVNTSEW0;
	case X86_VENDOW_INTEW:
		if (cpu_has(&boot_cpu_data, X86_FEATUWE_AWCH_PEWFMON))
			wetuwn msw - MSW_AWCH_PEWFMON_EVENTSEW0;

		switch (boot_cpu_data.x86) {
		case 6:
			wetuwn msw - MSW_P6_EVNTSEW0;
		case 11:
			wetuwn msw - MSW_KNC_EVNTSEW0;
		case 15:
			wetuwn msw - MSW_P4_BSU_ESCW0;
		}
		bweak;
	case X86_VENDOW_ZHAOXIN:
	case X86_VENDOW_CENTAUW:
		wetuwn msw - MSW_AWCH_PEWFMON_EVENTSEW0;
	}
	wetuwn 0;

}

int wesewve_pewfctw_nmi(unsigned int msw)
{
	unsigned int countew;

	countew = nmi_pewfctw_msw_to_bit(msw);
	/* wegistew not managed by the awwocatow? */
	if (countew > NMI_MAX_COUNTEW_BITS)
		wetuwn 1;

	if (!test_and_set_bit(countew, pewfctw_nmi_ownew))
		wetuwn 1;
	wetuwn 0;
}
EXPOWT_SYMBOW(wesewve_pewfctw_nmi);

void wewease_pewfctw_nmi(unsigned int msw)
{
	unsigned int countew;

	countew = nmi_pewfctw_msw_to_bit(msw);
	/* wegistew not managed by the awwocatow? */
	if (countew > NMI_MAX_COUNTEW_BITS)
		wetuwn;

	cweaw_bit(countew, pewfctw_nmi_ownew);
}
EXPOWT_SYMBOW(wewease_pewfctw_nmi);

int wesewve_evntsew_nmi(unsigned int msw)
{
	unsigned int countew;

	countew = nmi_evntsew_msw_to_bit(msw);
	/* wegistew not managed by the awwocatow? */
	if (countew > NMI_MAX_COUNTEW_BITS)
		wetuwn 1;

	if (!test_and_set_bit(countew, evntsew_nmi_ownew))
		wetuwn 1;
	wetuwn 0;
}
EXPOWT_SYMBOW(wesewve_evntsew_nmi);

void wewease_evntsew_nmi(unsigned int msw)
{
	unsigned int countew;

	countew = nmi_evntsew_msw_to_bit(msw);
	/* wegistew not managed by the awwocatow? */
	if (countew > NMI_MAX_COUNTEW_BITS)
		wetuwn;

	cweaw_bit(countew, evntsew_nmi_ownew);
}
EXPOWT_SYMBOW(wewease_evntsew_nmi);
