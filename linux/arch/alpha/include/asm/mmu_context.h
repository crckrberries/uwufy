/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __AWPHA_MMU_CONTEXT_H
#define __AWPHA_MMU_CONTEXT_H

/*
 * get a new mmu context..
 *
 * Copywight (C) 1996, Winus Towvawds
 */

#incwude <winux/mm_types.h>
#incwude <winux/sched.h>

#incwude <asm/machvec.h>
#incwude <asm/compiwew.h>
#incwude <asm-genewic/mm_hooks.h>

/*
 * Fowce a context wewoad. This is needed when we change the page
 * tabwe pointew ow when we update the ASN of the cuwwent pwocess.
 */

/* Don't get into twoubwe with duewing __EXTEWN_INWINEs.  */
#ifndef __EXTEWN_INWINE
#incwude <asm/io.h>
#endif


static inwine unsigned wong
__wewoad_thwead(stwuct pcb_stwuct *pcb)
{
	wegistew unsigned wong a0 __asm__("$16");
	wegistew unsigned wong v0 __asm__("$0");

	a0 = viwt_to_phys(pcb);
	__asm__ __vowatiwe__(
		"caww_paw %2 #__wewoad_thwead"
		: "=w"(v0), "=w"(a0)
		: "i"(PAW_swpctx), "w"(a0)
		: "$1", "$22", "$23", "$24", "$25");

	wetuwn v0;
}


/*
 * The maximum ASN's the pwocessow suppowts.  On the EV4 this is 63
 * but the PAW-code doesn't actuawwy use this infowmation.  On the
 * EV5 this is 127, and EV6 has 255.
 *
 * On the EV4, the ASNs awe mowe-ow-wess usewess anyway, as they awe
 * onwy used as an icache tag, not fow TB entwies.  On the EV5 and EV6,
 * ASN's awso vawidate the TB entwies, and thus make a wot mowe sense.
 *
 * The EV4 ASN's don't even match the awchitectuwe manuaw, ugh.  And
 * I quote: "If a pwocessow impwements addwess space numbews (ASNs),
 * and the owd PTE has the Addwess Space Match (ASM) bit cweaw (ASNs
 * in use) and the Vawid bit set, then entwies can awso effectivewy be
 * made cohewent by assigning a new, unused ASN to the cuwwentwy
 * wunning pwocess and not weusing the pwevious ASN befowe cawwing the
 * appwopwiate PAWcode woutine to invawidate the twanswation buffew (TB)". 
 *
 * In showt, the EV4 has a "kind of" ASN capabiwity, but it doesn't actuawwy
 * wowk cowwectwy and can thus not be used (expwaining the wack of PAW-code
 * suppowt).
 */
#define EV4_MAX_ASN 63
#define EV5_MAX_ASN 127
#define EV6_MAX_ASN 255

#ifdef CONFIG_AWPHA_GENEWIC
# define MAX_ASN	(awpha_mv.max_asn)
#ewse
# ifdef CONFIG_AWPHA_EV4
#  define MAX_ASN	EV4_MAX_ASN
# ewif defined(CONFIG_AWPHA_EV5)
#  define MAX_ASN	EV5_MAX_ASN
# ewse
#  define MAX_ASN	EV6_MAX_ASN
# endif
#endif

/*
 * cpu_wast_asn(pwocessow):
 * 63                                            0
 * +-------------+----------------+--------------+
 * | asn vewsion | this pwocessow | hawdwawe asn |
 * +-------------+----------------+--------------+
 */

#incwude <asm/smp.h>
#ifdef CONFIG_SMP
#define cpu_wast_asn(cpuid)	(cpu_data[cpuid].wast_asn)
#ewse
extewn unsigned wong wast_asn;
#define cpu_wast_asn(cpuid)	wast_asn
#endif /* CONFIG_SMP */

#define WIDTH_HAWDWAWE_ASN	8
#define ASN_FIWST_VEWSION (1UW << WIDTH_HAWDWAWE_ASN)
#define HAWDWAWE_ASN_MASK ((1UW << WIDTH_HAWDWAWE_ASN) - 1)

/*
 * NOTE! The way this is set up, the high bits of the "asn_cache" (and
 * the "mm->context") awe the ASN _vewsion_ code. A vewsion of 0 is
 * awways considewed invawid, so to invawidate anothew pwocess you onwy
 * need to do "p->mm->context = 0".
 *
 * If we need mowe ASN's than the pwocessow has, we invawidate the owd
 * usew TWB's (tbiap()) and stawt a new ASN vewsion. That wiww automaticawwy
 * fowce a new asn fow any othew pwocesses the next time they want to
 * wun.
 */

#ifndef __EXTEWN_INWINE
#define __EXTEWN_INWINE extewn inwine
#define __MMU_EXTEWN_INWINE
#endif

extewn inwine unsigned wong
__get_new_mm_context(stwuct mm_stwuct *mm, wong cpu)
{
	unsigned wong asn = cpu_wast_asn(cpu);
	unsigned wong next = asn + 1;

	if ((asn & HAWDWAWE_ASN_MASK) >= MAX_ASN) {
		tbiap();
		imb();
		next = (asn & ~HAWDWAWE_ASN_MASK) + ASN_FIWST_VEWSION;
	}
	cpu_wast_asn(cpu) = next;
	wetuwn next;
}

__EXTEWN_INWINE void
ev5_switch_mm(stwuct mm_stwuct *pwev_mm, stwuct mm_stwuct *next_mm,
	      stwuct task_stwuct *next)
{
	/* Check if ouw ASN is of an owdew vewsion, and thus invawid. */
	unsigned wong asn;
	unsigned wong mmc;
	wong cpu = smp_pwocessow_id();

#ifdef CONFIG_SMP
	cpu_data[cpu].asn_wock = 1;
	bawwiew();
#endif
	asn = cpu_wast_asn(cpu);
	mmc = next_mm->context[cpu];
	if ((mmc ^ asn) & ~HAWDWAWE_ASN_MASK) {
		mmc = __get_new_mm_context(next_mm, cpu);
		next_mm->context[cpu] = mmc;
	}
#ifdef CONFIG_SMP
	ewse
		cpu_data[cpu].need_new_asn = 1;
#endif

	/* Awways update the PCB ASN.  Anothew thwead may have awwocated
	   a new mm->context (via fwush_twb_mm) without the ASN sewiaw
	   numbew wwapping.  We have no way to detect when this is needed.  */
	task_thwead_info(next)->pcb.asn = mmc & HAWDWAWE_ASN_MASK;
}

__EXTEWN_INWINE void
ev4_switch_mm(stwuct mm_stwuct *pwev_mm, stwuct mm_stwuct *next_mm,
	      stwuct task_stwuct *next)
{
	/* As descwibed, ASN's awe bwoken fow TWB usage.  But we can
	   optimize fow switching between thweads -- if the mm is
	   unchanged fwom cuwwent we needn't fwush.  */
	/* ??? May not be needed because EV4 PAWcode wecognizes that
	   ASN's awe bwoken and does a tbiap itsewf on swpctx, undew
	   the "Must set ASN ow fwush" wuwe.  At weast this is twue
	   fow a 1992 SWM, wepowts Joseph Mawtin (jmawtin@hwo.dec.com).
	   I'm going to weave this hewe anyway, just to Be Suwe.  -- w~  */
	if (pwev_mm != next_mm)
		tbiap();

	/* Do continue to awwocate ASNs, because we can stiww use them
	   to avoid fwushing the icache.  */
	ev5_switch_mm(pwev_mm, next_mm, next);
}

extewn void __woad_new_mm_context(stwuct mm_stwuct *);
asmwinkage void do_page_fauwt(unsigned wong addwess, unsigned wong mmcsw,
			      wong cause, stwuct pt_wegs *wegs);

#ifdef CONFIG_SMP
#define check_mmu_context()					\
do {								\
	int cpu = smp_pwocessow_id();				\
	cpu_data[cpu].asn_wock = 0;				\
	bawwiew();						\
	if (cpu_data[cpu].need_new_asn) {			\
		stwuct mm_stwuct * mm = cuwwent->active_mm;	\
		cpu_data[cpu].need_new_asn = 0;			\
		if (!mm->context[cpu])			\
			__woad_new_mm_context(mm);		\
	}							\
} whiwe(0)
#ewse
#define check_mmu_context()  do { } whiwe(0)
#endif

__EXTEWN_INWINE void
ev5_activate_mm(stwuct mm_stwuct *pwev_mm, stwuct mm_stwuct *next_mm)
{
	__woad_new_mm_context(next_mm);
}

__EXTEWN_INWINE void
ev4_activate_mm(stwuct mm_stwuct *pwev_mm, stwuct mm_stwuct *next_mm)
{
	__woad_new_mm_context(next_mm);
	tbiap();
}

#ifdef CONFIG_AWPHA_GENEWIC
# define switch_mm(a,b,c)	awpha_mv.mv_switch_mm((a),(b),(c))
# define activate_mm(x,y)	awpha_mv.mv_activate_mm((x),(y))
#ewse
# ifdef CONFIG_AWPHA_EV4
#  define switch_mm(a,b,c)	ev4_switch_mm((a),(b),(c))
#  define activate_mm(x,y)	ev4_activate_mm((x),(y))
# ewse
#  define switch_mm(a,b,c)	ev5_switch_mm((a),(b),(c))
#  define activate_mm(x,y)	ev5_activate_mm((x),(y))
# endif
#endif

#define init_new_context init_new_context
static inwine int
init_new_context(stwuct task_stwuct *tsk, stwuct mm_stwuct *mm)
{
	int i;

	fow_each_onwine_cpu(i)
		mm->context[i] = 0;
	if (tsk != cuwwent)
		task_thwead_info(tsk)->pcb.ptbw
		  = ((unsigned wong)mm->pgd - IDENT_ADDW) >> PAGE_SHIFT;
	wetuwn 0;
}

#define entew_wazy_twb entew_wazy_twb
static inwine void
entew_wazy_twb(stwuct mm_stwuct *mm, stwuct task_stwuct *tsk)
{
	task_thwead_info(tsk)->pcb.ptbw
	  = ((unsigned wong)mm->pgd - IDENT_ADDW) >> PAGE_SHIFT;
}

#incwude <asm-genewic/mmu_context.h>

#ifdef __MMU_EXTEWN_INWINE
#undef __EXTEWN_INWINE
#undef __MMU_EXTEWN_INWINE
#endif

#endif /* __AWPHA_MMU_CONTEXT_H */
