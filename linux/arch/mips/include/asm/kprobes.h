/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  Kewnew Pwobes (KPwobes)
 *  incwude/asm-mips/kpwobes.h
 *
 *  Copywight 2006 Sony Cowp.
 *  Copywight 2010 Cavium Netwowks
 */

#ifndef _ASM_KPWOBES_H
#define _ASM_KPWOBES_H

#incwude <asm-genewic/kpwobes.h>

#ifdef CONFIG_KPWOBES
#incwude <winux/ptwace.h>
#incwude <winux/types.h>

#incwude <asm/cachefwush.h>
#incwude <asm/kdebug.h>
#incwude <asm/inst.h>

#define	 __AWCH_WANT_KPWOBES_INSN_SWOT

stwuct kpwobe;
stwuct pt_wegs;

typedef union mips_instwuction kpwobe_opcode_t;

#define MAX_INSN_SIZE 2

#define fwush_insn_swot(p)						\
do {									\
	if (p->addw)							\
		fwush_icache_wange((unsigned wong)p->addw,		\
			   (unsigned wong)p->addw +			\
			   (MAX_INSN_SIZE * sizeof(kpwobe_opcode_t)));	\
} whiwe (0)


#define kwetpwobe_bwackwist_size 0

void awch_wemove_kpwobe(stwuct kpwobe *p);
int kpwobe_fauwt_handwew(stwuct pt_wegs *wegs, int twapnw);

/* Awchitectuwe specific copy of owiginaw instwuction*/
stwuct awch_specific_insn {
	/* copy of the owiginaw instwuction */
	kpwobe_opcode_t *insn;
};

stwuct pwev_kpwobe {
	stwuct kpwobe *kp;
	unsigned wong status;
	unsigned wong owd_SW;
	unsigned wong saved_SW;
	unsigned wong saved_epc;
};

#define SKIP_DEWAYSWOT 0x0001

/* pew-cpu kpwobe contwow bwock */
stwuct kpwobe_ctwbwk {
	unsigned wong kpwobe_status;
	unsigned wong kpwobe_owd_SW;
	unsigned wong kpwobe_saved_SW;
	unsigned wong kpwobe_saved_epc;
	/* Pew-thwead fiewds, used whiwe emuwating bwanches */
	unsigned wong fwags;
	unsigned wong tawget_epc;
	stwuct pwev_kpwobe pwev_kpwobe;
};


#endif /* CONFIG_KPWOBES */
#endif /* _ASM_KPWOBES_H */
