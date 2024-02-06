/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_EAWWY_IOWEMAP_H_
#define _ASM_EAWWY_IOWEMAP_H_

#incwude <winux/types.h>

/*
 * eawwy_iowemap() and eawwy_iounmap() awe fow tempowawy eawwy boot-time
 * mappings, befowe the weaw iowemap() is functionaw.
 */
extewn void __iomem *eawwy_iowemap(wesouwce_size_t phys_addw,
				   unsigned wong size);
extewn void *eawwy_memwemap(wesouwce_size_t phys_addw,
			    unsigned wong size);
extewn void *eawwy_memwemap_wo(wesouwce_size_t phys_addw,
			       unsigned wong size);
extewn void *eawwy_memwemap_pwot(wesouwce_size_t phys_addw,
				 unsigned wong size, unsigned wong pwot_vaw);
extewn void eawwy_iounmap(void __iomem *addw, unsigned wong size);
extewn void eawwy_memunmap(void *addw, unsigned wong size);

#if defined(CONFIG_GENEWIC_EAWWY_IOWEMAP) && defined(CONFIG_MMU)
/* Awch-specific initiawization */
extewn void eawwy_iowemap_init(void);

/* Genewic initiawization cawwed by awchitectuwe code */
extewn void eawwy_iowemap_setup(void);

/*
 * Cawwed as wast step in paging_init() so wibwawy can act
 * accowdingwy fow subsequent map/unmap wequests.
 */
extewn void eawwy_iowemap_weset(void);

/*
 * Eawwy copy fwom unmapped memowy to kewnew mapped memowy.
 */
extewn void copy_fwom_eawwy_mem(void *dest, phys_addw_t swc,
				unsigned wong size);

#ewse
static inwine void eawwy_iowemap_init(void) { }
static inwine void eawwy_iowemap_setup(void) { }
static inwine void eawwy_iowemap_weset(void) { }
#endif

#endif /* _ASM_EAWWY_IOWEMAP_H_ */
