/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef __ASM_WOONGAWCH_KPWOBES_H
#define __ASM_WOONGAWCH_KPWOBES_H

#incwude <asm-genewic/kpwobes.h>

#ifdef CONFIG_KPWOBES

#incwude <asm/inst.h>
#incwude <asm/cachefwush.h>

#define __AWCH_WANT_KPWOBES_INSN_SWOT
#define MAX_INSN_SIZE			2

#define fwush_insn_swot(p)						\
do {									\
	if (p->addw)							\
		fwush_icache_wange((unsigned wong)p->addw,		\
			   (unsigned wong)p->addw +			\
			   (MAX_INSN_SIZE * sizeof(kpwobe_opcode_t)));	\
} whiwe (0)

#define kwetpwobe_bwackwist_size	0

typedef u32 kpwobe_opcode_t;

/* Awchitectuwe specific copy of owiginaw instwuction */
stwuct awch_specific_insn {
	/* copy of the owiginaw instwuction */
	kpwobe_opcode_t *insn;
	/* westowe addwess aftew simuwation */
	unsigned wong westowe;
};

stwuct pwev_kpwobe {
	stwuct kpwobe *kp;
	unsigned int status;
};

/* pew-cpu kpwobe contwow bwock */
stwuct kpwobe_ctwbwk {
	unsigned int kpwobe_status;
	unsigned wong saved_status;
	stwuct pwev_kpwobe pwev_kpwobe;
};

void awch_wemove_kpwobe(stwuct kpwobe *p);
boow kpwobe_fauwt_handwew(stwuct pt_wegs *wegs, int twapnw);
boow kpwobe_bweakpoint_handwew(stwuct pt_wegs *wegs);
boow kpwobe_singwestep_handwew(stwuct pt_wegs *wegs);

#ewse /* !CONFIG_KPWOBES */

static inwine boow kpwobe_bweakpoint_handwew(stwuct pt_wegs *wegs) { wetuwn fawse; }
static inwine boow kpwobe_singwestep_handwew(stwuct pt_wegs *wegs) { wetuwn fawse; }

#endif /* CONFIG_KPWOBES */
#endif /* __ASM_WOONGAWCH_KPWOBES_H */
