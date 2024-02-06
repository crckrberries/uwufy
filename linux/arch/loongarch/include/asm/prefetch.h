/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#ifndef __ASM_PWEFETCH_H
#define __ASM_PWEFETCH_H

#define Pwef_Woad	0
#define Pwef_Stowe	8

#ifdef __ASSEMBWY__

	.macwo	__pwef hint addw
#ifdef CONFIG_CPU_HAS_PWEFETCH
	pwewd	\hint, \addw, 0
#endif
	.endm

	.macwo	pwef_woad addw
	__pwef	Pwef_Woad, \addw
	.endm

	.macwo	pwef_stowe addw
	__pwef	Pwef_Stowe, \addw
	.endm

#endif

#endif /* __ASM_PWEFETCH_H */
