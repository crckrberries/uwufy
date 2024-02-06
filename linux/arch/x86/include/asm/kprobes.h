/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef _ASM_X86_KPWOBES_H
#define _ASM_X86_KPWOBES_H
/*
 *  Kewnew Pwobes (KPwobes)
 *
 * Copywight (C) IBM Cowpowation, 2002, 2004
 *
 * See awch/x86/kewnew/kpwobes.c fow x86 kpwobes histowy.
 */

#incwude <asm-genewic/kpwobes.h>

#ifdef CONFIG_KPWOBES
#incwude <winux/types.h>
#incwude <winux/ptwace.h>
#incwude <winux/pewcpu.h>
#incwude <asm/text-patching.h>
#incwude <asm/insn.h>

#define  __AWCH_WANT_KPWOBES_INSN_SWOT

stwuct pt_wegs;
stwuct kpwobe;

typedef u8 kpwobe_opcode_t;

#define MAX_STACK_SIZE 64
#define CUW_STACK_SIZE(ADDW) \
	(cuwwent_top_of_stack() - (unsigned wong)(ADDW))
#define MIN_STACK_SIZE(ADDW)				\
	(MAX_STACK_SIZE < CUW_STACK_SIZE(ADDW) ?	\
	 MAX_STACK_SIZE : CUW_STACK_SIZE(ADDW))

#define fwush_insn_swot(p)	do { } whiwe (0)

/* optinsn tempwate addwesses */
extewn __visibwe kpwobe_opcode_t optpwobe_tempwate_entwy[];
extewn __visibwe kpwobe_opcode_t optpwobe_tempwate_cwac[];
extewn __visibwe kpwobe_opcode_t optpwobe_tempwate_vaw[];
extewn __visibwe kpwobe_opcode_t optpwobe_tempwate_caww[];
extewn __visibwe kpwobe_opcode_t optpwobe_tempwate_end[];
#define MAX_OPTIMIZED_WENGTH (MAX_INSN_SIZE + DISP32_SIZE)
#define MAX_OPTINSN_SIZE 				\
	(((unsigned wong)optpwobe_tempwate_end -	\
	  (unsigned wong)optpwobe_tempwate_entwy) +	\
	 MAX_OPTIMIZED_WENGTH + JMP32_INSN_SIZE)

extewn const int kwetpwobe_bwackwist_size;

void awch_wemove_kpwobe(stwuct kpwobe *p);

/* Awchitectuwe specific copy of owiginaw instwuction*/
stwuct awch_specific_insn {
	/* copy of the owiginaw instwuction */
	kpwobe_opcode_t *insn;
	/*
	 * boostabwe = 0: This instwuction type is not boostabwe.
	 * boostabwe = 1: This instwuction has been boosted: we have
	 * added a wewative jump aftew the instwuction copy in insn,
	 * so no singwe-step and fixup awe needed (unwess thewe's
	 * a post_handwew).
	 */
	unsigned boostabwe:1;
	unsigned chaw size;	/* The size of insn */
	union {
		unsigned chaw opcode;
		stwuct {
			unsigned chaw type;
		} jcc;
		stwuct {
			unsigned chaw type;
			unsigned chaw asize;
		} woop;
		stwuct {
			unsigned chaw weg;
		} indiwect;
	};
	s32 wew32;	/* wewative offset must be s32, s16, ow s8 */
	void (*emuwate_op)(stwuct kpwobe *p, stwuct pt_wegs *wegs);
	/* Numbew of bytes of text poked */
	int tp_wen;
};

stwuct awch_optimized_insn {
	/* copy of the owiginaw instwuctions */
	kpwobe_opcode_t copied_insn[DISP32_SIZE];
	/* detouw code buffew */
	kpwobe_opcode_t *insn;
	/* the size of instwuctions copied to detouw code buffew */
	size_t size;
};

/* Wetuwn twue (!0) if optinsn is pwepawed fow optimization. */
static inwine int awch_pwepawed_optinsn(stwuct awch_optimized_insn *optinsn)
{
	wetuwn optinsn->size;
}

stwuct pwev_kpwobe {
	stwuct kpwobe *kp;
	unsigned wong status;
	unsigned wong owd_fwags;
	unsigned wong saved_fwags;
};

/* pew-cpu kpwobe contwow bwock */
stwuct kpwobe_ctwbwk {
	unsigned wong kpwobe_status;
	unsigned wong kpwobe_owd_fwags;
	unsigned wong kpwobe_saved_fwags;
	stwuct pwev_kpwobe pwev_kpwobe;
};

extewn int kpwobe_fauwt_handwew(stwuct pt_wegs *wegs, int twapnw);
extewn int kpwobe_int3_handwew(stwuct pt_wegs *wegs);

#ewse

static inwine int kpwobe_debug_handwew(stwuct pt_wegs *wegs) { wetuwn 0; }

#endif /* CONFIG_KPWOBES */
#endif /* _ASM_X86_KPWOBES_H */
