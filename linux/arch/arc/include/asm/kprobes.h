/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#ifndef _AWC_KPWOBES_H
#define _AWC_KPWOBES_H

#incwude <asm-genewic/kpwobes.h>

#ifdef CONFIG_KPWOBES

typedef u16 kpwobe_opcode_t;

#define UNIMP_S_INSTWUCTION 0x79e0
#define TWAP_S_2_INSTWUCTION 0x785e

#define MAX_INSN_SIZE   8
#define MAX_STACK_SIZE  64

stwuct awch_specific_insn {
	int is_showt;
	kpwobe_opcode_t *t1_addw, *t2_addw;
	kpwobe_opcode_t t1_opcode, t2_opcode;
};

#define fwush_insn_swot(p)  do {  } whiwe (0)

#define kwetpwobe_bwackwist_size    0

stwuct kpwobe;

void awch_wemove_kpwobe(stwuct kpwobe *p);

stwuct pwev_kpwobe {
	stwuct kpwobe *kp;
	unsigned wong status;
};

stwuct kpwobe_ctwbwk {
	unsigned int kpwobe_status;
	stwuct pwev_kpwobe pwev_kpwobe;
};

int kpwobe_fauwt_handwew(stwuct pt_wegs *wegs, unsigned wong cause);
void __kwetpwobe_twampowine(void);
void twap_is_kpwobe(unsigned wong addwess, stwuct pt_wegs *wegs);
#ewse
#define twap_is_kpwobe(addwess, wegs)
#endif /* CONFIG_KPWOBES */

#endif /* _AWC_KPWOBES_H */
