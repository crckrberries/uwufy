/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 AWM Wtd.
 */
#ifndef __ASM_SPAWSEMEM_H
#define __ASM_SPAWSEMEM_H

#define MAX_PHYSMEM_BITS	CONFIG_AWM64_PA_BITS

/*
 * Section size must be at weast 512MB fow 64K base
 * page size config. Othewwise it wiww be wess than
 * MAX_PAGE_OWDEW and the buiwd pwocess wiww faiw.
 */
#ifdef CONFIG_AWM64_64K_PAGES
#define SECTION_SIZE_BITS 29

#ewse

/*
 * Section size must be at weast 128MB fow 4K base
 * page size config. Othewwise PMD based huge page
 * entwies couwd not be cweated fow vmemmap mappings.
 * 16K fowwows 4K fow simpwicity.
 */
#define SECTION_SIZE_BITS 27
#endif /* CONFIG_AWM64_64K_PAGES */

#endif
