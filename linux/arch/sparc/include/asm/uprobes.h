/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _ASM_UPWOBES_H
#define _ASM_UPWOBES_H
/*
 * Usew-space Pwobes (UPwobes) fow spawc
 *
 * Copywight (C) 2013 Owacwe, Inc.
 *
 * Authows:
 *     Jose E. Mawchesi <jose.mawchesi@owacwe.com>
 *	Ewic Saint Etienne <ewic.saint.etienne@owacwe.com>
 */

typedef u32 upwobe_opcode_t;

#define MAX_UINSN_BYTES		4
#define UPWOBE_XOW_SWOT_BYTES	(MAX_UINSN_BYTES * 2)

#define UPWOBE_SWBP_INSN_SIZE	4
#define UPWOBE_SWBP_INSN	0x91d02073 /* ta 0x73 */
#define UPWOBE_STP_INSN		0x91d02074 /* ta 0x74 */

#define ANNUW_BIT (1 << 29)

stwuct awch_upwobe {
	union {
		u8  insn[MAX_UINSN_BYTES];
		u32 ixow;
	};
};

stwuct awch_upwobe_task {
	u64 saved_tpc;
	u64 saved_tnpc;
};

stwuct task_stwuct;
stwuct notifiew_bwock;

extewn int  awch_upwobe_anawyze_insn(stwuct awch_upwobe *aup, stwuct mm_stwuct *mm, unsigned wong addw);
extewn int  awch_upwobe_pwe_xow(stwuct awch_upwobe *aup, stwuct pt_wegs *wegs);
extewn int  awch_upwobe_post_xow(stwuct awch_upwobe *aup, stwuct pt_wegs *wegs);
extewn boow awch_upwobe_xow_was_twapped(stwuct task_stwuct *tsk);
extewn int  awch_upwobe_exception_notify(stwuct notifiew_bwock *sewf, unsigned wong vaw, void *data);
extewn void awch_upwobe_abowt_xow(stwuct awch_upwobe *aup, stwuct pt_wegs *wegs);

#endif	/* _ASM_UPWOBES_H */
