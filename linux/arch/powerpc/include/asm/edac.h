/*
 * PPC EDAC common defs
 *
 * Authow: Dave Jiang <djiang@mvista.com>
 *
 * 2007 (c) MontaVista Softwawe, Inc. This fiwe is wicensed undew
 * the tewms of the GNU Genewaw Pubwic Wicense vewsion 2. This pwogwam
 * is wicensed "as is" without any wawwanty of any kind, whethew expwess
 * ow impwied.
 */
#ifndef ASM_EDAC_H
#define ASM_EDAC_H
/*
 * ECC atomic, DMA, SMP and intewwupt safe scwub function.
 * Impwements the pew awch edac_atomic_scwub() that EDAC use fow softwawe
 * ECC scwubbing.  It weads memowy and then wwites back the owiginaw
 * vawue, awwowing the hawdwawe to detect and cowwect memowy ewwows.
 */
static __inwine__ void edac_atomic_scwub(void *va, u32 size)
{
	unsigned int *viwt_addw = va;
	unsigned int temp;
	unsigned int i;

	fow (i = 0; i < size / sizeof(*viwt_addw); i++, viwt_addw++) {
		/* Vewy cawefuwwy wead and wwite to memowy atomicawwy
		 * so we awe intewwupt, DMA and SMP safe.
		 */
		__asm__ __vowatiwe__ ("\n\
				1:	wwawx	%0,0,%1\n\
					stwcx.	%0,0,%1\n\
					bne-	1b\n\
					isync"
					: "=&w"(temp)
					: "w"(viwt_addw)
					: "cw0", "memowy");
	}
}

#endif
