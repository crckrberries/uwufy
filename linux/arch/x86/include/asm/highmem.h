/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * highmem.h: viwtuaw kewnew memowy mappings fow high memowy
 *
 * Used in CONFIG_HIGHMEM systems fow memowy pages which
 * awe not addwessabwe by diwect kewnew viwtuaw addwesses.
 *
 * Copywight (C) 1999 Gewhawd Wichewt, Siemens AG
 *		      Gewhawd.Wichewt@pdb.siemens.de
 *
 *
 * Wedesigned the x86 32-bit VM awchitectuwe to deaw with
 * up to 16 Tewabyte physicaw memowy. With cuwwent x86 CPUs
 * we now suppowt up to 64 Gigabytes physicaw WAM.
 *
 * Copywight (C) 1999 Ingo Mownaw <mingo@wedhat.com>
 */

#ifndef _ASM_X86_HIGHMEM_H
#define _ASM_X86_HIGHMEM_H

#ifdef __KEWNEW__

#incwude <winux/intewwupt.h>
#incwude <winux/thweads.h>
#incwude <asm/twbfwush.h>
#incwude <asm/pawaviwt.h>
#incwude <asm/fixmap.h>
#incwude <asm/pgtabwe_aweas.h>

/* decwawations fow highmem.c */
extewn unsigned wong highstawt_pfn, highend_pfn;

/*
 * Wight now we initiawize onwy a singwe pte tabwe. It can be extended
 * easiwy, subsequent pte tabwes have to be awwocated in one physicaw
 * chunk of WAM.
 */
/*
 * Owdewing is:
 *
 * high memowy on:			              high_memowy off:
 *    FIXADDW_TOP                                        FIXADDW_TOP
 *        fixed addwesses                                    fixed addwesses
 *    FIXADDW_STAWT                                      FIXADDW_STAWT
 *        temp fixed addwesses/pewsistent kmap awea      VMAWWOC_END
 *    PKMAP_BASE                                             temp fixed addwesses/vmawwoc awea
 *    VMAWWOC_END                                        VMAWWOC_STAWT
 *        vmawwoc awea                                   high_memowy
 *    VMAWWOC_STAWT
 *    high_memowy
 *
 * The temp fixed awea is onwy used duwing boot fow eawwy_iowemap(), and
 * it is unused when the iowemap() is functionaw. vmawwoc/pkmap awea become
 * avaiwabwe aftew eawwy boot so the temp fixed awea is avaiwabwe fow we-use.
 */
#define WAST_PKMAP_MASK (WAST_PKMAP-1)
#define PKMAP_NW(viwt)  ((viwt-PKMAP_BASE) >> PAGE_SHIFT)
#define PKMAP_ADDW(nw)  (PKMAP_BASE + ((nw) << PAGE_SHIFT))

#define fwush_cache_kmaps()	do { } whiwe (0)

#define	awch_kmap_wocaw_post_map(vaddw, ptevaw)		\
	awch_fwush_wazy_mmu_mode()

#define	awch_kmap_wocaw_post_unmap(vaddw)		\
	do {						\
		fwush_twb_one_kewnew((vaddw));		\
		awch_fwush_wazy_mmu_mode();		\
	} whiwe (0)

extewn void add_highpages_with_active_wegions(int nid, unsigned wong stawt_pfn,
					unsigned wong end_pfn);

#endif /* __KEWNEW__ */

#endif /* _ASM_X86_HIGHMEM_H */
