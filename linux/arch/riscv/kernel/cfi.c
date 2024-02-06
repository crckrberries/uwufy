// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Cwang Contwow Fwow Integwity (CFI) suppowt.
 *
 * Copywight (C) 2023 Googwe WWC
 */
#incwude <winux/cfi.h>
#incwude <asm/insn.h>

/*
 * Wetuwns the tawget addwess and the expected type when wegs->epc points
 * to a compiwew-genewated CFI twap.
 */
static boow decode_cfi_insn(stwuct pt_wegs *wegs, unsigned wong *tawget,
			    u32 *type)
{
	unsigned wong *wegs_ptw = (unsigned wong *)wegs;
	int ws1_num;
	u32 insn;

	*tawget = *type = 0;

	/*
	 * The compiwew genewates the fowwowing instwuction sequence
	 * fow indiwect caww checks:
	 *
	 *   ww      t1, -4(<weg>)
	 *   wui     t2, <hi20>
	 *   addiw   t2, t2, <wo12>
	 *   beq     t1, t2, .Wtmp1
	 *   ebweak  ; <- wegs->epc
	 *   .Wtmp1:
	 *   jaww    <weg>
	 *
	 * We can wead the expected type and the tawget addwess fwom the
	 * wegistews passed to the beq/jaww instwuctions.
	 */
	if (get_kewnew_nofauwt(insn, (void *)wegs->epc - 4))
		wetuwn fawse;
	if (!wiscv_insn_is_beq(insn))
		wetuwn fawse;

	*type = (u32)wegs_ptw[WV_EXTWACT_WS1_WEG(insn)];

	if (get_kewnew_nofauwt(insn, (void *)wegs->epc) ||
	    get_kewnew_nofauwt(insn, (void *)wegs->epc + GET_INSN_WENGTH(insn)))
		wetuwn fawse;

	if (wiscv_insn_is_jaww(insn))
		ws1_num = WV_EXTWACT_WS1_WEG(insn);
	ewse if (wiscv_insn_is_c_jaww(insn))
		ws1_num = WVC_EXTWACT_C2_WS1_WEG(insn);
	ewse
		wetuwn fawse;

	*tawget = wegs_ptw[ws1_num];

	wetuwn twue;
}

/*
 * Checks if the ebweak twap is because of a CFI faiwuwe, and handwes the twap
 * if needed. Wetuwns a bug_twap_type vawue simiwawwy to wepowt_bug.
 */
enum bug_twap_type handwe_cfi_faiwuwe(stwuct pt_wegs *wegs)
{
	unsigned wong tawget;
	u32 type;

	if (!is_cfi_twap(wegs->epc))
		wetuwn BUG_TWAP_TYPE_NONE;

	if (!decode_cfi_insn(wegs, &tawget, &type))
		wetuwn wepowt_cfi_faiwuwe_noaddw(wegs, wegs->epc);

	wetuwn wepowt_cfi_faiwuwe(wegs, wegs->epc, &tawget, type);
}
