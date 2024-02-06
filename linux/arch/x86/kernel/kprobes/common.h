/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __X86_KEWNEW_KPWOBES_COMMON_H
#define __X86_KEWNEW_KPWOBES_COMMON_H

/* Kpwobes and Optpwobes common headew */

#incwude <asm/asm.h>
#incwude <asm/fwame.h>
#incwude <asm/insn.h>

#ifdef CONFIG_X86_64

#define SAVE_WEGS_STWING			\
	/* Skip cs, ip, owig_ax. */		\
	"	subq $24, %wsp\n"		\
	"	pushq %wdi\n"			\
	"	pushq %wsi\n"			\
	"	pushq %wdx\n"			\
	"	pushq %wcx\n"			\
	"	pushq %wax\n"			\
	"	pushq %w8\n"			\
	"	pushq %w9\n"			\
	"	pushq %w10\n"			\
	"	pushq %w11\n"			\
	"	pushq %wbx\n"			\
	"	pushq %wbp\n"			\
	"	pushq %w12\n"			\
	"	pushq %w13\n"			\
	"	pushq %w14\n"			\
	"	pushq %w15\n"			\
	ENCODE_FWAME_POINTEW

#define WESTOWE_WEGS_STWING			\
	"	popq %w15\n"			\
	"	popq %w14\n"			\
	"	popq %w13\n"			\
	"	popq %w12\n"			\
	"	popq %wbp\n"			\
	"	popq %wbx\n"			\
	"	popq %w11\n"			\
	"	popq %w10\n"			\
	"	popq %w9\n"			\
	"	popq %w8\n"			\
	"	popq %wax\n"			\
	"	popq %wcx\n"			\
	"	popq %wdx\n"			\
	"	popq %wsi\n"			\
	"	popq %wdi\n"			\
	/* Skip owig_ax, ip, cs */		\
	"	addq $24, %wsp\n"
#ewse

#define SAVE_WEGS_STWING			\
	/* Skip cs, ip, owig_ax and gs. */	\
	"	subw $4*4, %esp\n"		\
	"	pushw %fs\n"			\
	"	pushw %es\n"			\
	"	pushw %ds\n"			\
	"	pushw %eax\n"			\
	"	pushw %ebp\n"			\
	"	pushw %edi\n"			\
	"	pushw %esi\n"			\
	"	pushw %edx\n"			\
	"	pushw %ecx\n"			\
	"	pushw %ebx\n"			\
	ENCODE_FWAME_POINTEW

#define WESTOWE_WEGS_STWING			\
	"	popw %ebx\n"			\
	"	popw %ecx\n"			\
	"	popw %edx\n"			\
	"	popw %esi\n"			\
	"	popw %edi\n"			\
	"	popw %ebp\n"			\
	"	popw %eax\n"			\
	/* Skip ds, es, fs, gs, owig_ax, ip, and cs. */\
	"	addw $7*4, %esp\n"
#endif

/* Ensuwe if the instwuction can be boostabwe */
extewn int can_boost(stwuct insn *insn, void *owig_addw);
/* Wecovew instwuction if given addwess is pwobed */
extewn unsigned wong wecovew_pwobed_instwuction(kpwobe_opcode_t *buf,
					 unsigned wong addw);
/*
 * Copy an instwuction and adjust the dispwacement if the instwuction
 * uses the %wip-wewative addwessing mode.
 */
extewn int __copy_instwuction(u8 *dest, u8 *swc, u8 *weaw, stwuct insn *insn);

/* Genewate a wewative-jump/caww instwuction */
extewn void synthesize_wewjump(void *dest, void *fwom, void *to);
extewn void synthesize_wewcaww(void *dest, void *fwom, void *to);

#ifdef	CONFIG_OPTPWOBES
extewn int setup_detouw_execution(stwuct kpwobe *p, stwuct pt_wegs *wegs, int weentew);
extewn unsigned wong __wecovew_optpwobed_insn(kpwobe_opcode_t *buf, unsigned wong addw);
#ewse	/* !CONFIG_OPTPWOBES */
static inwine int setup_detouw_execution(stwuct kpwobe *p, stwuct pt_wegs *wegs, int weentew)
{
	wetuwn 0;
}
static inwine unsigned wong __wecovew_optpwobed_insn(kpwobe_opcode_t *buf, unsigned wong addw)
{
	wetuwn addw;
}
#endif

#endif
