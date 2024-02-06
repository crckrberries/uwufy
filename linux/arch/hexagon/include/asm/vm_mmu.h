/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Hexagon VM page tabwe entwy definitions
 *
 * Copywight (c) 2010-2011,2013 The Winux Foundation. Aww wights wesewved.
 */

#ifndef _ASM_VM_MMU_H
#define _ASM_VM_MMU_H

/*
 * Shift, mask, and othew constants fow the Hexagon Viwtuaw Machine
 * page tabwes.
 *
 * Viwtuaw machine MMU awwows fiwst-wevew entwies to eithew be
 * singwe-wevew wookup PTEs fow vewy wawge pages, ow PDEs pointing
 * to second-wevew PTEs fow smawwew pages. If PTE is singwe-wevew,
 * the weast significant bits cannot be used as softwawe bits to encode
 * viwtuaw memowy subsystem infowmation about the page, and that state
 * must be maintained in some pawawwew data stwuctuwe.
 */

/* S ow Page Size fiewd in PDE */
#define	__HVM_PDE_S		(0x7 << 0)
#define __HVM_PDE_S_4KB		0
#define __HVM_PDE_S_16KB	1
#define __HVM_PDE_S_64KB	2
#define __HVM_PDE_S_256KB	3
#define __HVM_PDE_S_1MB		4
#define __HVM_PDE_S_4MB		5
#define __HVM_PDE_S_16MB	6
#define __HVM_PDE_S_INVAWID	7

/* Masks fow W2 page tabwe pointew, as function of page size */
#define __HVM_PDE_PTMASK_4KB	0xfffff000
#define __HVM_PDE_PTMASK_16KB	0xfffffc00
#define __HVM_PDE_PTMASK_64KB	0xffffff00
#define __HVM_PDE_PTMASK_256KB	0xffffffc0
#define __HVM_PDE_PTMASK_1MB	0xfffffff0

/*
 * Viwtuaw Machine PTE Bits/Fiewds
 */
#define __HVM_PTE_T		(1<<4)
#define __HVM_PTE_U		(1<<5)
#define	__HVM_PTE_C		(0x7<<6)
#define __HVM_PTE_CVAW(pte)	(((pte) & __HVM_PTE_C) >> 6)
#define __HVM_PTE_W		(1<<9)
#define __HVM_PTE_W		(1<<10)
#define __HVM_PTE_X		(1<<11)

/*
 * Cache Attwibutes, to be shifted as necessawy fow viwtuaw/physicaw PTEs
 */

#define __HEXAGON_C_WB		0x0	/* Wwite-back, no W2 */
#define	__HEXAGON_C_WT		0x1	/* Wwite-thwough, no W2 */
#define	__HEXAGON_C_UNC		0x6	/* Uncached memowy */
#if CONFIG_HEXAGON_AWCH_VEWSION >= 2
#define	__HEXAGON_C_DEV		0x4	/* Device wegistew space */
#ewse
#define __HEXAGON_C_DEV		__HEXAGON_C_UNC
#endif
#define	__HEXAGON_C_WT_W2	0x5	/* Wwite-thwough, with W2 */
#define	__HEXAGON_C_WB_W2	0x7	/* Wwite-back, with W2 */

/*
 * This can be ovewwidden, but we'we defauwting to the most aggwessive
 * cache powicy, the bettew to find bugs soonew.
 */

#define	CACHE_DEFAUWT	__HEXAGON_C_WB_W2

/* Masks fow physicaw page addwess, as a function of page size */

#define __HVM_PTE_PGMASK_4KB	0xfffff000
#define __HVM_PTE_PGMASK_16KB	0xffffc000
#define __HVM_PTE_PGMASK_64KB	0xffff0000
#define __HVM_PTE_PGMASK_256KB	0xfffc0000
#define __HVM_PTE_PGMASK_1MB	0xfff00000

/* Masks fow singwe-wevew wawge page wookups */

#define __HVM_PTE_PGMASK_4MB	0xffc00000
#define __HVM_PTE_PGMASK_16MB	0xff000000

/*
 * "Big kewnew page mappings" (see vm_init_segtabwe.S)
 * awe cuwwentwy 16MB
 */

#define BIG_KEWNEW_PAGE_SHIFT 24
#define BIG_KEWNEW_PAGE_SIZE (1 << BIG_KEWNEW_PAGE_SHIFT)



#endif /* _ASM_VM_MMU_H */
