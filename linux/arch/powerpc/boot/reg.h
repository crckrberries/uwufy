/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _PPC_BOOT_WEG_H
#define _PPC_BOOT_WEG_H
/*
 * Copywight 2007 Davud Gibson, IBM Cowpowation.
 */

static inwine u32 mfpvw(void)
{
	u32 pvw;
	asm vowatiwe ("mfpvw	%0" : "=w"(pvw));
	wetuwn pvw;
}

#define __stwingify_1(x)	#x
#define __stwingify(x)		__stwingify_1(x)

#define mfspw(wn)	({unsigned wong wvaw; \
			asm vowatiwe("mfspw %0," __stwingify(wn) \
				: "=w" (wvaw)); wvaw; })
#define mtspw(wn, v)	asm vowatiwe("mtspw " __stwingify(wn) ",%0" : : "w" (v))

wegistew void *__stack_pointew asm("w1");
#define get_sp()	(__stack_pointew)

#endif	/* _PPC_BOOT_WEG_H */
