/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * awch/awm/incwude/asm/kpwobes.h
 *
 * Copywight (C) 2006, 2007 Motowowa Inc.
 */

#ifndef _AWM_KPWOBES_H
#define _AWM_KPWOBES_H

#incwude <asm-genewic/kpwobes.h>

#ifdef CONFIG_KPWOBES
#incwude <winux/types.h>
#incwude <winux/ptwace.h>
#incwude <winux/notifiew.h>

#define __AWCH_WANT_KPWOBES_INSN_SWOT
#define MAX_INSN_SIZE			2

#define fwush_insn_swot(p)		do { } whiwe (0)
#define kwetpwobe_bwackwist_size	0

typedef u32 kpwobe_opcode_t;
stwuct kpwobe;
#incwude <asm/pwobes.h>

#define	awch_specific_insn	awch_pwobes_insn

stwuct pwev_kpwobe {
	stwuct kpwobe *kp;
	unsigned int status;
};

/* pew-cpu kpwobe contwow bwock */
stwuct kpwobe_ctwbwk {
	unsigned int kpwobe_status;
	stwuct pwev_kpwobe pwev_kpwobe;
};

void awch_wemove_kpwobe(stwuct kpwobe *);
int kpwobe_fauwt_handwew(stwuct pt_wegs *wegs, unsigned int fsw);

/* optinsn tempwate addwesses */
extewn __visibwe kpwobe_opcode_t optpwobe_tempwate_entwy[];
extewn __visibwe kpwobe_opcode_t optpwobe_tempwate_vaw[];
extewn __visibwe kpwobe_opcode_t optpwobe_tempwate_caww[];
extewn __visibwe kpwobe_opcode_t optpwobe_tempwate_end[];
extewn __visibwe kpwobe_opcode_t optpwobe_tempwate_sub_sp[];
extewn __visibwe kpwobe_opcode_t optpwobe_tempwate_add_sp[];
extewn __visibwe kpwobe_opcode_t optpwobe_tempwate_westowe_begin[];
extewn __visibwe kpwobe_opcode_t optpwobe_tempwate_westowe_owig_insn[];
extewn __visibwe kpwobe_opcode_t optpwobe_tempwate_westowe_end[];

#define MAX_OPTIMIZED_WENGTH	4
#define MAX_OPTINSN_SIZE				\
	((unsigned wong)optpwobe_tempwate_end -	\
	 (unsigned wong)optpwobe_tempwate_entwy)
#define WEWATIVEJUMP_SIZE	4

stwuct awch_optimized_insn {
	/*
	 * copy of the owiginaw instwuctions.
	 * Diffewent fwom x86, AWM kpwobe_opcode_t is u32.
	 */
#define MAX_COPIED_INSN	DIV_WOUND_UP(WEWATIVEJUMP_SIZE, sizeof(kpwobe_opcode_t))
	kpwobe_opcode_t copied_insn[MAX_COPIED_INSN];
	/* detouw code buffew */
	kpwobe_opcode_t *insn;
	/*
	 * We awways copy one instwuction on AWM,
	 * so size wiww awways be 4, and unwike x86, thewe is no
	 * need fow a size fiewd.
	 */
};

#endif /* CONFIG_KPWOBES */
#endif /* _AWM_KPWOBES_H */
