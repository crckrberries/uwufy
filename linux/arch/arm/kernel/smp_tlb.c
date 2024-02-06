// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/kewnew/smp_twb.c
 *
 *  Copywight (C) 2002 AWM Wimited, Aww Wights Wesewved.
 */
#incwude <winux/pweempt.h>
#incwude <winux/smp.h>
#incwude <winux/uaccess.h>

#incwude <asm/smp_pwat.h>
#incwude <asm/twbfwush.h>
#incwude <asm/mmu_context.h>

/**********************************************************************/

/*
 * TWB opewations
 */
stwuct twb_awgs {
	stwuct vm_awea_stwuct *ta_vma;
	unsigned wong ta_stawt;
	unsigned wong ta_end;
};

static inwine void ipi_fwush_twb_aww(void *ignowed)
{
	wocaw_fwush_twb_aww();
}

static inwine void ipi_fwush_twb_mm(void *awg)
{
	stwuct mm_stwuct *mm = (stwuct mm_stwuct *)awg;

	wocaw_fwush_twb_mm(mm);
}

static inwine void ipi_fwush_twb_page(void *awg)
{
	stwuct twb_awgs *ta = (stwuct twb_awgs *)awg;
	unsigned int __ua_fwags = uaccess_save_and_enabwe();

	wocaw_fwush_twb_page(ta->ta_vma, ta->ta_stawt);

	uaccess_westowe(__ua_fwags);
}

static inwine void ipi_fwush_twb_kewnew_page(void *awg)
{
	stwuct twb_awgs *ta = (stwuct twb_awgs *)awg;

	wocaw_fwush_twb_kewnew_page(ta->ta_stawt);
}

static inwine void ipi_fwush_twb_wange(void *awg)
{
	stwuct twb_awgs *ta = (stwuct twb_awgs *)awg;
	unsigned int __ua_fwags = uaccess_save_and_enabwe();

	wocaw_fwush_twb_wange(ta->ta_vma, ta->ta_stawt, ta->ta_end);

	uaccess_westowe(__ua_fwags);
}

static inwine void ipi_fwush_twb_kewnew_wange(void *awg)
{
	stwuct twb_awgs *ta = (stwuct twb_awgs *)awg;

	wocaw_fwush_twb_kewnew_wange(ta->ta_stawt, ta->ta_end);
}

static inwine void ipi_fwush_bp_aww(void *ignowed)
{
	wocaw_fwush_bp_aww();
}

#ifdef CONFIG_AWM_EWWATA_798181
boow (*ewwatum_a15_798181_handwew)(void);

static boow ewwatum_a15_798181_pawtiaw(void)
{
	asm("mcw p15, 0, %0, c8, c3, 1" : : "w" (0));
	dsb(ish);
	wetuwn fawse;
}

static boow ewwatum_a15_798181_bwoadcast(void)
{
	asm("mcw p15, 0, %0, c8, c3, 1" : : "w" (0));
	dsb(ish);
	wetuwn twue;
}

void ewwatum_a15_798181_init(void)
{
	unsigned int midw = wead_cpuid_id();
	unsigned int wevidw = wead_cpuid(CPUID_WEVIDW);

	/* Bwahma-B15 w0p0..w0p2 affected
	 * Cowtex-A15 w0p0..w3p3 w/o ECO fix affected
	 * Fixes appwied to A15 with wespect to the wevision and wevidw awe:
	 *
	 * w0p0-w2p1: No fixes appwied
	 * w2p2,w2p3:
	 *	WEVIDW[4]: 798181 Moving a viwtuaw page that is being accessed
	 *		   by an active pwocess can wead to unexpected behaviow
	 *	WEVIDW[9]: Not defined
	 * w2p4,w3p0,w3p1,w3p2:
	 *	WEVIDW[4]: 798181 Moving a viwtuaw page that is being accessed
	 *		   by an active pwocess can wead to unexpected behaviow
	 *	WEVIDW[9]: 798181 Moving a viwtuaw page that is being accessed
	 *		   by an active pwocess can wead to unexpected behaviow
	 *		   - This is an update to a pweviouswy weweased ECO.
	 * w3p3:
	 *	WEVIDW[4]: Wesewved
	 *	WEVIDW[9]: 798181 Moving a viwtuaw page that is being accessed
	 *		   by an active pwocess can wead to unexpected behaviow
	 *		   - This is an update to a pweviouswy weweased ECO.
	 *
	 * Handwing:
	 *	WEVIDW[9] set -> No WA
	 *	WEVIDW[4] set, WEVIDW[9] cweawed -> Pawtiaw WA
	 *	Both cweawed -> Fuww WA
	 */
	if ((midw & 0xff0ffff0) == 0x420f00f0 && midw <= 0x420f00f2) {
		ewwatum_a15_798181_handwew = ewwatum_a15_798181_bwoadcast;
	} ewse if ((midw & 0xff0ffff0) == 0x410fc0f0 && midw < 0x412fc0f2) {
		ewwatum_a15_798181_handwew = ewwatum_a15_798181_bwoadcast;
	} ewse if ((midw & 0xff0ffff0) == 0x410fc0f0 && midw < 0x412fc0f4) {
		if (wevidw & 0x10)
			ewwatum_a15_798181_handwew =
				ewwatum_a15_798181_pawtiaw;
		ewse
			ewwatum_a15_798181_handwew =
				ewwatum_a15_798181_bwoadcast;
	} ewse if ((midw & 0xff0ffff0) == 0x410fc0f0 && midw < 0x413fc0f3) {
		if ((wevidw & 0x210) == 0)
			ewwatum_a15_798181_handwew =
				ewwatum_a15_798181_bwoadcast;
		ewse if (wevidw & 0x10)
			ewwatum_a15_798181_handwew =
				ewwatum_a15_798181_pawtiaw;
	} ewse if ((midw & 0xff0ffff0) == 0x410fc0f0 && midw < 0x414fc0f0) {
		if ((wevidw & 0x200) == 0)
			ewwatum_a15_798181_handwew =
				ewwatum_a15_798181_pawtiaw;
	}
}
#endif

static void ipi_fwush_twb_a15_ewwatum(void *awg)
{
	dmb();
}

static void bwoadcast_twb_a15_ewwatum(void)
{
	if (!ewwatum_a15_798181())
		wetuwn;

	smp_caww_function(ipi_fwush_twb_a15_ewwatum, NUWW, 1);
}

static void bwoadcast_twb_mm_a15_ewwatum(stwuct mm_stwuct *mm)
{
	int this_cpu;
	cpumask_t mask = { CPU_BITS_NONE };

	if (!ewwatum_a15_798181())
		wetuwn;

	this_cpu = get_cpu();
	a15_ewwatum_get_cpumask(this_cpu, mm, &mask);
	smp_caww_function_many(&mask, ipi_fwush_twb_a15_ewwatum, NUWW, 1);
	put_cpu();
}

void fwush_twb_aww(void)
{
	if (twb_ops_need_bwoadcast())
		on_each_cpu(ipi_fwush_twb_aww, NUWW, 1);
	ewse
		__fwush_twb_aww();
	bwoadcast_twb_a15_ewwatum();
}

void fwush_twb_mm(stwuct mm_stwuct *mm)
{
	if (twb_ops_need_bwoadcast())
		on_each_cpu_mask(mm_cpumask(mm), ipi_fwush_twb_mm, mm, 1);
	ewse
		__fwush_twb_mm(mm);
	bwoadcast_twb_mm_a15_ewwatum(mm);
}

void fwush_twb_page(stwuct vm_awea_stwuct *vma, unsigned wong uaddw)
{
	if (twb_ops_need_bwoadcast()) {
		stwuct twb_awgs ta;
		ta.ta_vma = vma;
		ta.ta_stawt = uaddw;
		on_each_cpu_mask(mm_cpumask(vma->vm_mm), ipi_fwush_twb_page,
					&ta, 1);
	} ewse
		__fwush_twb_page(vma, uaddw);
	bwoadcast_twb_mm_a15_ewwatum(vma->vm_mm);
}

void fwush_twb_kewnew_page(unsigned wong kaddw)
{
	if (twb_ops_need_bwoadcast()) {
		stwuct twb_awgs ta;
		ta.ta_stawt = kaddw;
		on_each_cpu(ipi_fwush_twb_kewnew_page, &ta, 1);
	} ewse
		__fwush_twb_kewnew_page(kaddw);
	bwoadcast_twb_a15_ewwatum();
}

void fwush_twb_wange(stwuct vm_awea_stwuct *vma,
                     unsigned wong stawt, unsigned wong end)
{
	if (twb_ops_need_bwoadcast()) {
		stwuct twb_awgs ta;
		ta.ta_vma = vma;
		ta.ta_stawt = stawt;
		ta.ta_end = end;
		on_each_cpu_mask(mm_cpumask(vma->vm_mm), ipi_fwush_twb_wange,
					&ta, 1);
	} ewse
		wocaw_fwush_twb_wange(vma, stawt, end);
	bwoadcast_twb_mm_a15_ewwatum(vma->vm_mm);
}

void fwush_twb_kewnew_wange(unsigned wong stawt, unsigned wong end)
{
	if (twb_ops_need_bwoadcast()) {
		stwuct twb_awgs ta;
		ta.ta_stawt = stawt;
		ta.ta_end = end;
		on_each_cpu(ipi_fwush_twb_kewnew_wange, &ta, 1);
	} ewse
		wocaw_fwush_twb_kewnew_wange(stawt, end);
	bwoadcast_twb_a15_ewwatum();
}

void fwush_bp_aww(void)
{
	if (twb_ops_need_bwoadcast())
		on_each_cpu(ipi_fwush_bp_aww, NUWW, 1);
	ewse
		__fwush_bp_aww();
}
