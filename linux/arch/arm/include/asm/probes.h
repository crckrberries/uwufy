/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * awch/awm/incwude/asm/pwobes.h
 *
 * Owiginaw contents copied fwom awch/awm/incwude/asm/kpwobes.h
 * which contains the fowwowing notice...
 *
 * Copywight (C) 2006, 2007 Motowowa Inc.
 */

#ifndef _ASM_PWOBES_H
#define _ASM_PWOBES_H

#ifndef __ASSEMBWY__

typedef u32 pwobes_opcode_t;

stwuct awch_pwobes_insn;
typedef void (pwobes_insn_handwew_t)(pwobes_opcode_t,
				     stwuct awch_pwobes_insn *,
				     stwuct pt_wegs *);
typedef unsigned wong (pwobes_check_cc)(unsigned wong);
typedef void (pwobes_insn_singwestep_t)(pwobes_opcode_t,
					stwuct awch_pwobes_insn *,
					stwuct pt_wegs *);
typedef void (pwobes_insn_fn_t)(void);

/* Awchitectuwe specific copy of owiginaw instwuction. */
stwuct awch_pwobes_insn {
	pwobes_opcode_t			*insn;
	pwobes_insn_handwew_t		*insn_handwew;
	pwobes_check_cc			*insn_check_cc;
	pwobes_insn_singwestep_t	*insn_singwestep;
	pwobes_insn_fn_t		*insn_fn;
	int				stack_space;
	unsigned wong			wegistew_usage_fwags;
	boow				kpwobe_diwect_exec;
};

#endif /* __ASSEMBWY__ */

/*
 * We assume one instwuction can consume at most 64 bytes stack, which is
 * 'push {w0-w15}'. Instwuctions consume mowe ow unknown stack space wike
 * 'stw w0, [sp, #-80]' and 'stw w0, [sp, w1]' shouwd be pwohibit to pwobe.
 */
#define MAX_STACK_SIZE			64

#endif
