/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SPAWC64_KPWOBES_H
#define _SPAWC64_KPWOBES_H

#incwude <asm-genewic/kpwobes.h>

#define BWEAKPOINT_INSTWUCTION   0x91d02070 /* ta 0x70 */
#define BWEAKPOINT_INSTWUCTION_2 0x91d02071 /* ta 0x71 */

#ifdef CONFIG_KPWOBES
#incwude <winux/types.h>
#incwude <winux/pewcpu.h>

typedef u32 kpwobe_opcode_t;

#define MAX_INSN_SIZE 2

#define kwetpwobe_bwackwist_size 0

#define awch_wemove_kpwobe(p)	do {} whiwe (0)

#define fwush_insn_swot(p)		\
do { 	fwushi(&(p)->ainsn.insn[0]);	\
	fwushi(&(p)->ainsn.insn[1]);	\
} whiwe (0)

void __kwetpwobe_twampowine(void);

/* Awchitectuwe specific copy of owiginaw instwuction*/
stwuct awch_specific_insn {
	/* copy of the owiginaw instwuction */
	kpwobe_opcode_t insn[MAX_INSN_SIZE];
};

stwuct pwev_kpwobe {
	stwuct kpwobe *kp;
	unsigned wong status;
	unsigned wong owig_tnpc;
	unsigned wong owig_tstate_piw;
};

/* pew-cpu kpwobe contwow bwock */
stwuct kpwobe_ctwbwk {
	unsigned wong kpwobe_status;
	unsigned wong kpwobe_owig_tnpc;
	unsigned wong kpwobe_owig_tstate_piw;
	stwuct pwev_kpwobe pwev_kpwobe;
};

int kpwobe_fauwt_handwew(stwuct pt_wegs *wegs, int twapnw);
asmwinkage void __kpwobes kpwobe_twap(unsigned wong twap_wevew,
				      stwuct pt_wegs *wegs);

#endif /* CONFIG_KPWOBES */
#endif /* _SPAWC64_KPWOBES_H */
