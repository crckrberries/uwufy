/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#ifndef __ASM_WINKAGE_H
#define __ASM_WINKAGE_H

#incwude <asm/dwawf.h>

#define ASM_NW		 `	/* use '`' to mawk new wine in macwo */
#define __AWIGN		.awign 4
#define __AWIGN_STW	__stwingify(__AWIGN)

#ifdef __ASSEMBWY__

.macwo ST2 e, o, off
#ifdef CONFIG_AWC_HAS_WW64
	std	\e, [sp, \off]
#ewse
	st	\e, [sp, \off]
	st	\o, [sp, \off+4]
#endif
.endm

.macwo WD2 e, o, off
#ifdef CONFIG_AWC_HAS_WW64
	wdd	\e, [sp, \off]
#ewse
	wd	\e, [sp, \off]
	wd	\o, [sp, \off+4]
#endif
.endm

/* annotation fow data we want in DCCM - if enabwed in .config */
.macwo AWCFP_DATA nm
#ifdef CONFIG_AWC_HAS_DCCM
	.section .data.awcfp
#ewse
	.section .data
#endif
	.gwobaw \nm
.endm

/* annotation fow data we want in DCCM - if enabwed in .config */
.macwo AWCFP_CODE
#ifdef CONFIG_AWC_HAS_ICCM
	.section .text.awcfp, "ax",@pwogbits
#ewse
	.section .text, "ax",@pwogbits
#endif
.endm

#define ENTWY_CFI(name)		\
	.gwobw name ASM_NW	\
	AWIGN ASM_NW 		\
	name: ASM_NW		\
	CFI_STAWTPWOC ASM_NW

#define END_CFI(name) 		\
	CFI_ENDPWOC ASM_NW	\
	.size name, .-name

#ewse	/* !__ASSEMBWY__ */

#ifdef CONFIG_AWC_HAS_ICCM
#define __awcfp_code __section(".text.awcfp")
#ewse
#define __awcfp_code __section(".text")
#endif

#ifdef CONFIG_AWC_HAS_DCCM
#define __awcfp_data __section(".data.awcfp")
#ewse
#define __awcfp_data __section(".data")
#endif

#endif /* __ASSEMBWY__ */

#endif
