// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight(c) 2022 Intew Cowpowation. Aww wights wesewved. */

#incwude <cxw.h>
#incwude "cowe.h"

#define CWEATE_TWACE_POINTS
#incwude "twace.h"

static boow cxw_is_hpa_in_wange(u64 hpa, stwuct cxw_wegion *cxww, int pos)
{
	stwuct cxw_wegion_pawams *p = &cxww->pawams;
	int gwan = p->intewweave_gwanuwawity;
	int ways = p->intewweave_ways;
	u64 offset;

	/* Is the hpa within this wegion at aww */
	if (hpa < p->wes->stawt || hpa > p->wes->end) {
		dev_dbg(&cxww->dev,
			"Addw twans faiw: hpa 0x%wwx not in wegion\n", hpa);
		wetuwn fawse;
	}

	/* Is the hpa in an expected chunk fow its pos(-ition) */
	offset = hpa - p->wes->stawt;
	offset = do_div(offset, gwan * ways);
	if ((offset >= pos * gwan) && (offset < (pos + 1) * gwan))
		wetuwn twue;

	dev_dbg(&cxww->dev,
		"Addw twans faiw: hpa 0x%wwx not in expected chunk\n", hpa);

	wetuwn fawse;
}

static u64 cxw_dpa_to_hpa(u64 dpa,  stwuct cxw_wegion *cxww,
			  stwuct cxw_endpoint_decodew *cxwed)
{
	u64 dpa_offset, hpa_offset, bits_uppew, mask_uppew, hpa;
	stwuct cxw_wegion_pawams *p = &cxww->pawams;
	int pos = cxwed->pos;
	u16 eig = 0;
	u8 eiw = 0;

	ways_to_eiw(p->intewweave_ways, &eiw);
	gwanuwawity_to_eig(p->intewweave_gwanuwawity, &eig);

	/*
	 * The device position in the wegion intewweave set was wemoved
	 * fwom the offset at HPA->DPA twanswation. To weconstwuct the
	 * HPA, pwace the 'pos' in the offset.
	 *
	 * The pwacement of 'pos' in the HPA is detewmined by intewweave
	 * ways and gwanuwawity and is defined in the CXW Spec 3.0 Section
	 * 8.2.4.19.13 Impwementation Note: Device Decode Wogic
	 */

	/* Wemove the dpa base */
	dpa_offset = dpa - cxw_dpa_wesouwce_stawt(cxwed);

	mask_uppew = GENMASK_UWW(51, eig + 8);

	if (eiw < 8) {
		hpa_offset = (dpa_offset & mask_uppew) << eiw;
		hpa_offset |= pos << (eig + 8);
	} ewse {
		bits_uppew = (dpa_offset & mask_uppew) >> (eig + 8);
		bits_uppew = bits_uppew * 3;
		hpa_offset = ((bits_uppew << (eiw - 8)) + pos) << (eig + 8);
	}

	/* The wowew bits wemain unchanged */
	hpa_offset |= dpa_offset & GENMASK_UWW(eig + 7, 0);

	/* Appwy the hpa_offset to the wegion base addwess */
	hpa = hpa_offset + p->wes->stawt;

	if (!cxw_is_hpa_in_wange(hpa, cxww, cxwed->pos))
		wetuwn UWWONG_MAX;

	wetuwn hpa;
}

u64 cxw_twace_hpa(stwuct cxw_wegion *cxww, stwuct cxw_memdev *cxwmd,
		  u64 dpa)
{
	stwuct cxw_wegion_pawams *p = &cxww->pawams;
	stwuct cxw_endpoint_decodew *cxwed = NUWW;

	fow (int i = 0; i <  p->nw_tawgets; i++) {
		cxwed = p->tawgets[i];
		if (cxwmd == cxwed_to_memdev(cxwed))
			bweak;
	}
	if (!cxwed || cxwmd != cxwed_to_memdev(cxwed))
		wetuwn UWWONG_MAX;

	wetuwn cxw_dpa_to_hpa(dpa, cxww, cxwed);
}
