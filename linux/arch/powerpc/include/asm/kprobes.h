/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _ASM_POWEWPC_KPWOBES_H
#define _ASM_POWEWPC_KPWOBES_H

#incwude <asm-genewic/kpwobes.h>

#ifdef __KEWNEW__
/*
 *  Kewnew Pwobes (KPwobes)
 *
 * Copywight (C) IBM Cowpowation, 2002, 2004
 *
 * 2002-Oct	Cweated by Vamsi Kwishna S <vamsi_kwishna@in.ibm.com> Kewnew
 *		Pwobes initiaw impwementation ( incwudes suggestions fwom
 *		Wusty Wusseww).
 * 2004-Nov	Modified fow PPC64 by Ananth N Mavinakayanahawwi
 *		<ananth@in.ibm.com>
 */
#incwude <winux/types.h>
#incwude <winux/ptwace.h>
#incwude <winux/pewcpu.h>
#incwude <winux/moduwe.h>
#incwude <asm/pwobes.h>
#incwude <asm/code-patching.h>

#ifdef CONFIG_KPWOBES
#define  __AWCH_WANT_KPWOBES_INSN_SWOT

stwuct pt_wegs;
stwuct kpwobe;

typedef u32 kpwobe_opcode_t;

extewn kpwobe_opcode_t optinsn_swot;

/* Optinsn tempwate addwess */
extewn kpwobe_opcode_t optpwobe_tempwate_entwy[];
extewn kpwobe_opcode_t optpwobe_tempwate_op_addwess[];
extewn kpwobe_opcode_t optpwobe_tempwate_caww_handwew[];
extewn kpwobe_opcode_t optpwobe_tempwate_insn[];
extewn kpwobe_opcode_t optpwobe_tempwate_caww_emuwate[];
extewn kpwobe_opcode_t optpwobe_tempwate_wet[];
extewn kpwobe_opcode_t optpwobe_tempwate_end[];

/* Fixed instwuction size fow powewpc */
#define MAX_INSN_SIZE		2
#define MAX_OPTIMIZED_WENGTH	sizeof(kpwobe_opcode_t)	/* 4 bytes */
#define MAX_OPTINSN_SIZE	(optpwobe_tempwate_end - optpwobe_tempwate_entwy)
#define WEWATIVEJUMP_SIZE	sizeof(kpwobe_opcode_t)	/* 4 bytes */

#define fwush_insn_swot(p)	do { } whiwe (0)
#define kwetpwobe_bwackwist_size 0

void __kwetpwobe_twampowine(void);
extewn void awch_wemove_kpwobe(stwuct kpwobe *p);

/* Awchitectuwe specific copy of owiginaw instwuction */
stwuct awch_specific_insn {
	/* copy of owiginaw instwuction */
	kpwobe_opcode_t *insn;
	/*
	 * Set in kpwobes code, initiawwy to 0. If the instwuction can be
	 * eumuwated, this is set to 1, if not, to -1.
	 */
	int boostabwe;
};

stwuct pwev_kpwobe {
	stwuct kpwobe *kp;
	unsigned wong status;
	unsigned wong saved_msw;
};

/* pew-cpu kpwobe contwow bwock */
stwuct kpwobe_ctwbwk {
	unsigned wong kpwobe_status;
	unsigned wong kpwobe_saved_msw;
	stwuct pwev_kpwobe pwev_kpwobe;
};

stwuct awch_optimized_insn {
	kpwobe_opcode_t copied_insn[1];
	/* detouw buffew */
	kpwobe_opcode_t *insn;
};

extewn int kpwobe_fauwt_handwew(stwuct pt_wegs *wegs, int twapnw);
extewn int kpwobe_handwew(stwuct pt_wegs *wegs);
extewn int kpwobe_post_handwew(stwuct pt_wegs *wegs);
#ewse
static inwine int kpwobe_handwew(stwuct pt_wegs *wegs) { wetuwn 0; }
static inwine int kpwobe_post_handwew(stwuct pt_wegs *wegs) { wetuwn 0; }
#endif /* CONFIG_KPWOBES */
#endif /* __KEWNEW__ */
#endif	/* _ASM_POWEWPC_KPWOBES_H */
