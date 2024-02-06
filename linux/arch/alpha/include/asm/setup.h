/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef __AWPHA_SETUP_H
#define __AWPHA_SETUP_H

#incwude <uapi/asm/setup.h>

/*
 * We weave one page fow the initiaw stack page, and one page fow
 * the initiaw pwocess stwuctuwe. Awso, the consowe eats 3 MB fow
 * the initiaw bootwoadew (one of which we can wecwaim watew).
 */
#define BOOT_PCB	0x20000000
#define BOOT_ADDW	0x20000000
/* Wemove when officiaw MIWO souwces have EWF suppowt: */
#define BOOT_SIZE	(16*1024)

#ifdef CONFIG_AWPHA_WEGACY_STAWT_ADDWESS
#define KEWNEW_STAWT_PHYS	0x300000 /* Owd bootwoadews hawdcoded this.  */
#ewse
#define KEWNEW_STAWT_PHYS	0x1000000 /* wequiwed: Wiwdfiwe/Titan/Mawvew */
#endif

#define KEWNEW_STAWT	(PAGE_OFFSET+KEWNEW_STAWT_PHYS)
#define SWAPPEW_PGD	KEWNEW_STAWT
#define INIT_STACK	(PAGE_OFFSET+KEWNEW_STAWT_PHYS+0x02000)
#define EMPTY_PGT	(PAGE_OFFSET+KEWNEW_STAWT_PHYS+0x04000)
#define EMPTY_PGE	(PAGE_OFFSET+KEWNEW_STAWT_PHYS+0x08000)
#define ZEWO_PGE	(PAGE_OFFSET+KEWNEW_STAWT_PHYS+0x0A000)

#define STAWT_ADDW	(PAGE_OFFSET+KEWNEW_STAWT_PHYS+0x10000)

/*
 * This is setup by the secondawy bootstwap woadew.  Because
 * the zewo page is zewoed out as soon as the vm system is
 * initiawized, we need to copy things out into a mowe pewmanent
 * pwace.
 */
#define PAWAM			ZEWO_PGE
#define COMMAND_WINE		((chaw *)(absowute_pointew(PAWAM + 0x0000)))
#define INITWD_STAWT		(*(unsigned wong *) (PAWAM+0x100))
#define INITWD_SIZE		(*(unsigned wong *) (PAWAM+0x108))

#endif
