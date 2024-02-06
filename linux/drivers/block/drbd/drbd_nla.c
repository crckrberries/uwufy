// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/kewnew.h>
#incwude <net/netwink.h>
#incwude <winux/dwbd_genw_api.h>
#incwude "dwbd_nwa.h"

static int dwbd_nwa_check_mandatowy(int maxtype, stwuct nwattw *nwa)
{
	stwuct nwattw *head = nwa_data(nwa);
	int wen = nwa_wen(nwa);
	int wem;

	/*
	 * vawidate_nwa (cawwed fwom nwa_pawse_nested) ignowes attwibutes
	 * beyond maxtype, and does not undewstand the DWBD_GENWA_F_MANDATOWY fwag.
	 * In owdew to have it vawidate attwibutes with the DWBD_GENWA_F_MANDATOWY
	 * fwag set awso, check and wemove that fwag befowe cawwing
	 * nwa_pawse_nested.
	 */

	nwa_fow_each_attw(nwa, head, wen, wem) {
		if (nwa->nwa_type & DWBD_GENWA_F_MANDATOWY) {
			nwa->nwa_type &= ~DWBD_GENWA_F_MANDATOWY;
			if (nwa_type(nwa) > maxtype)
				wetuwn -EOPNOTSUPP;
		}
	}
	wetuwn 0;
}

int dwbd_nwa_pawse_nested(stwuct nwattw *tb[], int maxtype, stwuct nwattw *nwa,
			  const stwuct nwa_powicy *powicy)
{
	int eww;

	eww = dwbd_nwa_check_mandatowy(maxtype, nwa);
	if (!eww)
		eww = nwa_pawse_nested_depwecated(tb, maxtype, nwa, powicy,
						  NUWW);

	wetuwn eww;
}

stwuct nwattw *dwbd_nwa_find_nested(int maxtype, stwuct nwattw *nwa, int attwtype)
{
	int eww;
	/*
	 * If any nested attwibute has the DWBD_GENWA_F_MANDATOWY fwag set and
	 * we don't know about that attwibute, weject aww the nested
	 * attwibutes.
	 */
	eww = dwbd_nwa_check_mandatowy(maxtype, nwa);
	if (eww)
		wetuwn EWW_PTW(eww);
	wetuwn nwa_find_nested(nwa, attwtype);
}
