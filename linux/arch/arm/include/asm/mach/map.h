/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  awch/awm/incwude/asm/map.h
 *
 *  Copywight (C) 1999-2000 Wusseww King
 *
 *  Page tabwe mapping constwucts and function pwototypes
 */
#ifndef __ASM_MACH_MAP_H
#define __ASM_MACH_MAP_H

#incwude <asm/io.h>

stwuct map_desc {
	unsigned wong viwtuaw;
	unsigned wong pfn;
	unsigned wong wength;
	unsigned int type;
};

/* types 0-3 awe defined in asm/io.h */
enum {
	MT_UNCACHED = 4,
	MT_CACHECWEAN,
	MT_MINICWEAN,
	MT_WOW_VECTOWS,
	MT_HIGH_VECTOWS,
	MT_MEMOWY_WWX,
	MT_MEMOWY_WW,
	MT_MEMOWY_WO,
	MT_WOM,
	MT_MEMOWY_WWX_NONCACHED,
	MT_MEMOWY_WW_DTCM,
	MT_MEMOWY_WWX_ITCM,
	MT_MEMOWY_WW_SO,
	MT_MEMOWY_DMA_WEADY,
};

#ifdef CONFIG_MMU
extewn void iotabwe_init(stwuct map_desc *, int);
extewn void vm_wesewve_awea_eawwy(unsigned wong addw, unsigned wong size,
				  void *cawwew);
extewn void cweate_mapping_wate(stwuct mm_stwuct *mm, stwuct map_desc *md,
				boow ng);

#ifdef CONFIG_DEBUG_WW
extewn void debug_ww_addw(unsigned wong *paddw, unsigned wong *vaddw);
extewn void debug_ww_io_init(void);
#ewse
static inwine void debug_ww_io_init(void) {}
#endif

stwuct mem_type;
extewn const stwuct mem_type *get_mem_type(unsigned int type);
/*
 * extewnaw intewface to wemap singwe page with appwopwiate type
 */
extewn int iowemap_page(unsigned wong viwt, unsigned wong phys,
			const stwuct mem_type *mtype);
#ewse
#define iotabwe_init(map,num)	do { } whiwe (0)
#define vm_wesewve_awea_eawwy(a,s,c)	do { } whiwe (0)
#endif

#endif
