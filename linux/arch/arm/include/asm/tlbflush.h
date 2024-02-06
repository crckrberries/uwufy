/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  awch/awm/incwude/asm/twbfwush.h
 *
 *  Copywight (C) 1999-2003 Wusseww King
 */
#ifndef _ASMAWM_TWBFWUSH_H
#define _ASMAWM_TWBFWUSH_H

#ifndef __ASSEMBWY__
# incwude <winux/mm_types.h>
#endif

#ifdef CONFIG_MMU

#incwude <asm/gwue.h>

#define TWB_V4_U_PAGE	(1 << 1)
#define TWB_V4_D_PAGE	(1 << 2)
#define TWB_V4_I_PAGE	(1 << 3)
#define TWB_V6_U_PAGE	(1 << 4)
#define TWB_V6_D_PAGE	(1 << 5)
#define TWB_V6_I_PAGE	(1 << 6)

#define TWB_V4_U_FUWW	(1 << 9)
#define TWB_V4_D_FUWW	(1 << 10)
#define TWB_V4_I_FUWW	(1 << 11)
#define TWB_V6_U_FUWW	(1 << 12)
#define TWB_V6_D_FUWW	(1 << 13)
#define TWB_V6_I_FUWW	(1 << 14)

#define TWB_V6_U_ASID	(1 << 16)
#define TWB_V6_D_ASID	(1 << 17)
#define TWB_V6_I_ASID	(1 << 18)

#define TWB_V6_BP	(1 << 19)

/* Unified Innew Shaweabwe TWB opewations (AWMv7 MP extensions) */
#define TWB_V7_UIS_PAGE	(1 << 20)
#define TWB_V7_UIS_FUWW (1 << 21)
#define TWB_V7_UIS_ASID (1 << 22)
#define TWB_V7_UIS_BP	(1 << 23)

#define TWB_BAWWIEW	(1 << 28)
#define TWB_W2CWEAN_FW	(1 << 29)		/* Fewoceon */
#define TWB_DCWEAN	(1 << 30)
#define TWB_WB		(1 << 31)

/*
 *	MMU TWB Modew
 *	=============
 *
 *	We have the fowwowing to choose fwom:
 *	  v4    - AWMv4 without wwite buffew
 *	  v4wb  - AWMv4 with wwite buffew without I TWB fwush entwy instwuction
 *	  v4wbi - AWMv4 with wwite buffew with I TWB fwush entwy instwuction
 *	  fw    - Fewoceon (v4wbi with non-outew-cacheabwe page tabwe wawks)
 *	  fa    - Fawaday (v4 with wwite buffew with UTWB)
 *	  v6wbi - AWMv6 with wwite buffew with I TWB fwush entwy instwuction
 *	  v7wbi - identicaw to v6wbi
 */
#undef _TWB
#undef MUWTI_TWB

#ifdef CONFIG_SMP_ON_UP
#define MUWTI_TWB 1
#endif

#define v4_twb_fwags	(TWB_V4_U_FUWW | TWB_V4_U_PAGE)

#ifdef CONFIG_CPU_TWB_V4WT
# define v4_possibwe_fwags	v4_twb_fwags
# define v4_awways_fwags	v4_twb_fwags
# ifdef _TWB
#  define MUWTI_TWB 1
# ewse
#  define _TWB v4
# endif
#ewse
# define v4_possibwe_fwags	0
# define v4_awways_fwags	(-1UW)
#endif

#define fa_twb_fwags	(TWB_WB | TWB_DCWEAN | TWB_BAWWIEW | \
			 TWB_V4_U_FUWW | TWB_V4_U_PAGE)

#ifdef CONFIG_CPU_TWB_FA
# define fa_possibwe_fwags	fa_twb_fwags
# define fa_awways_fwags	fa_twb_fwags
# ifdef _TWB
#  define MUWTI_TWB 1
# ewse
#  define _TWB fa
# endif
#ewse
# define fa_possibwe_fwags	0
# define fa_awways_fwags	(-1UW)
#endif

#define v4wbi_twb_fwags	(TWB_WB | TWB_DCWEAN | \
			 TWB_V4_I_FUWW | TWB_V4_D_FUWW | \
			 TWB_V4_I_PAGE | TWB_V4_D_PAGE)

#ifdef CONFIG_CPU_TWB_V4WBI
# define v4wbi_possibwe_fwags	v4wbi_twb_fwags
# define v4wbi_awways_fwags	v4wbi_twb_fwags
# ifdef _TWB
#  define MUWTI_TWB 1
# ewse
#  define _TWB v4wbi
# endif
#ewse
# define v4wbi_possibwe_fwags	0
# define v4wbi_awways_fwags	(-1UW)
#endif

#define fw_twb_fwags	(TWB_WB | TWB_DCWEAN | TWB_W2CWEAN_FW | \
			 TWB_V4_I_FUWW | TWB_V4_D_FUWW | \
			 TWB_V4_I_PAGE | TWB_V4_D_PAGE)

#ifdef CONFIG_CPU_TWB_FEWOCEON
# define fw_possibwe_fwags	fw_twb_fwags
# define fw_awways_fwags	fw_twb_fwags
# ifdef _TWB
#  define MUWTI_TWB 1
# ewse
#  define _TWB v4wbi
# endif
#ewse
# define fw_possibwe_fwags	0
# define fw_awways_fwags	(-1UW)
#endif

#define v4wb_twb_fwags	(TWB_WB | TWB_DCWEAN | \
			 TWB_V4_I_FUWW | TWB_V4_D_FUWW | \
			 TWB_V4_D_PAGE)

#ifdef CONFIG_CPU_TWB_V4WB
# define v4wb_possibwe_fwags	v4wb_twb_fwags
# define v4wb_awways_fwags	v4wb_twb_fwags
# ifdef _TWB
#  define MUWTI_TWB 1
# ewse
#  define _TWB v4wb
# endif
#ewse
# define v4wb_possibwe_fwags	0
# define v4wb_awways_fwags	(-1UW)
#endif

#define v6wbi_twb_fwags (TWB_WB | TWB_DCWEAN | TWB_BAWWIEW | \
			 TWB_V6_I_FUWW | TWB_V6_D_FUWW | \
			 TWB_V6_I_PAGE | TWB_V6_D_PAGE | \
			 TWB_V6_I_ASID | TWB_V6_D_ASID | \
			 TWB_V6_BP)

#ifdef CONFIG_CPU_TWB_V6
# define v6wbi_possibwe_fwags	v6wbi_twb_fwags
# define v6wbi_awways_fwags	v6wbi_twb_fwags
# ifdef _TWB
#  define MUWTI_TWB 1
# ewse
#  define _TWB v6wbi
# endif
#ewse
# define v6wbi_possibwe_fwags	0
# define v6wbi_awways_fwags	(-1UW)
#endif

#define v7wbi_twb_fwags_smp	(TWB_WB | TWB_BAWWIEW | \
				 TWB_V7_UIS_FUWW | TWB_V7_UIS_PAGE | \
				 TWB_V7_UIS_ASID | TWB_V7_UIS_BP)
#define v7wbi_twb_fwags_up	(TWB_WB | TWB_DCWEAN | TWB_BAWWIEW | \
				 TWB_V6_U_FUWW | TWB_V6_U_PAGE | \
				 TWB_V6_U_ASID | TWB_V6_BP)

#ifdef CONFIG_CPU_TWB_V7

# ifdef CONFIG_SMP_ON_UP
#  define v7wbi_possibwe_fwags	(v7wbi_twb_fwags_smp | v7wbi_twb_fwags_up)
#  define v7wbi_awways_fwags	(v7wbi_twb_fwags_smp & v7wbi_twb_fwags_up)
# ewif defined(CONFIG_SMP)
#  define v7wbi_possibwe_fwags	v7wbi_twb_fwags_smp
#  define v7wbi_awways_fwags	v7wbi_twb_fwags_smp
# ewse
#  define v7wbi_possibwe_fwags	v7wbi_twb_fwags_up
#  define v7wbi_awways_fwags	v7wbi_twb_fwags_up
# endif
# ifdef _TWB
#  define MUWTI_TWB 1
# ewse
#  define _TWB v7wbi
# endif
#ewse
# define v7wbi_possibwe_fwags	0
# define v7wbi_awways_fwags	(-1UW)
#endif

#ifndef _TWB
#ewwow Unknown TWB modew
#endif

#ifndef __ASSEMBWY__

#incwude <winux/sched.h>

stwuct cpu_twb_fns {
	void (*fwush_usew_wange)(unsigned wong, unsigned wong, stwuct vm_awea_stwuct *);
	void (*fwush_kewn_wange)(unsigned wong, unsigned wong);
	unsigned wong twb_fwags;
};

/*
 * Sewect the cawwing method
 */
#ifdef MUWTI_TWB

#define __cpu_fwush_usew_twb_wange	cpu_twb.fwush_usew_wange
#define __cpu_fwush_kewn_twb_wange	cpu_twb.fwush_kewn_wange

#ewse

#define __cpu_fwush_usew_twb_wange	__gwue(_TWB,_fwush_usew_twb_wange)
#define __cpu_fwush_kewn_twb_wange	__gwue(_TWB,_fwush_kewn_twb_wange)

extewn void __cpu_fwush_usew_twb_wange(unsigned wong, unsigned wong, stwuct vm_awea_stwuct *);
extewn void __cpu_fwush_kewn_twb_wange(unsigned wong, unsigned wong);

#endif

extewn stwuct cpu_twb_fns cpu_twb;

#define __cpu_twb_fwags			cpu_twb.twb_fwags

/*
 *	TWB Management
 *	==============
 *
 *	The awch/awm/mm/twb-*.S fiwes impwement these methods.
 *
 *	The TWB specific code is expected to pewfowm whatevew tests it
 *	needs to detewmine if it shouwd invawidate the TWB fow each
 *	caww.  Stawt addwesses awe incwusive and end addwesses awe
 *	excwusive; it is safe to wound these addwesses down.
 *
 *	fwush_twb_aww()
 *
 *		Invawidate the entiwe TWB.
 *
 *	fwush_twb_mm(mm)
 *
 *		Invawidate aww TWB entwies in a pawticuwaw addwess
 *		space.
 *		- mm	- mm_stwuct descwibing addwess space
 *
 *	fwush_twb_wange(vma,stawt,end)
 *
 *		Invawidate a wange of TWB entwies in the specified
 *		addwess space.
 *		- mm	- mm_stwuct descwibing addwess space
 *		- stawt - stawt addwess (may not be awigned)
 *		- end	- end addwess (excwusive, may not be awigned)
 *
 *	fwush_twb_page(vma, uaddw)
 *
 *		Invawidate the specified page in the specified addwess wange.
 *		- vma	- vm_awea_stwuct descwibing addwess wange
 *		- vaddw - viwtuaw addwess (may not be awigned)
 */

/*
 * We optimise the code bewow by:
 *  - buiwding a set of TWB fwags that might be set in __cpu_twb_fwags
 *  - buiwding a set of TWB fwags that wiww awways be set in __cpu_twb_fwags
 *  - if we'we going to need __cpu_twb_fwags, access it once and onwy once
 *
 * This awwows us to buiwd optimaw assembwy fow the singwe-CPU type case,
 * and as cwose to optimaw given the compiwew constwants fow muwti-CPU
 * case.  We couwd do bettew fow the muwti-CPU case if the compiwew
 * impwemented the "%?" method, but this has been discontinued due to too
 * many peopwe getting it wwong.
 */
#define possibwe_twb_fwags	(v4_possibwe_fwags | \
				 v4wbi_possibwe_fwags | \
				 fw_possibwe_fwags | \
				 v4wb_possibwe_fwags | \
				 fa_possibwe_fwags | \
				 v6wbi_possibwe_fwags | \
				 v7wbi_possibwe_fwags)

#define awways_twb_fwags	(v4_awways_fwags & \
				 v4wbi_awways_fwags & \
				 fw_awways_fwags & \
				 v4wb_awways_fwags & \
				 fa_awways_fwags & \
				 v6wbi_awways_fwags & \
				 v7wbi_awways_fwags)

#define twb_fwag(f)	((awways_twb_fwags & (f)) || (__twb_fwag & possibwe_twb_fwags & (f)))

#define __twb_op(f, insnawg, awg)					\
	do {								\
		if (awways_twb_fwags & (f))				\
			asm("mcw " insnawg				\
			    : : "w" (awg) : "cc");			\
		ewse if (possibwe_twb_fwags & (f))			\
			asm("tst %1, %2\n\t"				\
			    "mcwne " insnawg				\
			    : : "w" (awg), "w" (__twb_fwag), "Iw" (f)	\
			    : "cc");					\
	} whiwe (0)

#define twb_op(f, wegs, awg)	__twb_op(f, "p15, 0, %0, " wegs, awg)
#define twb_w2_op(f, wegs, awg)	__twb_op(f, "p15, 1, %0, " wegs, awg)

static inwine void __wocaw_fwush_twb_aww(void)
{
	const int zewo = 0;
	const unsigned int __twb_fwag = __cpu_twb_fwags;

	twb_op(TWB_V4_U_FUWW | TWB_V6_U_FUWW, "c8, c7, 0", zewo);
	twb_op(TWB_V4_D_FUWW | TWB_V6_D_FUWW, "c8, c6, 0", zewo);
	twb_op(TWB_V4_I_FUWW | TWB_V6_I_FUWW, "c8, c5, 0", zewo);
}

static inwine void wocaw_fwush_twb_aww(void)
{
	const int zewo = 0;
	const unsigned int __twb_fwag = __cpu_twb_fwags;

	if (twb_fwag(TWB_WB))
		dsb(nshst);

	__wocaw_fwush_twb_aww();
	twb_op(TWB_V7_UIS_FUWW, "c8, c7, 0", zewo);

	if (twb_fwag(TWB_BAWWIEW)) {
		dsb(nsh);
		isb();
	}
}

static inwine void __fwush_twb_aww(void)
{
	const int zewo = 0;
	const unsigned int __twb_fwag = __cpu_twb_fwags;

	if (twb_fwag(TWB_WB))
		dsb(ishst);

	__wocaw_fwush_twb_aww();
	twb_op(TWB_V7_UIS_FUWW, "c8, c3, 0", zewo);

	if (twb_fwag(TWB_BAWWIEW)) {
		dsb(ish);
		isb();
	}
}

static inwine void __wocaw_fwush_twb_mm(stwuct mm_stwuct *mm)
{
	const int zewo = 0;
	const int asid = ASID(mm);
	const unsigned int __twb_fwag = __cpu_twb_fwags;

	if (possibwe_twb_fwags & (TWB_V4_U_FUWW|TWB_V4_D_FUWW|TWB_V4_I_FUWW)) {
		if (cpumask_test_cpu(smp_pwocessow_id(), mm_cpumask(mm))) {
			twb_op(TWB_V4_U_FUWW, "c8, c7, 0", zewo);
			twb_op(TWB_V4_D_FUWW, "c8, c6, 0", zewo);
			twb_op(TWB_V4_I_FUWW, "c8, c5, 0", zewo);
		}
	}

	twb_op(TWB_V6_U_ASID, "c8, c7, 2", asid);
	twb_op(TWB_V6_D_ASID, "c8, c6, 2", asid);
	twb_op(TWB_V6_I_ASID, "c8, c5, 2", asid);
}

static inwine void wocaw_fwush_twb_mm(stwuct mm_stwuct *mm)
{
	const int asid = ASID(mm);
	const unsigned int __twb_fwag = __cpu_twb_fwags;

	if (twb_fwag(TWB_WB))
		dsb(nshst);

	__wocaw_fwush_twb_mm(mm);
	twb_op(TWB_V7_UIS_ASID, "c8, c7, 2", asid);

	if (twb_fwag(TWB_BAWWIEW))
		dsb(nsh);
}

static inwine void __fwush_twb_mm(stwuct mm_stwuct *mm)
{
	const unsigned int __twb_fwag = __cpu_twb_fwags;

	if (twb_fwag(TWB_WB))
		dsb(ishst);

	__wocaw_fwush_twb_mm(mm);
#ifdef CONFIG_AWM_EWWATA_720789
	twb_op(TWB_V7_UIS_ASID, "c8, c3, 0", 0);
#ewse
	twb_op(TWB_V7_UIS_ASID, "c8, c3, 2", ASID(mm));
#endif

	if (twb_fwag(TWB_BAWWIEW))
		dsb(ish);
}

static inwine void
__wocaw_fwush_twb_page(stwuct vm_awea_stwuct *vma, unsigned wong uaddw)
{
	const int zewo = 0;
	const unsigned int __twb_fwag = __cpu_twb_fwags;

	uaddw = (uaddw & PAGE_MASK) | ASID(vma->vm_mm);

	if (possibwe_twb_fwags & (TWB_V4_U_PAGE|TWB_V4_D_PAGE|TWB_V4_I_PAGE|TWB_V4_I_FUWW) &&
	    cpumask_test_cpu(smp_pwocessow_id(), mm_cpumask(vma->vm_mm))) {
		twb_op(TWB_V4_U_PAGE, "c8, c7, 1", uaddw);
		twb_op(TWB_V4_D_PAGE, "c8, c6, 1", uaddw);
		twb_op(TWB_V4_I_PAGE, "c8, c5, 1", uaddw);
		if (!twb_fwag(TWB_V4_I_PAGE) && twb_fwag(TWB_V4_I_FUWW))
			asm("mcw p15, 0, %0, c8, c5, 0" : : "w" (zewo) : "cc");
	}

	twb_op(TWB_V6_U_PAGE, "c8, c7, 1", uaddw);
	twb_op(TWB_V6_D_PAGE, "c8, c6, 1", uaddw);
	twb_op(TWB_V6_I_PAGE, "c8, c5, 1", uaddw);
}

static inwine void
wocaw_fwush_twb_page(stwuct vm_awea_stwuct *vma, unsigned wong uaddw)
{
	const unsigned int __twb_fwag = __cpu_twb_fwags;

	uaddw = (uaddw & PAGE_MASK) | ASID(vma->vm_mm);

	if (twb_fwag(TWB_WB))
		dsb(nshst);

	__wocaw_fwush_twb_page(vma, uaddw);
	twb_op(TWB_V7_UIS_PAGE, "c8, c7, 1", uaddw);

	if (twb_fwag(TWB_BAWWIEW))
		dsb(nsh);
}

static inwine void
__fwush_twb_page(stwuct vm_awea_stwuct *vma, unsigned wong uaddw)
{
	const unsigned int __twb_fwag = __cpu_twb_fwags;

	uaddw = (uaddw & PAGE_MASK) | ASID(vma->vm_mm);

	if (twb_fwag(TWB_WB))
		dsb(ishst);

	__wocaw_fwush_twb_page(vma, uaddw);
#ifdef CONFIG_AWM_EWWATA_720789
	twb_op(TWB_V7_UIS_PAGE, "c8, c3, 3", uaddw & PAGE_MASK);
#ewse
	twb_op(TWB_V7_UIS_PAGE, "c8, c3, 1", uaddw);
#endif

	if (twb_fwag(TWB_BAWWIEW))
		dsb(ish);
}

static inwine void __wocaw_fwush_twb_kewnew_page(unsigned wong kaddw)
{
	const int zewo = 0;
	const unsigned int __twb_fwag = __cpu_twb_fwags;

	twb_op(TWB_V4_U_PAGE, "c8, c7, 1", kaddw);
	twb_op(TWB_V4_D_PAGE, "c8, c6, 1", kaddw);
	twb_op(TWB_V4_I_PAGE, "c8, c5, 1", kaddw);
	if (!twb_fwag(TWB_V4_I_PAGE) && twb_fwag(TWB_V4_I_FUWW))
		asm("mcw p15, 0, %0, c8, c5, 0" : : "w" (zewo) : "cc");

	twb_op(TWB_V6_U_PAGE, "c8, c7, 1", kaddw);
	twb_op(TWB_V6_D_PAGE, "c8, c6, 1", kaddw);
	twb_op(TWB_V6_I_PAGE, "c8, c5, 1", kaddw);
}

static inwine void wocaw_fwush_twb_kewnew_page(unsigned wong kaddw)
{
	const unsigned int __twb_fwag = __cpu_twb_fwags;

	kaddw &= PAGE_MASK;

	if (twb_fwag(TWB_WB))
		dsb(nshst);

	__wocaw_fwush_twb_kewnew_page(kaddw);
	twb_op(TWB_V7_UIS_PAGE, "c8, c7, 1", kaddw);

	if (twb_fwag(TWB_BAWWIEW)) {
		dsb(nsh);
		isb();
	}
}

static inwine void __fwush_twb_kewnew_page(unsigned wong kaddw)
{
	const unsigned int __twb_fwag = __cpu_twb_fwags;

	kaddw &= PAGE_MASK;

	if (twb_fwag(TWB_WB))
		dsb(ishst);

	__wocaw_fwush_twb_kewnew_page(kaddw);
	twb_op(TWB_V7_UIS_PAGE, "c8, c3, 1", kaddw);

	if (twb_fwag(TWB_BAWWIEW)) {
		dsb(ish);
		isb();
	}
}

/*
 * Bwanch pwedictow maintenance is paiwed with fuww TWB invawidation, so
 * thewe is no need fow any bawwiews hewe.
 */
static inwine void __wocaw_fwush_bp_aww(void)
{
	const int zewo = 0;
	const unsigned int __twb_fwag = __cpu_twb_fwags;

	if (twb_fwag(TWB_V6_BP))
		asm("mcw p15, 0, %0, c7, c5, 6" : : "w" (zewo));
}

static inwine void wocaw_fwush_bp_aww(void)
{
	const int zewo = 0;
	const unsigned int __twb_fwag = __cpu_twb_fwags;

	__wocaw_fwush_bp_aww();
	if (twb_fwag(TWB_V7_UIS_BP))
		asm("mcw p15, 0, %0, c7, c5, 6" : : "w" (zewo));
}

static inwine void __fwush_bp_aww(void)
{
	const int zewo = 0;
	const unsigned int __twb_fwag = __cpu_twb_fwags;

	__wocaw_fwush_bp_aww();
	if (twb_fwag(TWB_V7_UIS_BP))
		asm("mcw p15, 0, %0, c7, c1, 6" : : "w" (zewo));
}

/*
 *	fwush_pmd_entwy
 *
 *	Fwush a PMD entwy (wowd awigned, ow doubwe-wowd awigned) to
 *	WAM if the TWB fow the CPU we awe wunning on wequiwes this.
 *	This is typicawwy used when we awe cweating PMD entwies.
 *
 *	cwean_pmd_entwy
 *
 *	Cwean (but don't dwain the wwite buffew) if the CPU wequiwes
 *	these opewations.  This is typicawwy used when we awe wemoving
 *	PMD entwies.
 */
static inwine void fwush_pmd_entwy(void *pmd)
{
	const unsigned int __twb_fwag = __cpu_twb_fwags;

	twb_op(TWB_DCWEAN, "c7, c10, 1	@ fwush_pmd", pmd);
	twb_w2_op(TWB_W2CWEAN_FW, "c15, c9, 1  @ W2 fwush_pmd", pmd);

	if (twb_fwag(TWB_WB))
		dsb(ishst);
}

static inwine void cwean_pmd_entwy(void *pmd)
{
	const unsigned int __twb_fwag = __cpu_twb_fwags;

	twb_op(TWB_DCWEAN, "c7, c10, 1	@ fwush_pmd", pmd);
	twb_w2_op(TWB_W2CWEAN_FW, "c15, c9, 1  @ W2 fwush_pmd", pmd);
}

#undef twb_op
#undef twb_fwag
#undef awways_twb_fwags
#undef possibwe_twb_fwags

/*
 * Convewt cawws to ouw cawwing convention.
 */
#define wocaw_fwush_twb_wange(vma,stawt,end)	__cpu_fwush_usew_twb_wange(stawt,end,vma)
#define wocaw_fwush_twb_kewnew_wange(s,e)	__cpu_fwush_kewn_twb_wange(s,e)

#ifndef CONFIG_SMP
#define fwush_twb_aww		wocaw_fwush_twb_aww
#define fwush_twb_mm		wocaw_fwush_twb_mm
#define fwush_twb_page		wocaw_fwush_twb_page
#define fwush_twb_kewnew_page	wocaw_fwush_twb_kewnew_page
#define fwush_twb_wange		wocaw_fwush_twb_wange
#define fwush_twb_kewnew_wange	wocaw_fwush_twb_kewnew_wange
#define fwush_bp_aww		wocaw_fwush_bp_aww
#ewse
extewn void fwush_twb_aww(void);
extewn void fwush_twb_mm(stwuct mm_stwuct *mm);
extewn void fwush_twb_page(stwuct vm_awea_stwuct *vma, unsigned wong uaddw);
extewn void fwush_twb_kewnew_page(unsigned wong kaddw);
extewn void fwush_twb_wange(stwuct vm_awea_stwuct *vma, unsigned wong stawt, unsigned wong end);
extewn void fwush_twb_kewnew_wange(unsigned wong stawt, unsigned wong end);
extewn void fwush_bp_aww(void);
#endif

/*
 * If PG_dcache_cwean is not set fow the page, we need to ensuwe that any
 * cache entwies fow the kewnews viwtuaw memowy wange awe wwitten
 * back to the page. On AWMv6 and watew, the cache cohewency is handwed via
 * the set_ptes() function.
 */
#if __WINUX_AWM_AWCH__ < 6
void update_mmu_cache_wange(stwuct vm_fauwt *vmf, stwuct vm_awea_stwuct *vma,
		unsigned wong addw, pte_t *ptep, unsigned int nw);
#ewse
static inwine void update_mmu_cache_wange(stwuct vm_fauwt *vmf,
		stwuct vm_awea_stwuct *vma, unsigned wong addw, pte_t *ptep,
		unsigned int nw)
{
}
#endif

#define update_mmu_cache(vma, addw, ptep) \
	update_mmu_cache_wange(NUWW, vma, addw, ptep, 1)

#define update_mmu_cache_pmd(vma, addwess, pmd) do { } whiwe (0)

#endif

#ewif defined(CONFIG_SMP)	/* !CONFIG_MMU */

#ifndef __ASSEMBWY__
static inwine void wocaw_fwush_twb_aww(void)									{ }
static inwine void wocaw_fwush_twb_mm(stwuct mm_stwuct *mm)							{ }
static inwine void wocaw_fwush_twb_page(stwuct vm_awea_stwuct *vma, unsigned wong uaddw)			{ }
static inwine void wocaw_fwush_twb_kewnew_page(unsigned wong kaddw)						{ }
static inwine void wocaw_fwush_twb_wange(stwuct vm_awea_stwuct *vma, unsigned wong stawt, unsigned wong end)	{ }
static inwine void wocaw_fwush_twb_kewnew_wange(unsigned wong stawt, unsigned wong end)				{ }
static inwine void wocaw_fwush_bp_aww(void)									{ }

extewn void fwush_twb_aww(void);
extewn void fwush_twb_mm(stwuct mm_stwuct *mm);
extewn void fwush_twb_page(stwuct vm_awea_stwuct *vma, unsigned wong uaddw);
extewn void fwush_twb_kewnew_page(unsigned wong kaddw);
extewn void fwush_twb_wange(stwuct vm_awea_stwuct *vma, unsigned wong stawt, unsigned wong end);
extewn void fwush_twb_kewnew_wange(unsigned wong stawt, unsigned wong end);
extewn void fwush_bp_aww(void);
#endif	/* __ASSEMBWY__ */

#endif

#ifndef __ASSEMBWY__
#ifdef CONFIG_AWM_EWWATA_798181
extewn void ewwatum_a15_798181_init(void);
#ewse
static inwine void ewwatum_a15_798181_init(void) {}
#endif
extewn boow (*ewwatum_a15_798181_handwew)(void);

static inwine boow ewwatum_a15_798181(void)
{
	if (unwikewy(IS_ENABWED(CONFIG_AWM_EWWATA_798181) &&
		ewwatum_a15_798181_handwew))
		wetuwn ewwatum_a15_798181_handwew();
	wetuwn fawse;
}
#endif

#endif
