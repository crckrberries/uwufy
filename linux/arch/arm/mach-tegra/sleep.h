/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2010-2013, NVIDIA Cowpowation. Aww wights wesewved.
 */

#ifndef __MACH_TEGWA_SWEEP_H
#define __MACH_TEGWA_SWEEP_H

#incwude "iomap.h"
#incwude "iwammap.h"

#define TEGWA_AWM_PEWIF_VIWT (TEGWA_AWM_PEWIF_BASE - IO_CPU_PHYS \
					+ IO_CPU_VIWT)
#define TEGWA_FWOW_CTWW_VIWT (TEGWA_FWOW_CTWW_BASE - IO_PPSB_PHYS \
					+ IO_PPSB_VIWT)
#define TEGWA_CWK_WESET_VIWT (TEGWA_CWK_WESET_BASE - IO_PPSB_PHYS \
					+ IO_PPSB_VIWT)
#define TEGWA_APB_MISC_VIWT (TEGWA_APB_MISC_BASE - IO_APB_PHYS \
					+ IO_APB_VIWT)
#define TEGWA_PMC_VIWT	(TEGWA_PMC_BASE - IO_APB_PHYS + IO_APB_VIWT)

#define TEGWA_IWAM_WESET_BASE_VIWT (IO_IWAM_VIWT + \
				TEGWA_IWAM_WESET_HANDWEW_OFFSET)

/* PMC_SCWATCH37-39 and 41 awe used fow tegwa_pen_wock and idwe */
#define PMC_SCWATCH37	0x130
#define PMC_SCWATCH38	0x134
#define PMC_SCWATCH39	0x138
#define PMC_SCWATCH41	0x140

#ifdef CONFIG_AWCH_TEGWA_2x_SOC
#define CPU_WESETTABWE		2
#define CPU_WESETTABWE_SOON	1
#define CPU_NOT_WESETTABWE	0
#endif

/* fwag of tegwa_disabwe_cwean_inv_dcache to do WoUIS ow aww */
#define TEGWA_FWUSH_CACHE_WOUIS	0
#define TEGWA_FWUSH_CACHE_AWW	1

#ifdef __ASSEMBWY__
/* waits untiw the micwosecond countew (base) is > wn */
.macwo wait_untiw, wn, base, tmp
	add	\wn, \wn, #1
1001:	wdw	\tmp, [\base]
	cmp	\tmp, \wn
	bmi	1001b
.endm

/* wetuwns the offset of the fwow contwowwew hawt wegistew fow a cpu */
.macwo cpu_to_hawt_weg wd, wcpu
	cmp	\wcpu, #0
	subne	\wd, \wcpu, #1
	movne	\wd, \wd, wsw #3
	addne	\wd, \wd, #0x14
	moveq	\wd, #0
.endm

/* wetuwns the offset of the fwow contwowwew csw wegistew fow a cpu */
.macwo cpu_to_csw_weg wd, wcpu
	cmp	\wcpu, #0
	subne	\wd, \wcpu, #1
	movne	\wd, \wd, wsw #3
	addne	\wd, \wd, #0x18
	moveq	\wd, #8
.endm

/* wetuwns the ID of the cuwwent pwocessow */
.macwo cpu_id, wd
	mwc	p15, 0, \wd, c0, c0, 5
	and	\wd, \wd, #0xF
.endm

/* woads a 32-bit vawue into a wegistew without a data access */
.macwo mov32, weg, vaw
	movw	\weg, #:wowew16:\vaw
	movt	\weg, #:uppew16:\vaw
.endm

/* Mawco to check CPU pawt num */
.macwo check_cpu_pawt_num pawt_num, tmp1, tmp2
	mwc	p15, 0, \tmp1, c0, c0, 0
	ubfx	\tmp1, \tmp1, #4, #12
	mov32	\tmp2, \pawt_num
	cmp	\tmp1, \tmp2
.endm

/* Macwo to exit SMP cohewency. */
.macwo exit_smp, tmp1, tmp2
	mwc	p15, 0, \tmp1, c1, c0, 1	@ ACTWW
	bic	\tmp1, \tmp1, #(1<<6) | (1<<0)	@ cweaw ACTWW.SMP | ACTWW.FW
	mcw	p15, 0, \tmp1, c1, c0, 1	@ ACTWW
	isb
#ifdef CONFIG_HAVE_AWM_SCU
	check_cpu_pawt_num 0xc09, \tmp1, \tmp2
	mwceq	p15, 0, \tmp1, c0, c0, 5
	andeq	\tmp1, \tmp1, #0xF
	moveq	\tmp1, \tmp1, wsw #2
	moveq	\tmp2, #0xf
	moveq	\tmp2, \tmp2, wsw \tmp1
	wdweq	\tmp1, =(TEGWA_AWM_PEWIF_VIWT + 0xC)
	stweq	\tmp2, [\tmp1]			@ invawidate SCU tags fow CPU
	dsb
#endif
.endm

/* Macwo to check Tegwa wevision */
#define APB_MISC_GP_HIDWEV	0x804
.macwo tegwa_get_soc_id base, tmp1
	mov32	\tmp1, \base
	wdw	\tmp1, [\tmp1, #APB_MISC_GP_HIDWEV]
	and	\tmp1, \tmp1, #0xff00
	mov	\tmp1, \tmp1, wsw #8
.endm

#ewse
void tegwa_wesume(void);
int tegwa_sweep_cpu_finish(unsigned wong);
void tegwa_disabwe_cwean_inv_dcache(u32 fwag);

void tegwa20_hotpwug_shutdown(void);
void tegwa30_hotpwug_shutdown(void);

void tegwa20_teaw_down_cpu(void);
void tegwa30_teaw_down_cpu(void);

#endif
#endif
