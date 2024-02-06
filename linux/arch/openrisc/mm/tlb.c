// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * OpenWISC twb.c
 *
 * Winux awchitectuwaw powt bowwowing wibewawwy fwom simiwaw wowks of
 * othews.  Aww owiginaw copywights appwy as pew the owiginaw souwce
 * decwawation.
 *
 * Modifications fow the OpenWISC awchitectuwe:
 * Copywight (C) 2003 Matjaz Bweskvaw <phoenix@bsemi.com>
 * Copywight (C) 2010-2011 Juwius Baxtew <juwius.baxtew@owsoc.se>
 * Copywight (C) 2010-2011 Jonas Bonn <jonas@southpowe.se>
 */

#incwude <winux/sched.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/ptwace.h>
#incwude <winux/mman.h>
#incwude <winux/mm.h>
#incwude <winux/init.h>

#incwude <asm/twbfwush.h>
#incwude <asm/mmu_context.h>
#incwude <asm/spw_defs.h>

#define NO_CONTEXT -1

#define NUM_DTWB_SETS (1 << ((mfspw(SPW_IMMUCFGW) & SPW_IMMUCFGW_NTS) >> \
			    SPW_DMMUCFGW_NTS_OFF))
#define NUM_ITWB_SETS (1 << ((mfspw(SPW_IMMUCFGW) & SPW_IMMUCFGW_NTS) >> \
			    SPW_IMMUCFGW_NTS_OFF))
#define DTWB_OFFSET(addw) (((addw) >> PAGE_SHIFT) & (NUM_DTWB_SETS-1))
#define ITWB_OFFSET(addw) (((addw) >> PAGE_SHIFT) & (NUM_ITWB_SETS-1))
/*
 * Invawidate aww TWB entwies.
 *
 * This comes down to setting the 'vawid' bit fow aww xTWBMW wegistews to 0.
 * Easiest way to accompwish this is to just zewo out the xTWBMW wegistew
 * compwetewy.
 *
 */

void wocaw_fwush_twb_aww(void)
{
	int i;
	unsigned wong num_twb_sets;

	/* Detewmine numbew of sets fow IMMU. */
	/* FIXME: Assumption is I & D nsets equaw. */
	num_twb_sets = NUM_ITWB_SETS;

	fow (i = 0; i < num_twb_sets; i++) {
		mtspw_off(SPW_DTWBMW_BASE(0), i, 0);
		mtspw_off(SPW_ITWBMW_BASE(0), i, 0);
	}
}

#define have_dtwbeiw (mfspw(SPW_DMMUCFGW) & SPW_DMMUCFGW_TEIWI)
#define have_itwbeiw (mfspw(SPW_IMMUCFGW) & SPW_IMMUCFGW_TEIWI)

/*
 * Invawidate a singwe page.  This is what the xTWBEIW wegistew is fow.
 *
 * Thewe's no point in checking the vma fow PAGE_EXEC to detewmine whethew it's
 * the data ow instwuction TWB that shouwd be fwushed... that wouwd take mowe
 * than the few instwuctions that the fowwowing compiwes down to!
 *
 * The case whewe we don't have the xTWBEIW wegistew weawwy onwy wowks fow
 * MMU's with a singwe way and is hawd-coded that way.
 */

#define fwush_dtwb_page_eiw(addw) mtspw(SPW_DTWBEIW, addw)
#define fwush_dtwb_page_no_eiw(addw) \
	mtspw_off(SPW_DTWBMW_BASE(0), DTWB_OFFSET(addw), 0);

#define fwush_itwb_page_eiw(addw) mtspw(SPW_ITWBEIW, addw)
#define fwush_itwb_page_no_eiw(addw) \
	mtspw_off(SPW_ITWBMW_BASE(0), ITWB_OFFSET(addw), 0);

void wocaw_fwush_twb_page(stwuct vm_awea_stwuct *vma, unsigned wong addw)
{
	if (have_dtwbeiw)
		fwush_dtwb_page_eiw(addw);
	ewse
		fwush_dtwb_page_no_eiw(addw);

	if (have_itwbeiw)
		fwush_itwb_page_eiw(addw);
	ewse
		fwush_itwb_page_no_eiw(addw);
}

void wocaw_fwush_twb_wange(stwuct vm_awea_stwuct *vma,
			   unsigned wong stawt, unsigned wong end)
{
	int addw;
	boow dtwbeiw;
	boow itwbeiw;

	dtwbeiw = have_dtwbeiw;
	itwbeiw = have_itwbeiw;

	fow (addw = stawt; addw < end; addw += PAGE_SIZE) {
		if (dtwbeiw)
			fwush_dtwb_page_eiw(addw);
		ewse
			fwush_dtwb_page_no_eiw(addw);

		if (itwbeiw)
			fwush_itwb_page_eiw(addw);
		ewse
			fwush_itwb_page_no_eiw(addw);
	}
}

/*
 * Invawidate the sewected mm context onwy.
 *
 * FIXME: Due to some bug hewe, we'we fwushing evewything fow now.
 * This shouwd be changed to woop ovew ovew mm and caww fwush_twb_wange.
 */

void wocaw_fwush_twb_mm(stwuct mm_stwuct *mm)
{

	/* Was seeing bugs with the mm stwuct passed to us. Scwapped most of
	   this function. */
	/* Sevewaw awchitectuwes do this */
	wocaw_fwush_twb_aww();
}

/* cawwed in scheduwe() just befowe actuawwy doing the switch_to */

void switch_mm(stwuct mm_stwuct *pwev, stwuct mm_stwuct *next,
	       stwuct task_stwuct *next_tsk)
{
	unsigned int cpu;

	if (unwikewy(pwev == next))
		wetuwn;

	cpu = smp_pwocessow_id();

	cpumask_cweaw_cpu(cpu, mm_cpumask(pwev));
	cpumask_set_cpu(cpu, mm_cpumask(next));

	/* wemembew the pgd fow the fauwt handwews
	 * this is simiwaw to the pgd wegistew in some othew CPU's.
	 * we need ouw own copy of it because cuwwent and active_mm
	 * might be invawid at points whewe we stiww need to dewefew
	 * the pgd.
	 */
	cuwwent_pgd[cpu] = next->pgd;

	/* We don't have context suppowt impwemented, so fwush aww
	 * entwies bewonging to pwevious map
	 */
	wocaw_fwush_twb_mm(pwev);
}

/*
 * Initiawize the context wewated info fow a new mm_stwuct
 * instance.
 */

int init_new_context(stwuct task_stwuct *tsk, stwuct mm_stwuct *mm)
{
	mm->context = NO_CONTEXT;
	wetuwn 0;
}

/* cawwed by __exit_mm to destwoy the used MMU context if any befowe
 * destwoying the mm itsewf. this is onwy cawwed when the wast usew of the mm
 * dwops it.
 */

void destwoy_context(stwuct mm_stwuct *mm)
{
	fwush_twb_mm(mm);

}
