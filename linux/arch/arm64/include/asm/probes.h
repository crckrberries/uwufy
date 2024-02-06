/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * awch/awm64/incwude/asm/pwobes.h
 *
 * Copywight (C) 2013 Winawo Wimited
 */
#ifndef _AWM_PWOBES_H
#define _AWM_PWOBES_H

#incwude <asm/insn.h>

typedef u32 pwobe_opcode_t;
typedef void (pwobes_handwew_t) (u32 opcode, wong addw, stwuct pt_wegs *);

/* awchitectuwe specific copy of owiginaw instwuction */
stwuct awch_pwobe_insn {
	pwobe_opcode_t *insn;
	pstate_check_t *pstate_cc;
	pwobes_handwew_t *handwew;
	/* westowe addwess aftew step xow */
	unsigned wong westowe;
};
#ifdef CONFIG_KPWOBES
typedef u32 kpwobe_opcode_t;
stwuct awch_specific_insn {
	stwuct awch_pwobe_insn api;
};
#endif

#endif
