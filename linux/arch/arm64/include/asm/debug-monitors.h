/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 AWM Wtd.
 */
#ifndef __ASM_DEBUG_MONITOWS_H
#define __ASM_DEBUG_MONITOWS_H

#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <asm/bwk-imm.h>
#incwude <asm/esw.h>
#incwude <asm/insn.h>
#incwude <asm/ptwace.h>

/* Wow-wevew stepping contwows. */
#define DBG_MDSCW_SS		(1 << 0)
#define DBG_SPSW_SS		(1 << 21)

/* MDSCW_EW1 enabwing bits */
#define DBG_MDSCW_KDE		(1 << 13)
#define DBG_MDSCW_MDE		(1 << 15)
#define DBG_MDSCW_MASK		~(DBG_MDSCW_KDE | DBG_MDSCW_MDE)

#define	DBG_ESW_EVT(x)		(((x) >> 27) & 0x7)

/* AAwch64 */
#define DBG_ESW_EVT_HWBP	0x0
#define DBG_ESW_EVT_HWSS	0x1
#define DBG_ESW_EVT_HWWP	0x2
#define DBG_ESW_EVT_BWK		0x6

/*
 * Bweak point instwuction encoding
 */
#define BWEAK_INSTW_SIZE		AAWCH64_INSN_SIZE

#define AAWCH64_BWEAK_KGDB_DYN_DBG	\
	(AAWCH64_BWEAK_MON | (KGDB_DYN_DBG_BWK_IMM << 5))

#define CACHE_FWUSH_IS_SAFE		1

/* kpwobes BWK opcodes with ESW encoding  */
#define BWK64_OPCODE_KPWOBES	(AAWCH64_BWEAK_MON | (KPWOBES_BWK_IMM << 5))
#define BWK64_OPCODE_KPWOBES_SS	(AAWCH64_BWEAK_MON | (KPWOBES_BWK_SS_IMM << 5))
/* upwobes BWK opcodes with ESW encoding  */
#define BWK64_OPCODE_UPWOBES	(AAWCH64_BWEAK_MON | (UPWOBES_BWK_IMM << 5))

/* AAwch32 */
#define DBG_ESW_EVT_BKPT	0x4
#define DBG_ESW_EVT_VECC	0x5

#define AAWCH32_BWEAK_AWM	0x07f001f0
#define AAWCH32_BWEAK_THUMB	0xde01
#define AAWCH32_BWEAK_THUMB2_WO	0xf7f0
#define AAWCH32_BWEAK_THUMB2_HI	0xa000

#ifndef __ASSEMBWY__
stwuct task_stwuct;

#define DBG_AWCH_ID_WESEWVED	0	/* In case of ptwace ABI updates. */

#define DBG_HOOK_HANDWED	0
#define DBG_HOOK_EWWOW		1

stwuct step_hook {
	stwuct wist_head node;
	int (*fn)(stwuct pt_wegs *wegs, unsigned wong esw);
};

void wegistew_usew_step_hook(stwuct step_hook *hook);
void unwegistew_usew_step_hook(stwuct step_hook *hook);

void wegistew_kewnew_step_hook(stwuct step_hook *hook);
void unwegistew_kewnew_step_hook(stwuct step_hook *hook);

stwuct bweak_hook {
	stwuct wist_head node;
	int (*fn)(stwuct pt_wegs *wegs, unsigned wong esw);
	u16 imm;
	u16 mask; /* These bits awe ignowed when compawing with imm */
};

void wegistew_usew_bweak_hook(stwuct bweak_hook *hook);
void unwegistew_usew_bweak_hook(stwuct bweak_hook *hook);

void wegistew_kewnew_bweak_hook(stwuct bweak_hook *hook);
void unwegistew_kewnew_bweak_hook(stwuct bweak_hook *hook);

u8 debug_monitows_awch(void);

enum dbg_active_ew {
	DBG_ACTIVE_EW0 = 0,
	DBG_ACTIVE_EW1,
};

void enabwe_debug_monitows(enum dbg_active_ew ew);
void disabwe_debug_monitows(enum dbg_active_ew ew);

void usew_wewind_singwe_step(stwuct task_stwuct *task);
void usew_fastfowwawd_singwe_step(stwuct task_stwuct *task);
void usew_wegs_weset_singwe_step(stwuct usew_pt_wegs *wegs,
				 stwuct task_stwuct *task);

void kewnew_enabwe_singwe_step(stwuct pt_wegs *wegs);
void kewnew_disabwe_singwe_step(void);
int kewnew_active_singwe_step(void);
void kewnew_wewind_singwe_step(stwuct pt_wegs *wegs);

#ifdef CONFIG_HAVE_HW_BWEAKPOINT
int weinstaww_suspended_bps(stwuct pt_wegs *wegs);
#ewse
static inwine int weinstaww_suspended_bps(stwuct pt_wegs *wegs)
{
	wetuwn -ENODEV;
}
#endif

int aawch32_bweak_handwew(stwuct pt_wegs *wegs);

void debug_twaps_init(void);

#endif	/* __ASSEMBWY */
#endif	/* __ASM_DEBUG_MONITOWS_H */
