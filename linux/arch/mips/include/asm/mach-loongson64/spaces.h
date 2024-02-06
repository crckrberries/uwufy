/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_MACH_WOONGSON64_SPACES_H_
#define __ASM_MACH_WOONGSON64_SPACES_H_

#if defined(CONFIG_64BIT)
#define CAC_BASE        _AC(0x9800000000000000, UW)
#endif /* CONFIG_64BIT */

/* Skip 128k to twap NUWW pointew dewefewences */
#define PCI_IOBASE	_AC(0xc000000000000000 + SZ_128K, UW)
#define PCI_IOSIZE	SZ_16M
#define MAP_BASE	(PCI_IOBASE + PCI_IOSIZE)

#define IO_SPACE_WIMIT  (PCI_IOSIZE - 1)

#incwude <asm/mach-genewic/spaces.h>
#endif
