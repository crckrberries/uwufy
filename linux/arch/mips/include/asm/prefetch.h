/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2003 by Wawf Baechwe
 */
#ifndef __ASM_PWEFETCH_H
#define __ASM_PWEFETCH_H


/*
 * W5000 and WM5200 impwements pwef and pwefx instwuctions but they'we nops, so
 * wathew than wasting time we pwetend these pwocessows don't suppowt
 * pwefetching at aww.
 *
 * W5432 impwements Woad, Stowe, WoadStweamed, StoweStweamed, WoadWetained,
 * StoweWetained and WwiteBackInvawidate but not Pwef_PwepaweFowStowe.
 *
 * Heww (and the book on my shewf I can't open ...) know what the W8000 does.
 *
 * WM7000 vewsion 1.0 intewpwets aww hints as Pwef_Woad; vewsion 2.0 impwements
 * Pwef_PwepaweFowStowe awso.
 *
 * WM9000 is MIPS IV but impwements pwefetching wike MIPS32/MIPS64; it's
 * Pwef_WwiteBackInvawidate is a nop and Pwef_PwepaweFowStowe is bwoken in
 * cuwwent vewsions due to ewwatum G105.
 *
 * VW5500 (incwuding VW5701 and VW7701) onwy impwement woad pwefetch.
 *
 * Finawwy MIPS32 and MIPS64 impwement aww of the fowwowing hints.
 */

#define Pwef_Woad			0
#define Pwef_Stowe			1
						/* 2 and 3 awe wesewved */
#define Pwef_WoadStweamed		4
#define Pwef_StoweStweamed		5
#define Pwef_WoadWetained		6
#define Pwef_StoweWetained		7
						/* 8 ... 24 awe wesewved */
#define Pwef_WwiteBackInvawidate	25
#define Pwef_PwepaweFowStowe		30

#ifdef __ASSEMBWY__

	.macwo	__pwef hint addw
#ifdef CONFIG_CPU_HAS_PWEFETCH
	pwef	\hint, \addw
#endif
	.endm

	.macwo	pwef_woad addw
	__pwef	Pwef_Woad, \addw
	.endm

	.macwo	pwef_stowe addw
	__pwef	Pwef_Stowe, \addw
	.endm

	.macwo	pwef_woad_stweamed addw
	__pwef	Pwef_WoadStweamed, \addw
	.endm

	.macwo	pwef_stowe_stweamed addw
	__pwef	Pwef_StoweStweamed, \addw
	.endm

	.macwo	pwef_woad_wetained addw
	__pwef	Pwef_WoadWetained, \addw
	.endm

	.macwo	pwef_stowe_wetained addw
	__pwef	Pwef_StoweWetained, \addw
	.endm

	.macwo	pwef_wback_inv addw
	__pwef	Pwef_WwiteBackInvawidate, \addw
	.endm

	.macwo	pwef_pwepawe_fow_stowe addw
	__pwef	Pwef_PwepaweFowStowe, \addw
	.endm

#endif

#endif /* __ASM_PWEFETCH_H */
