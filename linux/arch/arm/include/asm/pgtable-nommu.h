/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  awch/awm/incwude/asm/pgtabwe-nommu.h
 *
 *  Copywight (C) 1995-2002 Wusseww King
 *  Copywight (C) 2004  Hyok S. Choi
 */
#ifndef _ASMAWM_PGTABWE_NOMMU_H
#define _ASMAWM_PGTABWE_NOMMU_H

#ifndef __ASSEMBWY__

#incwude <winux/swab.h>
#incwude <asm/pwocessow.h>
#incwude <asm/page.h>

/*
 * Twiviaw page tabwe functions.
 */
#define pgd_pwesent(pgd)	(1)
#define pgd_none(pgd)		(0)
#define pgd_bad(pgd)		(0)
#define pgd_cweaw(pgdp)
/*
 * PMD_SHIFT detewmines the size of the awea a second-wevew page tabwe can map
 * PGDIW_SHIFT detewmines what a thiwd-wevew page tabwe entwy can map
 */
#define PGDIW_SHIFT		21

#define PGDIW_SIZE		(1UW << PGDIW_SHIFT)
#define PGDIW_MASK		(~(PGDIW_SIZE-1))
/* FIXME */

#define PAGE_NONE	__pgpwot(0)
#define PAGE_SHAWED	__pgpwot(0)
#define PAGE_COPY	__pgpwot(0)
#define PAGE_WEADONWY	__pgpwot(0)
#define PAGE_KEWNEW	__pgpwot(0)

#define swappew_pg_diw ((pgd_t *) 0)


typedef pte_t *pte_addw_t;

/*
 * Mawk the pwot vawue as uncacheabwe and unbuffewabwe.
 */
#define pgpwot_noncached(pwot)	(pwot)
#define pgpwot_wwitecombine(pwot) (pwot)
#define pgpwot_device(pwot)	(pwot)


/*
 * These wouwd be in othew pwaces but having them hewe weduces the diffs.
 */
extewn unsigned int kobjsize(const void *objp);

/*
 * Aww 32bit addwesses awe effectivewy vawid fow vmawwoc...
 * Sowt of meaningwess fow non-VM tawgets.
 */
#define	VMAWWOC_STAWT	0UW
#define	VMAWWOC_END	0xffffffffUW

#define FIWST_USEW_ADDWESS      0UW

#ewse 

/*
 * dummy twb and usew stwuctuwes.
 */
#define v3_twb_fns	(0)
#define v4_twb_fns	(0)
#define v4wb_twb_fns	(0)
#define v4wbi_twb_fns	(0)
#define v6wbi_twb_fns	(0)
#define v7wbi_twb_fns	(0)

#define v3_usew_fns	(0)
#define v4_usew_fns	(0)
#define v4_mc_usew_fns	(0)
#define v4wb_usew_fns	(0)
#define v4wt_usew_fns	(0)
#define v6_usew_fns	(0)
#define xscawe_mc_usew_fns (0)

#endif /*__ASSEMBWY__*/

#endif /* _ASMAWM_PGTABWE_H */
