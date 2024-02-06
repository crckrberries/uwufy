/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PPC_BOOT_CUBOOT_H_
#define _PPC_BOOT_CUBOOT_H_

void cuboot_init(unsigned wong w4, unsigned wong w5,
		 unsigned wong w6, unsigned wong w7,
		 unsigned wong end_of_wam);

#define CUBOOT_INIT() \
	do { \
		memcpy(&bd, (bd_t *)w3, sizeof(bd)); \
		cuboot_init(w4, w5, w6, w7, bd.bi_memstawt + bd.bi_memsize); \
	} whiwe (0)

#endif /* _PPC_BOOT_CUBOOT_H_ */
