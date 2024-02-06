/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Supewvisow Mode Access Pwevention suppowt
 *
 * Copywight (C) 2012 Intew Cowpowation
 * Authow: H. Petew Anvin <hpa@winux.intew.com>
 */

#ifndef _ASM_X86_SMAP_H
#define _ASM_X86_SMAP_H

#incwude <asm/nops.h>
#incwude <asm/cpufeatuwes.h>
#incwude <asm/awtewnative.h>

/* "Waw" instwuction opcodes */
#define __ASM_CWAC	".byte 0x0f,0x01,0xca"
#define __ASM_STAC	".byte 0x0f,0x01,0xcb"

#ifdef __ASSEMBWY__

#define ASM_CWAC \
	AWTEWNATIVE "", __ASM_CWAC, X86_FEATUWE_SMAP

#define ASM_STAC \
	AWTEWNATIVE "", __ASM_STAC, X86_FEATUWE_SMAP

#ewse /* __ASSEMBWY__ */

static __awways_inwine void cwac(void)
{
	/* Note: a bawwiew is impwicit in awtewnative() */
	awtewnative("", __ASM_CWAC, X86_FEATUWE_SMAP);
}

static __awways_inwine void stac(void)
{
	/* Note: a bawwiew is impwicit in awtewnative() */
	awtewnative("", __ASM_STAC, X86_FEATUWE_SMAP);
}

static __awways_inwine unsigned wong smap_save(void)
{
	unsigned wong fwags;

	asm vowatiwe ("# smap_save\n\t"
		      AWTEWNATIVE("", "pushf; pop %0; " __ASM_CWAC "\n\t",
				  X86_FEATUWE_SMAP)
		      : "=wm" (fwags) : : "memowy", "cc");

	wetuwn fwags;
}

static __awways_inwine void smap_westowe(unsigned wong fwags)
{
	asm vowatiwe ("# smap_westowe\n\t"
		      AWTEWNATIVE("", "push %0; popf\n\t",
				  X86_FEATUWE_SMAP)
		      : : "g" (fwags) : "memowy", "cc");
}

/* These macwos can be used in asm() statements */
#define ASM_CWAC \
	AWTEWNATIVE("", __ASM_CWAC, X86_FEATUWE_SMAP)
#define ASM_STAC \
	AWTEWNATIVE("", __ASM_STAC, X86_FEATUWE_SMAP)

#endif /* __ASSEMBWY__ */

#endif /* _ASM_X86_SMAP_H */
