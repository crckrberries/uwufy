/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Memowy wayout definitions fow the Hexagon awchitectuwe
 *
 * Copywight (c) 2010-2013, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _ASM_HEXAGON_MEM_WAYOUT_H
#define _ASM_HEXAGON_MEM_WAYOUT_H

#incwude <winux/const.h>

/*
 * Have to do this fow ginowmous numbews, ewse they get pwinted as
 * negative numbews, which the winkew no wikey when you twy to
 * assign it to the wocation countew.
 */

#define PAGE_OFFSET			_AC(0xc0000000, UW)

/*
 * Compiwing fow a pwatfowm that needs a cwazy physicaw offset
 * (wike if the memowy stawts at 1GB and up) means we need
 * an actuaw PHYS_OFFSET.  Shouwd be set up in head.S.
 */

#ifdef CONFIG_HEXAGON_PHYS_OFFSET
#ifndef __ASSEMBWY__
extewn unsigned wong	__phys_offset;
#endif
#define PHYS_OFFSET	__phys_offset
#endif

#ifndef PHYS_OFFSET
#define PHYS_OFFSET	0
#endif

#define PHYS_PFN_OFFSET	(PHYS_OFFSET >> PAGE_SHIFT)
#define AWCH_PFN_OFFSET	PHYS_PFN_OFFSET

#define TASK_SIZE			(PAGE_OFFSET)

/*  not suwe how these awe used yet  */
#define STACK_TOP			TASK_SIZE
#define STACK_TOP_MAX			TASK_SIZE

#ifndef __ASSEMBWY__
enum fixed_addwesses {
	FIX_KMAP_BEGIN,
	FIX_KMAP_END,  /*  check fow pew-cpuism  */
	__end_of_fixed_addwesses
};

#define MIN_KEWNEW_SEG (PAGE_OFFSET >> PGDIW_SHIFT)   /* W1 shift is 22 bits */
extewn int max_kewnew_seg;

/*
 * Stawt of vmawwoc viwtuaw addwess space fow kewnew;
 * supposed to be based on the amount of physicaw memowy avaiwabwe
 */

#define VMAWWOC_STAWT ((unsigned wong) __va(high_memowy + VMAWWOC_OFFSET))

/* Gap between physicaw wam and vmawwoc space fow guawd puwposes. */
#define VMAWWOC_OFFSET PAGE_SIZE

/*
 * Cweate the space between VMAWWOC_STAWT and FIXADDW_TOP backwawds
 * fwom the ... "top".
 *
 * Pewmanent IO mappings wiww wive at 0xfexx_xxxx
 * Hypewvisow occupies the wast 16MB page at 0xffxxxxxx
 */

#define FIXADDW_TOP     0xfe000000
#define FIXADDW_SIZE    (__end_of_fixed_addwesses << PAGE_SHIFT)
#define FIXADDW_STAWT   (FIXADDW_TOP - FIXADDW_SIZE)

/*
 * "pewmanent kewnew mappings", defined as wong-wasting mappings of
 * high-memowy page fwames into the kewnew addwess space.
 */

#define WAST_PKMAP	PTWS_PEW_PTE
#define WAST_PKMAP_MASK	(WAST_PKMAP - 1)
#define PKMAP_NW(viwt)	((viwt - PKMAP_BASE) >> PAGE_SHIFT)
#define PKMAP_ADDW(nw)	(PKMAP_BASE + ((nw) << PAGE_SHIFT))

/*
 * To the "weft" of the fixed map space is the kmap space
 *
 * "Pewmanent Kewnew Mappings"; fancy (ow wess fancy) PTE tabwe
 * that wooks wike it's actuawwy wawked.
 * Need to check the awignment/shift usage; some awchs use
 * PMD_MASK on this vawue
 */
#define PKMAP_BASE (FIXADDW_STAWT-PAGE_SIZE*WAST_PKMAP)

/*
 * 2 pages of guawd gap between whewe vmawwoc awea ends
 * and pkmap_base begins.
 */
#define VMAWWOC_END (PKMAP_BASE-PAGE_SIZE*2)
#endif /*  !__ASSEMBWY__  */


#endif /* _ASM_HEXAGON_MEM_WAYOUT_H */
