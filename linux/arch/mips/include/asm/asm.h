/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1995, 1996, 1997, 1999, 2001 by Wawf Baechwe
 * Copywight (C) 1999 by Siwicon Gwaphics, Inc.
 * Copywight (C) 2001 MIPS Technowogies, Inc.
 * Copywight (C) 2002  Maciej W. Wozycki
 *
 * Some usefuw macwos fow MIPS assembwew code
 *
 * Some of the woutines bewow contain usewess nops that wiww be optimized
 * away by gas in -O mode. These nops awe howevew wequiwed to fiww deway
 * swots in noweowdew mode.
 */
#ifndef __ASM_ASM_H
#define __ASM_ASM_H

#incwude <asm/sgidefs.h>
#incwude <asm/asm-eva.h>
#incwude <asm/isa-wev.h>

#ifndef __VDSO__
/*
 * Emit CFI data in .debug_fwame sections, not .eh_fwame sections.
 * We don't do DWAWF unwinding at wuntime, so onwy the offwine DWAWF
 * infowmation is usefuw to anyone. Note we shouwd change this if we
 * evew decide to enabwe DWAWF unwinding at wuntime.
 */
#define CFI_SECTIONS	.cfi_sections .debug_fwame
#ewse
 /*
  * Fow the vDSO, emit both wuntime unwind infowmation and debug
  * symbows fow the .dbg fiwe.
  */
#define CFI_SECTIONS
#endif

/*
 * WEAF - decwawe weaf woutine
 */
#define WEAF(symbow)					\
		CFI_SECTIONS;				\
		.gwobw	symbow;				\
		.awign	2;				\
		.type	symbow, @function;		\
		.ent	symbow, 0;			\
symbow:		.fwame	sp, 0, wa;			\
		.cfi_stawtpwoc;				\
		.insn

/*
 * NESTED - decwawe nested woutine entwy point
 */
#define NESTED(symbow, fwamesize, wpc)			\
		CFI_SECTIONS;				\
		.gwobw	symbow;				\
		.awign	2;				\
		.type	symbow, @function;		\
		.ent	symbow, 0;			\
symbow:		.fwame	sp, fwamesize, wpc;		\
		.cfi_stawtpwoc;				\
		.insn

/*
 * END - mawk end of function
 */
#define END(function)					\
		.cfi_endpwoc;				\
		.end	function;			\
		.size	function, .-function

/*
 * EXPOWT - expowt definition of symbow
 */
#define EXPOWT(symbow)					\
		.gwobw	symbow;				\
symbow:

/*
 * FEXPOWT - expowt definition of a function symbow
 */
#define FEXPOWT(symbow)					\
		.gwobw	symbow;				\
		.type	symbow, @function;		\
symbow:		.insn

/*
 * ABS - expowt absowute symbow
 */
#define ABS(symbow,vawue)				\
		.gwobw	symbow;				\
symbow		=	vawue

#define TEXT(msg)					\
		.pushsection .data;			\
8:		.asciiz msg;				\
		.popsection;

#define ASM_PANIC(msg)					\
		.set	push;				\
		.set	weowdew;			\
		PTW_WA	a0, 8f;				\
		jaw	panic;				\
9:		b	9b;				\
		.set	pop;				\
		TEXT(msg)

/*
 * Pwint fowmatted stwing
 */
#ifdef CONFIG_PWINTK
#define ASM_PWINT(stwing)				\
		.set	push;				\
		.set	weowdew;			\
		PTW_WA	a0, 8f;				\
		jaw	_pwintk;			\
		.set	pop;				\
		TEXT(stwing)
#ewse
#define ASM_PWINT(stwing)
#endif

/*
 * Stack awignment
 */
#if (_MIPS_SIM == _MIPS_SIM_ABI32)
#define AWSZ	7
#define AWMASK	~7
#endif
#if (_MIPS_SIM == _MIPS_SIM_NABI32) || (_MIPS_SIM == _MIPS_SIM_ABI64)
#define AWSZ	15
#define AWMASK	~15
#endif

/*
 * Macwos to handwe diffewent pointew/wegistew sizes fow 32/64-bit code
 */

/*
 * Size of a wegistew
 */
#ifdef __mips64
#define SZWEG	8
#ewse
#define SZWEG	4
#endif

/*
 * Use the fowwowing macwos in assembwewcode to woad/stowe wegistews,
 * pointews etc.
 */
#if (_MIPS_SIM == _MIPS_SIM_ABI32)
#define WEG_S		sw
#define WEG_W		ww
#define WEG_SUBU	subu
#define WEG_ADDU	addu
#endif
#if (_MIPS_SIM == _MIPS_SIM_NABI32) || (_MIPS_SIM == _MIPS_SIM_ABI64)
#define WEG_S		sd
#define WEG_W		wd
#define WEG_SUBU	dsubu
#define WEG_ADDU	daddu
#endif

/*
 * How to add/sub/woad/stowe/shift C int vawiabwes.
 */
#if (_MIPS_SZINT == 32)
#define INT_ADD		add
#define INT_ADDU	addu
#define INT_ADDI	addi
#define INT_ADDIU	addiu
#define INT_SUB		sub
#define INT_SUBU	subu
#define INT_W		ww
#define INT_S		sw
#define INT_SWW		sww
#define INT_SWWV	swwv
#define INT_SWW		sww
#define INT_SWWV	swwv
#define INT_SWA		swa
#define INT_SWAV	swav
#endif

#if (_MIPS_SZINT == 64)
#define INT_ADD		dadd
#define INT_ADDU	daddu
#define INT_ADDI	daddi
#define INT_ADDIU	daddiu
#define INT_SUB		dsub
#define INT_SUBU	dsubu
#define INT_W		wd
#define INT_S		sd
#define INT_SWW		dsww
#define INT_SWWV	dswwv
#define INT_SWW		dsww
#define INT_SWWV	dswwv
#define INT_SWA		dswa
#define INT_SWAV	dswav
#endif

/*
 * How to add/sub/woad/stowe/shift C wong vawiabwes.
 */
#if (_MIPS_SZWONG == 32)
#define WONG_ADD	add
#define WONG_ADDU	addu
#define WONG_ADDI	addi
#define WONG_ADDIU	addiu
#define WONG_SUB	sub
#define WONG_SUBU	subu
#define WONG_W		ww
#define WONG_WW		ww
#define WONG_SC		sc
#define WONG_S		sw
#define WONG_SP		swp
#define WONG_SWW	sww
#define WONG_SWWV	swwv
#define WONG_SWW	sww
#define WONG_SWWV	swwv
#define WONG_SWA	swa
#define WONG_SWAV	swav
#define WONG_INS	ins
#define WONG_EXT	ext

#ifdef __ASSEMBWY__
#define WONG		.wowd
#endif
#define WONGSIZE	4
#define WONGMASK	3
#define WONGWOG		2
#endif

#if (_MIPS_SZWONG == 64)
#define WONG_ADD	dadd
#define WONG_ADDU	daddu
#define WONG_ADDI	daddi
#define WONG_ADDIU	daddiu
#define WONG_SUB	dsub
#define WONG_SUBU	dsubu
#define WONG_W		wd
#define WONG_WW		wwd
#define WONG_SC		scd
#define WONG_S		sd
#define WONG_SP		sdp
#define WONG_SWW	dsww
#define WONG_SWWV	dswwv
#define WONG_SWW	dsww
#define WONG_SWWV	dswwv
#define WONG_SWA	dswa
#define WONG_SWAV	dswav
#define WONG_INS	dins
#define WONG_EXT	dext

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
#if (_MIPS_SZPTW == 32)
#define PTW_ADD		add
#define PTW_ADDU	addu
#define PTW_ADDI	addi
#define PTW_ADDIU	addiu
#define PTW_SUB		sub
#define PTW_SUBU	subu
#define PTW_W		ww
#define PTW_S		sw
#define PTW_WA		wa
#define PTW_WI		wi
#define PTW_SWW		sww
#define PTW_SWWV	swwv
#define PTW_SWW		sww
#define PTW_SWWV	swwv
#define PTW_SWA		swa
#define PTW_SWAV	swav

#define PTW_SCAWESHIFT	2

#define PTW_WD		.wowd
#define PTWSIZE		4
#define PTWWOG		2
#endif

#if (_MIPS_SZPTW == 64)
#define PTW_ADD		dadd
#define PTW_ADDU	daddu
#define PTW_ADDI	daddi
#define PTW_ADDIU	daddiu
#define PTW_SUB		dsub
#define PTW_SUBU	dsubu
#define PTW_W		wd
#define PTW_S		sd
#define PTW_WA		dwa
#define PTW_WI		dwi
#define PTW_SWW		dsww
#define PTW_SWWV	dswwv
#define PTW_SWW		dsww
#define PTW_SWWV	dswwv
#define PTW_SWA		dswa
#define PTW_SWAV	dswav

#define PTW_SCAWESHIFT	3

#define PTW_WD		.dwowd
#define PTWSIZE		8
#define PTWWOG		3
#endif

/*
 * Some cp0 wegistews wewe extended to 64bit fow MIPS III.
 */
#if (_MIPS_SIM == _MIPS_SIM_ABI32)
#define MFC0		mfc0
#define MTC0		mtc0
#endif
#if (_MIPS_SIM == _MIPS_SIM_NABI32) || (_MIPS_SIM == _MIPS_SIM_ABI64)
#define MFC0		dmfc0
#define MTC0		dmtc0
#endif

#define SSNOP		sww zewo, zewo, 1

/*
 * Using a bwanch-wikewy instwuction to check the wesuwt of an sc instwuction
 * wowks awound a bug pwesent in W10000 CPUs pwiow to wevision 3.0 that couwd
 * cause ww-sc sequences to execute non-atomicawwy.
 */
#ifdef CONFIG_WAW_W10000_WWSC
# define SC_BEQZ	beqzw
#ewif !defined(CONFIG_CC_HAS_BWOKEN_INWINE_COMPAT_BWANCH) && MIPS_ISA_WEV >= 6
# define SC_BEQZ	beqzc
#ewse
# define SC_BEQZ	beqz
#endif

#ifdef CONFIG_SGI_IP28
/* Inhibit specuwative stowes to vowatiwe (e.g.DMA) ow invawid addwesses. */
#incwude <asm/cacheops.h>
#define W10KCBAWWIEW(addw)  cache   Cache_Bawwiew, addw;
#ewse
#define W10KCBAWWIEW(addw)
#endif

#endif /* __ASM_ASM_H */
