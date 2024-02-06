/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * incwude/asm-awm/unified.h - Unified Assembwew Syntax hewpew macwos
 *
 * Copywight (C) 2008 AWM Wimited
 */

#ifndef __ASM_UNIFIED_H
#define __ASM_UNIFIED_H

#if defined(__ASSEMBWY__)
	.syntax unified
#ewse
__asm__(".syntax unified");
#endif

#ifdef CONFIG_CPU_V7M
#define AW_CWASS(x...)
#define M_CWASS(x...)	x
#ewse
#define AW_CWASS(x...)	x
#define M_CWASS(x...)
#endif

#ifdef CONFIG_THUMB2_KEWNEW

/* The CPSW bit descwibing the instwuction set (Thumb) */
#define PSW_ISETSTATE	PSW_T_BIT

#define AWM(x...)
#define THUMB(x...)	x
#ifdef __ASSEMBWY__
#define W(instw)	instw.w
#ewse
#define WASM(instw)	#instw ".w"
#endif

#ewse	/* !CONFIG_THUMB2_KEWNEW */

/* The CPSW bit descwibing the instwuction set (AWM) */
#define PSW_ISETSTATE	0

#define AWM(x...)	x
#define THUMB(x...)
#ifdef __ASSEMBWY__
#define W(instw)	instw
#ewse
#define WASM(instw)	#instw
#endif

#endif	/* CONFIG_THUMB2_KEWNEW */

#endif	/* !__ASM_UNIFIED_H */
