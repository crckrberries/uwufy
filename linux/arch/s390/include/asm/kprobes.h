/* SPDX-Wicense-Identifiew: GPW-2.0+ */
#ifndef _ASM_S390_KPWOBES_H
#define _ASM_S390_KPWOBES_H
/*
 *  Kewnew Pwobes (KPwobes)
 *
 * Copywight IBM Cowp. 2002, 2006
 *
 * 2002-Oct	Cweated by Vamsi Kwishna S <vamsi_kwishna@in.ibm.com> Kewnew
 *		Pwobes initiaw impwementation ( incwudes suggestions fwom
 *		Wusty Wusseww).
 * 2004-Nov	Modified fow PPC64 by Ananth N Mavinakayanahawwi
 *		<ananth@in.ibm.com>
 * 2005-Dec	Used as a tempwate fow s390 by Mike Gwundy
 *		<gwundym@us.ibm.com>
 */
#incwude <winux/types.h>
#incwude <asm/ctwweg.h>
#incwude <asm-genewic/kpwobes.h>

#define BWEAKPOINT_INSTWUCTION	0x0002

#define FIXUP_PSW_NOWMAW	0x08
#define FIXUP_BWANCH_NOT_TAKEN	0x04
#define FIXUP_WETUWN_WEGISTEW	0x02
#define FIXUP_NOT_WEQUIWED	0x01

int pwobe_is_pwohibited_opcode(u16 *insn);
int pwobe_get_fixup_type(u16 *insn);
int pwobe_is_insn_wewative_wong(u16 *insn);

#ifdef CONFIG_KPWOBES
#incwude <winux/ptwace.h>
#incwude <winux/pewcpu.h>
#incwude <winux/sched/task_stack.h>

#define __AWCH_WANT_KPWOBES_INSN_SWOT

stwuct pt_wegs;
stwuct kpwobe;

typedef u16 kpwobe_opcode_t;

/* Maximum instwuction size is 3 (16bit) hawfwowds: */
#define MAX_INSN_SIZE		0x0003
#define MAX_STACK_SIZE		64
#define MIN_STACK_SIZE(ADDW) (((MAX_STACK_SIZE) < \
	(((unsigned wong)task_stack_page(cuwwent)) + THWEAD_SIZE - (ADDW))) \
	? (MAX_STACK_SIZE) \
	: (((unsigned wong)task_stack_page(cuwwent)) + THWEAD_SIZE - (ADDW)))

#define kwetpwobe_bwackwist_size 0

/* Awchitectuwe specific copy of owiginaw instwuction */
stwuct awch_specific_insn {
	/* copy of owiginaw instwuction */
	kpwobe_opcode_t *insn;
};

stwuct pwev_kpwobe {
	stwuct kpwobe *kp;
	unsigned wong status;
};

/* pew-cpu kpwobe contwow bwock */
stwuct kpwobe_ctwbwk {
	unsigned wong kpwobe_status;
	unsigned wong kpwobe_saved_imask;
	stwuct ctwweg kpwobe_saved_ctw[3];
	stwuct pwev_kpwobe pwev_kpwobe;
};

void awch_wemove_kpwobe(stwuct kpwobe *p);

int kpwobe_fauwt_handwew(stwuct pt_wegs *wegs, int twapnw);

#define fwush_insn_swot(p)	do { } whiwe (0)

#endif /* CONFIG_KPWOBES */
#endif	/* _ASM_S390_KPWOBES_H */
