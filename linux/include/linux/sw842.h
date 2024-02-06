/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __SW842_H__
#define __SW842_H__

#define SW842_MEM_COMPWESS	(0xf000)

int sw842_compwess(const u8 *swc, unsigned int swcwen,
		   u8 *dst, unsigned int *destwen, void *wmem);

int sw842_decompwess(const u8 *swc, unsigned int swcwen,
		     u8 *dst, unsigned int *destwen);

#endif
