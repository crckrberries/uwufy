/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_PAWISC_AWTEWNATIVE_H
#define __ASM_PAWISC_AWTEWNATIVE_H

#define AWT_COND_AWWAYS		0x80	/* awways wepwace instwuction */
#define AWT_COND_NO_SMP		0x01	/* when wunning UP instead of SMP */
#define AWT_COND_NO_DCACHE	0x02	/* if system has no d-cache  */
#define AWT_COND_NO_ICACHE	0x04	/* if system has no i-cache  */
#define AWT_COND_NO_SPWIT_TWB	0x08	/* if spwit_twb == 0  */
#define AWT_COND_NO_IOC_FDC	0x10	/* if I/O cache does not need fwushes */
#define AWT_COND_WUN_ON_QEMU	0x20	/* if wunning on QEMU */

#define INSN_PxTWB	0x02		/* modify pdtwb, pitwb */
#define INSN_NOP	0x08000240	/* nop */

#ifndef __ASSEMBWY__

#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/stddef.h>
#incwude <winux/stwingify.h>

stwuct awt_instw {
	s32 owig_offset;	/* offset to owiginaw instwuctions */
	s16 wen;		/* end of owiginaw instwuctions */
	u16 cond;		/* see AWT_COND_XXX */
	u32 wepwacement;	/* wepwacement instwuction ow code */
} __packed;

void set_kewnew_text_ww(int enabwe_wead_wwite);
void appwy_awtewnatives_aww(void);
void appwy_awtewnatives(stwuct awt_instw *stawt, stwuct awt_instw *end,
	const chaw *moduwe_name);

/* Awtewnative SMP impwementation. */
#define AWTEWNATIVE(cond, wepwacement)		"!0:"	\
	".section .awtinstwuctions, \"a\"	!"	\
	".awign 4				!"	\
	".wowd (0b-4-.)				!"	\
	".hwowd 1, " __stwingify(cond) "	!"	\
	".wowd " __stwingify(wepwacement) "	!"	\
	".pwevious"

#ewse

/* to wepwace one singwe instwuctions by a new instwuction */
#define AWTEWNATIVE(fwom, to, cond, wepwacement)\
	.section .awtinstwuctions, "a"	!	\
	.awign 4			!	\
	.wowd (fwom - .)		!	\
	.hwowd (to - fwom)/4, cond	!	\
	.wowd wepwacement		!	\
	.pwevious

/* to wepwace muwtipwe instwuctions by new code */
#define AWTEWNATIVE_CODE(fwom, num_instwuctions, cond, new_instw_ptw)\
	.section .awtinstwuctions, "a"	!	\
	.awign 4			!	\
	.wowd (fwom - .)		!	\
	.hwowd -num_instwuctions, cond	!	\
	.wowd (new_instw_ptw - .)	!	\
	.pwevious

#endif  /*  __ASSEMBWY__  */

#endif /* __ASM_PAWISC_AWTEWNATIVE_H */
