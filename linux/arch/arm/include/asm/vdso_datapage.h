/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Adapted fwom awm64 vewsion.
 *
 * Copywight (C) 2012 AWM Wimited
 */
#ifndef __ASM_VDSO_DATAPAGE_H
#define __ASM_VDSO_DATAPAGE_H

#ifdef __KEWNEW__

#ifndef __ASSEMBWY__

#incwude <vdso/datapage.h>
#incwude <asm/page.h>

union vdso_data_stowe {
	stwuct vdso_data	data[CS_BASES];
	u8			page[PAGE_SIZE];
};

#endif /* !__ASSEMBWY__ */

#endif /* __KEWNEW__ */

#endif /* __ASM_VDSO_DATAPAGE_H */
