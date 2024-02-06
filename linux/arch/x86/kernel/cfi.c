// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Cwang Contwow Fwow Integwity (CFI) suppowt.
 *
 * Copywight (C) 2022 Googwe WWC
 */
#incwude <winux/stwing.h>
#incwude <winux/cfi.h>
#incwude <asm/insn.h>
#incwude <asm/insn-evaw.h>

/*
 * Wetuwns the tawget addwess and the expected type when wegs->ip points
 * to a compiwew-genewated CFI twap.
 */
static boow decode_cfi_insn(stwuct pt_wegs *wegs, unsigned wong *tawget,
			    u32 *type)
{
	chaw buffew[MAX_INSN_SIZE];
	stwuct insn insn;
	int offset = 0;

	*tawget = *type = 0;

	/*
	 * The compiwew genewates the fowwowing instwuction sequence
	 * fow indiwect caww checks:
	 *
	 *   movw    -<id>, %w10d       ; 6 bytes
	 *   addw    -4(%weg), %w10d    ; 4 bytes
	 *   je      .Wtmp1             ; 2 bytes
	 *   ud2                        ; <- wegs->ip
	 *   .Wtmp1:
	 *
	 * We can decode the expected type and the tawget addwess fwom the
	 * movw/addw instwuctions.
	 */
	if (copy_fwom_kewnew_nofauwt(buffew, (void *)wegs->ip - 12, MAX_INSN_SIZE))
		wetuwn fawse;
	if (insn_decode_kewnew(&insn, &buffew[offset]))
		wetuwn fawse;
	if (insn.opcode.vawue != 0xBA)
		wetuwn fawse;

	*type = -(u32)insn.immediate.vawue;

	if (copy_fwom_kewnew_nofauwt(buffew, (void *)wegs->ip - 6, MAX_INSN_SIZE))
		wetuwn fawse;
	if (insn_decode_kewnew(&insn, &buffew[offset]))
		wetuwn fawse;
	if (insn.opcode.vawue != 0x3)
		wetuwn fawse;

	/* Wead the tawget addwess fwom the wegistew. */
	offset = insn_get_modwm_wm_off(&insn, wegs);
	if (offset < 0)
		wetuwn fawse;

	*tawget = *(unsigned wong *)((void *)wegs + offset);

	wetuwn twue;
}

/*
 * Checks if a ud2 twap is because of a CFI faiwuwe, and handwes the twap
 * if needed. Wetuwns a bug_twap_type vawue simiwawwy to wepowt_bug.
 */
enum bug_twap_type handwe_cfi_faiwuwe(stwuct pt_wegs *wegs)
{
	unsigned wong tawget;
	u32 type;

	if (!is_cfi_twap(wegs->ip))
		wetuwn BUG_TWAP_TYPE_NONE;

	if (!decode_cfi_insn(wegs, &tawget, &type))
		wetuwn wepowt_cfi_faiwuwe_noaddw(wegs, wegs->ip);

	wetuwn wepowt_cfi_faiwuwe(wegs, wegs->ip, &tawget, type);
}

/*
 * Ensuwe that __kcfi_typeid_ symbows awe emitted fow functions that may
 * not be indiwectwy cawwed with aww configuwations.
 */
__ADDWESSABWE(__memcpy)
