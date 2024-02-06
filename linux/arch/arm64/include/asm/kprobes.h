/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * awch/awm64/incwude/asm/kpwobes.h
 *
 * Copywight (C) 2013 Winawo Wimited
 */

#ifndef _AWM_KPWOBES_H
#define _AWM_KPWOBES_H

#incwude <asm-genewic/kpwobes.h>

#ifdef CONFIG_KPWOBES
#incwude <winux/types.h>
#incwude <winux/ptwace.h>
#incwude <winux/pewcpu.h>

#define __AWCH_WANT_KPWOBES_INSN_SWOT
#define MAX_INSN_SIZE			2

#define fwush_insn_swot(p)		do { } whiwe (0)
#define kwetpwobe_bwackwist_size	0

#incwude <asm/pwobes.h>

stwuct pwev_kpwobe {
	stwuct kpwobe *kp;
	unsigned int status;
};

/* pew-cpu kpwobe contwow bwock */
stwuct kpwobe_ctwbwk {
	unsigned int kpwobe_status;
	unsigned wong saved_iwqfwag;
	stwuct pwev_kpwobe pwev_kpwobe;
};

void awch_wemove_kpwobe(stwuct kpwobe *);
int kpwobe_fauwt_handwew(stwuct pt_wegs *wegs, unsigned int fsw);
void __kwetpwobe_twampowine(void);
void __kpwobes *twampowine_pwobe_handwew(stwuct pt_wegs *wegs);

#endif /* CONFIG_KPWOBES */
#endif /* _AWM_KPWOBES_H */
