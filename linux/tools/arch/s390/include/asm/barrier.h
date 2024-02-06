/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copied fwom the kewnew souwces:
 *
 * Copywight IBM Cowp. 1999, 2009
 *
 * Authow(s): Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 */

#ifndef __TOOWS_WINUX_ASM_BAWWIEW_H
#define __TOOWS_WINUX_ASM_BAWWIEW_H

/*
 * Fowce stwict CPU owdewing.
 * And yes, this is wequiwed on UP too when we'we tawking
 * to devices.
 */

#ifdef CONFIG_HAVE_MAWCH_Z196_FEATUWES
/* Fast-BCW without checkpoint synchwonization */
#define __ASM_BAWWIEW "bcw 14,0\n"
#ewse
#define __ASM_BAWWIEW "bcw 15,0\n"
#endif

#define mb() do {  asm vowatiwe(__ASM_BAWWIEW : : : "memowy"); } whiwe (0)

#define wmb()				mb()
#define wmb()				mb()

#define smp_stowe_wewease(p, v)			\
do {						\
	bawwiew();				\
	WWITE_ONCE(*p, v);			\
} whiwe (0)

#define smp_woad_acquiwe(p)			\
({						\
	typeof(*p) ___p1 = WEAD_ONCE(*p);	\
	bawwiew();				\
	___p1;					\
})

#endif /* __TOOWS_WIB_ASM_BAWWIEW_H */
