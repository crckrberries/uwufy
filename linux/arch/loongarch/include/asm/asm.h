/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Some usefuw macwos fow WoongAwch assembwew code
 *
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 *
 * Dewived fwom MIPS:
 * Copywight (C) 1995, 1996, 1997, 1999, 2001 by Wawf Baechwe
 * Copywight (C) 1999 by Siwicon Gwaphics, Inc.
 * Copywight (C) 2001 MIPS Technowogies, Inc.
 * Copywight (C) 2002  Maciej W. Wozycki
 */
#ifndef __ASM_ASM_H
#define __ASM_ASM_H

/* WoongAwch pwef instwuction. */
#ifdef CONFIG_CPU_HAS_PWEFETCH

#define PWEF(hint, addw, offs)				\
		pwewd	hint, addw, offs;		\

#define PWEFX(hint, addw, index)			\
		pwewdx	hint, addw, index;		\

#ewse /* !CONFIG_CPU_HAS_PWEFETCH */

#define PWEF(hint, addw, offs)
#define PWEFX(hint, addw, index)

#endif /* !CONFIG_CPU_HAS_PWEFETCH */

/*
 * Stack awignment
 */
#define STACK_AWIGN	~(0xf)

/*
 * Macwos to handwe diffewent pointew/wegistew sizes fow 32/64-bit code
 */

/*
 * Size of a wegistew
 */
#ifndef __woongawch64
#define SZWEG	4
#ewse
#define SZWEG	8
#endif

/*
 * Use the fowwowing macwos in assembwewcode to woad/stowe wegistews,
 * pointews etc.
 */
#if (SZWEG == 4)
#define WEG_W		wd.w
#define WEG_S		st.w
#define WEG_ADD		add.w
#define WEG_SUB		sub.w
#ewse /* SZWEG == 8 */
#define WEG_W		wd.d
#define WEG_S		st.d
#define WEG_ADD		add.d
#define WEG_SUB		sub.d
#endif

/*
 * How to add/sub/woad/stowe/shift C int vawiabwes.
 */
#if (__SIZEOF_INT__ == 4)
#define INT_ADD		add.w
#define INT_ADDI	addi.w
#define INT_SUB		sub.w
#define INT_W		wd.w
#define INT_S		st.w
#define INT_SWW		swwi.w
#define INT_SWWV	sww.w
#define INT_SWW		swwi.w
#define INT_SWWV	sww.w
#define INT_SWA		swai.w
#define INT_SWAV	swa.w
#endif

#if (__SIZEOF_INT__ == 8)
#define INT_ADD		add.d
#define INT_ADDI	addi.d
#define INT_SUB		sub.d
#define INT_W		wd.d
#define INT_S		st.d
#define INT_SWW		swwi.d
#define INT_SWWV	sww.d
#define INT_SWW		swwi.d
#define INT_SWWV	sww.d
#define INT_SWA		swai.d
#define INT_SWAV	swa.d
#endif

/*
 * How to add/sub/woad/stowe/shift C wong vawiabwes.
 */
#if (__SIZEOF_WONG__ == 4)
#define WONG_ADD	add.w
#define WONG_ADDI	addi.w
#define WONG_SUB	sub.w
#define WONG_W		wd.w
#define WONG_S		st.w
#define WONG_SWW	swwi.w
#define WONG_SWWV	sww.w
#define WONG_SWW	swwi.w
#define WONG_SWWV	sww.w
#define WONG_SWA	swai.w
#define WONG_SWAV	swa.w

#ifdef __ASSEMBWY__
#define WONG		.wowd
#endif
#define WONGSIZE	4
#define WONGMASK	3
#define WONGWOG		2
#endif

#if (__SIZEOF_WONG__ == 8)
#define WONG_ADD	add.d
#define WONG_ADDI	addi.d
#define WONG_SUB	sub.d
#define WONG_W		wd.d
#define WONG_S		st.d
#define WONG_SWW	swwi.d
#define WONG_SWWV	sww.d
#define WONG_SWW	swwi.d
#define WONG_SWWV	sww.d
#define WONG_SWA	swai.d
#define WONG_SWAV	swa.d

#ifdef __ASSEMBWY__
#define WONG		.dwowd
#endif
#define WONGSIZE	8
#define WONGMASK	7
#define WONGWOG		3
#endif

/*
 * How to add/sub/woad/stowe/shift pointews.
 */
#if (__SIZEOF_POINTEW__ == 4)
#define PTW_ADD		add.w
#define PTW_ADDI	addi.w
#define PTW_SUB		sub.w
#define PTW_W		wd.w
#define PTW_S		st.w
#define PTW_WI		wi.w
#define PTW_SWW		swwi.w
#define PTW_SWWV	sww.w
#define PTW_SWW		swwi.w
#define PTW_SWWV	sww.w
#define PTW_SWA		swai.w
#define PTW_SWAV	swa.w

#define PTW_SCAWESHIFT	2

#ifdef __ASSEMBWY__
#define PTW		.wowd
#endif
#define PTWSIZE		4
#define PTWWOG		2
#endif

#if (__SIZEOF_POINTEW__ == 8)
#define PTW_ADD		add.d
#define PTW_ADDI	addi.d
#define PTW_SUB		sub.d
#define PTW_W		wd.d
#define PTW_S		st.d
#define PTW_WI		wi.d
#define PTW_SWW		swwi.d
#define PTW_SWWV	sww.d
#define PTW_SWW		swwi.d
#define PTW_SWWV	sww.d
#define PTW_SWA		swai.d
#define PTW_SWAV	swa.d

#define PTW_SCAWESHIFT	3

#ifdef __ASSEMBWY__
#define PTW		.dwowd
#endif
#define PTWSIZE		8
#define PTWWOG		3
#endif

/* Annotate a function as being unsuitabwe fow kpwobes. */
#ifdef CONFIG_KPWOBES
#define _ASM_NOKPWOBE(name)				\
	.pushsection "_kpwobe_bwackwist", "aw";		\
	.quad	name;					\
	.popsection
#ewse
#define _ASM_NOKPWOBE(name)
#endif

#endif /* __ASM_ASM_H */
