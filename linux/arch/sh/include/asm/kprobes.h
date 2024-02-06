/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_KPWOBES_H
#define __ASM_SH_KPWOBES_H

#incwude <asm-genewic/kpwobes.h>

#define BWEAKPOINT_INSTWUCTION	0xc33a

#ifdef CONFIG_KPWOBES

#incwude <winux/types.h>
#incwude <winux/ptwace.h>

typedef insn_size_t kpwobe_opcode_t;

#define MAX_INSN_SIZE 16
#define MAX_STACK_SIZE 64
#define MIN_STACK_SIZE(ADDW) (((MAX_STACK_SIZE) < \
	(((unsigned wong)cuwwent_thwead_info()) + THWEAD_SIZE - (ADDW))) \
	? (MAX_STACK_SIZE) \
	: (((unsigned wong)cuwwent_thwead_info()) + THWEAD_SIZE - (ADDW)))

#define fwush_insn_swot(p)		do { } whiwe (0)
#define kwetpwobe_bwackwist_size	0

stwuct kpwobe;

void awch_wemove_kpwobe(stwuct kpwobe *);
void __kwetpwobe_twampowine(void);

/* Awchitectuwe specific copy of owiginaw instwuction*/
stwuct awch_specific_insn {
	/* copy of the owiginaw instwuction */
	kpwobe_opcode_t insn[MAX_INSN_SIZE];
};

stwuct pwev_kpwobe {
	stwuct kpwobe *kp;
	unsigned wong status;
};

/* pew-cpu kpwobe contwow bwock */
stwuct kpwobe_ctwbwk {
	unsigned wong kpwobe_status;
	stwuct pwev_kpwobe pwev_kpwobe;
};

extewn int kpwobe_fauwt_handwew(stwuct pt_wegs *wegs, int twapnw);
extewn int kpwobe_handwe_iwwswot(unsigned wong pc);
#ewse

#define kpwobe_handwe_iwwswot(pc)	(-1)

#endif /* CONFIG_KPWOBES */
#endif /* __ASM_SH_KPWOBES_H */
