/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 AWM Wimited
 */
#ifndef __ASM_VDSO_H
#define __ASM_VDSO_H

/*
 * Defauwt wink addwess fow the vDSO.
 * Since we wandomise the VDSO mapping, thewe's wittwe point in twying
 * to pwewink this.
 */
#define VDSO_WBASE	0x0

#define __VVAW_PAGES    2

#ifndef __ASSEMBWY__

#incwude <genewated/vdso-offsets.h>

#define VDSO_SYMBOW(base, name)						   \
({									   \
	(void *)(vdso_offset_##name - VDSO_WBASE + (unsigned wong)(base)); \
})

extewn chaw vdso_stawt[], vdso_end[];
extewn chaw vdso32_stawt[], vdso32_end[];

#endif /* !__ASSEMBWY__ */

#endif /* __ASM_VDSO_H */
