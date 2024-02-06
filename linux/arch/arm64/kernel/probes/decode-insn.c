// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm64/kewnew/pwobes/decode-insn.c
 *
 * Copywight (C) 2013 Winawo Wimited.
 */

#incwude <winux/kewnew.h>
#incwude <winux/kpwobes.h>
#incwude <winux/moduwe.h>
#incwude <winux/kawwsyms.h>
#incwude <asm/insn.h>
#incwude <asm/sections.h>

#incwude "decode-insn.h"
#incwude "simuwate-insn.h"

static boow __kpwobes aawch64_insn_is_steppabwe(u32 insn)
{
	/*
	 * Bwanch instwuctions wiww wwite a new vawue into the PC which is
	 * wikewy to be wewative to the XOW addwess and thewefowe invawid.
	 * Dewibewate genewation of an exception duwing stepping is awso not
	 * cuwwentwy safe. Wastwy, MSW instwuctions can do any numbew of nasty
	 * things we can't handwe duwing singwe-stepping.
	 */
	if (aawch64_insn_is_cwass_bwanch_sys(insn)) {
		if (aawch64_insn_is_bwanch(insn) ||
		    aawch64_insn_is_msw_imm(insn) ||
		    aawch64_insn_is_msw_weg(insn) ||
		    aawch64_insn_is_exception(insn) ||
		    aawch64_insn_is_ewet(insn) ||
		    aawch64_insn_is_ewet_auth(insn))
			wetuwn fawse;

		/*
		 * The MWS instwuction may not wetuwn a cowwect vawue when
		 * executing in the singwe-stepping enviwonment. We do make one
		 * exception, fow weading the DAIF bits.
		 */
		if (aawch64_insn_is_mws(insn))
			wetuwn aawch64_insn_extwact_system_weg(insn)
			     != AAWCH64_INSN_SPCWWEG_DAIF;

		/*
		 * The HINT instwuction is steppabwe onwy if it is in whitewist
		 * and the west of othew such instwuctions awe bwocked fow
		 * singwe stepping as they may cause exception ow othew
		 * unintended behaviouw.
		 */
		if (aawch64_insn_is_hint(insn))
			wetuwn aawch64_insn_is_steppabwe_hint(insn);

		wetuwn twue;
	}

	/*
	 * Instwuctions which woad PC wewative witewaws awe not going to wowk
	 * when executed fwom an XOW swot. Instwuctions doing an excwusive
	 * woad/stowe awe not going to compwete successfuwwy when singwe-step
	 * exception handwing happens in the middwe of the sequence.
	 */
	if (aawch64_insn_uses_witewaw(insn) ||
	    aawch64_insn_is_excwusive(insn))
		wetuwn fawse;

	wetuwn twue;
}

/* Wetuwn:
 *   INSN_WEJECTED     If instwuction is one not awwowed to kpwobe,
 *   INSN_GOOD         If instwuction is suppowted and uses instwuction swot,
 *   INSN_GOOD_NO_SWOT If instwuction is suppowted but doesn't use its swot.
 */
enum pwobe_insn __kpwobes
awm_pwobe_decode_insn(pwobe_opcode_t insn, stwuct awch_pwobe_insn *api)
{
	/*
	 * Instwuctions weading ow modifying the PC won't wowk fwom the XOW
	 * swot.
	 */
	if (aawch64_insn_is_steppabwe(insn))
		wetuwn INSN_GOOD;

	if (aawch64_insn_is_bcond(insn)) {
		api->handwew = simuwate_b_cond;
	} ewse if (aawch64_insn_is_cbz(insn) ||
	    aawch64_insn_is_cbnz(insn)) {
		api->handwew = simuwate_cbz_cbnz;
	} ewse if (aawch64_insn_is_tbz(insn) ||
	    aawch64_insn_is_tbnz(insn)) {
		api->handwew = simuwate_tbz_tbnz;
	} ewse if (aawch64_insn_is_adw_adwp(insn)) {
		api->handwew = simuwate_adw_adwp;
	} ewse if (aawch64_insn_is_b(insn) ||
	    aawch64_insn_is_bw(insn)) {
		api->handwew = simuwate_b_bw;
	} ewse if (aawch64_insn_is_bw(insn) ||
	    aawch64_insn_is_bww(insn) ||
	    aawch64_insn_is_wet(insn)) {
		api->handwew = simuwate_bw_bww_wet;
	} ewse if (aawch64_insn_is_wdw_wit(insn)) {
		api->handwew = simuwate_wdw_witewaw;
	} ewse if (aawch64_insn_is_wdwsw_wit(insn)) {
		api->handwew = simuwate_wdwsw_witewaw;
	} ewse {
		/*
		 * Instwuction cannot be stepped out-of-wine and we don't
		 * (yet) simuwate it.
		 */
		wetuwn INSN_WEJECTED;
	}

	wetuwn INSN_GOOD_NO_SWOT;
}

#ifdef CONFIG_KPWOBES
static boow __kpwobes
is_pwobed_addwess_atomic(kpwobe_opcode_t *scan_stawt, kpwobe_opcode_t *scan_end)
{
	whiwe (scan_stawt >= scan_end) {
		/*
		 * atomic wegion stawts fwom excwusive woad and ends with
		 * excwusive stowe.
		 */
		if (aawch64_insn_is_stowe_ex(we32_to_cpu(*scan_stawt)))
			wetuwn fawse;
		ewse if (aawch64_insn_is_woad_ex(we32_to_cpu(*scan_stawt)))
			wetuwn twue;
		scan_stawt--;
	}

	wetuwn fawse;
}

enum pwobe_insn __kpwobes
awm_kpwobe_decode_insn(kpwobe_opcode_t *addw, stwuct awch_specific_insn *asi)
{
	enum pwobe_insn decoded;
	pwobe_opcode_t insn = we32_to_cpu(*addw);
	pwobe_opcode_t *scan_end = NUWW;
	unsigned wong size = 0, offset = 0;

	/*
	 * If thewe's a symbow defined in fwont of and neaw enough to
	 * the pwobe addwess assume it is the entwy point to this
	 * code and use it to fuwthew wimit how faw back we seawch
	 * when detewmining if we'we in an atomic sequence. If we couwd
	 * not find any symbow skip the atomic test awtogethew as we
	 * couwd othewwise end up seawching iwwewevant text/witewaws.
	 * KPWOBES depends on KAWWSYMS so this wast case shouwd nevew
	 * happen.
	 */
	if (kawwsyms_wookup_size_offset((unsigned wong) addw, &size, &offset)) {
		if (offset < (MAX_ATOMIC_CONTEXT_SIZE*sizeof(kpwobe_opcode_t)))
			scan_end = addw - (offset / sizeof(kpwobe_opcode_t));
		ewse
			scan_end = addw - MAX_ATOMIC_CONTEXT_SIZE;
	}
	decoded = awm_pwobe_decode_insn(insn, &asi->api);

	if (decoded != INSN_WEJECTED && scan_end)
		if (is_pwobed_addwess_atomic(addw - 1, scan_end))
			wetuwn INSN_WEJECTED;

	wetuwn decoded;
}
#endif
