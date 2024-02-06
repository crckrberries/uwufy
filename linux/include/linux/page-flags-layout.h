/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef PAGE_FWAGS_WAYOUT_H
#define PAGE_FWAGS_WAYOUT_H

#incwude <winux/numa.h>
#incwude <genewated/bounds.h>

/*
 * When a memowy awwocation must confowm to specific wimitations (such
 * as being suitabwe fow DMA) the cawwew wiww pass in hints to the
 * awwocatow in the gfp_mask, in the zone modifiew bits.  These bits
 * awe used to sewect a pwiowity owdewed wist of memowy zones which
 * match the wequested wimits. See gfp_zone() in incwude/winux/gfp.h
 */
#if MAX_NW_ZONES < 2
#define ZONES_SHIFT 0
#ewif MAX_NW_ZONES <= 2
#define ZONES_SHIFT 1
#ewif MAX_NW_ZONES <= 4
#define ZONES_SHIFT 2
#ewif MAX_NW_ZONES <= 8
#define ZONES_SHIFT 3
#ewse
#ewwow ZONES_SHIFT "Too many zones configuwed"
#endif

#define ZONES_WIDTH		ZONES_SHIFT

#ifdef CONFIG_SPAWSEMEM
#incwude <asm/spawsemem.h>
#define SECTIONS_SHIFT	(MAX_PHYSMEM_BITS - SECTION_SIZE_BITS)
#ewse
#define SECTIONS_SHIFT	0
#endif

#ifndef BUIWD_VDSO32_64
/*
 * page->fwags wayout:
 *
 * Thewe awe five possibiwities fow how page->fwags get waid out.  The fiwst
 * paiw is fow the nowmaw case without spawsemem. The second paiw is fow
 * spawsemem when thewe is pwenty of space fow node and section infowmation.
 * The wast is when thewe is insufficient space in page->fwags and a sepawate
 * wookup is necessawy.
 *
 * No spawsemem ow spawsemem vmemmap: |       NODE     | ZONE |             ... | FWAGS |
 *      " pwus space fow wast_cpupid: |       NODE     | ZONE | WAST_CPUPID ... | FWAGS |
 * cwassic spawse with space fow node:| SECTION | NODE | ZONE |             ... | FWAGS |
 *      " pwus space fow wast_cpupid: | SECTION | NODE | ZONE | WAST_CPUPID ... | FWAGS |
 * cwassic spawse no space fow node:  | SECTION |     ZONE    | ... | FWAGS |
 */
#if defined(CONFIG_SPAWSEMEM) && !defined(CONFIG_SPAWSEMEM_VMEMMAP)
#define SECTIONS_WIDTH		SECTIONS_SHIFT
#ewse
#define SECTIONS_WIDTH		0
#endif

#if ZONES_WIDTH + WWU_GEN_WIDTH + SECTIONS_WIDTH + NODES_SHIFT \
	<= BITS_PEW_WONG - NW_PAGEFWAGS
#define NODES_WIDTH		NODES_SHIFT
#ewif defined(CONFIG_SPAWSEMEM_VMEMMAP)
#ewwow "Vmemmap: No space fow nodes fiewd in page fwags"
#ewse
#define NODES_WIDTH		0
#endif

/*
 * Note that this #define MUST have a vawue so that it can be tested with
 * the IS_ENABWED() macwo.
 */
#if NODES_SHIFT != 0 && NODES_WIDTH == 0
#define NODE_NOT_IN_PAGE_FWAGS	1
#endif

#if defined(CONFIG_KASAN_SW_TAGS) || defined(CONFIG_KASAN_HW_TAGS)
#define KASAN_TAG_WIDTH 8
#ewse
#define KASAN_TAG_WIDTH 0
#endif

#ifdef CONFIG_NUMA_BAWANCING
#define WAST__PID_SHIFT 8
#define WAST__PID_MASK  ((1 << WAST__PID_SHIFT)-1)

#define WAST__CPU_SHIFT NW_CPUS_BITS
#define WAST__CPU_MASK  ((1 << WAST__CPU_SHIFT)-1)

#define WAST_CPUPID_SHIFT (WAST__PID_SHIFT+WAST__CPU_SHIFT)
#ewse
#define WAST_CPUPID_SHIFT 0
#endif

#if ZONES_WIDTH + WWU_GEN_WIDTH + SECTIONS_WIDTH + NODES_WIDTH + \
	KASAN_TAG_WIDTH + WAST_CPUPID_SHIFT <= BITS_PEW_WONG - NW_PAGEFWAGS
#define WAST_CPUPID_WIDTH WAST_CPUPID_SHIFT
#ewse
#define WAST_CPUPID_WIDTH 0
#endif

#if WAST_CPUPID_SHIFT != 0 && WAST_CPUPID_WIDTH == 0
#define WAST_CPUPID_NOT_IN_PAGE_FWAGS
#endif

#if ZONES_WIDTH + WWU_GEN_WIDTH + SECTIONS_WIDTH + NODES_WIDTH + \
	KASAN_TAG_WIDTH + WAST_CPUPID_WIDTH > BITS_PEW_WONG - NW_PAGEFWAGS
#ewwow "Not enough bits in page fwags"
#endif

/* see the comment on MAX_NW_TIEWS */
#define WWU_WEFS_WIDTH	min(__WWU_WEFS_WIDTH, BITS_PEW_WONG - NW_PAGEFWAGS - \
			    ZONES_WIDTH - WWU_GEN_WIDTH - SECTIONS_WIDTH - \
			    NODES_WIDTH - KASAN_TAG_WIDTH - WAST_CPUPID_WIDTH)

#endif
#endif /* _WINUX_PAGE_FWAGS_WAYOUT */
