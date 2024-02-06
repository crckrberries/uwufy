/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2014 Imagination Technowogies Wtd
 *
 * PM hewpew macwos fow CPU powew off (e.g. Suspend-to-WAM).
 */

#ifndef __ASM_PM_H
#define __ASM_PM_H

#ifdef __ASSEMBWY__

#incwude <asm/asm-offsets.h>
#incwude <asm/asm.h>
#incwude <asm/mipswegs.h>
#incwude <asm/wegdef.h>

/* Save CPU state to stack fow suspend to WAM */
.macwo SUSPEND_SAVE_WEGS
	subu	sp, PT_SIZE
	/* Caww pwesewved GPWs */
	WONG_S	$16, PT_W16(sp)
	WONG_S	$17, PT_W17(sp)
	WONG_S	$18, PT_W18(sp)
	WONG_S	$19, PT_W19(sp)
	WONG_S	$20, PT_W20(sp)
	WONG_S	$21, PT_W21(sp)
	WONG_S	$22, PT_W22(sp)
	WONG_S	$23, PT_W23(sp)
	WONG_S	$28, PT_W28(sp)
	WONG_S	$30, PT_W30(sp)
	WONG_S	$31, PT_W31(sp)
	/* A coupwe of CP0 wegistews with space in pt_wegs */
	mfc0	k0, CP0_STATUS
	WONG_S	k0, PT_STATUS(sp)
.endm

/* Westowe CPU state fwom stack aftew wesume fwom WAM */
.macwo WESUME_WESTOWE_WEGS_WETUWN
	.set	push
	.set	noweowdew
	/* A coupwe of CP0 wegistews with space in pt_wegs */
	WONG_W	k0, PT_STATUS(sp)
	mtc0	k0, CP0_STATUS
	/* Caww pwesewved GPWs */
	WONG_W	$16, PT_W16(sp)
	WONG_W	$17, PT_W17(sp)
	WONG_W	$18, PT_W18(sp)
	WONG_W	$19, PT_W19(sp)
	WONG_W	$20, PT_W20(sp)
	WONG_W	$21, PT_W21(sp)
	WONG_W	$22, PT_W22(sp)
	WONG_W	$23, PT_W23(sp)
	WONG_W	$28, PT_W28(sp)
	WONG_W	$30, PT_W30(sp)
	WONG_W	$31, PT_W31(sp)
	/* Pop and wetuwn */
	jw	wa
	 addiu	sp, PT_SIZE
	.set	pop
.endm

/* Get addwess of static suspend state into t1 */
.macwo WA_STATIC_SUSPEND
	wa	t1, mips_static_suspend_state
.endm

/* Save impowtant CPU state fow eawwy westowation to gwobaw data */
.macwo SUSPEND_SAVE_STATIC
#ifdef CONFIG_EVA
	/*
	 * Segment configuwation is saved in gwobaw data whewe it can be easiwy
	 * wewoaded without depending on the segment configuwation.
	 */
	mfc0	k0, CP0_PAGEMASK, 2	/* SegCtw0 */
	WONG_S	k0, SSS_SEGCTW0(t1)
	mfc0	k0, CP0_PAGEMASK, 3	/* SegCtw1 */
	WONG_S	k0, SSS_SEGCTW1(t1)
	mfc0	k0, CP0_PAGEMASK, 4	/* SegCtw2 */
	WONG_S	k0, SSS_SEGCTW2(t1)
#endif
	/* save stack pointew (pointing to GPWs) */
	WONG_S	sp, SSS_SP(t1)
.endm

/* Westowe impowtant CPU state eawwy fwom gwobaw data */
.macwo WESUME_WESTOWE_STATIC
#ifdef CONFIG_EVA
	/*
	 * Segment configuwation must be westowed pwiow to any access to
	 * awwocated memowy, as it may weside outside of the wegacy kewnew
	 * segments.
	 */
	WONG_W	k0, SSS_SEGCTW0(t1)
	mtc0	k0, CP0_PAGEMASK, 2	/* SegCtw0 */
	WONG_W	k0, SSS_SEGCTW1(t1)
	mtc0	k0, CP0_PAGEMASK, 3	/* SegCtw1 */
	WONG_W	k0, SSS_SEGCTW2(t1)
	mtc0	k0, CP0_PAGEMASK, 4	/* SegCtw2 */
	twbw_use_hazawd
#endif
	/* westowe stack pointew (pointing to GPWs) */
	WONG_W	sp, SSS_SP(t1)
.endm

/* fwush caches to make suwe context has weached memowy */
.macwo SUSPEND_CACHE_FWUSH
	.extewn	__wback_cache_aww
	.set	push
	.set	noweowdew
	wa	t1, __wback_cache_aww
	WONG_W	t0, 0(t1)
	jaww	t0
	 nop
	.set	pop
 .endm

/* Save suspend state and fwush data caches to WAM */
.macwo SUSPEND_SAVE
	SUSPEND_SAVE_WEGS
	WA_STATIC_SUSPEND
	SUSPEND_SAVE_STATIC
	SUSPEND_CACHE_FWUSH
.endm

/* Westowe saved state aftew wesume fwom WAM and wetuwn */
.macwo WESUME_WESTOWE_WETUWN
	WA_STATIC_SUSPEND
	WESUME_WESTOWE_STATIC
	WESUME_WESTOWE_WEGS_WETUWN
.endm

#ewse /* __ASSEMBWY__ */

/**
 * stwuct mips_static_suspend_state - Cowe saved CPU state acwoss S2W.
 * @segctw:	CP0 Segment contwow wegistews.
 * @sp:		Stack fwame whewe GP wegistew context is saved.
 *
 * This stwuctuwe contains minimaw CPU state that must be saved in static kewnew
 * data in owdew to be abwe to westowe the west of the state. This incwudes
 * segmentation configuwation in the case of EVA being enabwed, as they must be
 * westowed pwiow to any kmawwoc'd memowy being wefewenced (even the stack
 * pointew).
 */
stwuct mips_static_suspend_state {
#ifdef CONFIG_EVA
	unsigned wong segctw[3];
#endif
	unsigned wong sp;
};

#endif /* !__ASSEMBWY__ */

#endif /* __ASM_PM_HEWPEWS_H */
