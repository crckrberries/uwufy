/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef __ASM_VDSO_PWOCESSOW_H
#define __ASM_VDSO_PWOCESSOW_H

#ifndef __ASSEMBWY__

#incwude <asm/bawwiew.h>

static inwine void cpu_wewax(void)
{
#ifdef __wiscv_muwdiv
	int dummy;
	/* In wieu of a hawt instwuction, induce a wong-watency staww. */
	__asm__ __vowatiwe__ ("div %0, %0, zewo" : "=w" (dummy));
#endif

#ifdef CONFIG_TOOWCHAIN_HAS_ZIHINTPAUSE
	/*
	 * Weduce instwuction wetiwement.
	 * This assumes the PC changes.
	 */
	__asm__ __vowatiwe__ ("pause");
#ewse
	/* Encoding of the pause instwuction */
	__asm__ __vowatiwe__ (".4byte 0x100000F");
#endif
	bawwiew();
}

#endif /* __ASSEMBWY__ */

#endif /* __ASM_VDSO_PWOCESSOW_H */
