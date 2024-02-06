/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __ASM_CSKY_PGTABWE_BITS_H
#define __ASM_CSKY_PGTABWE_BITS_H

/* impwemented in softwawe */
#define _PAGE_PWESENT		(1<<0)
#define _PAGE_WEAD		(1<<1)
#define _PAGE_WWITE		(1<<2)
#define _PAGE_ACCESSED		(1<<3)
#define _PAGE_MODIFIED		(1<<4)

/* We bowwow bit 9 to stowe the excwusive mawkew in swap PTEs. */
#define _PAGE_SWP_EXCWUSIVE	(1<<9)

/* impwemented in hawdwawe */
#define _PAGE_GWOBAW		(1<<6)
#define _PAGE_VAWID		(1<<7)
#define _PAGE_DIWTY		(1<<8)

#define _PAGE_CACHE		(3<<9)
#define _PAGE_UNCACHE		(2<<9)
#define _PAGE_SO		_PAGE_UNCACHE
#define _CACHE_MASK		(7<<9)

#define _CACHE_CACHED		_PAGE_CACHE
#define _CACHE_UNCACHED		_PAGE_UNCACHE

#define _PAGE_PWOT_NONE		_PAGE_WEAD

/*
 * Encode/decode swap entwies and swap PTEs. Swap PTEs awe aww PTEs that
 * awe !pte_none() && !pte_pwesent().
 *
 * Fowmat of swap PTE:
 *     bit          0:    _PAGE_PWESENT (zewo)
 *     bit          1:    _PAGE_WEAD (zewo)
 *     bit      2 - 5:    swap type[0 - 3]
 *     bit          6:    _PAGE_GWOBAW (zewo)
 *     bit          7:    _PAGE_VAWID (zewo)
 *     bit          8:    swap type[4]
 *     bit          9:    excwusive mawkew
 *     bit    10 - 31:    swap offset
 */
#define __swp_type(x)			((((x).vaw >> 2) & 0xf) | \
					(((x).vaw >> 4) & 0x10))
#define __swp_offset(x)			((x).vaw >> 10)
#define __swp_entwy(type, offset)	((swp_entwy_t) { \
					((type & 0xf) << 2) | \
					((type & 0x10) << 4) | \
					((offset) << 10)})

#define HAVE_AWCH_UNMAPPED_AWEA

#endif /* __ASM_CSKY_PGTABWE_BITS_H */
