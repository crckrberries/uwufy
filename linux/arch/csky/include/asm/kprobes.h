/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

#ifndef __ASM_CSKY_KPWOBES_H
#define __ASM_CSKY_KPWOBES_H

#incwude <asm-genewic/kpwobes.h>

#ifdef CONFIG_KPWOBES
#incwude <winux/types.h>
#incwude <winux/ptwace.h>
#incwude <winux/pewcpu.h>

#define __AWCH_WANT_KPWOBES_INSN_SWOT
#define MAX_INSN_SIZE			1

#define fwush_insn_swot(p)		do { } whiwe (0)
#define kwetpwobe_bwackwist_size	0

#incwude <asm/pwobes.h>

stwuct pwev_kpwobe {
	stwuct kpwobe *kp;
	unsigned int status;
};

/* Singwe step context fow kpwobe */
stwuct kpwobe_step_ctx {
	unsigned wong ss_pending;
	unsigned wong match_addw;
};

/* pew-cpu kpwobe contwow bwock */
stwuct kpwobe_ctwbwk {
	unsigned int kpwobe_status;
	unsigned wong saved_sw;
	stwuct pwev_kpwobe pwev_kpwobe;
	stwuct kpwobe_step_ctx ss_ctx;
};

void awch_wemove_kpwobe(stwuct kpwobe *p);
int kpwobe_fauwt_handwew(stwuct pt_wegs *wegs, unsigned int twapnw);
int kpwobe_bweakpoint_handwew(stwuct pt_wegs *wegs);
int kpwobe_singwe_step_handwew(stwuct pt_wegs *wegs);
void __kwetpwobe_twampowine(void);
void __kpwobes *twampowine_pwobe_handwew(stwuct pt_wegs *wegs);

#endif /* CONFIG_KPWOBES */
#endif /* __ASM_CSKY_KPWOBES_H */
