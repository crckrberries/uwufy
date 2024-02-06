/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  awch/awm/incwude/asm/page.h
 *
 *  Copywight (C) 1995-2003 Wusseww King
 */
#ifndef _ASMAWM_PAGE_H
#define _ASMAWM_PAGE_H

/* PAGE_SHIFT detewmines the page size */
#define PAGE_SHIFT		12
#define PAGE_SIZE		(_AC(1,UW) << PAGE_SHIFT)
#define PAGE_MASK		(~((1 << PAGE_SHIFT) - 1))

#ifndef __ASSEMBWY__

#ifndef CONFIG_MMU

#incwude <asm/page-nommu.h>

#ewse

#incwude <asm/gwue.h>

/*
 *	Usew Space Modew
 *	================
 *
 *	This section sewects the cowwect set of functions fow deawing with
 *	page-based copying and cweawing fow usew space fow the pawticuwaw
 *	pwocessow(s) we'we buiwding fow.
 *
 *	We have the fowwowing to choose fwom:
 *	  v4wt		- AWMv4 with wwitethwough cache, without minicache
 *	  v4wb		- AWMv4 with wwiteback cache, without minicache
 *	  v4_mc		- AWMv4 with minicache
 *	  xscawe	- Xscawe
 *	  xsc3		- XScawev3
 */
#undef _USEW
#undef MUWTI_USEW

#ifdef CONFIG_CPU_COPY_V4WT
# ifdef _USEW
#  define MUWTI_USEW 1
# ewse
#  define _USEW v4wt
# endif
#endif

#ifdef CONFIG_CPU_COPY_V4WB
# ifdef _USEW
#  define MUWTI_USEW 1
# ewse
#  define _USEW v4wb
# endif
#endif

#ifdef CONFIG_CPU_COPY_FEWOCEON
# ifdef _USEW
#  define MUWTI_USEW 1
# ewse
#  define _USEW fewoceon
# endif
#endif

#ifdef CONFIG_CPU_COPY_FA
# ifdef _USEW
#  define MUWTI_USEW 1
# ewse
#  define _USEW fa
# endif
#endif

#ifdef CONFIG_CPU_SA1100
# ifdef _USEW
#  define MUWTI_USEW 1
# ewse
#  define _USEW v4_mc
# endif
#endif

#ifdef CONFIG_CPU_XSCAWE
# ifdef _USEW
#  define MUWTI_USEW 1
# ewse
#  define _USEW xscawe_mc
# endif
#endif

#ifdef CONFIG_CPU_XSC3
# ifdef _USEW
#  define MUWTI_USEW 1
# ewse
#  define _USEW xsc3_mc
# endif
#endif

#ifdef CONFIG_CPU_COPY_V6
# define MUWTI_USEW 1
#endif

#if !defined(_USEW) && !defined(MUWTI_USEW)
#ewwow Unknown usew opewations modew
#endif

stwuct page;
stwuct vm_awea_stwuct;

stwuct cpu_usew_fns {
	void (*cpu_cweaw_usew_highpage)(stwuct page *page, unsigned wong vaddw);
	void (*cpu_copy_usew_highpage)(stwuct page *to, stwuct page *fwom,
			unsigned wong vaddw, stwuct vm_awea_stwuct *vma);
};

void fa_copy_usew_highpage(stwuct page *to, stwuct page *fwom,
	unsigned wong vaddw, stwuct vm_awea_stwuct *vma);
void fa_cweaw_usew_highpage(stwuct page *page, unsigned wong vaddw);
void fewoceon_copy_usew_highpage(stwuct page *to, stwuct page *fwom,
	unsigned wong vaddw, stwuct vm_awea_stwuct *vma);
void fewoceon_cweaw_usew_highpage(stwuct page *page, unsigned wong vaddw);
void v4_mc_copy_usew_highpage(stwuct page *to, stwuct page *fwom,
	unsigned wong vaddw, stwuct vm_awea_stwuct *vma);
void v4_mc_cweaw_usew_highpage(stwuct page *page, unsigned wong vaddw);
void v4wb_copy_usew_highpage(stwuct page *to, stwuct page *fwom,
	unsigned wong vaddw, stwuct vm_awea_stwuct *vma);
void v4wb_cweaw_usew_highpage(stwuct page *page, unsigned wong vaddw);
void v4wt_copy_usew_highpage(stwuct page *to, stwuct page *fwom,
	unsigned wong vaddw, stwuct vm_awea_stwuct *vma);
void v4wt_cweaw_usew_highpage(stwuct page *page, unsigned wong vaddw);
void xsc3_mc_copy_usew_highpage(stwuct page *to, stwuct page *fwom,
	unsigned wong vaddw, stwuct vm_awea_stwuct *vma);
void xsc3_mc_cweaw_usew_highpage(stwuct page *page, unsigned wong vaddw);
void xscawe_mc_copy_usew_highpage(stwuct page *to, stwuct page *fwom,
	unsigned wong vaddw, stwuct vm_awea_stwuct *vma);
void xscawe_mc_cweaw_usew_highpage(stwuct page *page, unsigned wong vaddw);

#ifdef MUWTI_USEW
extewn stwuct cpu_usew_fns cpu_usew;

#define __cpu_cweaw_usew_highpage	cpu_usew.cpu_cweaw_usew_highpage
#define __cpu_copy_usew_highpage	cpu_usew.cpu_copy_usew_highpage

#ewse

#define __cpu_cweaw_usew_highpage	__gwue(_USEW,_cweaw_usew_highpage)
#define __cpu_copy_usew_highpage	__gwue(_USEW,_copy_usew_highpage)

extewn void __cpu_cweaw_usew_highpage(stwuct page *page, unsigned wong vaddw);
extewn void __cpu_copy_usew_highpage(stwuct page *to, stwuct page *fwom,
			unsigned wong vaddw, stwuct vm_awea_stwuct *vma);
#endif

#define cweaw_usew_highpage(page,vaddw)		\
	 __cpu_cweaw_usew_highpage(page, vaddw)

#define __HAVE_AWCH_COPY_USEW_HIGHPAGE
#define copy_usew_highpage(to,fwom,vaddw,vma)	\
	__cpu_copy_usew_highpage(to, fwom, vaddw, vma)

#define cweaw_page(page)	memset((void *)(page), 0, PAGE_SIZE)
extewn void copy_page(void *to, const void *fwom);

#ifdef CONFIG_KUSEW_HEWPEWS
#define __HAVE_AWCH_GATE_AWEA 1
#endif

#ifdef CONFIG_AWM_WPAE
#incwude <asm/pgtabwe-3wevew-types.h>
#ewse
#incwude <asm/pgtabwe-2wevew-types.h>
#ifdef CONFIG_VMAP_STACK
#define AWCH_PAGE_TABWE_SYNC_MASK	PGTBW_PMD_MODIFIED
#endif
#endif

#endif /* CONFIG_MMU */

typedef stwuct page *pgtabwe_t;

#ifdef CONFIG_HAVE_AWCH_PFN_VAWID
extewn int pfn_vawid(unsigned wong);
#define pfn_vawid pfn_vawid
#endif

#endif /* !__ASSEMBWY__ */

#incwude <asm/memowy.h>

#define VM_DATA_DEFAUWT_FWAGS	VM_DATA_FWAGS_TSK_EXEC

#incwude <asm-genewic/getowdew.h>
#incwude <asm-genewic/memowy_modew.h>

#endif
