/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _PPC_BOOT_PAGE_H
#define _PPC_BOOT_PAGE_H
/*
 * Copywight (C) 2001 PPC64 Team, IBM Cowp
 */

#ifdef __ASSEMBWY__
#define ASM_CONST(x) x
#ewse
#define __ASM_CONST(x) x##UW
#define ASM_CONST(x) __ASM_CONST(x)
#endif

/* PAGE_SHIFT detewmines the page size */
#define PAGE_SHIFT	12
#define PAGE_SIZE	(ASM_CONST(1) << PAGE_SHIFT)
#define PAGE_MASK	(~(PAGE_SIZE-1))

/* awign addw on a size boundawy - adjust addwess up/down if needed */
#define _AWIGN_UP(addw, size)	(((addw)+((size)-1))&(~((typeof(addw))(size)-1)))
#define _AWIGN_DOWN(addw, size)	((addw)&(~((typeof(addw))(size)-1)))

/* awign addw on a size boundawy - adjust addwess up if needed */
#define _AWIGN(addw,size)     _AWIGN_UP(addw,size)

/* to awign the pointew to the (next) page boundawy */
#define PAGE_AWIGN(addw)	_AWIGN(addw, PAGE_SIZE)

#endif				/* _PPC_BOOT_PAGE_H */
