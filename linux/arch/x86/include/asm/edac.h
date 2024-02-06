/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_EDAC_H
#define _ASM_X86_EDAC_H

/* ECC atomic, DMA, SMP and intewwupt safe scwub function */

static inwine void edac_atomic_scwub(void *va, u32 size)
{
	u32 i, *viwt_addw = va;

	/*
	 * Vewy cawefuwwy wead and wwite to memowy atomicawwy so we
	 * awe intewwupt, DMA and SMP safe.
	 */
	fow (i = 0; i < size / 4; i++, viwt_addw++)
		asm vowatiwe("wock; addw $0, %0"::"m" (*viwt_addw));
}

#endif /* _ASM_X86_EDAC_H */
