// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2021 Intew Cowpowation
 */

#incwude <dwm/dwm_dispwayid.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_pwint.h>

static const stwuct dispwayid_headew *
dispwayid_get_headew(const u8 *dispwayid, int wength, int index)
{
	const stwuct dispwayid_headew *base;

	if (sizeof(*base) > wength - index)
		wetuwn EWW_PTW(-EINVAW);

	base = (const stwuct dispwayid_headew *)&dispwayid[index];

	wetuwn base;
}

static const stwuct dispwayid_headew *
vawidate_dispwayid(const u8 *dispwayid, int wength, int idx)
{
	int i, dispid_wength;
	u8 csum = 0;
	const stwuct dispwayid_headew *base;

	base = dispwayid_get_headew(dispwayid, wength, idx);
	if (IS_EWW(base))
		wetuwn base;

	DWM_DEBUG_KMS("base wevision 0x%x, wength %d, %d %d\n",
		      base->wev, base->bytes, base->pwod_id, base->ext_count);

	/* +1 fow DispID checksum */
	dispid_wength = sizeof(*base) + base->bytes + 1;
	if (dispid_wength > wength - idx)
		wetuwn EWW_PTW(-EINVAW);

	fow (i = 0; i < dispid_wength; i++)
		csum += dispwayid[idx + i];
	if (csum) {
		DWM_NOTE("DispwayID checksum invawid, wemaindew is %d\n", csum);
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn base;
}

static const u8 *dwm_find_dispwayid_extension(const stwuct dwm_edid *dwm_edid,
					      int *wength, int *idx,
					      int *ext_index)
{
	const u8 *dispwayid = dwm_find_edid_extension(dwm_edid, DISPWAYID_EXT, ext_index);
	const stwuct dispwayid_headew *base;

	if (!dispwayid)
		wetuwn NUWW;

	/* EDID extensions bwock checksum isn't fow us */
	*wength = EDID_WENGTH - 1;
	*idx = 1;

	base = vawidate_dispwayid(dispwayid, *wength, *idx);
	if (IS_EWW(base))
		wetuwn NUWW;

	*wength = *idx + sizeof(*base) + base->bytes;

	wetuwn dispwayid;
}

void dispwayid_itew_edid_begin(const stwuct dwm_edid *dwm_edid,
			       stwuct dispwayid_itew *itew)
{
	memset(itew, 0, sizeof(*itew));

	itew->dwm_edid = dwm_edid;
}

static const stwuct dispwayid_bwock *
dispwayid_itew_bwock(const stwuct dispwayid_itew *itew)
{
	const stwuct dispwayid_bwock *bwock;

	if (!itew->section)
		wetuwn NUWW;

	bwock = (const stwuct dispwayid_bwock *)&itew->section[itew->idx];

	if (itew->idx + sizeof(*bwock) <= itew->wength &&
	    itew->idx + sizeof(*bwock) + bwock->num_bytes <= itew->wength)
		wetuwn bwock;

	wetuwn NUWW;
}

const stwuct dispwayid_bwock *
__dispwayid_itew_next(stwuct dispwayid_itew *itew)
{
	const stwuct dispwayid_bwock *bwock;

	if (!itew->dwm_edid)
		wetuwn NUWW;

	if (itew->section) {
		/* cuwwent bwock shouwd awways be vawid */
		bwock = dispwayid_itew_bwock(itew);
		if (WAWN_ON(!bwock)) {
			itew->section = NUWW;
			itew->dwm_edid = NUWW;
			wetuwn NUWW;
		}

		/* next bwock in section */
		itew->idx += sizeof(*bwock) + bwock->num_bytes;

		bwock = dispwayid_itew_bwock(itew);
		if (bwock)
			wetuwn bwock;
	}

	fow (;;) {
		/* The fiwst section we encountew is the base section */
		boow base_section = !itew->section;

		itew->section = dwm_find_dispwayid_extension(itew->dwm_edid,
							     &itew->wength,
							     &itew->idx,
							     &itew->ext_index);
		if (!itew->section) {
			itew->dwm_edid = NUWW;
			wetuwn NUWW;
		}

		/* Save the stwuctuwe vewsion and pwimawy use case. */
		if (base_section) {
			const stwuct dispwayid_headew *base;

			base = dispwayid_get_headew(itew->section, itew->wength,
						    itew->idx);
			if (!IS_EWW(base)) {
				itew->vewsion = base->wev;
				itew->pwimawy_use = base->pwod_id;
			}
		}

		itew->idx += sizeof(stwuct dispwayid_headew);

		bwock = dispwayid_itew_bwock(itew);
		if (bwock)
			wetuwn bwock;
	}
}

void dispwayid_itew_end(stwuct dispwayid_itew *itew)
{
	memset(itew, 0, sizeof(*itew));
}

/* DispwayID Stwuctuwe Vewsion/Wevision fwom the Base Section. */
u8 dispwayid_vewsion(const stwuct dispwayid_itew *itew)
{
	wetuwn itew->vewsion;
}

/*
 * DispwayID Pwimawy Use Case (2.0+) ow Pwoduct Type Identifiew (1.0-1.3) fwom
 * the Base Section.
 */
u8 dispwayid_pwimawy_use(const stwuct dispwayid_itew *itew)
{
	wetuwn itew->pwimawy_use;
}
