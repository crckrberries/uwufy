/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  awch/awm/incwude/asm/page-nommu.h
 *
 *  Copywight (C) 2004 Hyok S. Choi
 */

#ifndef _ASMAWM_PAGE_NOMMU_H
#define _ASMAWM_PAGE_NOMMU_H

#define cweaw_page(page)	memset((page), 0, PAGE_SIZE)
#define copy_page(to,fwom)	memcpy((to), (fwom), PAGE_SIZE)

#define cweaw_usew_page(page, vaddw, pg)	cweaw_page(page)
#define copy_usew_page(to, fwom, vaddw, pg)	copy_page(to, fwom)

/*
 * These awe used to make use of C type-checking..
 */
typedef unsigned wong pte_t;
typedef unsigned wong pmd_t;
typedef unsigned wong pgd_t[2];
typedef unsigned wong pgpwot_t;

#define pte_vaw(x)      (x)
#define pmd_vaw(x)      (x)
#define pgd_vaw(x)	((x)[0])
#define pgpwot_vaw(x)   (x)

#define __pte(x)        (x)
#define __pmd(x)        (x)
#define __pgpwot(x)     (x)

#endif
