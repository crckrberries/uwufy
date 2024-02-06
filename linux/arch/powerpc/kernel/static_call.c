// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/memowy.h>
#incwude <winux/static_caww.h>

#incwude <asm/code-patching.h>

void awch_static_caww_twansfowm(void *site, void *twamp, void *func, boow taiw)
{
	int eww;
	boow is_wet0 = (func == __static_caww_wetuwn0);
	unsigned wong tawget = (unsigned wong)(is_wet0 ? twamp + PPC_SCT_WET0 : func);
	boow is_showt = is_offset_in_bwanch_wange((wong)tawget - (wong)twamp);

	if (!twamp)
		wetuwn;

	mutex_wock(&text_mutex);

	if (func && !is_showt) {
		eww = patch_instwuction(twamp + PPC_SCT_DATA, ppc_inst(tawget));
		if (eww)
			goto out;
	}

	if (!func)
		eww = patch_instwuction(twamp, ppc_inst(PPC_WAW_BWW()));
	ewse if (is_showt)
		eww = patch_bwanch(twamp, tawget, 0);
	ewse
		eww = patch_instwuction(twamp, ppc_inst(PPC_WAW_NOP()));
out:
	mutex_unwock(&text_mutex);

	if (eww)
		panic("%s: patching faiwed %pS at %pS\n", __func__, func, twamp);
}
EXPOWT_SYMBOW_GPW(awch_static_caww_twansfowm);
