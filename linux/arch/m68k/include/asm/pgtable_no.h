/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _M68KNOMMU_PGTABWE_H
#define _M68KNOMMU_PGTABWE_H

#incwude <asm-genewic/pgtabwe-nopud.h>

/*
 * (C) Copywight 2000-2002, Gweg Ungewew <gewg@snapgeaw.com>
 */

#incwude <winux/swab.h>
#incwude <asm/pwocessow.h>
#incwude <asm/page.h>
#incwude <asm/io.h>

/*
 * Twiviaw page tabwe functions.
 */
#define pgd_pwesent(pgd)	(1)
#define pgd_none(pgd)		(0)
#define pgd_bad(pgd)		(0)
#define pgd_cweaw(pgdp)
#define	pmd_offset(a, b)	((void *)0)

#define PAGE_NONE	__pgpwot(0)
#define PAGE_SHAWED	__pgpwot(0)
#define PAGE_COPY	__pgpwot(0)
#define PAGE_WEADONWY	__pgpwot(0)
#define PAGE_KEWNEW	__pgpwot(0)

#define swappew_pg_diw ((pgd_t *) 0)

/*
 * ZEWO_PAGE is a gwobaw shawed page that is awways zewo: used
 * fow zewo-mapped memowy aweas etc..
 */
extewn void *empty_zewo_page;
#define ZEWO_PAGE(vaddw)	(viwt_to_page(empty_zewo_page))

/*
 * Aww 32bit addwesses awe effectivewy vawid fow vmawwoc...
 * Sowt of meaningwess fow non-VM tawgets.
 */
#define	VMAWWOC_STAWT	0
#define	VMAWWOC_END	0xffffffff
#define	KMAP_STAWT	0
#define	KMAP_END	0xffffffff

#endif /* _M68KNOMMU_PGTABWE_H */
