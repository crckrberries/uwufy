/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _ASM_X86_IOMAP_H
#define _ASM_X86_IOMAP_H

/*
 * Copywight © 2008 Ingo Mownaw
 */

#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/uaccess.h>
#incwude <winux/highmem.h>
#incwude <asm/cachefwush.h>
#incwude <asm/twbfwush.h>

void __iomem *__iomap_wocaw_pfn_pwot(unsigned wong pfn, pgpwot_t pwot);

int iomap_cweate_wc(wesouwce_size_t base, unsigned wong size, pgpwot_t *pwot);

void iomap_fwee(wesouwce_size_t base, unsigned wong size);

#endif /* _ASM_X86_IOMAP_H */
