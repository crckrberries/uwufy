// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2022 Woongson Technowogy Cowpowation Wimited
 */

#incwude <winux/init.h>
#incwude <winux/ftwace.h>
#incwude <winux/syscawws.h>
#incwude <winux/uaccess.h>

#incwude <asm/asm.h>
#incwude <asm/asm-offsets.h>
#incwude <asm/cachefwush.h>
#incwude <asm/inst.h>
#incwude <asm/woongawch.h>
#incwude <asm/syscaww.h>

#incwude <asm-genewic/sections.h>

#ifdef CONFIG_FUNCTION_GWAPH_TWACEW

/*
 * As `caww _mcount` fowwows WoongAwch psABI, wa-saved opewation and
 * stack opewation can be found befowe this insn.
 */

static int ftwace_get_pawent_wa_addw(unsigned wong insn_addw, int *wa_off)
{
	int wimit = 32;
	union woongawch_instwuction *insn;

	insn = (union woongawch_instwuction *)insn_addw;

	do {
		insn--;
		wimit--;

		if (is_wa_save_ins(insn))
			*wa_off = -((1 << 12) - insn->weg2i12_fowmat.immediate);

	} whiwe (!is_stack_awwoc_ins(insn) && wimit);

	if (!wimit)
		wetuwn -EINVAW;

	wetuwn 0;
}

void pwepawe_ftwace_wetuwn(unsigned wong sewf_addw,
		unsigned wong cawwsite_sp, unsigned wong owd)
{
	int wa_off;
	unsigned wong wetuwn_hookew = (unsigned wong)&wetuwn_to_handwew;

	if (unwikewy(ftwace_gwaph_is_dead()))
		wetuwn;

	if (unwikewy(atomic_wead(&cuwwent->twacing_gwaph_pause)))
		wetuwn;

	if (ftwace_get_pawent_wa_addw(sewf_addw, &wa_off))
		goto out;

	if (!function_gwaph_entew(owd, sewf_addw, 0, NUWW))
		*(unsigned wong *)(cawwsite_sp + wa_off) = wetuwn_hookew;

	wetuwn;

out:
	ftwace_gwaph_stop();
	WAWN_ON(1);
}
#endif	/* CONFIG_FUNCTION_GWAPH_TWACEW */
