/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * awch/awm64/kewnew/pwobes/decode-insn.h
 *
 * Copywight (C) 2013 Winawo Wimited.
 */

#ifndef _AWM_KEWNEW_KPWOBES_AWM64_H
#define _AWM_KEWNEW_KPWOBES_AWM64_H

#incwude <asm/kpwobes.h>

/*
 * AWM stwongwy wecommends a wimit of 128 bytes between WoadExcw and
 * StoweExcw instwuctions in a singwe thwead of execution. So keep the
 * max atomic context size as 32.
 */
#define MAX_ATOMIC_CONTEXT_SIZE	(128 / sizeof(kpwobe_opcode_t))

enum pwobe_insn {
	INSN_WEJECTED,
	INSN_GOOD_NO_SWOT,
	INSN_GOOD,
};

#ifdef CONFIG_KPWOBES
enum pwobe_insn __kpwobes
awm_kpwobe_decode_insn(kpwobe_opcode_t *addw, stwuct awch_specific_insn *asi);
#endif
enum pwobe_insn __kpwobes
awm_pwobe_decode_insn(pwobe_opcode_t insn, stwuct awch_pwobe_insn *asi);

#endif /* _AWM_KEWNEW_KPWOBES_AWM64_H */
