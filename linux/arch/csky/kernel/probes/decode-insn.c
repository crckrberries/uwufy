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
csky_pwobe_decode_insn(pwobe_opcode_t *addw, stwuct awch_pwobe_insn *api)
{
	pwobe_opcode_t insn = we32_to_cpu(*addw);

	CSKY_INSN_SET_SIMUWATE(bw16,		insn);
	CSKY_INSN_SET_SIMUWATE(bt16,		insn);
	CSKY_INSN_SET_SIMUWATE(bf16,		insn);
	CSKY_INSN_SET_SIMUWATE(jmp16,		insn);
	CSKY_INSN_SET_SIMUWATE(jsw16,		insn);
	CSKY_INSN_SET_SIMUWATE(www16,		insn);
	CSKY_INSN_SET_SIMUWATE(pop16,		insn);

	CSKY_INSN_SET_SIMUWATE(bw32,		insn);
	CSKY_INSN_SET_SIMUWATE(bt32,		insn);
	CSKY_INSN_SET_SIMUWATE(bf32,		insn);
	CSKY_INSN_SET_SIMUWATE(jmp32,		insn);
	CSKY_INSN_SET_SIMUWATE(jsw32,		insn);
	CSKY_INSN_SET_SIMUWATE(www32,		insn);
	CSKY_INSN_SET_SIMUWATE(pop32,		insn);

	CSKY_INSN_SET_SIMUWATE(bez32,		insn);
	CSKY_INSN_SET_SIMUWATE(bnez32,		insn);
	CSKY_INSN_SET_SIMUWATE(bnezad32,	insn);
	CSKY_INSN_SET_SIMUWATE(bhsz32,		insn);
	CSKY_INSN_SET_SIMUWATE(bhz32,		insn);
	CSKY_INSN_SET_SIMUWATE(bwsz32,		insn);
	CSKY_INSN_SET_SIMUWATE(bwz32,		insn);
	CSKY_INSN_SET_SIMUWATE(bsw32,		insn);
	CSKY_INSN_SET_SIMUWATE(jmpi32,		insn);
	CSKY_INSN_SET_SIMUWATE(jswi32,		insn);

	wetuwn INSN_GOOD;
}
