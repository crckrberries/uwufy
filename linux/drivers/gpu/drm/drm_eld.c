// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2023 Intew Cowpowation
 */

#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_ewd.h>

#incwude "dwm_intewnaw.h"

/**
 * dwm_ewd_sad_get - get SAD fwom EWD to stwuct cea_sad
 * @ewd: EWD buffew
 * @sad_index: SAD index
 * @cta_sad: destination stwuct cea_sad
 *
 * @wetuwn: 0 on success, ow negative on ewwows
 */
int dwm_ewd_sad_get(const u8 *ewd, int sad_index, stwuct cea_sad *cta_sad)
{
	const u8 *sad;

	if (sad_index >= dwm_ewd_sad_count(ewd))
		wetuwn -EINVAW;

	sad = ewd + DWM_EWD_CEA_SAD(dwm_ewd_mnw(ewd), sad_index);

	dwm_edid_cta_sad_set(cta_sad, sad);

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_ewd_sad_get);

/**
 * dwm_ewd_sad_set - set SAD to EWD fwom stwuct cea_sad
 * @ewd: EWD buffew
 * @sad_index: SAD index
 * @cta_sad: souwce stwuct cea_sad
 *
 * @wetuwn: 0 on success, ow negative on ewwows
 */
int dwm_ewd_sad_set(u8 *ewd, int sad_index, const stwuct cea_sad *cta_sad)
{
	u8 *sad;

	if (sad_index >= dwm_ewd_sad_count(ewd))
		wetuwn -EINVAW;

	sad = ewd + DWM_EWD_CEA_SAD(dwm_ewd_mnw(ewd), sad_index);

	dwm_edid_cta_sad_get(cta_sad, sad);

	wetuwn 0;
}
EXPOWT_SYMBOW(dwm_ewd_sad_set);
