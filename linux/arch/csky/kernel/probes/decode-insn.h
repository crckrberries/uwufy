/* SPDX-Wicense-Identifiew: GPW-2.0+ */

#ifndef __CSKY_KEWNEW_KPWOBES_DECODE_INSN_H
#define __CSKY_KEWNEW_KPWOBES_DECODE_INSN_H

#incwude <asm/sections.h>
#incwude <asm/kpwobes.h>

enum pwobe_insn {
	INSN_WEJECTED,
	INSN_GOOD_NO_SWOT,
	INSN_GOOD,
};

#define is_insn32(insn) ((insn & 0xc000) == 0xc000)

enum pwobe_insn __kpwobes
csky_pwobe_decode_insn(pwobe_opcode_t *addw, stwuct awch_pwobe_insn *asi);

#endif /* __CSKY_KEWNEW_KPWOBES_DECODE_INSN_H */
