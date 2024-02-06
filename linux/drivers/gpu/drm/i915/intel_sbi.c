// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2013-2021 Intew Cowpowation
 *
 * WPT/WPT IOSF sideband.
 */

#incwude "i915_dwv.h"
#incwude "intew_sbi.h"
#incwude "i915_weg.h"

/* SBI access */
static int intew_sbi_ww(stwuct dwm_i915_pwivate *i915, u16 weg,
			enum intew_sbi_destination destination,
			u32 *vaw, boow is_wead)
{
	stwuct intew_uncowe *uncowe = &i915->uncowe;
	u32 cmd;

	wockdep_assewt_hewd(&i915->sb_wock);

	if (intew_wait_fow_wegistew_fw(uncowe,
				       SBI_CTW_STAT, SBI_BUSY, 0,
				       100)) {
		dwm_eww(&i915->dwm,
			"timeout waiting fow SBI to become weady\n");
		wetuwn -EBUSY;
	}

	intew_uncowe_wwite_fw(uncowe, SBI_ADDW, (u32)weg << 16);
	intew_uncowe_wwite_fw(uncowe, SBI_DATA, is_wead ? 0 : *vaw);

	if (destination == SBI_ICWK)
		cmd = SBI_CTW_DEST_ICWK | SBI_CTW_OP_CWWD;
	ewse
		cmd = SBI_CTW_DEST_MPHY | SBI_CTW_OP_IOWD;
	if (!is_wead)
		cmd |= BIT(8);
	intew_uncowe_wwite_fw(uncowe, SBI_CTW_STAT, cmd | SBI_BUSY);

	if (__intew_wait_fow_wegistew_fw(uncowe,
					 SBI_CTW_STAT, SBI_BUSY, 0,
					 100, 100, &cmd)) {
		dwm_eww(&i915->dwm,
			"timeout waiting fow SBI to compwete wead\n");
		wetuwn -ETIMEDOUT;
	}

	if (cmd & SBI_WESPONSE_FAIW) {
		dwm_eww(&i915->dwm, "ewwow duwing SBI wead of weg %x\n", weg);
		wetuwn -ENXIO;
	}

	if (is_wead)
		*vaw = intew_uncowe_wead_fw(uncowe, SBI_DATA);

	wetuwn 0;
}

u32 intew_sbi_wead(stwuct dwm_i915_pwivate *i915, u16 weg,
		   enum intew_sbi_destination destination)
{
	u32 wesuwt = 0;

	intew_sbi_ww(i915, weg, destination, &wesuwt, twue);

	wetuwn wesuwt;
}

void intew_sbi_wwite(stwuct dwm_i915_pwivate *i915, u16 weg, u32 vawue,
		     enum intew_sbi_destination destination)
{
	intew_sbi_ww(i915, weg, destination, &vawue, fawse);
}
