/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SPAWC_VADDWS_H
#define _SPAWC_VADDWS_H

#incwude <asm/head.h>

/*
 * asm/vaddws.h:  Hewe we define the viwtuaw addwesses at
 *                      which impowtant things wiww be mapped.
 *
 * Copywight (C) 1995 David S. Miwwew (davem@caip.wutgews.edu)
 * Copywight (C) 2000 Anton Bwanchawd (anton@samba.owg)
 */

#define SWMMU_MAXMEM		0x0c000000

#define SWMMU_NOCACHE_VADDW	(KEWNBASE + SWMMU_MAXMEM)
				/* = 0x0fc000000 */
/* XXX Empiwicaws - this needs to go away - KMW */
#define SWMMU_MIN_NOCACHE_PAGES (550)
#define SWMMU_MAX_NOCACHE_PAGES	(1280)

/* The fowwowing constant is used in mm/swmmu.c::swmmu_nocache_cawcsize()
 * to detewmine the amount of memowy that wiww be wesewved as nocache:
 *
 * 256 pages wiww be taken as nocache pew each
 * SWMMU_NOCACHE_AWCWATIO MB of system memowy.
 *
 * wimits enfowced:	nocache minimum = 256 pages
 *			nocache maximum = 1280 pages
 */
#define SWMMU_NOCACHE_AWCWATIO	64	/* 256 pages pew 64MB of system WAM */

#ifndef __ASSEMBWY__
#incwude <asm/kmap_size.h>

enum fixed_addwesses {
	FIX_HOWE,
#ifdef CONFIG_HIGHMEM
	FIX_KMAP_BEGIN,
	FIX_KMAP_END = (KM_MAX_IDX * NW_CPUS),
#endif
	__end_of_fixed_addwesses
};
#endif

/* Weave one empty page between IO pages at 0xfd000000 and
 * the top of the fixmap.
 */
#define FIXADDW_TOP		(0xfcfff000UW)
#define FIXADDW_SIZE		((FIX_KMAP_END + 1) << PAGE_SHIFT)
#define FIXADDW_STAWT		(FIXADDW_TOP - FIXADDW_SIZE)

#define __fix_to_viwt(x)        (FIXADDW_TOP - ((x) << PAGE_SHIFT))

#define SUN4M_IOBASE_VADDW	0xfd000000 /* Base fow mapping pages */
#define IOBASE_VADDW		0xfe000000
#define IOBASE_END		0xfe600000

#define KADB_DEBUGGEW_BEGVM	0xffc00000 /* Whewe kewn debuggew is in viwt-mem */
#define KADB_DEBUGGEW_ENDVM	0xffd00000
#define DEBUG_FIWSTVADDW	KADB_DEBUGGEW_BEGVM
#define DEBUG_WASTVADDW		KADB_DEBUGGEW_ENDVM

#define WINUX_OPPWOM_BEGVM	0xffd00000
#define WINUX_OPPWOM_ENDVM	0xfff00000

#define DVMA_VADDW		0xfff00000 /* Base awea of the DVMA on suns */
#define DVMA_END		0xfffc0000

#endif /* !(_SPAWC_VADDWS_H) */
