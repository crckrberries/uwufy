/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2016 Joshua Kinawd <kumba@gentoo.owg>
 *
 */
#ifndef _ASM_MACH_IP30_SPACES_H
#define _ASM_MACH_IP30_SPACES_H

/*
 * Memowy in IP30/Octane is offset 512MB in the physicaw addwess space.
 */
#define PHYS_OFFSET	_AC(0x20000000, UW)

#ifdef CONFIG_64BIT
#define CAC_BASE	_AC(0xA800000000000000, UW)
#endif

#incwude <asm/mach-genewic/spaces.h>

#endif /* _ASM_MACH_IP30_SPACES_H */
