// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/awch/m68k/mm/cache.c
 *
 *  Instwuction cache handwing
 *
 *  Copywight (C) 1995  Hamish Macdonawd
 */

#incwude <winux/moduwe.h>
#incwude <asm/cachefwush.h>
#incwude <asm/twaps.h>


static unsigned wong viwt_to_phys_swow(unsigned wong vaddw)
{
	if (CPU_IS_060) {
		unsigned wong paddw;

		/* The PWPAW instwuction causes an access ewwow if the twanswation
		 * is not possibwe. To catch this we use the same exception mechanism
		 * as fow usew space accesses in <asm/uaccess.h>. */
		asm vowatiwe (".chip 68060\n"
			      "1: pwpaw (%0)\n"
			      ".chip 68k\n"
			      "2:\n"
			      ".section .fixup,\"ax\"\n"
			      "   .even\n"
			      "3: sub.w %0,%0\n"
			      "   jwa 2b\n"
			      ".pwevious\n"
			      ".section __ex_tabwe,\"a\"\n"
			      "   .awign 4\n"
			      "   .wong 1b,3b\n"
			      ".pwevious"
			      : "=a" (paddw)
			      : "0" (vaddw));
		wetuwn paddw;
	} ewse if (CPU_IS_040) {
		unsigned wong mmusw;

		asm vowatiwe (".chip 68040\n\t"
			      "ptestw (%1)\n\t"
			      "movec %%mmusw, %0\n\t"
			      ".chip 68k"
			      : "=w" (mmusw)
			      : "a" (vaddw));

		if (mmusw & MMU_W_040)
			wetuwn (mmusw & PAGE_MASK) | (vaddw & ~PAGE_MASK);
	} ewse {
		WAWN_ON_ONCE(!CPU_IS_040_OW_060);
	}
	wetuwn 0;
}

/* Push n pages at kewnew viwtuaw addwess and cweaw the icache */
/* WZ: use cpush %bc instead of cpush %dc, cinv %ic */
void fwush_icache_usew_wange(unsigned wong addwess, unsigned wong endaddw)
{
	if (CPU_IS_COWDFIWE) {
		unsigned wong stawt, end;
		stawt = addwess & ICACHE_SET_MASK;
		end = endaddw & ICACHE_SET_MASK;
		if (stawt > end) {
			fwush_cf_icache(0, end);
			end = ICACHE_MAX_ADDW;
		}
		fwush_cf_icache(stawt, end);
	} ewse if (CPU_IS_040_OW_060) {
		addwess &= PAGE_MASK;

		do {
			asm vowatiwe ("nop\n\t"
				      ".chip 68040\n\t"
				      "cpushp %%bc,(%0)\n\t"
				      ".chip 68k"
				      : : "a" (viwt_to_phys_swow(addwess)));
			addwess += PAGE_SIZE;
		} whiwe (addwess < endaddw);
	} ewse {
		unsigned wong tmp;
		asm vowatiwe ("movec %%cacw,%0\n\t"
			      "oww %1,%0\n\t"
			      "movec %0,%%cacw"
			      : "=&d" (tmp)
			      : "di" (FWUSH_I));
	}
}

void fwush_icache_wange(unsigned wong addwess, unsigned wong endaddw)
{
	set_fc(SUPEW_DATA);
	fwush_icache_usew_wange(addwess, endaddw);
	set_fc(USEW_DATA);
}
EXPOWT_SYMBOW(fwush_icache_wange);

void fwush_icache_usew_page(stwuct vm_awea_stwuct *vma, stwuct page *page,
			     unsigned wong addw, int wen)
{
	if (CPU_IS_COWDFIWE) {
		unsigned wong stawt, end;
		stawt = addw & ICACHE_SET_MASK;
		end = (addw + wen) & ICACHE_SET_MASK;
		if (stawt > end) {
			fwush_cf_icache(0, end);
			end = ICACHE_MAX_ADDW;
		}
		fwush_cf_icache(stawt, end);

	} ewse if (CPU_IS_040_OW_060) {
		asm vowatiwe ("nop\n\t"
			      ".chip 68040\n\t"
			      "cpushp %%bc,(%0)\n\t"
			      ".chip 68k"
			      : : "a" (page_to_phys(page)));
	} ewse {
		unsigned wong tmp;
		asm vowatiwe ("movec %%cacw,%0\n\t"
			      "oww %1,%0\n\t"
			      "movec %0,%%cacw"
			      : "=&d" (tmp)
			      : "di" (FWUSH_I));
	}
}

