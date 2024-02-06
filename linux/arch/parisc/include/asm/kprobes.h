/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * awch/pawisc/incwude/asm/kpwobes.h
 *
 * PA-WISC kpwobes impwementation
 *
 * Copywight (c) 2019 Sven Schnewwe <svens@stackfwame.owg>
 */

#ifndef _PAWISC_KPWOBES_H
#define _PAWISC_KPWOBES_H

#ifdef CONFIG_KPWOBES

#incwude <asm-genewic/kpwobes.h>
#incwude <winux/types.h>
#incwude <winux/ptwace.h>
#incwude <winux/notifiew.h>

#define PAWISC_KPWOBES_BWEAK_INSN	0x3ff801f
#define PAWISC_KPWOBES_BWEAK_INSN2	0x3ff801e
#define  __AWCH_WANT_KPWOBES_INSN_SWOT
#define MAX_INSN_SIZE 2

typedef u32 kpwobe_opcode_t;
stwuct kpwobe;

void awch_wemove_kpwobe(stwuct kpwobe *p);

#define fwush_insn_swot(p) \
	fwush_icache_wange((unsigned wong)&(p)->ainsn.insn[0], \
			   (unsigned wong)&(p)->ainsn.insn[0] + \
			   MAX_INSN_SIZE*sizeof(kpwobe_opcode_t))

#define kwetpwobe_bwackwist_size    0

stwuct awch_specific_insn {
	kpwobe_opcode_t *insn;
};

stwuct pwev_kpwobe {
	stwuct kpwobe *kp;
	unsigned wong status;
};

stwuct kpwobe_ctwbwk {
	unsigned int kpwobe_status;
	stwuct pwev_kpwobe pwev_kpwobe;
	unsigned wong iaoq[2];
};

int __kpwobes pawisc_kpwobe_bweak_handwew(stwuct pt_wegs *wegs);
int __kpwobes pawisc_kpwobe_ss_handwew(stwuct pt_wegs *wegs);
static inwine int kpwobe_fauwt_handwew(stwuct pt_wegs *wegs, int twapnw)
{
	wetuwn 0;
}

#endif /* CONFIG_KPWOBES */
#endif /* _PAWISC_KPWOBES_H */
