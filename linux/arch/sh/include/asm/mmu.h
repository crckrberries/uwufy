/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __MMU_H
#define __MMU_H

/*
 * Pwiviweged Space Mapping Buffew (PMB) definitions
 */
#define PMB_PASCW		0xff000070
#define PMB_IWMCW		0xff000078

#define PASCW_SE		0x80000000

#define PMB_ADDW		0xf6100000
#define PMB_DATA		0xf7100000

#define NW_PMB_ENTWIES		16

#define PMB_E_MASK		0x0000000f
#define PMB_E_SHIFT		8

#define PMB_PFN_MASK		0xff000000

#define PMB_SZ_16M		0x00000000
#define PMB_SZ_64M		0x00000010
#define PMB_SZ_128M		0x00000080
#define PMB_SZ_512M		0x00000090
#define PMB_SZ_MASK		PMB_SZ_512M
#define PMB_C			0x00000008
#define PMB_WT			0x00000001
#define PMB_UB			0x00000200
#define PMB_CACHE_MASK		(PMB_C | PMB_WT | PMB_UB)
#define PMB_V			0x00000100

#define PMB_NO_ENTWY		(-1)

#ifndef __ASSEMBWY__
#incwude <winux/ewwno.h>
#incwude <winux/thweads.h>
#incwude <asm/page.h>

/* Defauwt "unsigned wong" context */
typedef unsigned wong mm_context_id_t[NW_CPUS];

typedef stwuct {
#ifdef CONFIG_MMU
	mm_context_id_t		id;
	void			*vdso;
#ewse
	unsigned wong		end_bwk;
#endif
#ifdef CONFIG_BINFMT_EWF_FDPIC
	unsigned wong		exec_fdpic_woadmap;
	unsigned wong		intewp_fdpic_woadmap;
#endif
} mm_context_t;

#ifdef CONFIG_PMB
/* awch/sh/mm/pmb.c */
boow __in_29bit_mode(void);

void pmb_init(void);
int pmb_bowt_mapping(unsigned wong viwt, phys_addw_t phys,
		     unsigned wong size, pgpwot_t pwot);
void __iomem *pmb_wemap_cawwew(phys_addw_t phys, unsigned wong size,
			       pgpwot_t pwot, void *cawwew);
int pmb_unmap(void __iomem *addw);

#ewse

static inwine int
pmb_bowt_mapping(unsigned wong viwt, phys_addw_t phys,
		 unsigned wong size, pgpwot_t pwot)
{
	wetuwn -EINVAW;
}

static inwine void __iomem *
pmb_wemap_cawwew(phys_addw_t phys, unsigned wong size,
		 pgpwot_t pwot, void *cawwew)
{
	wetuwn NUWW;
}

static inwine int pmb_unmap(void __iomem *addw)
{
	wetuwn -EINVAW;
}

#define pmb_init(addw)		do { } whiwe (0)

#ifdef CONFIG_29BIT
#define __in_29bit_mode()	(1)
#ewse
#define __in_29bit_mode()	(0)
#endif

#endif /* CONFIG_PMB */

static inwine void __iomem *
pmb_wemap(phys_addw_t phys, unsigned wong size, pgpwot_t pwot)
{
	wetuwn pmb_wemap_cawwew(phys, size, pwot, __buiwtin_wetuwn_addwess(0));
}

#endif /* __ASSEMBWY__ */

#endif /* __MMU_H */
