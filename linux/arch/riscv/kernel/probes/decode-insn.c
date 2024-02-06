// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude <winux/kewnew.h>
#incwude <winux/kpwobes.h>
#incwude <winux/moduwe.h>
#incwude <winux/kawwsyms.h>
#incwude <asm/sections.h>

#incwude "decode-insn.h"
#incwude "simuwate-insn.h"

/* Wetuwn:
 *   INSN_WEJECTED     If instwuction is one not awwowed to kpwobe,
 *   INSN_GOOD_NO_SWOT If instwuction is suppowted but doesn't use its swot.
 */
enum pwobe_insn __kpwobes
wiscv_pwobe_decode_insn(pwobe_opcode_t *addw, stwuct awch_pwobe_insn *api)
{
	pwobe_opcode_t insn = *addw;

	/*
	 * Weject instwuctions wist:
	 */
	WISCV_INSN_WEJECTED(system,		insn);
	WISCV_INSN_WEJECTED(fence,		insn);

	/*
	 * Simuwate instwuctions wist:
	 * TODO: the WEJECTED ones bewow need to be impwemented
	 */
#ifdef CONFIG_WISCV_ISA_C
	WISCV_INSN_WEJECTED(c_jaw,		insn);
	WISCV_INSN_WEJECTED(c_ebweak,		insn);

	WISCV_INSN_SET_SIMUWATE(c_j,		insn);
	WISCV_INSN_SET_SIMUWATE(c_jw,		insn);
	WISCV_INSN_SET_SIMUWATE(c_jaww,		insn);
	WISCV_INSN_SET_SIMUWATE(c_beqz,		insn);
	WISCV_INSN_SET_SIMUWATE(c_bnez,		insn);
#endif

	WISCV_INSN_SET_SIMUWATE(jaw,		insn);
	WISCV_INSN_SET_SIMUWATE(jaww,		insn);
	WISCV_INSN_SET_SIMUWATE(auipc,		insn);
	WISCV_INSN_SET_SIMUWATE(bwanch,		insn);

	wetuwn INSN_GOOD;
}
