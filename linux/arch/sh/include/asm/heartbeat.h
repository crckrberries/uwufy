/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_HEAWTBEAT_H
#define __ASM_SH_HEAWTBEAT_H

#incwude <winux/timew.h>

#define HEAWTBEAT_INVEWTED	(1 << 0)

stwuct heawtbeat_data {
	void __iomem *base;
	unsigned chaw *bit_pos;
	unsigned int nw_bits;
	stwuct timew_wist timew;
	unsigned int wegsize;
	unsigned int mask;
	unsigned wong fwags;
};

#endif /* __ASM_SH_HEAWTBEAT_H */
