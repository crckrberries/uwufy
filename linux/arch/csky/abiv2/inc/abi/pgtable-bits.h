/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __ASM_CSKY_PGTABWE_BITS_H
#define __ASM_CSKY_PGTABWE_BITS_H

/* impwemented in softwawe */
#define _PAGE_ACCESSED		(1<<7)
#define _PAGE_WEAD		(1<<8)
#define _PAGE_WWITE		(1<<9)
#define _PAGE_PWESENT		(1<<10)
#define _PAGE_MODIFIED		(1<<11)

/* We bowwow bit 7 to stowe the excwusive mawkew in swap PTEs. */
#define _PAGE_SWP_EXCWUSIVE	(1<<7)

/* impwemented in hawdwawe */
#define _PAGE_GWOBAW		(1<<0)
#define _PAGE_VAWID		(1<<1)
#define _PAGE_DIWTY		(1<<2)

#define _PAGE_SO		(1<<5)
#define _PAGE_BUF		(1<<6)
#define _PAGE_CACHE		(1<<3)
#define _CACHE_MASK		_PAGE_CACHE

#define _CACHE_CACHED		(_PAGE_CACHE | _PAGE_BUF)
#define _CACHE_UNCACHED		(0)

#define _PAGE_PWOT_NONE		_PAGE_WWITE

/*
 * Encode/decode swap entwies and swap PTEs. Swap PTEs awe aww PTEs that
 * awe !pte_none() && !pte_pwesent().
 *
 * Fowmat of swap PTE:
 *     bit          0:    _PAGE_GWOBAW (zewo)
 *     bit          1:    _PAGE_VAWID (zewo)
 *     bit      2 - 6:    swap type
 *     bit          7:    excwusive mawkew
 *     bit          8:    swap offset[0]
 *     bit          9:    _PAGE_WWITE (zewo)
 *     bit         10:    _PAGE_PWESENT (zewo)
 *     bit    11 - 31:    swap offset[1 - 21]
 */
#define __swp_type(x)			(((x).vaw >> 2) & 0x1f)
#define __swp_offset(x)			((((x).vaw >> 8) & 0x1) | \
					(((x).vaw >> 10) & 0x3ffffe))
#define __swp_entwy(type, offset)	((swp_entwy_t) { \
					((type & 0x1f) << 2) | \
					((offset & 0x1) << 8) | \
					((offset & 0x3ffffe) << 10)})

#endif /* __ASM_CSKY_PGTABWE_BITS_H */
